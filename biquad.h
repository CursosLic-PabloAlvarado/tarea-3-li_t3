#ifndef BIQUAD_H
#define BIQUAD_H

#include <jack/jack.h>
#include <array>

#include <iostream>

class biquad {
private:
    double b0, b1, b2;  // Coeficientes del numerador
    double a1, a2;      // Coeficientes del denominador (a0 siempre es 1 en la forma canónica)
    double z1, z2;      // Elementos de retardo (estados del filtro)

public:

    biquad();
    ~biquad();

    //void setCoefficients(const float* coeffs);
    
    float process(float input);
    void reset();

    void switch_state();
};

#endif // BIQUAD_H