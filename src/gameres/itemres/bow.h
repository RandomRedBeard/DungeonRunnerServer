/*
 * bow.h
 *
 *  Created on: May 18, 2018
 *      Author: thomasjansen
 */

#ifndef BOW_H_
#define BOW_H_

#include "weapon.h"

#include "arrow.h"

class bow: public weapon {
	int baseRangeMax, baseRangeMin;
	int rangeMaxDmg, rangeMinDmg;
	void calculateDamage();
public:
	bow(const char*, objid*, int, int, int, int, int);

	int getRangeMaxDmg();
	int getRangeMinDmg();

	int rangeAttack(arrow*);
};

#endif /* BOW_H_ */
