//
// Created by Andrea Semprebon on 27/05/17.
//

#ifndef FEES_SYSTEM_ADSPROPAGATIONANGULARVELOCITY_H
#define FEES_SYSTEM_ADSPROPAGATIONANGULARVELOCITY_H

class FEESADS;

class ADSPropagationAngularVelocity {
public:
    ADSPropagationAngularVelocity();

    bool Init();

    void Run(float w_m[3], float w_e[3]);

    /**
     * Sistema ADS centrale
     */
    FEESADS *ads;
};

#endif //FEES_SYSTEM_ADSPROPAGATIONANGULARVELOCITY_H
