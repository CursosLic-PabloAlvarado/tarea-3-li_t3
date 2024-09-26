#ifndef BIQUAD_H
#define BIQUAD_H

#include "jack_client.h"

class biquad : public jack::client{
    public:
        biquad();
        ~biquad();
        void set_coefficients(double a0, double a1, double a2, double b1, double b2);
        virtual bool process(jack_nframes_t nframes, const sample_t * const in, 
                             sample_t * const out) override;
    private:
        double a0;
        double a1;
        double a2;
        double b0;
        double b1;
        double b2;
        double x1, x2;
        double y1, y2;
}; 



#endif