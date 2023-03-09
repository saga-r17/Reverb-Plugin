/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "reverbDSP.h"
#include "CustomKnobs.h"

//==============================================================================
/**
*/
class FreeReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FreeReverbAudioProcessorEditor (FreeReverbAudioProcessor&);
    ~FreeReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    FreeReverbAudioProcessor& audioProcessor;

    CustomFeel myFeel;

    CustomKnob wet_Slider;
    CustomKnob damp_Slider;
    CustomKnob room_Slider;
    CustomKnob spread_Slider;
    
    Label wet_Label;
    Label damp_Label;
    Label room_Label;
    Label spread_Label;

    juce::Image baseImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeReverbAudioProcessorEditor)
};
