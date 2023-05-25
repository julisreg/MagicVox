/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MagicVoxAudioProcessor::MagicVoxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
                #if ! JucePlugin_IsMidiEffect
                 #if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                 #endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                #endif
                  ), apvts(*this, nullptr, "parametros", createParameters())
#endif
{
}

MagicVoxAudioProcessor::~MagicVoxAudioProcessor()
{
}
juce::AudioProcessorValueTreeState::ParameterLayout MagicVoxAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parametros;
    
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("PreGain",1), "PreGain",0.0f, 5.0f, 1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID ("Soft Clipping",1), "Soft Clipping", 0.0f, 5.0f, 1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Gain", 1), "Gain", 0.0f, 5.0f, 1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutGain", 1), "OutGain", 0.0f, 5.0f, 1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Q",1), "Q",0.0f,10.0f,5.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("GainFactorEq",1), "GainFactorEq",-50.0f,10.0f,0.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Compressor",1), "Compressor",-50.0f,10.0f,1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Volume",1), "Volume",0.0f,1.0f,1.0f));
    parametros.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("DryWet",1), "DryWet",0.0f, 100.0f, 100.0f));

    
    return parametros;
}
//==============================================================================
const juce::String MagicVoxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MagicVoxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MagicVoxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MagicVoxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MagicVoxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MagicVoxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MagicVoxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MagicVoxAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MagicVoxAudioProcessor::getProgramName (int index)
{
    return {};
}

void MagicVoxAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MagicVoxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) //EL PLATO.
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    spec.maximumBlockSize = samplesPerBlock; // BUFFER SIZE
    
    equalization.prepare(spec);
    compressor.prepare (spec);
    
}

void MagicVoxAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MagicVoxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MagicVoxAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dryBuffer.makeCopyOf (buffer);
    
    //GAIN
    auto preGainValue = apvts.getRawParameterValue ("PreGain") -> load();
    auto gainValue = apvts.getRawParameterValue ("Gain") -> load();
    
    //VOLUMEN
    float volValue     = apvts.getRawParameterValue ("Volume")->load();
    
    //DISTORSION
    auto distortionIndex = apvts.getRawParameterValue ("Distortion") -> load();
    auto outGainValue = apvts.getRawParameterValue ("OutGain") -> load();
    
    //EQ
    auto qValue = apvts.getRawParameterValue("Q")->load(); //float
    auto gainFactorDB = apvts.getRawParameterValue("GainFactorEq")->load();
    auto gainFactorEq =    juce::Decibels::decibelsToGain(gainFactorDB); //paso de DBs a LINEAL
    
    //COMPRESOR
    auto compressorInputGainDB = apvts.getRawParameterValue("Compressor")->load();
    auto compressorInputGain = juce::Decibels::decibelsToGain(compressorInputGainDB);
    
    //DRY WET
    float dryWetValue  = apvts.getRawParameterValue ("DryWet")->load();
    
    equalization.updateFilter(qValue, gainFactorEq);
    
//COMER /// PROCESOS
    equalization.process(buffer);
    compressor.process(buffer);
    preGain.setGain (preGainValue);
    outGain.setGain (outGainValue);
    volumenObject.process (buffer, volValue);
    distorsion.setGain (gainValue);
    distorsion.setDistortion(distortionIndex);
    distorsion.process(buffer);
    dryWetObject.process  (dryBuffer, buffer, dryWetValue);
}

//==============================================================================
bool MagicVoxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MagicVoxAudioProcessor::createEditor()
{
//    return new MagicVoxAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void MagicVoxAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MagicVoxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MagicVoxAudioProcessor();
}
