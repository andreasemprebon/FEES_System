//
// Created by Andrea Semprebon on 28/05/17.
//

#ifndef FEES_SYSTEM_FEESDEBUG_H
#define FEES_SYSTEM_FEESDEBUG_H

#include "mbed.h"

class FEESDebug {
public:
    static void printf(const char *buf);
    static void printFloat(float num);
    static void printInt(int num);
    static void printVect(float *vec, int size);
};

#endif //FEES_SYSTEM_FEESDEBUG_H
