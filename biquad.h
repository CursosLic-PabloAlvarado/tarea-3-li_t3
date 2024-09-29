#ifndef BIQUAD_H
#define BIQUAD_H

#include <jack/jack.h>
#include <array>

#include <iostream>

class biquad {
private:
    /*
    std::array<float, 3> a; // Coeficientes del denominador
    std::array<float, 3> b; // Coeficientes del numerador
    std::array<float, 2> x; // Estado de entrada
    std::array<float, 2> y; // Estado de salida
    */
    double b0, b1, b2;  // Coeficientes del numerador
    double a1, a2;      // Coeficientes del denominador (a0 siempre es 1 en la forma canónica)
    double z1, z2;      // Elementos de retardo (estados del filtro)

    bool isActive = false;

public:

    biquad();
    biquad(double b0, double b1, double b2, double a1, double a2);  // Constructor para inicializar coeficientes
    ~biquad();

    //void setCoefficients(const float* coeffs);
    
    //void process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out);
    float process(float input);
    void reset();

    void switch_state();
};

#endif // BIQUAD_H