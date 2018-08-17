/*
 * weapon.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "item.h"

class weapon: public item {
	int baseMax, baseMin;
	int maxdmg, mindmg;
	bool equipped;
protected:
	virtual void calculateDamage();
public:
	weapon();
	weapon(const char*, objid*, int, int, int);

	void setMaxDmg(int);
	int getMaxDmg();
	void setMinDmg(int);
	int getMinDmg();

	void equip();
	void unequip();
	bool isEquip();

	virtual int melee();
};

#endif /* WEAPON_H_ */
