/*
  ==============================================================================

    Eq.cpp
    Created: 13 May 2023 12:18:33pm
    Author:  Julieth Noelia Rego Cortes

  ==============================================================================
*/

#include "Eq.h"

Eq::Eq()
{
    
}
Eq::~Eq()
{
    
}

//{
//    NormalisableRange<float>;
//
//}
void Eq::prepare (juce::dsp::ProcessSpec& spec) //processspec clase contiene: variable sample rate, buffersize y no. canales), PREPARAR EL FILTRO.
{
    sampleRate = spec.sampleRate;
    
    //PREPARACION : El prepare solo se llama una vez
    highShelfFilter.prepare(spec);
        
    
    // DATOS : aqui es donde se modifica los parametros. Actualizacion.
    highShelfFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighShelf(spec.sampleRate, 7000.0f, 0.5f, 2.0f);
    // ACTUALIZAR PARAMETROS POR EL USUARIO
    
}
void Eq::process (juce::AudioBuffer <float> buffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer); //crear audioblock apartir del buffer
    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock); //intermediario, contexto para los modulos de juce
    highShelfFilter.process(context);


}
void Eq::updateFilter(float Q, float gainFactorEq)
{
    highShelfFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 7000.0f, Q, gainFactorEq);
}
