/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomKnobs.h"

//==============================================================================
JuceFaustAudioProcessorEditor::JuceFaustAudioProcessorEditor (JuceFaustAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 600);

    juce::LookAndFeel::setDefaultLookAndFeel(&myFeel);

    addAndMakeVisible(attack_Slider);
    attack_Slider.setRange(0.01, 4.0);
    attack_Slider.setValue(0.5);
    attack_Slider.onValueChange = [this] {
        audioProcessor.setAttack(attack_Slider.getValue());
    };

    addAndMakeVisible(attack_Label);
    attack_Label.setText("Attack", dontSendNotification);
    attack_Label.attachToComponent(&attack_Slider, false);

    addAndMakeVisible(decay_Slider);
    decay_Slider.setRange(0.01, 8.0);
    decay_Slider.setValue(0.5);
    decay_Slider.onValueChange = [this] {
        audioProcessor.setDecay(decay_Slider.getValue());
    };

    addAndMakeVisible(decay_Label);
    decay_Label.setText("Decay", dontSendNotification);
    decay_Label.attachToComponent(&decay_Slider, false);

    addAndMakeVisible(sustain_Slider);
    sustain_Slider.setRange(0.0, 1.0);
    sustain_Slider.setValue(0.5);
    sustain_Slider.onValueChange = [this] {
        audioProcessor.setSustain(sustain_Slider.getValue());
    };


    addAndMakeVisible(sustain_Label);
    sustain_Label.setText("Sustain", dontSendNotification);
    sustain_Label.attachToComponent(&sustain_Slider, false);
    

    addAndMakeVisible(release_Slider);
    release_Slider.setRange(0.01, 8.0);
    release_Slider.setValue(0.5);
    release_Slider.onValueChange = [this] {
        audioProcessor.setRelease(release_Slider.getValue());
    };

    addAndMakeVisible(release_Label);
    release_Label.setText("Release", dontSendNotification);
    release_Label.attachToComponent(&release_Slider, false);


    attack_Slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decay_Slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sustain_Slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    release_Slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);




    addAndMakeVisible(gate_Button);
    gate_Button.onClick = [this] {
        audioProcessor.setGate(gate_Button.getToggleState());
    };

    addAndMakeVisible(gate_Label);
    gate_Label.setText("Trigger", dontSendNotification);
    gate_Label.attachToComponent(&gate_Button, false);



    addAndMakeVisible(midi_frequency_Slider);
    midi_frequency_Slider.setRange(20, 20000);
    midi_frequency_Slider.setSkewFactorFromMidPoint(500.0);
    midi_frequency_Slider.setValue(200);
    midi_frequency_Slider.onValueChange = [this] {
        audioProcessor.setFrequency(midi_frequency_Slider.getValue());
    };

    addAndMakeVisible(midi_frequency_Label);
    midi_frequency_Label.setText("Frequency", dontSendNotification);
    midi_frequency_Label.attachToComponent(&midi_frequency_Slider, false);



    addAndMakeVisible(midi_gain_Slider);
    midi_gain_Slider.setRange(0.01, 1.0);
    midi_gain_Slider.setValue(0.1);
    midi_gain_Slider.onValueChange = [this] {
        audioProcessor.setGain(midi_gain_Slider.getValue());
    };

    addAndMakeVisible(midi_gain_Label);
    midi_gain_Label.setText("Gain", dontSendNotification);
    midi_gain_Label.attachToComponent(&midi_gain_Slider, false);


    addAndMakeVisible(modulation_Slider);
    modulation_Slider.setRange(0.0, 1.0);
    modulation_Slider.setValue(0.5);
    modulation_Slider.onValueChange = [this] {
        audioProcessor.setModulation(modulation_Slider.getValue());
    };

    addAndMakeVisible(modulation_Label);
    modulation_Label.setText("Modulation", dontSendNotification);
    modulation_Label.attachToComponent(&modulation_Slider, false);

    addAndMakeVisible(mod_ratio_Slider);
    mod_ratio_Slider.setRange(0.0, 20.0);
    mod_ratio_Slider.setValue(0.5);
    mod_ratio_Slider.onValueChange = [this] {
        audioProcessor.setMod_ratio(mod_ratio_Slider.getValue());
    };

    addAndMakeVisible(mod_ratio_Label);
    mod_ratio_Label.setText("Modualtion Ratio", dontSendNotification);
    mod_ratio_Label.attachToComponent(&mod_ratio_Slider, false);

    addAndMakeVisible(bend_Slider);
    bend_Slider.setRange(-2.0, 2.0);
    bend_Slider.setValue(0.0);
    bend_Slider.onValueChange = [this] {
        audioProcessor.setBend(bend_Slider.getValue());
    };

    addAndMakeVisible(bend_Label);
    bend_Label.setText("Bend", dontSendNotification);
    bend_Label.attachToComponent(&bend_Slider, false);



}

JuceFaustAudioProcessorEditor::~JuceFaustAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void JuceFaustAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::grey);


}

void JuceFaustAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


    const int knobSize = 90;
    const int RightAllign = getWidth() - knobSize;

    attack_Slider.setBounds(0,30,knobSize,knobSize);
    decay_Slider.setBounds(0, getHeight()/4, knobSize, knobSize);
    sustain_Slider.setBounds(0, getHeight() / 2, knobSize, knobSize);
    release_Slider.setBounds(0, getHeight() *3/ 4, knobSize, knobSize);

    modulation_Slider.setBounds(getWidth()/2.5, getHeight() / 4, knobSize, knobSize);
    gate_Button.setBounds(getWidth() / 2, getHeight() / 2, 50, 30);

    midi_frequency_Slider.setBounds(RightAllign, 30, knobSize, knobSize);
    midi_gain_Slider.setBounds(RightAllign, getHeight() / 4, knobSize, knobSize);
    mod_ratio_Slider.setBounds(RightAllign, getHeight() / 2, knobSize, knobSize);
    bend_Slider.setBounds(RightAllign, getHeight() *3/ 4, knobSize, knobSize);
}
