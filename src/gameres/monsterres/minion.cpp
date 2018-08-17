/*
 * minion.cpp
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#include "minion.h"

minion::minion(objid* id, int lvl, const int hp, const int xp, const int maxdmg,
		const int mindmg, const int ac) :
		monster("Minion", id, lvl, hp, xp, maxdmg, mindmg, ac) {
}

