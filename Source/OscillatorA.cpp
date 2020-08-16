/*
  ==========================================================================

    OscillatorA.cpp
    Created: 25 June 2020 4:49:45pm
    Author:  Lukey

  ==========================================================================
*/

#include <JuceHeader.h>
#include "OscillatorA.h"

//==========================================================================

OscillatorA::OscillatorA(mySynthAudioProcessor& p) : audioProcessor(p)
{
    // Set GUI for Osc A
    setSize(400, 200);

    // Create ComboBox for wave type
    //These decrease by one when passed into the tree for some reason
    oscAMenu.addItem("Sine", 1);
    oscAMenu.addItem("Saw", 2);
    oscAMenu.addItem("Square", 3);
    oscAMenu.addItem("Triangle", 4);
    oscAMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscAMenu);
    scopedOscAMenu = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "oscAWave", oscAMenu);

    // Create Slider for osc volume
    oscAMix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    oscAMix.setRange(0.0f, 1.0f);
    oscAMix.setValue(0.5f);
    oscAMix.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&oscAMix);
    scopedOscAMix = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "oscAMix", oscAMix);
}

//==========================================================================

OscillatorA::~OscillatorA()
{
}

//==========================================================================

void OscillatorA::paint (juce::Graphics& g)
{
    // Make the GUI white and add some text
    g.fillAll(juce::Colour::fromRGB(255, 255, 255));
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawText("A Mix", 75, 150, 50, 20, juce::Justification::centredTop);
    g.drawText("Oscillator A", 50, 15, 100, 20, juce::Justification::centredTop);

    juce::Rectangle<int> area(0, 0, 200, 200);
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawRect(area, 2.0f);
}

//==========================================================================

void OscillatorA::resized()
{
    // Set the positions of the Slider and Combobox
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscAMenu.setBounds(area.removeFromTop(20));
    oscAMix.setBounds(65, 80, 70, 70);
}

//==========================================================================

void OscillatorA::comboBoxChanged(juce::ComboBox* box) {

}