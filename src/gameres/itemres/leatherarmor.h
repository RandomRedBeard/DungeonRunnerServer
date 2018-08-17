/*
 * leatherarmor.h
 *
 *  Created on: Apr 14, 2018
 *      Author: thomasjansen
 */

#ifndef LEATHERARMOR_H_
#define LEATHERARMOR_H_

#include "armor.h"

class leatherarmor: public armor {
public:
	leatherarmor(objid*, int, const int baseAc = 5);
};

#endif /* LEATHERARMOR_H_ */
