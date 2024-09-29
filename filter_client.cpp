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

        default: 
            pt_client.process(nframes, in, out);
            break;
    }
    /*if (use_test_filter) {
        test_filter.process(nframes, in, out);
    } else if (use_main_filter) {
        main_filter.process(nframes, in, out);
    } else {
        std::memcpy(out, in, nframes * sizeof(sample_t));
    }*/
    return true;
}

void filter_client::change_state(State new_state) {
    current_state = new_state;
    std::cout << "State changed to " << static_cast<int>(new_state) << std::endl;
}

/*
void filter_client::set_test_filter_active(bool active) {
    use_test_filter = active;
    if (active) {
        use_main_filter = false;
    }
}

void filter_client::set_main_filter_active(bool active) {
    use_main_filter = active;
    if (active) {
        use_test_filter = false;
    }
}

void filter_client::set_filter_coeffs(const std::vector<std::vector<float>>& coeffs) {
    main_filter = cascade(coeffs);
}
*/