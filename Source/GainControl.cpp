/*
  ==========================================================================

    GainControl.cpp
    Created: 25 June 2020 7:21:48pm
    Author:  Lukey

  ==========================================================================
*/

#include <JuceHeader.h>
#include "GainControl.h"

//==========================================================================

GainControl::GainControl(mySynthAudioProcessor& p) : audioProcessor(p)
{
    // Set Gui for gain Slider
    setSize(50, 200);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(0.0f, 1.0f);
    gainSlider.setValue(0.5f);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&gainSlider);
    gainVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "gain", gainSlider);
}

//==========================================================================

GainControl::~GainControl()
{
}

//==========================================================================

void GainControl::paint (juce::Graphics& g)
{
    // Make the GUI white and add some text
    g.fillAll (juce::Colour::fromRGB(255, 255, 255));   // clear the background
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawText("Gain", 1, 15, 50, 20, juce::Justification::centredTop);

    juce::Rectangle<int> area(0, 0, 50, 200);
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawRect(area, 2.0f);
}

//==========================================================================

void GainControl::resized()
{
    // Set position of the Slider
    juce::Rectangle<int> area = getLocalBounds().reduced(0, 20);
    int sliderWidth = 50;
    int sliderHeight = 175;
    gainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
