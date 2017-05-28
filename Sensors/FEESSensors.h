//
// Created by Andrea Semprebon on 28/05/17.
//

#ifndef FEES_SYSTEM_FEESSENSORS_H
#define FEES_SYSTEM_FEESSENSORS_H

struct SensorFlag {
    bool sunFine;
    bool sunCoarse;
    bool magneticField;
    bool earth;
};

class FEESSensors {
public:
    FEESSensors();

    int numberOfWorkingSensor();

    /**
     * Variabili
     */
    SensorFlag flag;
};

#endif //FEES_SYSTEM_FEESSENSORS_H
