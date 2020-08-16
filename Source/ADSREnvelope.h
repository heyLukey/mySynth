/*
  ==========================================================================

    ADSREnvelope.h
    Created: 7 July 2020 5:32:58pm
    Author:  Lukey

  ==========================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==========================================================================

class ADSREnvelope  : public juce::Component
{
public:
    ADSREnvelope(mySynthAudioProcessor&);
    ~ADSREnvelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    mySynthAudioProcessor& audioProcessor;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> attackVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> decayVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> releaseVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSREnvelope)
};
