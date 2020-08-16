/*
  ==========================================================================

    ADSREnvelope.cpp
    Created: 7 July 2020 5:32:58pm
    Author:  Lukey

  ==========================================================================
*/

#include <JuceHeader.h>
#include "ADSREnvelope.h"

//==========================================================================

ADSREnvelope::ADSREnvelope(mySynthAudioProcessor& p) : audioProcessor(p)
{
    // Set GUI for the ADSR envelope
    setSize(200, 200);

    // Create a Slider for attack
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(100.0f, 5000.0f);
    attackSlider.setValue(100.0f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);

    // Create a Slider for decay
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(100.0f, 5000.0f);
    decaySlider.setValue(100.0f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);

    // Create a Slider for sustain
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);

    // Create a Slider for release
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(100.0f, 5000.0f);
    releaseSlider.setValue(100.0f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);

    attackVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    decayVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "decay", decaySlider);
    sustainVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sustain", sustainSlider);
    releaseVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "release", releaseSlider);


}

//==========================================================================

ADSREnvelope::~ADSREnvelope()
{
}

//==========================================================================

void ADSREnvelope::paint(juce::Graphics& g)
{
    // Make the GUI white and add some text
    g.fillAll(juce::Colour::fromRGB(255, 255, 255));
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawText("A", 45, 170, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 75, 170, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 105, 170, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 135, 170, 20, 20, juce::Justification::centredTop);
    g.drawText("Volume Envelope", 50, 15, 100, 20, juce::Justification::centredTop);

    juce::Rectangle<int> area(0, 0, 200, 200);
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawRect(area, 2.0f);
}

//==========================================================================

void ADSREnvelope::resized()
{   
    // Set the position of the sliders
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int sliderWidth = 30;
    int sliderHeight = 175;
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
