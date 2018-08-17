/*
 * kobold.h
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#ifndef KOBOLD_H_
#define KOBOLD_H_

#include "monster.h"

class kobold: public monster {
public:
	kobold(objid*, int, const int hp = 50, const int xp = 25, const int maxdmg =
			12, const int mindmg = 8, const int ac = 5);
};

#endif /* KOBOLD_H_ */
