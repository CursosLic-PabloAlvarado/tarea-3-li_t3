#ifndef BIQUAD_H
#define BIQUAD_H

#include <jack/jack.h>
#include <array>

class biquad {
private:
    std::array<float, 3> a; // Coeficientes del denominador
    std::array<float, 3> b; // Coeficientes del numerador
    std::array<float, 2> x; // Estado de entrada
    std::array<float, 2> y; // Estado de salida

public:
    biquad();
    ~biquad();

    void setCoefficients(const float* coeffs);
    void reset();
    void process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out);
};

#endif