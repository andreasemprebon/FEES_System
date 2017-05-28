//
// Created by Andrea Semprebon on 27/05/17.
//

#include "ADSPropagationBiasSavingLogic.h"
#include <math.h>
#include "ADS/FEESADS.h"
#include "Sensors/FEESSensors.h"

#define FLT_EPSILON 0.00001
#define FLT_MAX 10000

ADSPropagationBiasSavingLogic::ADSPropagationBiasSavingLogic() {
    ads = NULL;
}

bool ADSPropagationBiasSavingLogic::Init() {

    if ( ads == NULL ) {
        return false;
    }

    bias_old[0] = 0;
    bias_old[1] = 0;
    bias_old[2] = 0;

    t_sens      = 0;
    t_sens_old  = 0;

    return true;
}


void ADSPropagationBiasSavingLogic::Run(SensorFlag flag, float bias_e[3]) {

    if ( flag.sunFine && flag.magneticField ) {
        //Forse posso propagare il bias

        this->Increment();

        if ( t_sens > t_sens_old ) {
            //Passo il bias PROPAGATO
            ads->bias_ads[0] = bias_e[0];
            ads->bias_ads[1] = bias_e[1];
            ads->bias_ads[2] = bias_e[2];

            //Aggiorno la variabile bias_old con l'ultimo valore di bias passato
            bias_old[0] = ads->bias_ads[0];
            bias_old[1] = ads->bias_ads[1];
            bias_old[2] = ads->bias_ads[2];

        } else {
            //Passo il VECCHIO bias
            ads->bias_ads[0] = bias_old[0];
            ads->bias_ads[1] = bias_old[1];
            ads->bias_ads[2] = bias_old[2];
        }

    } else {
        //Passo il VECCHIO bias
        ads->bias_ads[0] = bias_old[0];
        ads->bias_ads[1] = bias_old[1];
        ads->bias_ads[2] = bias_old[2];

        //Il vecchio valore del tempo per il quale il sensore e' rimasto accesso
        //viene aggiornato solamente se il nuovo tempo e' maggiore del tempo
        //precesente, altrimenti rimane invariato
        t_sens_old = fmaxf(t_sens_old, t_sens);
    }

}

/**
 * @TODO: Dobbiamo gestire in maniera diversa l'overflow oppure va bene cosi?
 */
void ADSPropagationBiasSavingLogic::Increment() {

    t_sens = t_sens + FLT_EPSILON;

    if ( t_sens < 0 ) {
        t_sens = FLT_MAX;
    }

}

