/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

mySynthAudioProcessor::mySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree(*this, nullptr, "PARAMETERS", 
    // This tree contains all the parameters we want to pass from the GUI to the backend of the synth, initialize each param as follows:
    // std::make_unique<juce::AudioParameterFloat>("paramIdentifier", "paramIdentifier", juce::NormalisableRange<float>(range_min, range_max), initial_value)
    {   std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>(100.0f, 5000.0f), 100.0f),
        std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float>(100.0f, 5000.0f), 100.0f),
        std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.8f),
        std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>(100.0f, 5000.0f), 100.0f),
        std::make_unique<juce::AudioParameterFloat>("oscAWave", "OscAWave", juce::NormalisableRange<float>(0.0f, 3.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>("oscAMix", "OscAMix", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
        std::make_unique<juce::AudioParameterFloat>("oscBWave", "OscBWave", juce::NormalisableRange<float>(0.0f, 4.0f), 4.0f),
        std::make_unique<juce::AudioParameterFloat>("oscBMix", "OscBMix", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
        std::make_unique<juce::AudioParameterFloat>("gain", "Gain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
        std::make_unique<juce::AudioParameterFloat>("filterCutoff", "FilterCutoff", juce::NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
        std::make_unique<juce::AudioParameterFloat>("filterRes", "FilterRes", juce::NormalisableRange<float>(0.0f, 5.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat>("filterType", "FilterType", juce::NormalisableRange<float>(0.0f, 2.0f), 2.0f) })
#endif
{
    tree.state = juce::ValueTree("Foo"); // Have to initialize tree state
    mySynth.clearVoices();

    // Add voices to the synth by iteratively creating new SynthVoice objects
    for (int i = 0; i < 5; i++) 
        mySynth.addVoice(new SynthVoice());

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

//==============================================================================

mySynthAudioProcessor::~mySynthAudioProcessor()
{
}

//==============================================================================

const juce::String mySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

//==============================================================================

bool mySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================

bool mySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================

bool mySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

//==============================================================================

double mySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================

int mySynthAudioProcessor::getNumPrograms()
{
    return 1;   
}

//==============================================================================

int mySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

//==============================================================================

void mySynthAudioProcessor::setCurrentProgram (int index)
{
}

//==============================================================================

const juce::String mySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

//==============================================================================

void mySynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void mySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

//==============================================================================

void mySynthAudioProcessor::releaseResources()
{
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool mySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================

void mySynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))); {
            
            // Pass in GUI values as params to relevant function in SynthVoice.h

            // Pass in ADSR Envelope values
            float* floatPtrAttack = (float*)tree.getRawParameterValue("attack");
            float* floatPtrDecay = (float*)tree.getRawParameterValue("decay");
            float* floatPtrSustain = (float*)tree.getRawParameterValue("sustain");
            float* floatPtrRelease = (float*)tree.getRawParameterValue("release");
            myVoice->getEnvParams(floatPtrAttack, floatPtrDecay, floatPtrSustain, floatPtrRelease);

            // Pass in Oscillator A values
            float* floatPtrOscAWave = (float*)tree.getRawParameterValue("oscAWave");
            float* floatPtrOscAMix = (float*)tree.getRawParameterValue("oscAMix");
            myVoice->getOscAWave(floatPtrOscAWave, floatPtrOscAMix);

            // Pass in Oscillator B values
            float* floatPtrOscBWave = (float*)tree.getRawParameterValue("oscBWave");
            float* floatPtrOscBMix = (float*)tree.getRawParameterValue("oscBMix");
            myVoice->getOscBWave(floatPtrOscBWave, floatPtrOscBMix);

            // Pass in Gain value
            float* floatPtrGain = (float*)tree.getRawParameterValue("gain");
            myVoice->getGain(floatPtrGain);

            // Pass in Filter Values
            float* floatPtrFilterType = (float*)tree.getRawParameterValue("filterType");
            float* floatPtrFilterCutoff = (float*)tree.getRawParameterValue("filterCutoff");
            float* floatPtrFilterRes = (float*)tree.getRawParameterValue("filterRes");
            myVoice->getFilterParams(floatPtrFilterType, floatPtrFilterCutoff, floatPtrFilterRes);
            
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool mySynthAudioProcessor::hasEditor() const
{
    return true; 
}

//==============================================================================

juce::AudioProcessorEditor* mySynthAudioProcessor::createEditor()
{
    return new mySynthAudioProcessorEditor (*this);
}

//==============================================================================
void mySynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

//==============================================================================

void mySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new mySynthAudioProcessor();
}
