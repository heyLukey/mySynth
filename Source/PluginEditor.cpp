/*
  ==========================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==========================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==========================================================================

mySynthAudioProcessorEditor::mySynthAudioProcessorEditor (mySynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), envGui(p), osc1Gui(p), osc2Gui(p), gainGui(p), filterGui(p)
{
    // Create the GUI for the Synth
    setSize (850, 200);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&osc1Gui);
    addAndMakeVisible(&osc2Gui);
    addAndMakeVisible(&gainGui);
    addAndMakeVisible(&filterGui);
}

//==========================================================================

mySynthAudioProcessorEditor::~mySynthAudioProcessorEditor()
{
}

//==========================================================================
void mySynthAudioProcessorEditor::paint (juce::Graphics& g)
{
}

//==========================================================================

void mySynthAudioProcessorEditor::resized()
{
    // Create Blocks to place each synth component
    juce::Rectangle<int> area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;

    osc1Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc2Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    gainGui.setBounds(area.removeFromLeft(componentWidth / 4).removeFromTop(componentHeight)); // Smaller so divide width by 4
}




