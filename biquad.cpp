#include "biquad.h"
#include <cstring>

biquad::biquad() {
    // Inicializar coeficientes y estados
    a = {1.0f, 0.0f, 0.0f};
    b = {1.0f, 0.0f, 0.0f};
    x = {0.0f, 0.0f};
    y = {0.0f, 0.0f};
}

biquad::~biquad() {
}

void biquad::setCoefficients(const float* coeffs) {
    std::memcpy(b.data(), coeffs, 3 * sizeof(float));
    std::memcpy(a.data() + 1, coeffs + 3, 2 * sizeof(float));
    // Nota: a[0] siempre debe ser 1 para un filtro biquad normalizado
    a[0] = 1.0f;
}

void biquad::reset() {
    x.fill(0.0f);
    y.fill(0.0f);
}

void biquad::process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out) {
    for (jack_nframes_t i = 0; i < nframes; ++i) {
        float input = in[i];
        float output = b[0] * input + b[1] * x[0] + b[2] * x[1] - a[1] * y[0] - a[2] * y[1];
        
        x[1] = x[0];
        x[0] = input;
        y[1] = y[0];
        y[0] = output;
        
        out[i] = output;
    }
}