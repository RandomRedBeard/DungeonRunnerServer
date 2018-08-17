/*
 * longsword.h
 *
 *  Created on: Apr 14, 2018
 *      Author: thomasjansen
 */

#ifndef LONGSWORD_H_
#define LONGSWORD_H_

#include "weapon.h"

class longsword: public weapon {
public:
	longsword(objid*, int l, const int baseMax = 21, const int baseMin = 4);
};

#endif /* LONGSWORD_H_ */
