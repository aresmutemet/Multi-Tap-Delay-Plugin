//------------------------------------------------------------------------
// Copyright(c) 2023 Ares Mutemet.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
#include "ringBuffer.h"
#include <algorithm>

using namespace Steinberg;

namespace aresmutemet {
//------------------------------------------------------------------------
// MultitapperProcessor
//------------------------------------------------------------------------
MultitapperProcessor::MultitapperProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kMultitapperControllerUID);
}

//------------------------------------------------------------------------
MultitapperProcessor::~MultitapperProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
    Steinberg::Vst::SpeakerArrangement arr;
    if (getBusArrangement (Steinberg::Vst::kOutput, 0, arr) != kResultTrue)
        return kResultFalse ;
    int numChannels = Steinberg::Vst::SpeakerArr :: getChannelCount (arr );
    double sampleRate = processSetup.sampleRate;
    ringSample = sampleRate;
    
    if(state)
    {
        ringVector.clear();
        for (int i = 0; i < numChannels; i++)
        {
            ringVector.push_back(ringBuffer(sampleRate * 2)); // Consider the maximum delay time for each tap
        }
    }
    
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::process (Vst::ProcessData& data)
{
    
	//--- First : Read inputs parameter changes----------
    if (data.inputParameterChanges) {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
        for (int32 index = 0; index < numParamsChanged; index++) {
            Vst::IParamValueQueue* paramQueue = data.inputParameterChanges->getParameterData(index);
            if (paramQueue) {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount();
                switch (paramQueue->getParameterId()) {
                        
                    case MultiTapParams::kMixId:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            mix = value;
                        }
                        break;
                        
                        
                    case MultiTapParams::kDelay1Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            delay1 = value;
                        }
                        break;
                    case MultiTapParams::kGain1Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            gain1 = value;
                        }
                        break;
                    case MultiTapParams::kFeedback1Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            feedback1 = value;
                        }
                        
                        
                        break;
                    case MultiTapParams::kDelay2Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            delay2 = value;
                        }
                        break;
                    case MultiTapParams::kGain2Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            gain2 = value;
                        }
                        break;
                    case MultiTapParams::kFeedback2Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            feedback2 = value;
                        }
                        break;
                        
                        
                    case MultiTapParams::kDelay3Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            delay3 = value;
                        }
                        break;
                    case MultiTapParams::kGain3Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            gain3 = value;
                        }
                        break;
                    case MultiTapParams::kFeedback3Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            feedback3 = value;
                        }
                        break;
                        
                        
                    case MultiTapParams::kDelay4Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            delay4 = value;
                        }
                        break;
                    case MultiTapParams::kGain4Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            gain4 = value;
                        }
                        break;
                    case MultiTapParams::kFeedback4Id:
                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                            feedback4 = value;
                        }
                        break;
                }
            }
        }
    }
    
	//--- Here you have to implement your processing
    
    if (data.numInputs == 0 || data.numSamples == 0)
        return kResultOk;
    
    
    int32 numChannels = data.inputs[0].numChannels;
    uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
    void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
    void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);
    
    data.outputs[0].silenceFlags = 0;
    
    // Declare dry part of mix value
    double dry = (1.0 - mix);
    
    // Declare wet part of mix value
    double wet = mix;
    
    // Declare gain limiter
    double gainLimitter = 1.0 - wet * 0.5;
    
    
    // Do process for each channel
    for (int32 i = 0; i < numChannels; i++) {
        
        // Take samples from input audio
        int32 samples = data.numSamples;
        Vst::Sample32* ptrIn = (Vst::Sample32*)in[0];
        Vst::Sample32* ptrOut = (Vst::Sample32*)out[0];
        Vst::Sample32 outputAudio;
        
        while (--samples >= 0) {
            
            // Pointer to inputAudio
            double inputAudio = (*ptrIn++);
            
            // ringdelay is the minumum delay for one sample
            const double ringDelay = 1.0 / ringSample;
            
            // Declare delay times to process for each tap
            double time1 = std::max(static_cast<double>(delay1), ringDelay);
            double time2 = std::max(static_cast<double>(delay1 * delay2), ringDelay);
            double time3 = std::max(static_cast<double>(delay1 * delay3), ringDelay);
            double time4 = std::max(static_cast<double>(delay1 * delay4), ringDelay);
            
            // Delayed sample for each tap
            double delayed1 = ringVector[i].interpolation(ringSample * time1);
            double delayed2 = ringVector[i].interpolation(ringSample * time2);
            double delayed3 = ringVector[i].interpolation(ringSample * time3);
            double delayed4 = ringVector[i].interpolation(ringSample * time4);
            
            // Multiple feedback gain with delayed samples
            double feedded1 = feedback1 * delayed1;
            double feedded2 = feedback2 * delayed2;
            double feedded3 = feedback3 * delayed3;
            double feedded4 = feedback4 * delayed4;
            
            // Sum all feeded taps
            double totalFeeded = feedded1 + feedded2 + feedded3 + feedded4;
            
            // Add gain limitter to totalFeeded
            double mixedFeeded = gainLimitter * totalFeeded;
            
            // Write it back to ring buffer vector with inputAudio
            ringVector[i].write(inputAudio + mixedFeeded);
            
            // Multiple feedback gain with delayed samples each tap
            double gained1 = gain1 * delayed1;
            double gained2 = gain2 * delayed2;
            double gained3 = gain3 * delayed3;
            double gained4 = gain4 * delayed4;
            
            // Sum all gained taps
            double totalGained = gained1 + gained2 + gained3 + gained4;
            
            // Add dry and wet portions to inputAudio and totalGained
            double mixedAudio = (dry * inputAudio) + (wet * totalGained);
            
            // Apply gain limitter to mixed Audio
            outputAudio = gainLimitter * mixedAudio;
            
            // Send outputAudio to output pointer
            (*ptrOut++) = outputAudio;
        }
    }

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace aresmutemet
