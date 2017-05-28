//
// Created by Andrea Semprebon on 27/05/17.
//

#ifndef FEES_SYSTEM_ADSPROPAGATION_H
#define FEES_SYSTEM_ADSPROPAGATION_H

class ADSPropagationBlock;
class ADSPropagationBiasSavingLogic;
class ADSPropagationAngularVelocity;

class FEESSensors;
struct SensorFlag;

class FEESADS;

class ADSPropagation {
public:

    ADSPropagation();
    ~ADSPropagation();

    bool Init();

    void Propagate(float w[3], bool reset);

    void Run(float w_m[3], float q_e[4], float w_e[3], float bias_e[3], SensorFlag flag);

    /**
     * Sistema ADS centrale
     */
    FEESADS *ads;

    /**
     * Sistema sensori centrale
     */
    FEESSensors *sensors;

private:
    float w_minus_bias[3];

    ADSPropagationBlock             *adsPropagationBlock;
    ADSPropagationBiasSavingLogic   *adsPropagationBiasSavingLogic;
    ADSPropagationAngularVelocity   *adsPropagationAngularVelocity;

};

#endif //FEES_SYSTEM_ADSPROPAGATION_H
