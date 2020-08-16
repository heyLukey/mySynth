/*
  ==============================================================================

    SynthSound.h
    Created: 15 June 2020 12:38:32pm
    Author:  Lukey

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "maximilian.h"

//==========================================================================

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int /*midiNoteNumber*/) {return true;}
    bool appliesToChannel(int /*midiChannel*/) { return true; }
};
