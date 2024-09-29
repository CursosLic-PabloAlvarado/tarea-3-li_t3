#ifndef FILTER_CLIENT_H
#define FILTER_CLIENT_H

#include "jack_client.h"
#include "passthrough_client.h"
#include "biquad.h"
#include "cascade.h"
#include <vector>

class filter_client : public jack::client {
private:
    /*biquad test_filter;
    cascade main_filter;
    bool use_test_filter;
    bool use_main_filter;*/

    passthrough_client pt_client;
    biquad bq_client;

public:
    enum class State {
        Passthrough,
        Biquad
    };

    State current_state;

    filter_client();
    ~filter_client();

    //virtual jack::client_state init() override;

    virtual bool process(jack_nframes_t nframes, 
                 const sample_t* const in,
                 sample_t* const out) override;

    void change_state(State new_state);

    void set_test_filter_active(bool active);
    void set_main_filter_active(bool active);
    void set_filter_coeffs(const std::vector<std::vector<float>>& coeffs);
};

#endif

