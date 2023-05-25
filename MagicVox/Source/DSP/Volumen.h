/*
  ==============================================================================

    Volumen.h
    Created: 24 May 2023 6:37:22pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Volumen
{
    public:
    
        Volumen();
        
        ~Volumen();
    
        void process (juce::AudioBuffer<float>& buffer, float volumenValue);
    
};
