//------------------------------------------------------------------------
// Copyright(c) 2023 Ares Mutemet.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace aresmutemet {
//------------------------------------------------------------------------
static const Steinberg::FUID kMultitapperProcessorUID (0xE0DC2898, 0x6C455EC8, 0xA326E653, 0x9B480294);
static const Steinberg::FUID kMultitapperControllerUID (0xDD7ED5CD, 0x6FC05BE0, 0x8966DFD9, 0x16C3260C);

#define MultitapperVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace aresmutemet

enum MultiTapParams : Steinberg::Vst::ParamID
{
    kDelay1Id = 101,
    kFeedback1Id = 102,
    kGain1Id = 103,
    
    kDelay2Id = 104,
    kFeedback2Id = 105,
    kGain2Id = 106,
    
    kDelay3Id = 107,
    kFeedback3Id = 108,
    kGain3Id = 109,
    
    kDelay4Id = 110,
    kFeedback4Id = 111,
    kGain4Id = 112,
    
    kMixId = 113,
};
