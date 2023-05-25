/*
  ==============================================================================

    Eq.h
    Created: 13 May 2023 12:18:33pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Eq
{
public:
    Eq();
    ~Eq();
    void prepare (juce::dsp::ProcessSpec& spec);
    void process (juce::AudioBuffer <float> buffer);
    void updateFilter(float Q, float gainFactorEq);
    
    
private:
    //para filtros como REGLA tener estructura PREPARE 
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,juce::dsp::IIR::Coefficients<float>> highShelfFilter;
    //variables personalizadas por el usuario
    
    double sampleRate;

  };
// procesor dupliactor>> estereo


