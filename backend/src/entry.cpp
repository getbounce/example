#include <public.sdk/source/main/pluginfactory.h>
#include <studiobridge/vst/Controller.hpp>

#include "cids.h"
#include "processor/Processor.h"
#include "version.h"

#define stringPluginName "StudioBridgeExample"

using namespace Steinberg::Vst;

BEGIN_FACTORY_DEF("", "", "mailto:")

DEF_CLASS2(INLINE_UID_FROM_FUID(kStudioBridgeExampleProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass,
           stringPluginName, Vst::kDistributable, StudioBridgeExampleVST3Category, FULL_VERSION_STR, kVstVersionString,
           StudioBridgeExampleProcessor::createInstance)

DEF_CLASS2(INLINE_UID_FROM_FUID(kStudioBridgeExampleControllerUID), PClassInfo::kManyInstances,
           kVstComponentControllerClass, stringPluginName "Controller", 0, "", FULL_VERSION_STR, kVstVersionString,
           SB::VST::Controller::createInstance)

END_FACTORY
