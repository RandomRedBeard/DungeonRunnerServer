/*
 * monster.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: thomasjansen
 */

#include "monster.h"

monster::monster(const char* name_t, objid* tid, int level, int hp, int tac,
		int txp, int xd, int nd) :
		id(tid), lvl(level), baseHp(hp), baseAc(tac), xp(txp), baseMax(xd), baseMin(
				nd) {
	state = STATE_NORM;

	name = (char*) nullptr;
	setName(name_t);

	calculateStats();

	t = (std::thread*) nullptr;
}

monster::~monster() {
	killed();
	if (t) {
		t->join();
		delete (t);
	}

	if (name)
		free(name);

	if (id)
		delete (id);
}

void monster::calculateStats() {
	curhp = maxhp = baseHp * lvl;
	ac = baseAc * lvl;

	maxdmg = baseMax * lvl;
	mindmg = baseMin * lvl;

	xp = xp * lvl;
}

std::mutex* monster::getLock() {
	return &myLock;
}

std::condition_variable* monster::getCond() {
	return &sig;
}

int monster::lock() {
	myLock.lock();
	return 0;
}

int monster::unlock() {
	myLock.unlock();
	return 0;
}

void monster::setThread(std::thread* newThread) {
	t = newThread;
}

void monster::setId(objid* tid) {
	id = tid;
}

objid* monster::getId() {
	return id;
}

void monster::setName(const char* name_t) {
	if (name)
		free(name);

	name = (char*) malloc(strlen(name_t) + 1);
	name = strcpy(name, name_t);
}

const char* monster::getName() {
	return (const char*) name;
}

void monster::setPt(point newpt) {
	pt = newpt;
}

point monster::getPt() {
	return pt;
}

void monster::setLvl(int level) {
	lvl = level;
}

int monster::getLvl() {
	return lvl;
}

void monster::setCurHp(int chp) {
	curhp = chp;
}

int monster::getCurHp() {
	return curhp;
}

void monster::setMaxHp(int mhp) {
	maxhp = mhp;
}

int monster::getMaxHp() {
	return maxhp;
}

void monster::setAc(int a) {
	ac = a;
}

int monster::getAc() {
	return ac;
}

void monster::setState(int newstate) {
	state = newstate;
}

int monster::getState() {
	return state;
}

void monster::setXp(int nxp) {
	xp = nxp;
}

int monster::getXp() {
	return xp;
}

void monster::setMaxDmg(int xdmg) {
	maxdmg = xdmg;
}

int monster::getMaxDmg() {
	return maxdmg;
}

void monster::setMinDmg(int ndmg) {
	mindmg = ndmg;
}

int monster::getMinDmg() {
	return mindmg;
}

int monster::killed() {
	int n;
	n = lock();
	if (n != 0) {
		logerr("%s killed lock failure %s\n", name, strerror(n));
		return -1;
	}

	state = STATE_DEAD;

	sig.notify_all();
	if (n != 0) {
		logerr("%s killed signal failure %s\n", name, strerror(n));
		return -1;
	}

	n = unlock();
	if (n != 0) {
		logerr("%s killed unlock failure %s\n", name, strerror(n));
		return -1;
	}

	return 0;
}

int monster::melee() {
	int dmg = mindmg + rand() % (maxdmg - mindmg + 1);

	return dmg;
}

int monster::takeDamage(int dmg) {
	if (dmg < 0) {
		return -1;
	}

	double n = (double) ac / ((double) ac + ((1 / (double) lvl) / AC_SKEW));

	int i = dmg - dmg * n;

	curhp -= i;

	return i;
}
