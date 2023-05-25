/*
  ==============================================================================

    Volumen.cpp
    Created: 24 May 2023 6:37:22pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#include "Volumen.h"

Volumen::Volumen() {}

Volumen::~Volumen() {}

void Volumen::process (juce::AudioBuffer<float>& buffer, float volumenValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Get sample
            float sample = buffer.getSample (channel, i);
            
            // Process and set new sample
            buffer.setSample (channel, i, sample * volumenValue);
        }
    }
}
