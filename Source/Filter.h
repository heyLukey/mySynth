/*
  ==========================================================================

    Filter.h
    Created: 8 July 2020 8:24:02pm
    Author:  Lukey

  ==========================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==========================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(mySynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    mySynthAudioProcessor& audioProcessor;

    juce::Slider filterCuttoff;
    juce::Slider filterRes;
    juce::ComboBox filterMenu;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterCuttoffVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterResVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
