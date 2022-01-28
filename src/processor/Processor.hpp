#pragma once

#include <sidechain/vst/Processor.hpp>

#include "schemas/ProcessorState.hpp"

class Processor : public SB::VST::Processor<Schema::ProcessorState> {
public:
  Processor();

  Steinberg::tresult initialize(Steinberg::FUnknown* context) override;
  Steinberg::tresult setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) override;
  Steinberg::tresult process(Steinberg::Vst::ProcessData& data) override;
  Steinberg::tresult canProcessSampleSize(Steinberg::int32 symbolicSampleSize) override;
  Steinberg::tresult setActive(Steinberg::TBool state) override;
  Steinberg::tresult terminate() override;

  static Steinberg::FUnknown* createInstance(void* context);

private:
  float gain = 1;
};
