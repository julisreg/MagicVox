/*
  ==============================================================================

    Compressor.h
    Created: 19 May 2023 10:25:32pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#pragma once

//#include <stdio.h>
#pragma once
#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>


class Compressor
{
public:
    Compressor();
    ~Compressor();
    
    void prepare (juce::dsp::ProcessSpec& spec);
    
    void setThreshold(float newThreshold);
    void setRatio(float newRatio);
    void setAttack (float newAttack);
    void setRelease (float newRelease);
    
    void process (juce::AudioBuffer <float> buffer);
    
private:
    juce::dsp::Compressor<float> compressor;
};

