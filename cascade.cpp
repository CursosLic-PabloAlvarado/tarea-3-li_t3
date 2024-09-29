#include "cascade.h"
#include <cstring> // Añadimos esta línea para incluir memcpy


cascade::cascade() {
}

void cascade::configure(const std::vector<std::vector<double>>& coeffs) {
    filters.clear();
    for (const auto& coeff : coeffs) {
        biquad filter;
        filter.set_coefficients(coeff[0], coeff[1], coeff[2], coeff[3], coeff[4]);
        filters.push_back(filter);
    }
}

void cascade::process(jack_nframes_t nframes, const float* const in, float* const out) {
    if (filters.empty()) {
        std::memcpy(out, in, nframes * sizeof(float));
        return;
    }

    for (jack_nframes_t i = 0; i < nframes; ++i) {
        float sample = in[i];
        for (auto& filter : filters) {
            sample = filter.process(sample);
        }
        out[i] = sample;
    }
}

/*
cascade::cascade(const std::vector<std::vector<float>>& coeffs) {
    stages.reserve(coeffs.size());
    for (const auto& stage_coeffs : coeffs) {
        biquad stage;
        stage.setCoefficients(stage_coeffs.data());
        stages.push_back(stage);
    }
}

void cascade::process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out) {
    std::vector<jack_default_audio_sample_t> temp(nframes);
    
    stages[0].process(nframes, in, temp.data());
    
    for (size_t i = 1; i < stages.size() - 1; ++i) {
        stages[i].process(nframes, temp.data(), temp.data());
    }
    
    if (stages.size() > 1) {
        stages.back().process(nframes, temp.data(), out);
    } else {
        memcpy(out, temp.data(), nframes * sizeof(jack_default_audio_sample_t));
    }
}
*/