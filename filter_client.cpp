#include "filter_client.h"
#include <cstring>

filter_client::filter_client(): 
      jack::client(),
      use_test_filter(false),
      use_main_filter(false)
{
    // Inicializar test_filter con coeficientes de ejemplo
    float test_coeffs[6] = {1.0f, -0.5f, 0.25f, 1.0f, 0.1f, 0.05f};
    test_filter.setCoefficients(test_coeffs);
}

filter_client::~filter_client() {
}

bool filter_client::process(jack_nframes_t nframes, 
                            const sample_t* const in,
                            sample_t* const out)  {
    if (use_test_filter) {
        test_filter.process(nframes, in, out);
    } else if (use_main_filter) {
        main_filter.process(nframes, in, out);
    } else {
        std::memcpy(out, in, nframes * sizeof(sample_t));
    }
    return true;
}

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

