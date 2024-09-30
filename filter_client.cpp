#include "filter_client.h"
#include <cstring>

filter_client::filter_client(): 
      jack::client(),
      current_state(State::Passthrough){
}

filter_client::~filter_client() {
}

bool filter_client::process(jack_nframes_t nframes, 
                            const sample_t* const in,
                            sample_t* const out)  {

    switch (current_state){
        case State::Passthrough:{
            pt_client.process(nframes, in, out);
            break;
        }

        case State::CascadeFilter:{
            cascade_filter.process(nframes, in, out);
            break;
        }
        
        default:
            pt_client.process(nframes, in, out);
            break;
    }
    return true;
}

void filter_client::set_filter_coeffs(const std::vector<std::vector<float>>& coeffs) {
    cascade_filter = cascade(coeffs);
}

void filter_client::change_state(State new_state) {
    current_state = new_state;
}
