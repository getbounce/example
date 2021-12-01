#include <public.sdk/source/main/pluginfactory.h>
#include <studiobridge/vst/Controller.hpp>

#include "info.h"
#include "processor/Processor.hpp"
#include "schemas/Parameter.hpp"
#include "schemas/ProcessorState.hpp"
#include "schemas/State.hpp"

using Controller = SB::VST::Controller<Schema::ParametersConfig, Schema::State, Schema::ProcessorState>;

BEGIN_FACTORY_DEF(VENDOR, WEBSITE, EMAIL)

DEF_CLASS2(INLINE_UID_FROM_FUID(ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass, NAME,
           Vst::kDistributable, CATEGORY, VERSION, kVstVersionString, Processor::createInstance)

DEF_CLASS2(INLINE_UID_FROM_FUID(ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
           NAME "Controller", 0, "", VERSION, kVstVersionString, Controller::createInstance)

END_FACTORY
