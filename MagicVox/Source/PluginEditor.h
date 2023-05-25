/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//#include "./LookAndFeel/KnobLookAndFeel.h"

//==============================================================================
/**
*/
class MagicVoxAudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    MagicVoxAudioProcessorEditor (MagicVoxAudioProcessor&);
    ~MagicVoxAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void prepareSliders();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MagicVoxAudioProcessor& audioProcessor;

  
    juce::Slider volumeSlider, dryWetSlider, compressorSlider, distorsionSlider, gainSlider, qEqSlider, gainFactorEqSlider;
    juce::Label volumeLabel, dryWetLabel, compressorLabel, distorsionLabel, gainLabel, qEqLabel, gainFactorEqLabel;
    
    //CREACION DE ATTACHMENTS
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttach, dryWetAttach, compressorAttach, distorsionAttach, gainAttach, qEqAttach, gainFactorEqAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagicVoxAudioProcessorEditor)
};
