/*
  ==============================================================================

    Distorsion.h
    Created: 19 May 2023 7:11:45pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distorsion
{
public:
    Distorsion();
    ~Distorsion();
    void setGain (float inGain);
    void setDistortion (int inDistortionIndex);
    
    float softClipping (float inSample);
    
    void process (juce::AudioBuffer<float>& inBuffer);
private:
    int distortionIndex { 0 };
    float distortionGain { 1.0f };
};
