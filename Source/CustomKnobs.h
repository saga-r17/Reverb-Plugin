#pragma once

#include <JuceHeader.h>

class CustomFeel : public juce::LookAndFeel_V4
{
public:
    CustomFeel();
    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;
    juce::Label* createSliderTextBox(juce::Slider& slider) override;
    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
private:
    juce::Image knobImage;
};


class CustomKnob : public juce::Slider
{
public:
    CustomKnob()
    {
        setLookAndFeel(&myFeel);
        auto rotaryParameters = getRotaryParameters();
        rotaryParameters.startAngleRadians = juce::MathConstants<float>::pi * 0.0f;
        rotaryParameters.endAngleRadians = juce::MathConstants<float>::pi * 1.5f;
        rotaryParameters.stopAtEnd = true;
        setRotaryParameters(rotaryParameters);
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::blue);
        setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    }

    ~CustomKnob()
    {
        setLookAndFeel(nullptr);
    }

private:
    CustomFeel myFeel;
};
