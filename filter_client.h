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
    //biquad bq_client;
    cascade cascade_filter; // TODO: Usar para implementar cascade

public:
    enum class State {
        Passthrough,
        CascadeFilter 
    };

    State current_state;

    filter_client();
    ~filter_client();

    //virtual jack::client_state init() override;

    virtual bool process(jack_nframes_t nframes, 
                 const sample_t* const in,
                 sample_t* const out) override;

    void change_state(State new_state);

    // Modificar esta función para configurar la cascada de filtros
    void set_filter_coeffs(const std::vector<std::vector<sample_t>>& coeffs);
};

#endif

