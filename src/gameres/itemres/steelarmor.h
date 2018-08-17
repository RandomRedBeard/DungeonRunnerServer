/*
 * steelarmor.h
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#ifndef STEELARMOR_H_
#define STEELARMOR_H_

#include "armor.h"

class steelarmor: public armor {
public:
	steelarmor(objid*, int, const int baseAc = 12);
};

#endif /* STEELARMOR_H_ */
