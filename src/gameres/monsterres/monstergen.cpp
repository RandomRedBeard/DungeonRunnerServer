/*
 * monstergen.cpp
 *
 *  Created on: Apr 16, 2018
 *      Author: thomasjansen
 */

#include "monstergen.h"

monster* createMonster(objid* id, int lvl) {
	switch (rand() % NUMBER_OF_MONSTERS) {
	case 0:
		return new minion(id, lvl);
	case 1:
		return new kobold(id, lvl);
	}

	return (monster*) nullptr;
}


