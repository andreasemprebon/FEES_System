//
// Created by Andrea Semprebon on 27/05/17.
//

#ifndef FEES_SYSTEM_ADSPROPAGATIONBLOCK_H
#define FEES_SYSTEM_ADSPROPAGATIONBLOCK_H

class FEESADS;

class ADSPropagationBlock {
public:
    ADSPropagationBlock();

    bool Init();

    void Run(float w[3], bool reset);

    /**
     * Output variable
     */
    float q_n[4];

    /**
     * Sistema ADS centrale
     */
    FEESADS *ads;

private:
    void ComputeMatrixOMEGA(float W[3], float OMEGA[4][4]);

    /**
     * Variabili di supporto
     */
    float mOMEGA[4][4];
    float q[4];

    /**
     * Forward Euler
     */
    bool old_reset;
    float y_n_old[4];

};

#endif //FEES_SYSTEM_ADSPROPAGATIONBLOCK_H
