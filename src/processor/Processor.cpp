#include <base/source/fstreamer.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>

#include "Processor.hpp"
#include "info.h"

StudioBridgeExampleProcessor::StudioBridgeExampleProcessor() {
  setControllerClass(ControllerUID);
}

StudioBridgeExampleProcessor::~StudioBridgeExampleProcessor() {}

Steinberg::tresult StudioBridgeExampleProcessor::initialize(FUnknown* context) {
  Steinberg::tresult result = AudioEffect::initialize(context);
  if (result != Steinberg::kResultOk) {
    return result;
  }

  addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
  addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
  // addEventInput(STR16("Event In"), 1);

  return Steinberg::kResultOk;
}

Steinberg::tresult StudioBridgeExampleProcessor::terminate() {
  return AudioEffect::terminate();
}

Steinberg::tresult StudioBridgeExampleProcessor::setActive(Steinberg::TBool state) {
  return AudioEffect::setActive(state);
}

Steinberg::tresult StudioBridgeExampleProcessor::process(Steinberg::Vst::ProcessData& data) {
  if (data.inputParameterChanges) {
    Steinberg::int32 paramsChangedCount = data.inputParameterChanges->getParameterCount();
    for (Steinberg::int32 index = 0; index < paramsChangedCount; index++) {
      Steinberg::Vst::IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
      if (!paramQueue) {
        continue;
      }

      Steinberg::int32 sampleOffset;
      Steinberg::Vst::ParamValue value;
      auto result = paramQueue->getPoint(paramQueue->getPointCount() - 1, sampleOffset, value);
      if (result != Steinberg::kResultOk) {
        continue;
      }

      switch (paramQueue->getParameterId()) {
      case 42:
        this->gain = value;
        break;
      }
    }
  }

  if (data.numInputs == 0 || data.numSamples == 0) {
    return Steinberg::kResultOk;
  }

  Steinberg::int32 numChannels = data.inputs[0].numChannels;
  Steinberg::uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
  void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
  void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);
  data.outputs[0].silenceFlags = 0;

  for (Steinberg::int32 i = 0; i < numChannels; i++) {
    Steinberg::int32 samples = data.numSamples;
    Steinberg::Vst::Sample32* ptrIn = (Steinberg::Vst::Sample32*)in[i];
    Steinberg::Vst::Sample32* ptrOut = (Steinberg::Vst::Sample32*)out[i];
    Steinberg::Vst::Sample32 tmp;

    for (Steinberg::int32 j = 0; j < samples; j++) {
      ptrOut[j] = ptrIn[j] * this->gain;
    }
  }

  return Steinberg::kResultOk;
}

Steinberg::tresult StudioBridgeExampleProcessor::setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) {
  return AudioEffect::setupProcessing(newSetup);
}

Steinberg::tresult StudioBridgeExampleProcessor::canProcessSampleSize(Steinberg::int32 symbolicSampleSize) {
  if (symbolicSampleSize == Steinberg::Vst::kSample32) {
    return Steinberg::kResultTrue;
  }

  // if (symbolicSampleSize == Vst::kSample64) {
  // 	return kResultTrue;
  // }

  return Steinberg::kResultFalse;
}

Steinberg::tresult StudioBridgeExampleProcessor::setState(Steinberg::IBStream* state) {
  Steinberg::IBStreamer streamer(state, kLittleEndian);
  return Steinberg::kResultOk;
}

Steinberg::tresult StudioBridgeExampleProcessor::getState(Steinberg::IBStream* state) {
  Steinberg::IBStreamer streamer(state, kLittleEndian);
  return Steinberg::kResultOk;
}

Steinberg::FUnknown* StudioBridgeExampleProcessor::createInstance(void* context) {
  return (Steinberg::Vst::IAudioProcessor*)new StudioBridgeExampleProcessor;
}
