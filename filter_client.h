#ifndef FILTER_CLIENT_H
#define FILTER_CLIENT_H

#include "jack_client.h"
#include "passthrough_client.h"
#include "biquad.h"
#include "cascade.h"
#include <vector>

class filter_client : public jack::client {
private:
    biquad test_filter;
    cascade main_filter;
    bool use_test_filter;
    bool use_main_filter;

public:
    filter_client();
    ~filter_client() override;

    bool process(jack_nframes_t nframes, 
                 const jack_default_audio_sample_t* const in,
                 jack_default_audio_sample_t* const out) override;

    void set_test_filter_active(bool active);
    void set_main_filter_active(bool active);
    void set_filter_coeffs(const std::vector<std::vector<float>>& coeffs);
};

#endif