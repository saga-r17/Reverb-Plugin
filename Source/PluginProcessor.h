
#pragma once

#include <JuceHeader.h>
#include "reverbDSP.h"

//==============================================================================
/**
*/
class FreeReverbAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FreeReverbAudioProcessor();
    ~FreeReverbAudioProcessor() override;

    //thee functions used to set the panning,distance and channel value to the audioprocessor
    void setWet(float wet);
    void setDamp(float damp);
    void setRoom(float room);
    void setSpread(float spread);

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:


    private:

    //This code declares four variables: fUI of type MapUI, fDSP of type dsp, and two arrays of float pointers, inputs and outputs

    MapUI* fUI; //a pointer to a MapUI class instance, which is responsible for handling the graphical user interface for the DSP.
    dsp* fDSP;  // a pointer to a dsp class instance, which contains the audio processing code.
    float **inputs; //a 2D array of floats, representing the input audio data. The first dimension represents the channel, and the second dimension represents the sample index.
    float **outputs; //a 2D array of floats, representing the output audio data. 

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeReverbAudioProcessor)
};
