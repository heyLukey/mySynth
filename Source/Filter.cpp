/*
  ==========================================================================

    Filter.cpp
    Created: 8 July 2020 8:24:02pm
    Author:  Lukey

  ==========================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==========================================================================

Filter::Filter(mySynthAudioProcessor& p) : audioProcessor(p)
{
    // Set GUI for Filter
    setSize(200, 200);

    // Create Combobox for filter type
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("None", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "filterType", filterMenu);

    // Create Slider for filter cutoff
    filterCuttoff.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    filterCuttoff.setRange(20.0f, 10000.0f);
    filterCuttoff.setValue(400.0f);
    filterCuttoff.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCuttoff);
    filterCuttoffVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterCutoff", filterCuttoff);
    filterCuttoff.setSkewFactorFromMidPoint(1000.0);
    
    // Create Slider for filter resonance
    filterRes.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    filterRes.setRange(0.0f, 5.0f);
    filterRes.setValue(0.0f);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    filterResVal = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "filterRes", filterRes);
}

//==========================================================================

Filter::~Filter()
{
}

//==========================================================================

void Filter::paint (juce::Graphics& g)
{
    // Make the GUI white and add some text
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);

    g.fillAll (juce::Colour::fromRGB(255, 255, 255));   
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawText("Cutoff", 40, 150, 50, 20, juce::Justification::centredTop);
    g.drawText("Res", 110, 150, 50, 20, juce::Justification::centredTop);
    g.drawText("Filter", 50, 15, 100, 20, juce::Justification::centredTop);
    
    juce::Rectangle<int> area(0, 0, 200, 200);
    g.setColour(juce::Colour::fromRGB(0, 0, 0));
    g.drawRect(area, 2.0f);
}

//==========================================================================

void Filter::resized()
{
    // Set position of Combobox and Sliders
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    filterMenu.setBounds(area.removeFromTop(20));
    filterCuttoff.setBounds(30, 80, 70, 70);
    filterRes.setBounds(100, 80, 70, 70);
}
