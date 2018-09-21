/*
 * player.h
 *
 *  Created on: Apr 9, 2018
 *      Author: thomasjansen
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string.h>

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "../globals.h"
#include "../log.h"
#include "../iores/Socket.h"
#include "objid.h"
#include "point.h"
#include "itemres/item.h"
#include "itemres/weapon.h"
#include "itemres/armor.h"
#include "itemres/bow.h"
#include "itemres/arrow.h"

#include "attr.h"

class player {
	Socket* fd;

	std::thread* ostreamThread;
	std::queue<char*> ostream;
	std::mutex ostreamLock;
	std::condition_variable ostreamCond;

	char* name;
	point pt;
	int lvl;
	int curhp, maxhp;

	int curxp, nextxp;

	int state;

	attr* attrs;

	std::vector<item*> inventory;
	std::queue<arrow*> quiver;
	weapon* mainhand, *offhand;
	armor* body;

	int findItem(const char*);

	void calculateHealth();

	void writerThread();
public:
	player(Socket* fd);
	virtual ~player();

	int read(char*, int);
	int read(char*);

	int addMessage(const char*);

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

	void setAttrs(attr*);
	attr* getAttrs();

	int pickUp(item*);
	item* drop(const char*);
	int equip(const char*, const char*);
	int unequip(const char*);

	int melee();
	int range();
	int takeDamage(int);

	void addXp(int);
	bool isLevel();
	void levelUp();

	int getState();

	int killed();
};

#endif /* PLAYER_H_ */
