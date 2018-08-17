/*
 * ironarmor.h
 *
 *  Created on: Apr 15, 2018
 *      Author: thomasjansen
 */

#ifndef IRONARMOR_H_
#define IRONARMOR_H_

#include "armor.h"

class ironarmor: public armor {
public:
	ironarmor(objid*, int, const int baseAc = 8);
};

#endif /* IRONARMOR_H_ */
