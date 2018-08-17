/*
 * monster.h
 *
 *  Created on: Apr 3, 2018
 *      Author: thomasjansen
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <thread>
#include <mutex>

#include "../../globals.h"
#include "../../log.h"
#include "../point.h"
#include "../objid.h"

class monster {
	std::mutex myLock;
	std::condition_variable sig;
	std::thread* t;

	int state;

	objid* id;
	char* name;
	point pt;
	int lvl;

	int baseHp;
	int curhp, maxhp;

	int baseAc;
	int ac;

	int xp;

	int baseMax, baseMin;
	int maxdmg, mindmg;

	void calculateStats();
public:
	monster(const char*, objid*, int, int, int, int, int, int);
	virtual ~monster();

	std::mutex* getLock();
	std::condition_variable* getCond();

	int lock();
	int unlock();

	void setThread(std::thread*);

	void setId(objid*);
	objid* getId();
	void setName(const char*);
	const char* getName();
	void setPt(point);
	point getPt();
	void setLvl(int);
	int getLvl();
	void setCurHp(int);
	int getCurHp();
	void setMaxHp(int);
	int getMaxHp();
	void setAc(int);
	int getAc();
	void setState(int);
	int getState();
	void setXp(int);
	int getXp();
	void setMaxDmg(int);
	int getMaxDmg();
	void setMinDmg(int);
	int getMinDmg();

	int killed();
	int melee();
	int takeDamage(int);
};

#endif /* MONSTER_H_ */
