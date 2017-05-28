//
// Created by Andrea Semprebon on 27/05/17.
//

#include "ADSPropagation.h"
#include "ADS/FEESADS.h"
#include "Math/FEESMath.h"
#include "Block/ADSPropagationBlock.h"
#include "BiasSavingLogic/ADSPropagationBiasSavingLogic.h"
#include "AngularVelocity/ADSPropagationAngularVelocity.h"
#include "Sensors/FEESSensors.h"

ADSPropagation::ADSPropagation() {
    adsPropagationBlock             = NULL;
    adsPropagationBiasSavingLogic   = NULL;
    adsPropagationAngularVelocity   = NULL;

    ads       = NULL;
    sensors   = NULL;
}

bool ADSPropagation::Init() {
    bool result = true;

    // Se il sistema ADS non è ancora collegato non posso
    // inizializzare gli altri sistemi, quindi ritorno errore
    if ( ads == NULL ) {
        return false;
    }

    // Se non ho a disposizione la gestione dei sensori, non posso attivare il sistema
    if ( sensors == NULL ) {
        return false;
    }

    // Se il sistema è già inizializzato non lo reinizializzo,
    // altrimenti avrei un memory leak.
    // @TODO: Aggiungere una force Init() dove tutti i sistemi sono rimossi e dopo ricreati

    if ( adsPropagationBlock == NULL ) {
        // Creo l'istanza del blocco propagazione e gli associo l'ADS
        adsPropagationBlock = new ADSPropagationBlock();
        adsPropagationBlock->ads = ads;

        result = result && adsPropagationBlock->Init();
    }

    if ( adsPropagationBiasSavingLogic == NULL ) {
        // Istanza della propagazione del bias
        adsPropagationBiasSavingLogic = new ADSPropagationBiasSavingLogic();
        adsPropagationBiasSavingLogic->ads = ads;

        result = result && adsPropagationBiasSavingLogic->Init();
    }

    if ( adsPropagationAngularVelocity == NULL ) {
        adsPropagationAngularVelocity = new ADSPropagationAngularVelocity();
        adsPropagationAngularVelocity->ads = ads;

        result = result && adsPropagationAngularVelocity->Init();
    }

    return result;
}

void ADSPropagation::Run(float w_m[3], float q_e[4], float w_e[3], float bias_e[3], SensorFlag flag) {

    /**
     * Calcolo il bias
     */
    adsPropagationBiasSavingLogic->Run(flag, bias_e);

    /**
     * Calcolo la velocita' angolare
     */
    adsPropagationAngularVelocity->Run(w_m, w_e);

    /**
     * Sottraggo il bias alla velocita'
     */
    FEESMath::Vector3SubVector3(w_m, ads->bias_ads, w_minus_bias);

    /**
     * DECISIONI SULLA PROPAGAZIONE
     */

    /**
     * Propago
     */
    if ( !flag.sunCoarse && !flag.sunFine ) {
        Propagate(w_minus_bias, ads->bool_propagation);
        return;
    }

    if ( sensors->numberOfWorkingSensor() < 2 ) {
        Propagate(w_minus_bias, ads->bool_propagation);
        return;
    }

    /**
     * Stimata
     */
    ads->q_ads[0] = q_e[0];
    ads->q_ads[1] = q_e[1];
    ads->q_ads[2] = q_e[2];
    ads->q_ads[3] = q_e[3];

}

/**
 * In caso in cui si decida di propagare, il blocco di propagazione viene attivato
 * ed è chiamato in questa funzione
 * @param w
 * @param reset
 */
void ADSPropagation::Propagate(float w[3], bool reset) {
    adsPropagationBlock->Run(w, reset);

    // Copio i risultati del propagatore all'interno dell'ADS
    ads->q_ads[0] = adsPropagationBlock->q_n[0];
    ads->q_ads[1] = adsPropagationBlock->q_n[1];
    ads->q_ads[2] = adsPropagationBlock->q_n[2];
    ads->q_ads[3] = adsPropagationBlock->q_n[3];
}

/**
 * Distruggo anche tutte le istanze create degli altri sistemi
 */
ADSPropagation::~ADSPropagation() {
    if ( adsPropagationBlock != NULL ) {
        delete adsPropagationBlock;
    }

    if ( adsPropagationBiasSavingLogic != NULL ) {
        delete adsPropagationBiasSavingLogic;
    }

    if ( adsPropagationAngularVelocity != NULL ) {
        delete adsPropagationAngularVelocity;
    }
}
