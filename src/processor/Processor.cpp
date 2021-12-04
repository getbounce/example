#include <base/source/fstreamer.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>

#include "Processor.hpp"
#include "info.hpp"
#include "schemas/Parameter.hpp"

Processor::Processor() {
  this->setControllerClass(ControllerUID);
}

Steinberg::tresult Processor::initialize(FUnknown* context) {
  if (AudioEffect::initialize(context) != Steinberg::kResultOk) {
    return Steinberg::kResultFalse;
  }

  this->addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
  this->addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
  this->addEventInput(STR16("Event In"), 1);

  return Steinberg::kResultOk;
}

Steinberg::tresult Processor::setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) {
  return AudioEffect::setupProcessing(newSetup);
}

Steinberg::tresult Processor::process(Steinberg::Vst::ProcessData& data) {
  if (data.inputParameterChanges) {

    // For each changed parameter
    auto changedParametersCount = data.inputParameterChanges->getParameterCount();
    for (auto index = 0; index < changedParametersCount; index++) {

      // Retreive change queue
      auto parameterQueue = data.inputParameterChanges->getParameterData(index);
      if (!parameterQueue) {
        continue;
      }

      // Retreive lastest change in queue
      Steinberg::int32 sampleOffset;
      Steinberg::Vst::ParamValue value;
      auto result = parameterQueue->getPoint(parameterQueue->getPointCount() - 1, sampleOffset, value);
      if (result != Steinberg::kResultOk) {
        continue;
      }

      // Find out which parameter it is
      // by comparing its id against
      // the `Parameter` enum
      switch (parameterQueue->getParameterId()) {
      case Parameter::GAIN:
        this->gain = value;
        break;
      }
    }
  }

  // Host may call `process` with no inputs to update parameters
  if (data.numInputs == 0 || data.numSamples == 0) {
    return Steinberg::kResultOk;
  }

  // Using a single input and single output
  // In theory we should iterate and multiplex
  auto input = data.inputs[0];
  auto output = data.outputs[0];
  auto inputChannels = getChannelBuffersPointer(this->processSetup, input);
  auto outputChannels = getChannelBuffersPointer(this->processSetup, output);

  // For each channel (left and right)
  for (auto channelIndex = 0; channelIndex < input.numChannels; channelIndex++) {
    auto inputSamples = static_cast<Steinberg::Vst::Sample32*>(inputChannels[channelIndex]);
    auto outputSamples = static_cast<Steinberg::Vst::Sample32*>(outputChannels[channelIndex]);

    // For each sample
    for (auto sampleIndex = 0; sampleIndex < data.numSamples; sampleIndex++) {
      // Copying input to output will forward sound with no change
      // By multiplying everything we can control the volume
      outputSamples[sampleIndex] = inputSamples[sampleIndex] * this->gain;
    }
  }

  // Indicate host output is not silent
  // In VST3 we have to manage the silence feature manually
  output.silenceFlags = 0;
  return Steinberg::kResultOk;
}

Steinberg::tresult Processor::setActive(Steinberg::TBool state) {
  return AudioEffect::setActive(state);
}

Steinberg::tresult Processor::canProcessSampleSize(Steinberg::int32 symbolicSampleSize) {
  if (symbolicSampleSize == Steinberg::Vst::kSample32) {
    return Steinberg::kResultTrue;
  }

  // if (symbolicSampleSize == Vst::kSample64) {
  // 	return kResultTrue;
  // }

  return Steinberg::kResultFalse;
}

Steinberg::tresult Processor::terminate() {
  return AudioEffect::terminate();
}

Steinberg::FUnknown* Processor::createInstance(void* context) {
  return (Steinberg::Vst::IAudioProcessor*)new Processor();
}
