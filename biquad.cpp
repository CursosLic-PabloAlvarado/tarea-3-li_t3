#include "biquad.h"

// Constructor para inicializar los coeficientes y estado
biquad::biquad() {}


// Implementación del método para procesar muestras
bool process(jack_nframes_t nframes, const sample_t * const in, sample_t * const out) {
    
    for (size_t i = 0; i < nframes; ++i) {
        // Filtrar la muestra actual
        double x0 = in[i];
        double y0 = (b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2) / a0;

        // Actualizar el estado
        x2 = x1;
        x1 = x0;
        y2 = y1;
        y1 = y0;

        // Guardar la salida
        out[i] = y0;
    }
}
