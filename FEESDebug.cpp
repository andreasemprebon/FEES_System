//
// Created by Andrea Semprebon on 28/05/17.
//

#include "FEESDebug.h"
#include "Math/FEESMath.h"

Serial pc(SERIAL_TX, SERIAL_RX);

void FEESDebug::printf(const char *buf) {
    pc.printf(buf);
}

void FEESDebug::printFloat(float num) {
    char _tmp_buf[20];
    FEESMath::ftos(_tmp_buf, num);
    pc.printf("%s", _tmp_buf);
}

void FEESDebug::printInt(int num) {
    pc.printf("%i", num);
}

void FEESDebug::printVect(float *vec, int size) {
	int i;
	pc.printf("[ ");
	for (i = 0; i < size-1; i++) {
		printFloat(vec[i]);
		pc.printf(", ");
	}
	printFloat(vec[i]);
	pc.printf(" ]\n");
}
