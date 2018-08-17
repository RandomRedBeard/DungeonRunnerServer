/*
 * armor.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef ARMOR_H_
#define ARMOR_H_

#include "item.h"

class armor: public item {
	int baseAc;
	int ac;
	bool equipped;
	void calculateArmor();
public:
	armor();
	armor(const char*, objid*, int, int);

	void setAc(int);
	int getAc();

	void equip();
	void unequip();
	bool isEquip();
};

#endif /* ARMOR_H_ */
