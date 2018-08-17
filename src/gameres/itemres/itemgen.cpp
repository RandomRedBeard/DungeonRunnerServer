/*
 * itemgen.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: thomasjansen
 */

#include "itemgen.h"

item* createItem(objid* id, int lvl) {
	switch (rand() % NUMBER_OF_ITEMS) {
	case 0:
		return createWeapon(id, lvl);
	case 1:
		return createArmor(id, lvl);
	case 2:
		return createArrow(id, lvl);
	case 3:
		return createBow(id, lvl);
	}
	return (item*) nullptr;
}

weapon* createWeapon(objid* id, int lvl) {
	switch (rand() % NUMBER_OF_WEAPONS) {
	case 0:
		return new shortsword(id, lvl);
	case 1:
		return new longsword(id, lvl);
	case 2:
		return new axe(id, lvl);
	}

	return (weapon*) nullptr;
}

armor* createArmor(objid* id, int lvl) {
	switch (rand() % NUMBER_OF_ARMORS) {
	case 0:
		return new leatherarmor(id, lvl);
	case 1:
		return new ironarmor(id, lvl);
	case 2:
		return new steelarmor(id, lvl);
	}

	return (armor*) nullptr;
}

arrow* createArrow(objid* id, int lvl) {
	int n = MIN_NUMBER_ARROWS
			+ rand() % (MAX_NUMBER_ARROWS - MIN_NUMBER_ARROWS + 1);
	switch (rand() % NUMBER_OF_ARROWS) {
	case 0:
		return new woodarrow(id, lvl, n);
	}

	return (arrow*) nullptr;
}

bow* createBow(objid* id, int lvl) {
	switch (rand() % NUMBER_OF_BOWS) {
	case 0:
		return new woodbow(id, lvl);
	}

	return (bow*) nullptr;
}

