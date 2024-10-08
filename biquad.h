#ifndef BIQUAD_H
#define BIQUAD_H

#include <jack/jack.h>
#include <array>

#include <iostream>

class biquad {
private:
    float b0, b1, b2;  // Coeficientes del numerador
    float a1, a2;      // Coeficientes del denominador (a0 siempre es 1 en la forma canónica)
    float z1, z2;      // Elementos de retardo (estados del filtro)

public:

    biquad();
    ~biquad();

    inline float process(float input);
    void reset();

    void setCoefficients(float b0_, float b1_, float b2_, float a1_, float a2_);

    void process(int nframes, const float* in, float* out);
};

#endif // BIQUAD_H