/*
 * arrow.cpp
 *
 *  Created on: May 18, 2018
 *      Author: thomasjansen
 */

#include "arrow.h"

arrow::arrow(const char* name, objid* id, int l, int n, int xd, int nd) :
		item(name, id, l), numberOfArrows(n), baseMax(xd), baseMin(nd) {
	maxdmg = mindmg = 0;

	calculateDamage();
}

void arrow::calculateDamage() {
	maxdmg = baseMax * getLvl();
	mindmg = baseMin * getLvl();
}

int arrow::getNumberArrows() {
	return numberOfArrows;
}

int arrow::getMaxDmg() {
	return maxdmg;
}

int arrow::getMinDmg() {
	return mindmg;
}

int arrow::range() {
	if (numberOfArrows <= 0) {
		return -1;
	}

	numberOfArrows--;

	return mindmg + rand() % (maxdmg - mindmg + 1);
}
