#ifndef FILTER_CLIENT_H
#define FILTER_CLIENT_H

#include "jack_client.h"
#include "passthrough_client.h"
#include "biquad.h"
#include "cascade.h"
#include <vector>

class filter_client : public jack::client {
private:
    passthrough_client pt_client;
    cascade cascade_filter;

public:
    enum class State {
        Passthrough,
        CascadeFilter
    };

    filter_client();
    ~filter_client();

    State current_state;

    //virtual jack::client_state init() override;

    virtual bool process(jack_nframes_t nframes, 
                 const sample_t* const in,
                 sample_t* const out) override;

    void change_state(State new_state); 
    void set_filter_coeffs(const std::vector<std::vector<float>>& coeffs); // TODO 
};

#endif

