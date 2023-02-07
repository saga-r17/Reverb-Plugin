# juce-faust-integration

JuceFaust is a project that integrates the audio DSP created in Faust with the JUCE framework. It combines the powerful audio processing capabilities of Faust with the user-friendly UI creation features of JUCE.

#Features
A UI created using JUCE
Audio processing implemented using the Faust DSP library

#Prerequisites
-A working installation of the JUCE framework (optional because CMakeLists has a script that fetch JUCE from repositary)
-A working installation of the Faust DSP library (mandatory because faced several issue while trying to fetch from repository)
-make sure CMake is installed on your system

#Running the Project
1.Clone or download the repository to your local machine
2.Create an empty build directory then run cmake commands to build the project

#How it Works
The project consists of two main components: the Faust DSP code and the JUCE code. The Faust DSP code provides the audio processing capabilities, while the JUCE code creates the UI and implements the audio callback function.

The DSP object created in Faust is embedded in a JuceFaustAudioProcessor class, which serves as an interface between the DSP and the JUCE framework. The JuceFaustAudioProcessor class implements the audio callback function, which retrieves audio samples from the input and passes them through the Faust DSP object. The processed audio samples are then passed back to the JUCE framework to be output.

The UI of the project is created using JUCE's graphical components. In the PluginEditor class, the components are added to the window and their properties such as size and position are set. The UI components are connected to the audio processing code through the JuceFaustAudioProcessor class.

#Contributions
Contributions to the project are always welcome. If you would like to contribute, please follow these steps:

#License
This project is licensed under the MIT License.