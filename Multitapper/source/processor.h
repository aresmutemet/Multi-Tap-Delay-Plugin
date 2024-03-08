//------------------------------------------------------------------------
// Copyright(c) 2023 Ares Mutemet.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "ringBuffer.h"

namespace aresmutemet {

//------------------------------------------------------------------------
//  MultitapperProcessor
//------------------------------------------------------------------------
class MultitapperProcessor : public Steinberg::Vst::AudioEffect
{
public:
	MultitapperProcessor ();
	~MultitapperProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new MultitapperProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
    
    // Create sample rate variable for ring buffer
    int ringSample;
    
    // Create ring buffer vector
    std::vector<ringBuffer> ringVector;
    
    // Parameter for DRY/WET
    Steinberg::Vst::ParamValue mix = 0.;
    
    // Parameters for Tap 1
    Steinberg::Vst::ParamValue delay1 = 0.;
    Steinberg::Vst::ParamValue gain1 = 0.;
    Steinberg::Vst::ParamValue feedback1 = 0.;
    
    // Parameters for Tap 2
    Steinberg::Vst::ParamValue delay2 = 0.;
    Steinberg::Vst::ParamValue gain2 = 0.;
    Steinberg::Vst::ParamValue feedback2 = 0.;
    
    // Parameters for Tap 3
    Steinberg::Vst::ParamValue delay3 = 0.;
    Steinberg::Vst::ParamValue gain3 = 0.;
    Steinberg::Vst::ParamValue feedback3 = 0.;
    
    // Parameters for Tap 4
    Steinberg::Vst::ParamValue delay4 = 0.;
    Steinberg::Vst::ParamValue gain4 = 0.;
    Steinberg::Vst::ParamValue feedback4 = 0.;
};

//------------------------------------------------------------------------
} // namespace aresmutemet
