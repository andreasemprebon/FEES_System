//
// Created by Andrea Semprebon on 27/05/17.
//

#include "FEESADS.h"
#include "Propagation/ADSPropagation.h"
#include "DynamicFilter/ADSDynamicFilter.h"
#include "Sensors/FEESSensors.h"

#include "FEESDebug.h"

/**
 * Costruttore del sistema ADS di FEES
 * Il sistema avvia ed inizializza i seguenti blocchi:
 * - ADSPropagation
 */
FEESADS::FEESADS() {

    adsPropagation      = new ADSPropagation();
    adsDynamicFilter    = new ADSDynamicFilter();
}

bool FEESADS::Init() {
    bool result = true;

    if ( !sensors ) {
        return false;
    }

    adsPropagation->ads = this;
    adsPropagation->sensors = sensors;
    result = result && adsPropagation->Init();

    adsDynamicFilter->ads = this;
    result = result && adsDynamicFilter->Init();

    bias_ads[0] = 0;
    bias_ads[1] = 0;
    bias_ads[2] = 0;

    w_ads[0] = 0;
    w_ads[1] = 0;
    w_ads[2] = 0;

    q_ads[0] = 0;
    q_ads[1] = 0;
    q_ads[2] = 0;
    q_ads[3] = 1;

    bool_propagation = false;

    return result;

}

void FEESADS::Run(float q_m[4], float w_m[3]) {
    /**
     * @TODO: SENSORI
     */

    /**
     * Sono tutti valori STIMATI
     * OUTPUT:
     * - adsDynamicFilter->q_e;
     * - adsDynamicFilter->w_e;
     * - adsDynamicFilter->b_e;
     */

    FEESDebug::printf("Avvio adsDynamicFilter\n");
    adsDynamicFilter->Run(q_m, w_m, bool_propagation);
    FEESDebug::printf("Fine adsDynamicFilter\n");

    /**
     * Alla fine dell'esecuzione di propagation mi trovo nelle seguenti
     * variabili gli output:
     * - bias_ads
     * - q_ads
     * - w_ads
     */
    adsPropagation->Run(w_m, adsDynamicFilter->q_e, adsDynamicFilter->w_e, adsDynamicFilter->b_e, sensors->flag);
}

FEESADS::~FEESADS() {

    if ( adsPropagation ) {
        delete adsPropagation;
    }

    if ( adsDynamicFilter ) {
        delete adsDynamicFilter;
    }
}
