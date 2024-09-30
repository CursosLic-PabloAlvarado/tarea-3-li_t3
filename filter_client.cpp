#include "filter_client.h"
#include <cstring>
#include <string>

filter_client::filter_client(){

}


/*
filter_client::filter_client(): 
      jack::client(),
      use_test_filter(false),
      use_main_filter(false)
{
    // Inicializar test_filter con coeficientes de ejemplo
    float test_coeffs[6] = {1.0f, -0.5f, 0.25f, 1.0f, 0.1f, 0.05f};
    test_filter.setCoefficients(test_coeffs);
}
*/

filter_client::~filter_client() {
}


bool filter_client::process(jack_nframes_t nframes, const sample_t* const in, sample_t* const out)  {
    
    switch (current_state) {
        case State::Passthrough: {
            pt_client.process(nframes, in, out);
            break;
        }

        case State::Biquad: {
            for (jack_nframes_t i = 0; i < nframes; ++i) {
                out[i] = bq_client.process(in[i]);
            }
            //bq_client.process(nframes, in, out);
            break;
        }

        case State::Cascade: {
            for (jack_nframes_t i = 0; i < nframes; ++i) {
                out[i] = main_filter.process(in[i]);
            }
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

void filter_client::setCoefficients(double b0_, double b1_, double b2_, double a1_, double a2_) {
    bq_client.setCoefficients(b0_, b1_, b2_, a1_, a2_);
}




// TODO: Usar para implementar cascade
/*
void filter_client::set_filter_coeffs(const std::vector<std::vector<float>>& coeffs) {
    main_filter = cascade(coeffs);
}
*/