//
// Created by Andrea Semprebon on 27/05/17.
//

#include "ADSPropagationBlock.h"
#include "ADS/FEESADS.h"
#include "Math/FEESMath.h"

ADSPropagationBlock::ADSPropagationBlock() {
    ads = NULL;
}

bool ADSPropagationBlock::Init() {

    if ( ads == NULL ) {
        return false;
    }

    /**
     * Inizializzo il vettore iniziale di output q_n tutto a 0.
     */
    q_n[0] = 0;
    q_n[1] = 0;
    q_n[2] = 0;
    q_n[3] = 0;

    /**
     * Inizializzo anche le altri variabili a 0
     */
    y_n_old[0] = 1;
    y_n_old[1] = 1;
    y_n_old[2] = 1;
    y_n_old[3] = 1;

    old_reset = 0;

    return true;
}

void ADSPropagationBlock::Run(float w[3], bool reset) {
    ComputeMatrixOMEGA(w, mOMEGA);

    // q = mOMEGA * q_old
    FEESMath::Matrix4x4MultiplyVector4x1(mOMEGA, y_n_old, q);

    // q = q * 0.5
    FEESMath::Vector4PerScalarInPlace(q, 0.5);

    /**
     * Integrazione Forward Euler ODE
     */

    // Se passo da 1 a 0, resetto l'integratore
    if (old_reset - reset == 1) {
        y_n_old[0] = ads->q_ads[0];
        y_n_old[1] = ads->q_ads[1];
        y_n_old[2] = ads->q_ads[2];
        y_n_old[3] = ads->q_ads[3];
    }

    q_n[0] = y_n_old[0] + kINTEGRATION_TIME * q[0];
    q_n[1] = y_n_old[1] + kINTEGRATION_TIME * q[1];
    q_n[2] = y_n_old[2] + kINTEGRATION_TIME * q[2];
    q_n[3] = y_n_old[3] + kINTEGRATION_TIME * q[3];

    /**
     * Mi salvo i vecchi valori
     */
    old_reset = reset;

    y_n_old[0] = q_n[0];
    y_n_old[1] = q_n[1];
    y_n_old[2] = q_n[2];
    y_n_old[3] = q_n[3];
}

void ADSPropagationBlock::ComputeMatrixOMEGA(float W[3], float OMEGA[4][4]) {
    OMEGA[0][0] = 0;
    OMEGA[0][1] = W[2];
    OMEGA[0][2] = -W[1];
    OMEGA[0][3] = W[0];

    OMEGA[1][0] = -W[2];
    OMEGA[1][1] = 0;
    OMEGA[1][2] = W[0];
    OMEGA[1][3] = W[1];

    OMEGA[2][0] = W[1];
    OMEGA[2][1] = -W[0];
    OMEGA[2][2] = 0;
    OMEGA[2][3] = W[2];

    OMEGA[3][0] = -W[0];
    OMEGA[3][1] = -W[1];
    OMEGA[3][2] = -W[2];
    OMEGA[3][3] = 0;
}
