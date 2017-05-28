//
// Created by Andrea Semprebon on 28/05/17.
//

#include "ADSDynamicFilter.h"
#include "Kinematic/ADSDynamicFilterKinematic.h"
#include "Observer/ADSDynamicFilterObserver.h"
#include "ADS/FEESADS.h"
#include "Math/FEESMath.h"

#include "FEESDebug.h"

ADSDynamicFilter::ADSDynamicFilter() {
    adsDynamicFilterObserver    = NULL;
    adsDynamicFilterKinematic   = NULL;

    ads = NULL;
}

bool ADSDynamicFilter::Init() {
    bool result = true;

    // Se il sistema ADS non è inizializzato, ritorno falso ed esco
    if ( ads == NULL ) {
        return false;
    }

    if ( adsDynamicFilterObserver == NULL ) {
        adsDynamicFilterObserver = new ADSDynamicFilterObserver();
        result = result && adsDynamicFilterObserver->Init();
    }

    if ( adsDynamicFilterKinematic == NULL ) {
        adsDynamicFilterKinematic = new ADSDynamicFilterKinematic();
        adsDynamicFilterKinematic->ads = ads;
        result = result && adsDynamicFilterKinematic->Init();
    }

    w_e[0] = 0;
    w_e[1] = 0;
    w_e[2] = 0;

    q_e[0] = 0;
    q_e[1] = 0;
    q_e[2] = 0;
    q_e[3] = 1;

    b_e[0] = 0;
    b_e[1] = 0;
    b_e[2] = 0;

    bias_old[0] = 0;
    bias_old[1] = 0;
    bias_old[2] = 0;

    w[0] = 0;
    w[1] = 0;
    w[2] = 0;

    return result;
}

void ADSDynamicFilter::Run(float q_m[4], float w_m[3], bool propagating) {
    //Preparazione del vettore w

    FEESMath::Vector3Clone(w_m, w);
    FEESMath::Vector3SubVector3InPlace(w, b_e);
    FEESMath::Vector3AddVector3InPlace(w, adsDynamicFilterObserver->kpsv);

    /**
     * Lancio il blocco Kinematic
     * OUTPUT: adsDynamicFilterKinematic->y_n;
     */
    FEESDebug::printf("Start adsDynamicFilterKinematic\n");
    adsDynamicFilterKinematic->Run(w, propagating);
    FEESDebug::printf("End adsDynamicFilterKinematic\n");

    /**
     * OUTPUT q_e
     */
    q_e[0] = adsDynamicFilterKinematic->y_n[0];
    q_e[1] = adsDynamicFilterKinematic->y_n[1];
    q_e[2] = adsDynamicFilterKinematic->y_n[2];
    q_e[3] = adsDynamicFilterKinematic->y_n[3];

    /**
     * Lancio il blocco Observer
     * OUTPUT:  - adsDynamicFilterObserver->kpsv
     *          - adsDynamicFilterObserver->kisv
     */
    FEESDebug::printf("Start adsDynamicFilterObserver\n");
    adsDynamicFilterObserver->Run(q_m, q_e);
    FEESDebug::printf("End adsDynamicFilterObserver\n");

    /**
     * INTEGRAZIONE DEL BIAS
     * Eulero in avanti
     */

    /**
     * OUTPUT b_e
     */
    b_e[0] = bias_old[0] + kINTEGRATION_TIME * adsDynamicFilterObserver->kisv[0];
    b_e[1] = bias_old[1] + kINTEGRATION_TIME * adsDynamicFilterObserver->kisv[1];
    b_e[2] = bias_old[2] + kINTEGRATION_TIME * adsDynamicFilterObserver->kisv[2];

    // Salvo i valori vecchi
    bias_old[0] = b_e[0];
    bias_old[1] = b_e[1];
    bias_old[2] = b_e[2];

    /**
     * OUTPUT w_e
     */
    w_e[0] = w_m[0] - b_e[0];
    w_e[1] = w_m[1] - b_e[1];
    w_e[2] = w_m[2] - b_e[2];

}

ADSDynamicFilter::~ADSDynamicFilter() {

    if ( adsDynamicFilterObserver != NULL ) {
        delete adsDynamicFilterObserver;
    }

    if ( adsDynamicFilterKinematic != NULL ) {
        delete adsDynamicFilterKinematic;
    }
}
