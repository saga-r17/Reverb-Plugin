#pragma once


#include <JuceHeader.h>

    class SwitchButton : public juce::Button
    {
    public:
        enum ColourIds
        {
            switchColour = 0x1B06000,
            switchOnBackgroundColour = 0x1B06001,
            switchOffBackgroundColour = 0x1B06002
        };

        SwitchButton(juce::String name, bool isInverted, bool isVertical)
            : Button("SwitchButton"), isInverted(isInverted), isVertical(isVertical)
        {
            setClickingTogglesState(true);
            addAndMakeVisible(switchCircle);
            switchCircle.setWantsKeyboardFocus(false);
            switchCircle.setInterceptsMouseClicks(false, false);
        }

        void setMillisecondsToSpendMoving(int newValue)
        {
            millisecondsToSpendMoving = newValue;
        }

        void paintButton(juce::Graphics& g,
            bool shouldDrawButtonAsHighlighted,
            bool shouldDrawButtonAsDown) override
        {
            auto b = getSwitchBounds();
            auto cornerSize = (isVertical ? b.getWidth() : b.getHeight()) * 0.5;
            g.setColour(juce::Colours::black.withAlpha(0.1f));
            g.drawRoundedRectangle(b, cornerSize, 2.0f);
            g.setColour(findColour(getSwitchState() ? switchOnBackgroundColour : switchOffBackgroundColour));
            g.fillRoundedRectangle(b, cornerSize);

            juce::Path switchPath;
            switchPath.addRoundedRectangle(b, cornerSize, cornerSize);
            g.fillPath(switchPath);

            juce::Rectangle<float> switchCircleBounds;
            if (!isVertical)
                switchCircleBounds = { getSwitchState() ? 1.5f + b.getRight() - b.getHeight() : b.getX() - 1.5f, b.getY(), b.getHeight(), b.getHeight() };
            else
                switchCircleBounds = {
                    b.getX(),
                    getSwitchState() ? b.getBottom() - b.getWidth() - 1.5f : b.getY() + 1.5f,
                    b.getWidth(),
                    b.getWidth()
            };
            animator.animateComponent(&switchCircle, switchCircleBounds.reduced(1).toNearestInt(), 1.0, millisecondsToSpendMoving, false, 0.5, 0.5);
        }

        void resized() override
        {
            Button::resized();
            auto b = getSwitchBounds();
            juce::Rectangle<float> switchCircleBounds;
            if (!isVertical)
                switchCircleBounds = { getSwitchState() ? b.getRight() - b.getHeight() : b.getX(), b.getY(), b.getHeight(), b.getHeight() };
            else
                switchCircleBounds = {
                    b.getX(),
                    getSwitchState() ? b.getBottom() - b.getWidth() : b.getY(),
                    b.getHeight(),
                    b.getHeight()
            };
            switchCircle.setBounds(switchCircleBounds.reduced(1).toNearestInt());
        }

    private:
        int millisecondsToSpendMoving{ 50 };

        bool getSwitchState() const
        {
            return isInverted ? !getToggleState() : getToggleState();
        }
        bool isInverted = false;
        bool isVertical = false;

        juce::Rectangle<float> getSwitchBounds()
        {
            auto b = getLocalBounds().toFloat().reduced(4, 4);
            return b;
        }

        juce::String onText, offText;
        class SwitchCircle : public Component
        {
            void paint(juce::Graphics& g) override
            {
                g.setColour(findColour(switchColour));
                g.fillEllipse(getLocalBounds().toFloat());
            }
        } switchCircle;
        juce::ComponentAnimator animator;
    };
