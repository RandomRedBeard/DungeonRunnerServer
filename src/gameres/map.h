/*
 * map.h
 *
 *  Created on: Apr 10, 2018
 *      Author: thomasjansen
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdio>
#include <chrono>

#include "../globals.h"
#include "../log.h"
#include "point.h"
#include "objid.h"
#include "itemres/itemgen.h"
#include "player.h"
#include "monsterres/monstergen.h"
#include "protocols.h"
#include "physmapres/physmap.h"

class map {
	std::mutex hardLock;
	std::vector<player*> playerList;
	std::vector<monster*> monsterList;
	std::vector<item*> itemList;

	objid* mapId;
	objid monsterId;
	objid* itemId;

	point playerSpawn;

	physmap* pmap;

	int lvl;

	void initiateMonsters();

	int findPlayer(const char*);
	int findPlayer(point);
	int findMonster(const char*);
	int findMonster(point);
	int findItem(const char*);
	int findItem(point);

	int unprotectedBroadcast(const char*);

	int lock();
	int unlock();

	point placePlayer();
	point placeMonster();
	point placeItem();

	bool isValidPoint(point);

	int monsterKilled(player*, monster*);
	int distributeXp(player*, monster*);
	void monsterThread(monster*);

	player* findClosestPlayer(point);
	point getClosestPt(point, point);
public:
	map(objid*, objid*, int);
	virtual ~map();
	int getPlayerSize();
	objid* getId();
	int broadcast(const char*);
	int addPlayer(player*);
	int removePlayer(player*);
	int playerMove(player*, point);
	int playerMeleeMonster(player*, const char*, int);
	int playerRangeMonster(player*, const char*, int);
	int playerPickup(player*);
	int playerDrop(player*, const char*);
	int playerEquip(player*, const char*, const char*);
	int playerUnequip(player*, const char*);
};

#endif /* MAP_H_ */
