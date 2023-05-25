/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MagicVoxAudioProcessorEditor::MagicVoxAudioProcessorEditor (MagicVoxAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    prepareSliders();
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MagicVoxAudioProcessorEditor::~MagicVoxAudioProcessorEditor()
{
}

void MagicVoxAudioProcessorEditor::prepareSliders()
{
    //VOLUMEN SLIDER
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(volumeSlider);
    
    volumenAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Volume", volumeSlider);
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred);
    volumeLabel.attachToComponent(&volumeSlider, false);
    addAndMakeVisible(volumeSlider);
    
    //DRY WET SLIDER
    dryWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    dryWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(dryWetSlider);
    
    dryWetAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DryWet", dryWetSlider);
    
    //COMPRESOR SLIDER
    compressorSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    compressorSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(compressorSlider);
    
    compressorAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Compressor", compressorSlider);
    
    //DISTORSION SLIDER
    distorsionSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    distorsionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(distorsionSlider);
    
    distorsionAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Soft Clipping", distorsionSlider);
    
    //GAIN SLIDER
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(gainSlider);
    
    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OutGain", gainSlider);
    
    //EQ  - Q SLIDER
    qEqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    qEqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(qEqSlider);
    
    qEqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Q", qEqSlider);
    
    //EQ  - gain Factor SLIDER
    gainFactorEqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainFactorEqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0.0f, 0.0f);
    addAndMakeVisible(gainFactorEqSlider);
    
    gainFactorEqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GainFactorEq", gainFactorEqSlider);
    
    
    
    
    
}

//==============================================================================
void MagicVoxAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MagicVoxAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volumeSlider.setBoundsRelative(0.0f, 0.1f, 0.2f, 0.3f);
    dryWetSlider.setBoundsRelative(0.2f, 0.0f, 0.2f, 0.3f);
//    compressorSlider.setBoundsRelative(0.0f, 0.0f, 0.3f, 0.3f);
//    distorsionSlider.setBoundsRelative(0.0f, 0.0f, 0.3f, 0.3f);
//    gainSlider.setBoundsRelative(0.0f, 0.0f, 0.3f, 0.3f);
//    qEqSlider.setBoundsRelative(0.0f, 0.0f, 0.3f, 0.3f);
//    gainFactorEqSlider.setBoundsRelative(0.0f, 0.0f, 0.3f, 0.3f);
    
}
