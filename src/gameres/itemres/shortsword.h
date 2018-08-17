/*
 * shortsword.h
 *
 *  Created on: Apr 14, 2018
 *      Author: thomasjansen
 */

#ifndef SHORTSWORD_H_
#define SHORTSWORD_H_

#include "weapon.h"

class shortsword: public weapon {
public:
	shortsword(objid*, int, const int baseMax = 15, const int baseMin = 10);
};

#endif /* SHORTSWORD_H_ */
