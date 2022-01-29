#include <public.sdk/source/main/pluginfactory.h>
#include <sidechain/utility/Configuration.hpp>
#include <sidechain/vst/Controller.hpp>

#include "info.hpp"
#include "processor/Processor.hpp"
#include "schemas/Parameter.hpp"
#include "schemas/ProcessorState.hpp"
#include "schemas/State.hpp"

#ifdef _DEBUG
Sidechain::Configuration Sidechain::Configuration::Shared = {
    .development = true,
    .enableSocketBridge = true,
};
#else
Sidechain::Configuration Sidechain::Configuration::Shared = {
    .development = false,
    .enableSocketBridge = false,
};
#endif

using Controller = Sidechain::VST::Controller<Schema::ParametersConfig, Schema::State, Schema::ProcessorState>;

BEGIN_FACTORY_DEF(VENDOR, WEBSITE, EMAIL)

DEF_CLASS2(INLINE_UID_FROM_FUID(::ProcessorUID), PClassInfo::kManyInstances, kVstAudioEffectClass, NAME,
           Vst::kDistributable, CATEGORY, VERSION, kVstVersionString, Processor::createInstance)

DEF_CLASS2(INLINE_UID_FROM_FUID(::ControllerUID), PClassInfo::kManyInstances, kVstComponentControllerClass,
           NAME "Controller", 0, "", VERSION, kVstVersionString, Controller::createInstance)

END_FACTORY
