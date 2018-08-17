/*
 * axe.h
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#ifndef AXE_H_
#define AXE_H_

#include "weapon.h"

class axe: public weapon {
public:
	axe(objid*, int, const int baseMax = 18, const int baseMin = 7);
};

#endif /* AXE_H_ */
