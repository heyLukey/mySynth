/*
  ==============================================================================

    Oscillator.h
    Created: 25 June 2020 4:49:45pm
    Author:  Lukey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class OscillatorA  : public juce::Component, private juce::ComboBox::Listener
{
public:
    OscillatorA(mySynthAudioProcessor&);
    ~OscillatorA() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox*) override;

private:
    mySynthAudioProcessor& audioProcessor;
    juce::ComboBox oscAMenu;
    juce::Slider oscAMix;

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> scopedOscAMenu;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> scopedOscAMix;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorA)
};
