/*
  ==========================================================================

    OscillatorB.h
    Created: 1 July 2020 7:37:41pm
    Author:  Lukey

  ==========================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==========================================================================

class OscillatorB : public juce::Component, private juce::ComboBox::Listener
{
public:
    OscillatorB(mySynthAudioProcessor&);
    ~OscillatorB() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox*) override;

private:
    mySynthAudioProcessor& audioProcessor;
    juce::ComboBox oscBMenu;
    juce::Slider oscBMix;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> scopedOscBMenu;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> scopedOscBMix;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorB)
};
