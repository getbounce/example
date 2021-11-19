cmake_minimum_required(VERSION 3.14.0)

set(PROJECT studiobridgeexample)

project(${PROJECT})
add_compile_definitions(_DEBUG)

set(STUDIO_BRIDGE_SDK ${PROJECT_SOURCE_DIR}/../..)
set(VST_SDK ${STUDIO_BRIDGE_SDK}/vendor/vst3sdk)

set(SMTG_VSTGUI_ROOT ${VST_SDK})
add_subdirectory(${VST_SDK} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(${PROJECT}
	src/entry.cpp
	src/processor/Processor.cpp
)

smtg_add_vst3_snapshot(${PROJECT} resource/7C41BB75B556527392439BEADC67B477_snapshot.png)
smtg_add_vst3_snapshot(${PROJECT} resource/7C41BB75B556527392439BEADC67B477_snapshot_2.0x.png)

include(${STUDIO_BRIDGE_SDK}/hack/studiobridge.cmake)
add_studio_bridge(${PROJECT})

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
