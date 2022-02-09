#pragma once

#include <sidechain/vst/Processor.hpp>

#include "schemas/ProcessorState.hpp"

class Processor : public Sidechain::VST::Processor<Schema::ProcessorState> {
public:
  Processor();

  Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) override;
  Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) override;
  Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) override;
  Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) override;
  Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) override;
  Steinberg::tresult PLUGIN_API terminate() override;

  static Steinberg::FUnknown* Create(void* context);

private:
  float gain = 1;
};
