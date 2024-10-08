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

    void addFilter(const biquad& filter); // Método para agregar un filtro biquad a la cascada
    inline float process(float input); // Método para procesar una muestra de entrada a través de la cascada
    
    void process(int nframes, const float* in, float* out);
    void reset(); // Resetea los estados de todos los biquads en cascada
};

#endif