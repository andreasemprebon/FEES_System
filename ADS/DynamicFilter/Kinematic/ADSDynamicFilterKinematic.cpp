//
// Created by Andrea Semprebon on 28/05/17.
//

#include "ADSDynamicFilterKinematic.h"
#include "ADS/FEESADS.h"
#include "Math/FEESMath.h"

#include "FEESDebug.h"

ADSDynamicFilterKinematic::ADSDynamicFilterKinematic() {
    ads = NULL;
}

bool ADSDynamicFilterKinematic::Init() {

    if ( ads == NULL ) {
        return false;
    }

    /**
     * Inizializzo il vettore iniziale di output y_n tutto a 0.
     */
    y_n[0] = 0;
    y_n[1] = 0;
    y_n[2] = 0;
    y_n[3] = 0;

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

void ADSDynamicFilterKinematic::Run(float w[3], bool reset) {
    ComputeMatrixOMEGA(w, mOMEGA);

    // y = mOMEGA * y_n_old
    FEESMath::Matrix4x4MultiplyVector4x1(mOMEGA, y_n_old, y);

    // y = y * 0.5
    FEESMath::Vector4PerScalarInPlace(y, 0.5);

    FEESDebug::printVect(y, 4);

    /**
     * Integrazione Forward Euler ODE
     */

    // Se passo da 0 a 1, resetto l'integratore
    if (reset - old_reset == 1) {
        y_n_old[0] = ads->q_ads[0];
        y_n_old[1] = ads->q_ads[1];
        y_n_old[2] = ads->q_ads[2];
        y_n_old[3] = ads->q_ads[3];
    }

    y_n[0] = y_n_old[0] + kINTEGRATION_TIME * y[0];
    y_n[1] = y_n_old[1] + kINTEGRATION_TIME * y[1];
    y_n[2] = y_n_old[2] + kINTEGRATION_TIME * y[2];
    y_n[3] = y_n_old[3] + kINTEGRATION_TIME * y[3];

    /**
     * Mi salvo i vecchi valori
     */
    old_reset = reset;

    y_n_old[0] = y_n[0];
    y_n_old[1] = y_n[1];
    y_n_old[2] = y_n[2];
    y_n_old[3] = y_n[3];

    FEESMath::Vector4NormalizeInPlace(y_n);
}

void ADSDynamicFilterKinematic::ComputeMatrixOMEGA(float W[3], float OMEGA[4][4]) {
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
