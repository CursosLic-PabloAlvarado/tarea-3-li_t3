#include "cascade.h"
#include <cstring> // Añadimos esta línea para incluir memcpy


cascade::cascade() {
}

cascade::~cascade(){    
}

void cascade::addFilter(const biquad& filter) {
    stages.push_back(filter);
}

float cascade::process(float input) {
    float output = input;
    // Aplicar cada filtro biquad en serie
    for (auto& stage : stages) {
        output = stage.process(output);
    }
    return output;
}

void cascade::reset() {
    for (auto& stage : stages) {
        stage.reset();
    }
}