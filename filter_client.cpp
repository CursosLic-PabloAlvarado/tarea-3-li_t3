#include "filter_client.h"
#include <cstring>
#include <iostream>

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
    std::cout << "Setting filter coefficients in the client:" << std::endl;
    for (const auto& set : coeffs) {
        std::cout << "Coefficients: ";
        for (auto coeff : set) {
            std::cout << coeff << " ";
        }
        std::cout << std::endl;
    }
    cascade_filter = cascade(coeffs);
}

void filter_client::change_state(State new_state) {
    current_state = new_state;
}
