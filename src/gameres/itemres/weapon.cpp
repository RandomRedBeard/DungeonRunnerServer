/*
 * weapon.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#include "weapon.h"

weapon::weapon() {
	baseMax = baseMin = 0;
	maxdmg = mindmg = 0;
	equipped = false;
}

weapon::weapon(const char* name_t, objid* tid, int l, int xd, int nd) :
		item(name_t, tid, l), baseMax(xd), baseMin(nd) {
	equipped = false;
	maxdmg = mindmg = 0;

	calculateDamage();
}

void weapon::setMaxDmg(int xd) {
	maxdmg = xd;
}

int weapon::getMaxDmg() {
	return maxdmg;
}

void weapon::setMinDmg(int nd) {
	mindmg = nd;
}

int weapon::getMinDmg() {
	return mindmg;
}

void weapon::calculateDamage() {
	maxdmg = baseMax * getLvl();
	mindmg = baseMin * getLvl();
}

void weapon::equip() {
	equipped = true;
}

void weapon::unequip() {
	equipped = false;
}

bool weapon::isEquip() {
	return equipped;
}

int weapon::melee() {
	return mindmg + rand() % (maxdmg - mindmg + 1);
}

