#include "biquad.h"
#include <cstring>

biquad::biquad() {
    // Passthrough
    b0 = 1;
    b1 = 1;
    b2 = 1;

    a1 = 1;
    a2 = 1;
    
    z1 = 0;
    z2 = 0;
    
} // Inicializa el filtro pasatodo por defecto

biquad::~biquad() {
} 

void biquad::setCoefficients(float b0_, float b1_, float b2_, float a1_, float a2_) {
    b0 = b0_;
    b1 = b1_;
    b2 = b2_;
    a1 = a1_;
    a2 = a2_;
    reset();  // Opcionalmente resetear los estados al cambiar coeficientes
}

void biquad::reset() {
    z1 = 0;
    z2 = 0;
}

inline float biquad::process(float input) {
    double output = b0 * input + z1;
    z1 = b1 * input - a1 * output + z2;
    z2 = b2 * input - a2 * output;
    
    return output;
}

// Nuevo método para procesar múltiples muestras
void biquad::process(int nframes, const float* in, float* out) {
    for (int i = 0; i < nframes; ++i) {
        out[i] = process(in[i]);
    }
}