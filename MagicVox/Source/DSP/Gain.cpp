//
//  Gain.cpp
//  MagicVox
//
//  Created by Noelia Rego Cortes on 02/05/23.
//

#include "Gain.h"
//CREACION DE LA FUNCION GAIN. PARAMETROS Q RECIBE ES GANANCIA USUARIO
void Gain::setGain (float inGain) //DESARROLLO DE LA FUNCION Q ESTA YA EN HEADER
{
    gainValue = inGain; //ACTUALIZA EL VALOR DE LA VARIABLE GAINVALUE A INPUTVALUE DEL USUARIO
}
// 
void Gain::process (juce::AudioBuffer<float> &inBuffer)// creacion objeto llamado inBuffer
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    // POR CANAL. FOR (INICIALIZACION, CONDICION, ITERACION)
    {
        for (int i = 0; i < inBuffer.getNumSamples();  i++)
        // FOR QUE SIRVE PARA CONTAR CUANTOS BUFFERS TIENE EL CANAR (buffersize)
        {
            auto sample = inBuffer.getSample (channel, i); //OBTIENE EL VALOR DE LA MUESTRA EN EL CANAL Y MUESTRA ESPECIFICADA
            inBuffer.setSample(channel, i, gainValue * sample); //REALIZA LA OPERACION
        }
    }
}
