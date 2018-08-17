/*
 * bow.cpp
 *
 *  Created on: May 18, 2018
 *      Author: thomasjansen
 */

#include "bow.h"

bow::bow(const char* name_t, objid* id, int lvl, int mxd, int mnd, int rxd,
		int rnd) :
		weapon(name_t, id, lvl, mxd, mnd), baseRangeMax(rxd), baseRangeMin(rnd) {
	rangeMaxDmg = rangeMinDmg = 0;

	calculateDamage();
}

void bow::calculateDamage() {
	weapon::calculateDamage();
	rangeMaxDmg = baseRangeMax * getLvl();
	rangeMinDmg = baseRangeMin * getLvl();
}

int bow::getRangeMaxDmg() {
	return rangeMaxDmg;
}

int bow::getRangeMinDmg() {
	return rangeMinDmg;
}

int bow::rangeAttack(arrow* ar) {
	if (ar->getNumberArrows() <= 0) {
		return -1;
	}

	int n = ar->range();
	int dmg = rangeMinDmg + rand() % (rangeMaxDmg - rangeMinDmg + 1);

	return n * dmg;
}

