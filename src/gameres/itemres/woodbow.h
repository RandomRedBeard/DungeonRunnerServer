/*
 * woodbow.h
 *
 *  Created on: May 18, 2018
 *      Author: thomasjansen
 */

#ifndef WOODBOW_H_
#define WOODBOW_H_

#include "bow.h"

class woodbow: public bow {
public:
	woodbow(objid*, int, const int baseMax = 3, const int baseMin = 1,
			const int rangeMax = 7, const int rangeMin = 4);
};

#endif /* WOODBOW_H_ */
