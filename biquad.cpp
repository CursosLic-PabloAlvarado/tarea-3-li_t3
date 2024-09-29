#include "biquad.h"
#include <cstring>


biquad::biquad() {

    b0 = 0.9244465617731541;
    b1 = -1.8488882933267354;
    b2 = 0.92444173157881804;

    a1 = -1.918570032544294;
    a2 = 0.92450263188812298;

    z1 = 0;
    z2 = 0;

} // Inicializa el filtro pasatodo por defecto

biquad::~biquad() {
} // Destructor, actualmente no necesario pero definido por completitud

void biquad::reset() {
    z1 = 0;
    z2 = 0;
}


double biquad::process(float input) {
    double output = b0 * input + z1;
    z1 = b1 * input - a1 * output + z2;
    z2 = b2 * input - a2 * output;
    
    return output;
}

void biquad::set_coefficients(double b0, double b1, double b2, double a1, double a2) {
    this->b0 = b0;
    this->b1 = b1;
    this->b2 = b2;
    this->a1 = a1;
    this->a2 = a2;
    reset();
}