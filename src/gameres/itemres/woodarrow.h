/*
 * woodarrow.h
 *
 *  Created on: May 18, 2018
 *      Author: thomasjansen
 */

#ifndef WOODARROW_H_
#define WOODARROW_H_

#include "arrow.h"

class woodarrow: public arrow {
public:
	woodarrow(objid*, int, int, const int baseMax = 3, const int baseMin = 1);
};

#endif /* WOODARROW_H_ */
