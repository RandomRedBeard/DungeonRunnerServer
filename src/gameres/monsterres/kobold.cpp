/*
 * kobold.cpp
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#include "kobold.h"

kobold::kobold(objid* id, int lvl, const int hp, const int xp, const int maxdmg,
		const int mindmg, const int ac) :
		monster("Kobold", id, lvl, hp, xp, maxdmg, mindmg, ac) {
}

