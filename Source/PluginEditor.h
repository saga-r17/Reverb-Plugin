/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomKnobs.h"

//==============================================================================
/**
*/
class JuceFaustAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceFaustAudioProcessorEditor (JuceFaustAudioProcessor&);
    ~JuceFaustAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceFaustAudioProcessor& audioProcessor;

    CustomFeel myFeel;

    CustomKnob attack_Slider;
    CustomKnob decay_Slider;
    CustomKnob sustain_Slider;
    CustomKnob release_Slider;

    ToggleButton gate_Button;

    CustomKnob modulation_Slider;

    CustomKnob midi_frequency_Slider;
    CustomKnob midi_gain_Slider;
    CustomKnob mod_ratio_Slider;
    CustomKnob bend_Slider;


    Label attack_Label;
    Label decay_Label;
    Label sustain_Label;
    Label release_Label;

    Label gate_Label;
    Label midi_frequency_Label;
    Label midi_gain_Label;
    Label modulation_Label;
    Label mod_ratio_Label;
    Label bend_Label;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceFaustAudioProcessorEditor)
};
