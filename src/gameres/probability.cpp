/*
 * probability.cpp
 *
 *  Created on: Mar 15, 2018
 *      Author: thomasjansen
 */

#include <stdio.h>
#include <stdlib.h>

#include "probability.h"

int prob(double p) {
	if (p == 0) {
		return false;
	}

	if (p >= 1) {
		return true;
	}

	int upperbound = 1;
	while (p < 1) {
		p *= 10;
		upperbound *= 10;
	}

	int rval = rand() % upperbound;
	return rval < p;
}


