# FreeReverb Plugin

## Prerequisites
- A working installation of the JUCE framework (optional because CMakeLists has a script that fetch JUCE from repositary)
- A working installation of the Faust DSP library (mandatory)
- CMake installed on your system

## Output UI

![User Interface of the Standalone Application build from source code provided](/freereverb_UI.jpg)


## How it Works
The project consists of two main components: the Faust DSP code and the JUCE code. The Faust DSP code provides the audio processing capabilities, while the JUCE code creates the UI and implements the audio callback function.

The DSP object created in Faust is embedded in a FreeReverbAudioProcessor class, which serves as an interface between the DSP and the JUCE framework. The FreeReverbAudioProcessor class implements the audio callback function, which retrieves audio samples from the input and passes them through the Faust DSP object. The processed audio samples are then passed back to the JUCE framework to be output.

The UI of the project is created using JUCE's graphical components. In the PluginEditor class, the components are added to the window and their properties such as size and position are set.
