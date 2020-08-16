/*
  ==============================================================================

    GainControl.h
    Created: 25 June 2020 7:21:48pm
    Author:  Lukey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class GainControl  : public juce::Component
{
public:
    GainControl(mySynthAudioProcessor&);
    ~GainControl() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    mySynthAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> gainVal;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainControl)
};
