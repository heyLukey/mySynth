/*
  ==============================================================================

    SynthVoice.h
    Created: 15 June 2020 12:38:40pm
    Author:  Lukey

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

//==========================================================================

class SynthVoice : public juce::SynthesiserVoice 
{
public:

    //==========================================================================

    bool canPlaySound(juce::SynthesiserSound* sound) 
    {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }

    //==========================================================================

    // Get Params for oscillator A from the GUI and set them
    void getOscAWave(float* waveA, float* oscAMix) {
        oscAWave = int(*waveA); // The type of wave to play
        oscAGain = double(*oscAMix); // The amplitude of said wave
    }

    //==========================================================================

    // Get Params for oscillator B from the GUI and set them
    void getOscBWave(float* waveB, float* oscBMix) {
        oscBWave = int(*waveB); // The type of wave to play
        oscBGain = double(*oscBMix); // The amplitude of said wave
    }

    //==========================================================================

    // Get Gain value from GUI and set it
    void getGain(float* gainValue) {
        gain = double(*gainValue);
    }

    //==========================================================================

    // Get Params for the filter from the GUI and set them
    void getFilterParams(float* type, float* cutoff, float* res) {
        filterType = int(*type); // The type of filter
        filterCutoff = double(*cutoff); // Cutoff value for said filter
        filterRes = double(*res); // Filter resonance
    }

    //==========================================================================

    // Get Params for the ADSR envelope from the GUI and set them
    void getEnvParams(float* attack, float* decay, float* sustain, float* release){
        env1.setAttack(double(*attack)); // Attack
        env1.setDecay(double(*decay)); // Decay
        env1.setSustain(double(*sustain)); // Sustain
        env1.setRelease(double(*release)); // Release
    }

    //==========================================================================

    /*
    The noise generation of thei synth is as follows:
    (OscA Wave * OscA Volume)
                +             ---> Filter --> Envelope --> Gain --> FINAL SOUND  
    (OscB Wave * OscB Volume)
    */

    // This function handles step 1 of the process
    // It determines the wave played by each oscillator, 
    // adjusts their induvidual volume, and then blends them
    double waveMaker() {
        
        double addWaveA;
        double addWaveB;
        
        // This synth uses the maximillian library for oscillator, filter and envelope;

        // Check wave type given from GUI and then set a var to corresponding wave
        if (oscAWave == 0)
            addWaveA = oscA.sinewave(frequency);
        else if (oscAWave == 1)
            addWaveA = oscA.saw(frequency);
        else if (oscAWave == 2)
            addWaveA = oscA.square(frequency);
        else if (oscAWave == 3)
            addWaveA = oscA.triangle(frequency);
        else
            addWaveA = oscA.sinewave(frequency);

        // Check wave type given from GUI and then set a var to corresponding wave
        if (oscBWave == 0)
            addWaveB = oscB.sinewave(frequency);
        else if (oscBWave == 1)
            addWaveB = oscB.saw(frequency);
        else if (oscBWave == 2)
            addWaveB = oscB.square(frequency);
        else if (oscBWave == 3)
            addWaveB = oscB.triangle(frequency);
        else 
            addWaveB = 0;

        // Adjust induvidual volume for both waves and then blend
        double finalWave = (addWaveA*oscAGain) + (addWaveB* oscBGain);

        return finalWave;
    }

    //==========================================================================
    
    // This function handles step 2 of the process
    // Setting the filter to the sound
    double setFilter() {

        double filterSignal;

        // Take a signal produced by waveMaker() and then apply the appropriate filter to it
        if (filterType == 0)
            filterSignal = filt1.lores(waveMaker(), filterCutoff, filterRes);
        else if (filterType == 1)
            filterSignal = filt1.hires(waveMaker(), filterCutoff, filterRes);
        else
            filterSignal = waveMaker();

        return filterSignal;
    }

    //==========================================================================

    // This function handles step 3 of the process
    // Setting the ADSR envelope for the sound
    double setEnv() {
        // Take a signal produced by setFilter() and then apply the envelope to it
        double envSignal = env1.adsr(setFilter(), env1.trigger);
        return envSignal;
    }

    //==========================================================================

    // This function handles the last step (4) of the process
    // It adjusts the amplitude of the final signal

    double setGain() {
        // Take a signal produced by setEnv() and then adjust its amplitude
        double gainSignal = setEnv() * gain;
        return gainSignal;
    }

    //==========================================================================

    void startNote(int midiNoteNumber, float velocity,
        juce::SynthesiserSound*, int currentPitchWheelPosition) 
    {
        env1.trigger = 1;
        gain = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    //==========================================================================

    void stopNote(float velocity, bool allowTailOff) 
    {
        env1.trigger = 0;
        allowTailOff = true;
        if (velocity == 0)
            clearCurrentNote();
    }
    //==========================================================================

    void pitchWheelMoved(int newPitchWheelValue) {}

    //==========================================================================

    void controllerMoved(int controllerNumber, int newControllerValue) {}

    //==========================================================================

    // The Audio Processing Block
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer,
        int startSample, int numSamples) 
    {
        // Add our sound to the buffer
        for (int sample = 0; sample < numSamples; ++sample) {

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
                outputBuffer.addSample(channel, startSample+sample, setGain());
            }
            //++startSample;
        }
    }

    //==========================================================================

private:
    double gain;
    double frequency;

    maxiOsc oscA;
    int oscAWave;
    double oscAGain;

    maxiOsc oscB;
    int oscBWave;
    double oscBGain;

    maxiFilter filt1;
    double filterCutoff;
    double filterRes;
    int filterType;

    maxiEnv env1;
};