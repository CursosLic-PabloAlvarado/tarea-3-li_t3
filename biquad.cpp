#include "biquad.h"
#include <cstring>


biquad::biquad() {
    std::cout << "mierdagrande";
    /*
    // Inicializar coeficientes y estados
    a = {1.0f, 0.0f, 0.0f};
    b = {1.0f, 0.0f, 0.0f};
    x = {0.0f, 0.0f};
    y = {0.0f, 0.0f};
    */

    b0 = 0.00012044276552320411;
    b1 = 0.00024088614702277451;
    b2 = 0.00012044338150272061;

    a1 = -1.8991886908811022;
    a2 = 0.90277707520710537;

    z1 = 0;
    z2 = 0;

} // Inicializa el filtro pasatodo por defecto

/*
biquad::biquad(double b0, double b1, double b2, double a1, double a2) : b0(b0), b1(b1), b2(b2), a1(a1), a2(a2), z1(0), z2(0) {
    std::cout << "JODEEER";
} // Inicializa el filtro con los coeficientes especificados
*/

biquad::~biquad() {
} // Destructor, actualmente no necesario pero definido por completitud

/*
void biquad::setCoefficients(const float* coeffs) {
    std::memcpy(b.data(), coeffs, 3 * sizeof(float));
    std::memcpy(a.data() + 1, coeffs + 3, 2 * sizeof(float));
    // Nota: a[0] siempre debe ser 1 para un filtro biquad normalizado
    a[0] = 1.0f;
}
*/

void biquad::reset() {
    /*x.fill(0.0f);
    y.fill(0.0f);*/
    z1 = 0;
    z2 = 0;
}

/*
void biquad::process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out) {
        for (jack_nframes_t i = 0; i < nframes; ++i) {
            //float input = in[i];
            //float output = b[0] * input + b[1] * x[0] + b[2] * x[1] - a[1] * y[0] - a[2] * y[1];
            
            //x[1] = x[0];
            //x[0] = input;
            //y[1] = y[0];
            //y[0] = output;

            double input = in[i];
            double output = b0 * input + z1;
            z1 = b1 * input - a1 * output + z2;
            z2 = b2 * input - a2 * output;
            
            out[i] = output;
        }
}*/



float biquad::process(float input) {
    double output = b0 * input + z1;
    z1 = b1 * input - a1 * output + z2;
    z2 = b2 * input - a2 * output;
    
    return output;
}


void biquad::switch_state() {
    isActive = !isActive;
    std::cout << "isActive: " << isActive << std::endl;
}