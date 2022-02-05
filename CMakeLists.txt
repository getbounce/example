cmake_minimum_required(VERSION 3.14.0)
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(PROJECT SidechainExample)
project(${PROJECT})
add_compile_definitions(VERSION="0.1.0")

# CMAKE_BUILD_TYPE must be defined at configuration time
# or the project won't build
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
	add_compile_definitions(_DEBUG)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_compile_definitions(RELEASE)
endif()

# Make sure boost is available
if(NOT DEFINED BOOST_SDK)
	set(BOOST_SDK ${PROJECT_BINARY_DIR}/vendor/boost)
	FetchContent_Declare(
		boost
		URL "https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz"
		SOURCE_DIR ${BOOST_SDK}
	)
	FetchContent_MakeAvailable(boost)
endif()

# Make sure Sidechain is available
# TODO: abstract platform
if(NOT DEFINED SIDECHAIN_SDK)
	set(SIDECHAIN_VERSION 1.0.0)
	set(SIDECHAIN_SDK ${PROJECT_BINARY_DIR}/vendor/sidechain)
	FetchContent_Declare(
		sidechain
		URL "https://github.com/getsidechain/sidechain/releases/download/${SIDECHAIN_VERSION}/sidechain-${SIDECHAIN_VERSION}-mac.zip"
		SOURCE_DIR ${SIDECHAIN_SDK}
	)
	FetchContent_MakeAvailable(sidechain)
endif()

# Load VST SDK
if (NOT DEFINED VST_SDK)
	set(VST_SDK ${PROJECT_SOURCE_DIR}/vendor/vst3sdk)
	add_subdirectory(${VST_SDK})
endif()
smtg_enable_vst3_sdk()

# Create VST
smtg_add_vst3plugin(${PROJECT}
	src/entry.cpp
	src/processor/Processor.cpp
)

# Load Sidechain
include(${SIDECHAIN_SDK}/hack/sidechain.cmake)
add_sidechain(${PROJECT})

# Snapshot name matters
smtg_add_vst3_snapshot(${PROJECT} public/7C41BB75B556527392439BEADC67B477_snapshot.png)
smtg_add_vst3_snapshot(${PROJECT} public/7C41BB75B556527392439BEADC67B477_snapshot_2.0x.png)

# Compilation settings
target_compile_features(${PROJECT} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT} PRIVATE sdk)
target_include_directories(
	${PROJECT} PRIVATE
	${BOOST_SDK}
	${VST_SDK}
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/vendor/json/include
)

# Generate schemas from TypeScript before compilation
add_custom_target(
	generateSchemas
	COMMAND
		mkdir -p ${PROJECT_SOURCE_DIR}/src/schemas &&
		sidechain generate schema -o ${PROJECT_SOURCE_DIR}/src/schemas ${PROJECT_SOURCE_DIR}/src/controller/State.ts ${PROJECT_SOURCE_DIR}/src/processor/ProcessorState.ts &&
		sidechain generate parameters -o ${PROJECT_SOURCE_DIR}/src/schemas ${PROJECT_SOURCE_DIR}/src/config/parameters.js
)
add_dependencies(${PROJECT} generateSchemas)

# Platform specifics
if (APPLE)
	set (RESOURCES_PATH ../Resources)
	smtg_set_bundle(${PROJECT}
		BUNDLE_IDENTIFIER com.sidechain.${PROJECT}
		INFOPLIST "public/Info.plist" PREPROCESS
	)
endif()

# Copy HTML bundle if needed
if (EXISTS ${PROJECT_SOURCE_DIR}/build/ui)
	add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND
		${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/build/ui $<TARGET_FILE_DIR:${PROJECT}>/${RESOURCES_PATH}/UI)
endif()

# Copy license if needed
if (EXISTS ${PROJECT_SOURCE_DIR}/license.pem)
	add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND
		${CMAKE_COMMAND} -E copy
		${PROJECT_SOURCE_DIR}/license.pem $<TARGET_FILE_DIR:${PROJECT}>/${HTML_BUNDLE_PATH}/${RESOURCES_PATH})
endif()
