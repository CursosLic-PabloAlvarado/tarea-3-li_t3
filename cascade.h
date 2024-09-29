#ifndef CASCADE_H
#define CASCADE_H

#include "biquad.h"
#include <vector>

class cascade {
private:
    std::vector<biquad> filters;

/*public:
    cascade();
    cascade(const std::vector<std::vector<float>>& coeffs);
    void process(jack_nframes_t nframes, const jack_default_audio_sample_t* in, jack_default_audio_sample_t* out);
};*/
public:
    void configure(const std::vector<std::vector<sample_t>>& coeffs);
    void process(jack_nframes_t nframes, const float* const in, float* const out);
};


#endif