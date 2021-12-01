#pragma once

#include <public.sdk/source/vst/vstaudioeffect.h>

class Processor : public Steinberg::Vst::AudioEffect {
public:
  Processor();
  ~Processor() SMTG_OVERRIDE;

  Steinberg::tresult initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
  Steinberg::tresult terminate() SMTG_OVERRIDE;
  Steinberg::tresult setActive(Steinberg::TBool state) SMTG_OVERRIDE;
  Steinberg::tresult setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
  Steinberg::tresult canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;
  Steinberg::tresult process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
  Steinberg::tresult setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
  Steinberg::tresult getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

  static Steinberg::FUnknown* createInstance(void* context);

private:
  float gain = 1;
};
