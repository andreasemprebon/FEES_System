//
// Created by Andrea Semprebon on 27/05/17.
//

#include "ADSPropagationAngularVelocity.h"
#include "Math/FEESMath.h"
#include "ADS/FEESADS.h"

#define kGain 0.1

ADSPropagationAngularVelocity::ADSPropagationAngularVelocity() {
    ads = NULL;
}

/**
 * Se il sistema ADS non è collegato, allora ritorna falso,
 * altrimenti torna vero.
 * @return
 */
bool ADSPropagationAngularVelocity::Init() {
    if ( ads == NULL ) {
        return false;
    }

    return true;
}

void ADSPropagationAngularVelocity::Run(float w_m[3], float w_e[3]) {
    float w_e_minus_w_m[3];
    float n1;
    float n2;

    FEESMath::Vector3SubVector3(w_e, w_m, w_e_minus_w_m);

    n1 = FEESMath::Vector3EuclideanNorm(w_e_minus_w_m);
    n2 = FEESMath::Vector3EuclideanNorm(w_m) * kGain;

    if ( n1 < n2 ) {
        ads->w_ads[0] = w_e[0];
        ads->w_ads[1] = w_e[1];
        ads->w_ads[2] = w_e[2];
    } else {
        ads->w_ads[0] = w_m[0] - ads->bias_ads[0];
        ads->w_ads[1] = w_m[1] - ads->bias_ads[1];
        ads->w_ads[2] = w_m[2] - ads->bias_ads[2];
    }
}