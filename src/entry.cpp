#include <public.sdk/source/main/pluginfactory.h>
#include <sidechain/vst/Controller.hpp>

#include "info.hpp"
#include "processor/Processor.hpp"
#include "schemas/Parameter.hpp"
#include "schemas/ProcessorState.hpp"
#include "schemas/State.hpp"

Sidechain::Configuration Sidechain::Configuration::Shared = {
    .name = NAME,
    .vendorName = VENDOR,
    .projectID = "projectID",
#ifdef _DEBUG
    .development = true,
    .enableSocketBridge = true,
#else
    .development = false,
    .enableSocketBridge = false,
#endif
};

using Controller = Sidechain::VST::Controller<Schema::ParametersConfig, Schema::State, Schema::ProcessorState>;

BEGIN_FACTORY_DEF(VENDOR, WEBSITE, EMAIL)

DEF_CLASS2(INLINE_UID_FROM_FUID(::ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass, NAME,
           Vst::kDistributable, CATEGORY, VERSION, kVstVersionString, Processor::Create)

DEF_CLASS2(INLINE_UID_FROM_FUID(::ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
           NAME "Controller", 0, "", VERSION, kVstVersionString, Controller::Create)

END_FACTORY
