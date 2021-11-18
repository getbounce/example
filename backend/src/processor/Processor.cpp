#include <base/source/fstreamer.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>

#include "Processor.h"
#include "cids.h"
#include "version.h"

using namespace Steinberg;

StudioBridgeExampleProcessor::StudioBridgeExampleProcessor() {
  setControllerClass(kStudioBridgeExampleControllerUID);
}

StudioBridgeExampleProcessor::~StudioBridgeExampleProcessor() {}

tresult StudioBridgeExampleProcessor::initialize(FUnknown* context) {
  tresult result = AudioEffect::initialize(context);
  if (result != kResultOk) {
    return result;
  }

  addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
  addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
  // addEventInput(STR16("Event In"), 1);

  return kResultOk;
}

tresult StudioBridgeExampleProcessor::terminate() {
  return AudioEffect::terminate();
}

tresult StudioBridgeExampleProcessor::setActive(TBool state) {
  return AudioEffect::setActive(state);
}

tresult StudioBridgeExampleProcessor::process(Vst::ProcessData& data) {
  if (data.inputParameterChanges) {
    int32 paramsChangedCount = data.inputParameterChanges->getParameterCount();
    for (int32 index = 0; index < paramsChangedCount; index++) {
      Vst::IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
      if (!paramQueue) {
        continue;
      }

      int32 sampleOffset;
      Vst::ParamValue value;
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
    return kResultOk;
  }

  int32 numChannels = data.inputs[0].numChannels;
  uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
  void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
  void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);
  data.outputs[0].silenceFlags = 0;

  for (int32 i = 0; i < numChannels; i++) {
    int32 samples = data.numSamples;
    Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
    Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
    Vst::Sample32 tmp;

    for (int32 j = 0; j < samples; j++) {
      ptrOut[j] = ptrIn[j] * this->gain;
    }
  }

  return kResultOk;
}

tresult StudioBridgeExampleProcessor::setupProcessing(Vst::ProcessSetup& newSetup) {
  return AudioEffect::setupProcessing(newSetup);
}

tresult StudioBridgeExampleProcessor::canProcessSampleSize(int32 symbolicSampleSize) {
  if (symbolicSampleSize == Vst::kSample32) {
    return kResultTrue;
  }

  // if (symbolicSampleSize == Vst::kSample64) {
  // 	return kResultTrue;
  // }

  return kResultFalse;
}

tresult StudioBridgeExampleProcessor::setState(IBStream* state) {
  IBStreamer streamer(state, kLittleEndian);
  return kResultOk;
}

tresult StudioBridgeExampleProcessor::getState(IBStream* state) {
  IBStreamer streamer(state, kLittleEndian);
  return kResultOk;
}

Steinberg::FUnknown* StudioBridgeExampleProcessor::createInstance(void* context) {
  return (Steinberg::Vst::IAudioProcessor*)new StudioBridgeExampleProcessor;
}
