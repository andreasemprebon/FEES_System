//
// Created by Andrea Semprebon on 28/05/17.
//

#ifndef FEES_SYSTEM_ADSDYNAMICFILTEROBSERVER_H
#define FEES_SYSTEM_ADSDYNAMICFILTEROBSERVER_H

class ADSDynamicFilterObserver {
public:
    ADSDynamicFilterObserver();

    bool Init();

    void Run(float q_m[4], float q_e[4]);

    float kpsv[3];
    float kisv[3];
};

#endif //FEES_SYSTEM_ADSDYNAMICFILTEROBSERVER_H
