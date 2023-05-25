/*
  ==============================================================================

    Compressor.cpp
    Created: 19 May 2023 10:25:32pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#include "Compressor.h"
Compressor::Compressor()
{
        
}
Compressor::~Compressor()
{
    
}

void Compressor::prepare(juce::dsp::ProcessSpec &spec)
{
    compressor.prepare(spec);
    
    compressor.setRatio(2.0f);
    compressor.setAttack(25.0f);
    compressor.setThreshold(-15.0f);
    compressor.setRelease(50.0f);
}



void Compressor::process (juce::AudioBuffer <float> buffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer); //crear audioblock apartir del buffer
    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock); //intermediario, contexto para los modulos de juce
    compressor.process(context);
}


void Compressor::setRatio(float newRatio)
{
    compressor.setRatio(newRatio); 
}

void Compressor::setAttack(float newAttack)
{
    compressor.setAttack(newAttack);
}

void Compressor::setThreshold(float newThreshold)
{
    compressor.setThreshold(newThreshold);
}

void Compressor::setRelease(float newRelease)
{
    compressor.setRelease(newRelease);
}
