//
// Created by Andrea Semprebon on 28/05/17.
//

#ifndef FEES_SYSTEM_ADSDYNAMICFILTERKINEMATIC_H
#define FEES_SYSTEM_ADSDYNAMICFILTERKINEMATIC_H

class FEESADS;

class ADSDynamicFilterKinematic {
public:
    ADSDynamicFilterKinematic();

    bool Init();
    void Run(float w[3], bool reset);

    FEESADS *ads;

    /**
     * OUTPUT
     */
    float y_n[4];

private:
    void ComputeMatrixOMEGA(float W[3], float OMEGA[4][4]);

    /**
     * Variabili di supporto
     */
    float mOMEGA[4][4];
    float y[4];

    /**
     * Forward Euler
     */
    bool old_reset;
    float y_n_old[4];

};
#endif //FEES_SYSTEM_ADSDYNAMICFILTERKINEMATIC_H
