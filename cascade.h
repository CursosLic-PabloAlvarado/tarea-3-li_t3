#ifndef CASCADE_H
#define CASCADE_H

#include "biquad.h"
#include <vector>

class cascade {
private:
    std::vector<biquad> stages;

public:
    cascade();  // Constructor
    ~cascade(); // Destructor

    //cascade(const std::vector<std::vector<float>>& coeffs);


    //void process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out);

    void addFilter(const biquad& filter); // Método para agregar un filtro biquad a la cascada
    float process(float input); // Método para procesar una muestra de entrada a través de la cascada

    void reset(); // Resetea los estados de todos los biquads en cascada
};

#endif