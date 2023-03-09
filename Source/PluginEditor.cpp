
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomKnobs.h"

//==============================================================================
FreeReverbAudioProcessorEditor::FreeReverbAudioProcessorEditor (FreeReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    setResizable(true,true);

    juce::LookAndFeel::setDefaultLookAndFeel(&myFeel);

    baseImage = juce::ImageCache::getFromMemory(BinaryData::base_png, BinaryData::base_pngSize);

    addAndMakeVisible(wet_Slider);
    wet_Slider.setRange(0.0, 1.0);
    wet_Slider.setValue(0.25);
    wet_Slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::lightcoral);
    wet_Slider.onValueChange = [this] {
        audioProcessor.setWet(wet_Slider.getValue());
    };

    addAndMakeVisible(wet_Label);
    wet_Label.setText("Wet", dontSendNotification);
    wet_Label.attachToComponent(&wet_Slider, false);

    // This block of code is for distance setting
    addAndMakeVisible(damp_Slider);
    damp_Slider.setRange(0.0, 1.0);
    damp_Slider.setValue(0.25);
    damp_Slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan);
    damp_Slider.onValueChange = [this] {
        audioProcessor.setDamp(damp_Slider.getValue());
    };

    addAndMakeVisible(damp_Label);
    damp_Label.setText("Damp", dontSendNotification);
    damp_Label.attachToComponent(&damp_Slider, false);


    addAndMakeVisible(room_Slider);
    room_Slider.setRange(0.0, 1.0);
    room_Slider.setValue(0.25);
    room_Slider.onValueChange = [this] {
        audioProcessor.setRoom(room_Slider.getValue());
    };


    addAndMakeVisible(room_Label);
    room_Label.setText("Room Size", dontSendNotification);
    room_Label.attachToComponent(&room_Slider, false);
    

    addAndMakeVisible(spread_Slider);
    spread_Slider.setRange(0.0, 1.0);
    spread_Slider.setValue(0.25);
    spread_Slider.onValueChange = [this] {
        audioProcessor.setSpread(spread_Slider.getValue());
    };

    addAndMakeVisible(spread_Label);
    spread_Label.setText("Stereo Spread", dontSendNotification);
    spread_Label.attachToComponent(&spread_Slider, false);


}

FreeReverbAudioProcessorEditor::~FreeReverbAudioProcessorEditor()
{
}


//==============================================================================
void FreeReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(baseImage,getLocalBounds().toFloat());
}

void FreeReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    const int knobSize = 85;
    const int RightAllign = getWidth() - knobSize-25;

    wet_Slider.setBounds(25, getHeight() / 10, knobSize, knobSize);
    damp_Slider.setBounds(RightAllign, getHeight() / 10, knobSize, knobSize);
    room_Slider.setBounds(25, getHeight()/1.5, knobSize, knobSize);
    spread_Slider.setBounds(RightAllign, getHeight()/1.5, knobSize, knobSize);

}
