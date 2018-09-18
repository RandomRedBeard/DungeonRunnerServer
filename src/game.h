/*
 * game.h
 *
 *  Created on: Apr 12, 2018
 *      Author: thomasjansen
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "gameres/player.h"
#include "gameres/map.h"
#include "gameres/protocols.h"
#include "gameres/objid.h"

class game {
	std::vector<map*> mapList;
	std::vector<player*> playerList;

	std::mutex hardLock;

	objid itemId, mapId;

	int findPlayer(const char*);
	int findMap(objid*);
public:
	int addPlayer(player*);
	int removePlayer(player*);
	map* getLowestMap(player*);
	map* getNextMap(player*, map*);
	int checkCleanup(map*);
	int globalMessage(player*, const char*);
};

#endif /* GAME_H_ */
