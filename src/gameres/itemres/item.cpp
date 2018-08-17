/*
 * item.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#include "item.h"

item::item() {
	name = (char*) nullptr;
	id = (objid*) nullptr;

	lvl = 1;
}

item::item(const char* name_t, objid* tid, int l) {
	name = (char*) nullptr;
	id = (objid*) nullptr;

	lvl = l;

	setName(name_t);
	setId(tid);
}

item::~item() {
	if (name)
		free(name);
	if (id)
		delete (id);
}

void item::setName(const char* name_t) {
	if (name)
		free(name);

	name = (char*) malloc(strlen(name_t) + 1);
	name = strcpy(name, name_t);
}

const char* item::getName() {
	return (const char*) name;
}

void item::setPt(point tpt) {
	pt = tpt;
}

point item::getPt() {
	return pt;
}

void item::setId(objid* tid) {
	id = tid;
}

objid* item::getId() {
	return id;
}

void item::setLvl(int l) {
	lvl = l;
}

int item::getLvl() {
	return lvl;
}
