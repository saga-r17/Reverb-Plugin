

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "reverbDSP.h"

//==============================================================================
FreeReverbAudioProcessor::FreeReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}


FreeReverbAudioProcessor::~FreeReverbAudioProcessor()
{
}

void FreeReverbAudioProcessor::setWet(float wet)
{
    fUI->setParamValue("Wet", wet);
}

void FreeReverbAudioProcessor::setDamp(float damp)
{
    fUI->setParamValue("Damp", damp);
}

void FreeReverbAudioProcessor::setRoom(float room)
{
    fUI->setParamValue("RoomSize", room);
}

void FreeReverbAudioProcessor::setSpread(float spread)
{
    fUI->setParamValue("Stereo Spread", spread);
}

//==============================================================================
const juce::String FreeReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FreeReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FreeReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FreeReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FreeReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FreeReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FreeReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FreeReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FreeReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void FreeReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FreeReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    //This creates a new instance of the mydsp class and initializes it with the given sampleRate.
    fDSP = new mydsp();  
    fDSP->init(sampleRate);

    //This creates a new instance of the MapUI class and initializes the user interface of the mydsp instance with it.
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);

    //This initializes two new arrays, inputs and outputs, as pointers to pointers to float values.
    inputs = new float*[2]; 
    outputs = new float*[2]; 

    //This allocates memory for the inputs array for a single channel and sets each channel to have a block size of samplesPerBlock.
    for (int channel = 0; channel < 2; ++channel) {
        inputs[channel] = new float[samplesPerBlock];
    }

    //This allocates memory for the outputs array for six channels and sets each channel to have a block size of samplesPerBlock.
    for (int channel = 0; channel < 2; ++channel) {
        outputs[channel] = new float[samplesPerBlock];
    }


  
}

void FreeReverbAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FreeReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FreeReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //// Disable denormal numbers for improved processing performance
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Copy the input buffer samples for the selected channel to the input buffer of the fDSP object
    for (int channel = 0; channel < 2; ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            inputs[channel][i] = *buffer.getWritePointer(channel,i);
        }
    }

    // Process the audio samples using the fDSP object
    fDSP->compute(buffer.getNumSamples(),inputs,outputs);


    // Copy the output buffer samples of fDSP object to the output buffer of the audio block for all channels
    for (int channel = 0; channel < 2; ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); i++){
            *buffer.getWritePointer(channel,i) = outputs[channel][i];
        }
    }
}

//==============================================================================
bool FreeReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FreeReverbAudioProcessor::createEditor()
{
    return new FreeReverbAudioProcessorEditor (*this);
}

//==============================================================================
void FreeReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FreeReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FreeReverbAudioProcessor();
}
