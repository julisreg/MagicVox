/*
  ==============================================================================

    Distorsion.cpp
    Created: 19 May 2023 7:11:45pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#include "Distorsion.h"

Distorsion::Distorsion()
{
        
}
Distorsion::~Distorsion()
{
    
}
//CREACION DE LA FUNCION Distorsion.
void Distorsion::setGain (float inGain) //DESARROLLO DE LA FUNCION Q ESTA YA EN HEADER
{
    distortionGain = inGain; //ACTUALIZA EL VALOR DE LA VARIABLE distortionIndex A INPUTVALUE DEL USUARIO
}
//
void Distorsion::setDistortion (int inDistortionIndex)
{
    distortionIndex = inDistortionIndex;
}
float Distorsion::softClipping (float inSample)
{
    float gainSample = distortionGain * inSample;
    return (gainSample) - (powf(gainSample, 3.0f) / 3.0f) ; //ecuacion para hacer softclipping
}

void Distorsion::process (juce::AudioBuffer<float> &inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples();  i++)
        {
            auto sample = inBuffer.getSample (channel, i);
            float processedSample;
            processedSample = softClipping (sample);
            
            inBuffer.setSample (channel, i, processedSample);
        }
    }
}
