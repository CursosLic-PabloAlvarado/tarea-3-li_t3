#include "filter_client.h"
#include <cstring>
#include <string>

filter_client::filter_client(){
}

filter_client::~filter_client() {
}

bool filter_client::process(jack_nframes_t nframes, const sample_t* const in, sample_t* const out)  {
    
    switch (current_state) {
        case State::Passthrough: {
            pt_client.process(nframes, in, out);
            break;
        }

        case State::Biquad: {
            bq_client.process(nframes, in, out);
            break;
        }

        case State::Cascade: {
            main_filter.process(nframes, in, out);
            break;
        }

        default: 
            pt_client.process(nframes, in, out);
            break;
    }
    
    return true;
}

void filter_client::change_state(State new_state) {
    current_state = new_state;
    std::cout << "State changed to " << static_cast<int>(new_state) << std::endl;
}

void filter_client::setCoefficients(float b0_, float b1_, float b2_, float a1_, float a2_) {
    bq_client.setCoefficients(b0_, b1_, b2_, a1_, a2_);
}

void filter_client::set_biquad(biquad &my_biquad) {
    bq_client = my_biquad;
}

void filter_client::set_cascade(cascade &my_cascade) {
    main_filter = my_cascade;
}
