//------------------------------------------------------------------------
// Copyright(c) 2023 Ares Mutemet.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"


using namespace Steinberg;

namespace aresmutemet {

//------------------------------------------------------------------------
// MultitapperController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
    
    // Dry/Wet mix control
    parameters.addParameter(STR16("DRY/WET"),STR16("Balance"), 0, 0, Vst::ParameterInfo::kCanAutomate, kMixId);
    
    parameters.addParameter(STR16("Delay 1"), STR16("Seconds"), 0, 0, Vst::ParameterInfo::kCanAutomate, kDelay1Id);
    parameters.addParameter(STR16("Gain 1"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kGain1Id);
    parameters.addParameter(STR16("Feedback 1"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kFeedback1Id);
    
    parameters.addParameter(STR16("Delay 2"), STR16("Seconds"), 0, 0, Vst::ParameterInfo::kCanAutomate, kDelay2Id);
    parameters.addParameter(STR16("Gain 2"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kGain2Id);
    parameters.addParameter(STR16("Feedback 2"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kFeedback2Id);
    
    parameters.addParameter(STR16("Delay 3"), STR16("Seconds"), 0, 0, Vst::ParameterInfo::kCanAutomate, kDelay3Id);
    parameters.addParameter(STR16("Gain 3"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kGain3Id);
    parameters.addParameter(STR16("Feedback 3"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kFeedback3Id);
    
    parameters.addParameter(STR16("Delay 4"), STR16("Seconds"), 0, 0, Vst::ParameterInfo::kCanAutomate, kDelay4Id);
    parameters.addParameter(STR16("Gain 4"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kGain4Id);
    parameters.addParameter(STR16("Feedback 4"), STR16("Level"), 0, 0, Vst::ParameterInfo::kCanAutomate, kFeedback4Id);
    
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API MultitapperController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultitapperController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace aresmutemet
