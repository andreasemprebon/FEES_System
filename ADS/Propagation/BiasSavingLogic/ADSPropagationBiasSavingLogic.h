//
// Created by Andrea Semprebon on 27/05/17.
//

#ifndef FEES_SYSTEM_ADSPROPAGATIONBIASSAVINGLOGIC_H
#define FEES_SYSTEM_ADSPROPAGATIONBIASSAVINGLOGIC_H

class FEESADS;

class FEESSensors;
struct SensorFlag;

class ADSPropagationBiasSavingLogic {
public:
    ADSPropagationBiasSavingLogic();

    bool Init();

    void Run(SensorFlag flag, float bias_e[3]);

    FEESADS *ads;

private:
    void Increment();

    /**
     * Variabili
     */
    float t_sens;
    float t_sens_old;

    float bias_old[3];
};

#endif //FEES_SYSTEM_ADSPROPAGATIONBIASSAVINGLOGIC_H
