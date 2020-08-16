/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSREnvelope.h"
#include "OscillatorA.h"
#include "OscillatorB.h"
#include "GainControl.h"
#include "Filter.h"

//==============================================================================

class mySynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    mySynthAudioProcessorEditor (mySynthAudioProcessor&);
    ~mySynthAudioProcessorEditor() override;
 
    //==========================================================================

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Pass GUI for each synth component
    mySynthAudioProcessor& audioProcessor;
    ADSREnvelope envGui;
    OscillatorA osc1Gui;
    OscillatorB osc2Gui;
    GainControl gainGui;
    Filter filterGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mySynthAudioProcessorEditor)
};
