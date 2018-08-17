/*
 * minion.h
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#ifndef MINION_H_
#define MINION_H_

#include "monster.h"

class minion: public monster {
public:
	minion(objid*, int, const int hp = 25, const int xp = 10, const int maxdmg =
			7, const int mindmg = 4, const int ac = 2);
};

#endif /* MINION_H_ */
