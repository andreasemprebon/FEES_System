//
// Created by Andrea Semprebon on 27/05/17.
//

#ifndef FEES_SYSTEM_FEESADS_H
#define FEES_SYSTEM_FEESADS_H

class ADSPropagation;
class ADSDynamicFilter;
class FEESSensors;

class FEESADS {
public:
    FEESADS();
    ~FEESADS();

    bool Init();

    void Run(float q_m[4], float w_m[3]);

    /**
     * Variabili globali sistema ADS
     */
    float 	q_ads[4];
    float 	bias_ads[3];
    float 	w_ads[3];
    bool 	bool_propagation;

    /**
     * Componenti base del sistema ADS
     */
    ADSPropagation *adsPropagation;
    ADSDynamicFilter *adsDynamicFilter;

    /**
     * Sensori
     */
    FEESSensors *sensors;


};

#endif //FEES_SYSTEM_FEESADS_H
