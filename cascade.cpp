#include "cascade.h"
#include <cstring> // Añadimos esta línea para incluir memcpy


cascade::cascade() {
}

cascade::~cascade(){    
}

void cascade::addFilter(const biquad& filter) {
    stages.push_back(filter);
}

/*inline float cascade::process(float input) {
    float output = input;
    // Aplicar cada filtro biquad en serie
    for (auto& stage : stages) {
        output = stage.process(output);
    }
    return output;
}*/


void cascade::process(int nframes, const float* in, float* out) {
    std::memcpy(out, in, nframes * sizeof(float));
    for (auto& stage : stages) {
        stage.process(nframes, out, out);
    }
}

void cascade::reset() {
    for (auto& stage : stages) {
        stage.reset();
    }
}