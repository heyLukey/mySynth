/*
  ==========================================================================

    OscillatorB.cpp
    Created: 1 July 2020 7:37:41pm
    Author:  Lukey

  ==========================================================================
*/

#include <JuceHeader.h>
#include "OscillatorB.h"

//==========================================================================

// Basically a duplicate of OscillatorA.cpp  except for line 26 as second oscillator should be optional
OscillatorB::OscillatorB(mySynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(400, 200);

    oscBMenu.addItem("Sine", 1);
    oscBMenu.addItem("Saw", 2);
    oscBMenu.addItem("Square", 3);
    oscBMenu.addItem("Triangle", 4);
    oscBMenu.addItem("None", 5); // Don't want the synth to start with two waves initialised
    oscBMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscBMenu);
    scopedOscBMenu = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "oscBWave", oscBMenu);

    oscBMix.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscBMix.setRange(0.0f, 1.0f);
    oscBMix.setValue(0.5f);
    oscBMix.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&oscBMix);
    scopedOscBMix = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "oscBMix", oscBMix);
}

//==========================================================================

OscillatorB::~OscillatorB()
{
}

//==========================================================================

void OscillatorB::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(255, 255, 255));
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawText("B Mix", 75, 150, 50, 20, juce::Justification::centredTop);
    g.drawText("Oscillator B", 50, 15, 100, 20, juce::Justification::centredTop);

    juce::Rectangle<int> area(0, 0, 200, 200);
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawRect(area, 2.0f);
}

//==========================================================================

void OscillatorB::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscBMenu.setBounds(area.removeFromTop(20));
    oscBMix.setBounds(65, 80, 70, 70);
}

//==========================================================================

void OscillatorB::comboBoxChanged(juce::ComboBox* box) {

}