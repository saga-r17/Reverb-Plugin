/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "dspfaust.h"
#include "polyFM.h"

//==============================================================================
JuceFaustAudioProcessor::JuceFaustAudioProcessor()
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

JuceFaustAudioProcessor::~JuceFaustAudioProcessor()
{
}

void JuceFaustAudioProcessor::setAttack(float attack)
{
    fUI->setParamValue("Attack", attack);
}

void JuceFaustAudioProcessor::setDecay(float decay)
{
    fUI->setParamValue("Decay", decay);
}

void JuceFaustAudioProcessor::setSustain(float sustain)
{
    fUI->setParamValue("Sustain", sustain);
}

void JuceFaustAudioProcessor::setRelease(float release)
{
    fUI->setParamValue("Release", release);
}

void JuceFaustAudioProcessor::setBend(float bend)
{
    fUI->setParamValue("bend", bend);
}

void JuceFaustAudioProcessor::setModulation(float modulation)
{
    fUI->setParamValue("modulation", modulation);
}

void JuceFaustAudioProcessor::setMod_ratio(float mod_ratio)
{
    fUI->setParamValue("mod_ratio", mod_ratio);
}

void JuceFaustAudioProcessor::setFrequency(int frequency)
{
    fUI->setParamValue("midi_frequency", frequency);
}

void JuceFaustAudioProcessor::setGain(float gain)
{
    fUI->setParamValue("midi_gain", gain);
}

void JuceFaustAudioProcessor::setGate(bool gate)
{
    if (gate) {
        fUI->setParamValue("midi_gate", 1);
    }
    else {
        fUI->setParamValue("midi_gate", 0);
    }
}









//==============================================================================
const juce::String JuceFaustAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceFaustAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceFaustAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceFaustAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceFaustAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceFaustAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceFaustAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceFaustAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JuceFaustAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceFaustAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JuceFaustAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fDSP = new mydsp();
    fDSP->init(sampleRate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    outputs = new float* [2];
    for (int channel = 0; channel < 2; ++channel) {
        outputs[channel] = new float[samplesPerBlock];
    }

    //driver = new dummyaudio(sampleRate, samplesPerBlock);
    //faustObject = new FaustPolyEngine(NULL, driver, NULL);
    //outputs = new float* [2];
    //for (int channel = 0; channel < 2; ++channel) {
    //    outputs[channel] = new float[samplesPerBlock];
    //}


}

void JuceFaustAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

    delete fDSP;
    delete fUI;
    for (int channel = 0; channel < 2; ++channel) {
        delete[] outputs[channel];
    }
    delete [] outputs;

    //delete driver;
    //for (int channel = 0; channel < 2; ++channel) {
    //    delete[] outputs[channel];
    //}
    //delete[] outputs;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceFaustAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JuceFaustAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    fDSP->compute(buffer.getNumSamples(), NULL, outputs);

    for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            *buffer.getWritePointer(channel, i) = outputs[channel][i];
        }
    }


    //faustObject->compute(buffer.getNumSamples(), NULL, outputs);

    //for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
    //    for (int i = 0; i < buffer.getNumSamples(); i++) {
    //        *buffer.getWritePointer(channel, i) = outputs[channel][i];
    //    }
    //}

}

//==============================================================================
bool JuceFaustAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JuceFaustAudioProcessor::createEditor()
{
    return new JuceFaustAudioProcessorEditor (*this);
}

//==============================================================================
void JuceFaustAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceFaustAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceFaustAudioProcessor();
}
