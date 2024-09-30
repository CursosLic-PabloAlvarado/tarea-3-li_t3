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
    biquad bq_client;
    cascade main_filter;

public:
    enum class State {
        Passthrough,
        Biquad,
        Cascade
    };

    State current_state;

    filter_client();
    ~filter_client();

    //virtual jack::client_state init() override;

    virtual bool process(jack_nframes_t nframes, 
                 const sample_t* const in,
                 sample_t* const out) override;

    void change_state(State new_state);
    void setCoefficients(double b0_, double b1_, double b2_, double a1_, double a2_);

    void set_biquad(biquad &my_biquad);
    void set_cascade(cascade &my_cascade);


    void set_filter_coeffs(const std::vector<std::vector<float>>& coeffs);
};

#endif

