cmake_minimum_required(VERSION 3.14.0)
include(FetchContent)

set(PROJECT StudioBridgeExample)
project(${PROJECT})

add_compile_definitions(_DEBUG)
add_compile_definitions(VERSION="0.1.0")

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

# Make sure VST SDK is available
if(NOT DEFINED VST_SDK)
	set(VST_SDK ${PROJECT_BINARY_DIR}/vendor/vst3sdk)
	FetchContent_Declare(
		vstsdk
		GIT_REPOSITORY "git@github.com:steinbergmedia/vst3sdk"
		GIT_TAG 2cc517019a2681fccf211e6a95776a0af1e16d04 # release 3.7.3
		SOURCE_DIR ${VST_SDK}
	)
	FetchContent_MakeAvailable(vstsdk)
endif()

# Make sure Studio Bridge is available
# TODO: abstract platform
if(NOT DEFINED STUDIO_BRIDGE_SDK)
	set(STUDIO_BRIDGE_VERSION 1.0.0)
	set(STUDIO_BRIDGE_SDK ${PROJECT_BINARY_DIR}/vendor/studiobridge)
	FetchContent_Declare(
		studiobridge
		URL "https://github.com/getstudiobridge/studiobridge/releases/download/${STUDIO_BRIDGE_VERSION}/studiobridge-macos-${STUDIO_BRIDGE_VERSION}.zip"
		SOURCE_DIR ${STUDIO_BRIDGE_SDK}
	)
	FetchContent_MakeAvailable(studiobridge)
endif()

# Load VST SDK
set(SMTG_VSTGUI_ROOT ${VST_SDK})
smtg_enable_vst3_sdk()

# Create VST
smtg_add_vst3plugin(${PROJECT}
	src/entry.cpp
	src/processor/Processor.cpp
)

# Load Studio Bridge
include(${STUDIO_BRIDGE_SDK}/hack/studiobridge.cmake)
add_studio_bridge(${PROJECT})

# Snapshot name matters
smtg_add_vst3_snapshot(${PROJECT} public/7C41BB75B556527392439BEADC67B477_snapshot.png)
smtg_add_vst3_snapshot(${PROJECT} public/7C41BB75B556527392439BEADC67B477_snapshot_2.0x.png)

# Compilation settings
target_compile_options(${PROJECT} PUBLIC -std=c++11)
target_link_libraries(${PROJECT} PRIVATE sdk)
target_include_directories(
	${PROJECT} PUBLIC
	${VST_SDK}
	${PROJECT_SOURCE_DIR}/src
)

# Platform specifics
if (APPLE)
	smtg_set_bundle(${PROJECT}
		BUNDLE_IDENTIFIER com.studiobridge.${PROJECT}
		INFOPLIST "public/Info.plist" PREPROCESS
	)
endif()
