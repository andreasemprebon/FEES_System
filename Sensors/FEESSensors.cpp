//
// Created by Andrea Semprebon on 28/05/17.
//

#include "FEESSensors.h"

FEESSensors::FEESSensors() {
    flag.sunFine        = true;
    flag.sunCoarse      = true;
    flag.earth          = true;
    flag.magneticField  = true;
}

int FEESSensors::numberOfWorkingSensor() {
    return flag.sunFine + flag.sunCoarse + flag.earth + flag.magneticField;
}