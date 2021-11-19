#include <public.sdk/source/main/pluginfactory.h>
#include <studiobridge/vst/Controller.hpp>

#include "info.h"
#include "processor/Processor.hpp"

BEGIN_FACTORY_DEF(VENDOR, WEBSITE, EMAIL)

DEF_CLASS2(INLINE_UID_FROM_FUID(ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass, NAME,
           Vst::kDistributable, CATEGORY, VERSION, kVstVersionString, StudioBridgeExampleProcessor::createInstance)

DEF_CLASS2(INLINE_UID_FROM_FUID(ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
           NAME "Controller", 0, "", VERSION, kVstVersionString, SB::VST::Controller::createInstance)

END_FACTORY
