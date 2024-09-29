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

        case State::CascadeFilter: {
            cascade_filter.process(nframes, in, out);
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


void filter_client::set_filter_coeffs(const std::vector<std::vector<sample_t>>& coeffs) {
    cascade_filter.configure(coeffs);
    std::cout << "Cascade filter configured with " << coeffs.size() << " stages." << std::endl;
}

// TODO: Usar para implementar cascade
/*
void filter_client::set_filter_coeffs(const std::vector<std::vector<float>>& coeffs) {
    main_filter = cascade(coeffs);
}
*/