cmake_minimum_required(VERSION 3.14.0)
include(FetchContent)

set(PROJECT studiobridgeexample)
project(${PROJECT})

add_compile_definitions(_DEBUG)
add_compile_definitions(VERSION="0.1.0")

# Make sure boost is available
if(NOT DEFINED BOOST_SDK)
	set(BOOST_SDK ${PROJECT_SOURCE_DIR}/vendor/boost)
	FetchContent_Declare(
		boost
		URL "https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz"
		SOURCE_DIR ${BOOST_SDK}
	)
	FetchContent_MakeAvailable(boost)
endif()

# Make sure studiobridge is available
if(NOT DEFINED STUDIO_BRIDGE_SDK)
	set(STUDIO_BRIDGE_SDK ${PROJECT_SOURCE_DIR}/vendor/studiobridge)
	FetchContent_Declare(
		studiobridge
		URL "https://github.com/getstudiobridge/studiobridge/releases/download/1.0.0/studiobridge-macos-1.0.0.zip"
		SOURCE_DIR ${STUDIO_BRIDGE_SDK}
	)
	FetchContent_MakeAvailable(studiobridge)
endif()
include(${STUDIO_BRIDGE_SDK}/hack/studiobridge.cmake)

# Load VST SDK
set(VST_SDK ${STUDIO_BRIDGE_SDK}/vendor/vst3sdk)
set(SMTG_VSTGUI_ROOT ${VST_SDK})
add_subdirectory(${VST_SDK} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()



# Create VST
smtg_add_vst3plugin(${PROJECT}
	src/entry.cpp
	src/processor/Processor.cpp
)

add_studio_bridge(${PROJECT})
smtg_add_vst3_snapshot(${PROJECT} resource/7C41BB75B556527392439BEADC67B477_snapshot.png)
smtg_add_vst3_snapshot(${PROJECT} resource/7C41BB75B556527392439BEADC67B477_snapshot_2.0x.png)

target_compile_options(${PROJECT} PUBLIC -std=c++11)
target_link_libraries(${PROJECT} PRIVATE sdk)
target_include_directories(
	${PROJECT} PUBLIC
	${VST_SDK}
	${PROJECT_SOURCE_DIR}/src
)

if (APPLE)
	smtg_set_bundle(${PROJECT}
		BUNDLE_IDENTIFIER com.achaloin.${PROJECT}
		INFOPLIST "resource/Info.plist" PREPROCESS
	)
endif()
