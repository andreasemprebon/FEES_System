//
// Created by Andrea Semprebon on 28/05/17.
//

#ifndef FEES_SYSTEM_ADSDYNAMICFILTER_H
#define FEES_SYSTEM_ADSDYNAMICFILTER_H

class ADSDynamicFilterKinematic;
class ADSDynamicFilterObserver;

class FEESADS;

class ADSDynamicFilter {
public:
    ADSDynamicFilter();
    ~ADSDynamicFilter();

    bool Init();
    void Run(float q_m[4], float w_m[3], bool propagating);

    FEESADS *ads;

    /**
     * Output Filtro Dinamico
     */
    float w_e[3];
    float q_e[4];
    float b_e[3];

private:

    float w[3];
    float bias_old[3];

    ADSDynamicFilterKinematic   *adsDynamicFilterKinematic;
    ADSDynamicFilterObserver    *adsDynamicFilterObserver;
};

#endif //FEES_SYSTEM_ADSDYNAMICFILTER_H
