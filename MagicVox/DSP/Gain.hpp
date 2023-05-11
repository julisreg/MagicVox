//
//  Gain.hpp
//  MagicVox
//
//  Created by Noelia Rego Cortes on 02/05/23.
//

#ifndef Gain_hpp
#define Gain_hpp

//#include <stdio.h>
#pragma once
#include <JuceHeader.h>

#endif /* Gain_hpp */

class Gain
{
public:
    void setGain (float inGain);
    void process (juce::AudioBuffer<float>& inBuffer);
private:
    float gainValue { 1.0f };
};

