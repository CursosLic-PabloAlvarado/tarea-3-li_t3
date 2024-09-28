#include "cascade.h"
#include <cstring> // Añadimos esta línea para incluir memcpy


cascade::cascade() {
}

cascade::cascade(const std::vector<std::vector<float>>& coeffs) {
    stages.reserve(coeffs.size());
    for (const auto& stage_coeffs : coeffs) {
        biquad stage;
        stage.setCoefficients(stage_coeffs.data());
        stages.push_back(stage);
    }
}

void cascade::process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out) {
    if (stages.empty()) {
        memcpy(out, in, nframes * sizeof(jack_default_audio_sample_t));
        return;
    }

    if (stages.size() == 1) {
        stages[0].process(nframes, in, out);
        return;
    }

    std::vector<jack_default_audio_sample_t> temp(nframes);
    
    stages[0].process(nframes, in, temp.data());
    
    for (size_t i = 1; i < stages.size() - 1; ++i) {
        stages[i].process(nframes, temp.data(), temp.data());
    }
    stages.back().process(nframes, temp.data(), out);  
}

bool cascade::is_empty() const {
    return stages.empty();
}
