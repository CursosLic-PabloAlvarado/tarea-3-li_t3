#include "biquad.h"
#include <cstring>


biquad::biquad() {
    /*
    // Inicializar coeficientes y estados
    a = {1.0f, 0.0f, 0.0f};
    b = {1.0f, 0.0f, 0.0f};
    x = {0.0f, 0.0f};
    y = {0.0f, 0.0f};
    */

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
} // Destructor, actualmente no necesario pero definido por completitud


void biquad::setCoefficients(double b0_, double b1_, double b2_, double a1_, double a2_) {
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


float biquad::process(float input) {
    double output = b0 * input + z1;
    z1 = b1 * input - a1 * output + z2;
    z2 = b2 * input - a2 * output;
    
    return output;
}