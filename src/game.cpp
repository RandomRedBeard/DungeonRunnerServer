/*
 * game.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: thomasjansen
 */

#include "game.h"

int game::findPlayer(const char* name) {
	for (unsigned int i = 0; i < playerList.size(); i++) {
		if (strcmp(name, playerList[i]->getName()) == 0) {
			return i;
		}
	}

	return -1;
}

int game::findMap(objid* id) {
	for (unsigned int i = 0; i < mapList.size(); i++) {
		if (id == mapList[i]->getId()) {
			return i;
		}
	}

	return -1;
}

int game::addPlayer(player* p) {
	hardLock.lock();

	if (findPlayer(p->getName()) >= 0) {
		hardLock.unlock();
		return -1;
	}

	char buffer[STD_LEN];
	player_login_op(buffer, STD_LEN, p);

	for (unsigned int i = 0; i < playerList.size(); i++) {
		playerList[i]->addMessage(buffer);
		player_login_op(buffer, STD_LEN, playerList[i]);
		p->addMessage(buffer);
	}

	playerList.push_back(p);
	
	hardLock.unlock();

	return 0;
}

int game::removePlayer(player* p) {
	hardLock.lock();

	int index = findPlayer(p->getName());
	if (index < 0) {
		hardLock.unlock();
		return -1;
	}

	playerList.erase(playerList.begin() + index);

	char buffer[STD_LEN];
	player_logoff_op(buffer, STD_LEN, p);

	for (unsigned int i = 0; i < playerList.size(); i++) {
		playerList[i]->addMessage(buffer);
	}

	hardLock.unlock();

	return 0;
}

map* game::getLowestMap(player* p) {
	hardLock.lock();

	map* m;
	if (mapList.size() == 0) {
		m = new map(mapId.childId(), &itemId, p->getLvl());
		mapList.push_back(m);
	} else {
		m = mapList.front();
	}

	hardLock.unlock();

	return m;
}

map* game::getNextMap(player* p, map* m) {
	hardLock.lock();

	unsigned int index = findMap(m->getId());
	if (index < 0) {
		hardLock.unlock();
		return (map*) nullptr;
	}

	m = mapList[index];
	if (m->getPlayerSize() == 0 && index == 0) {
		mapList.erase(mapList.begin() + index);
		delete (m);
		index--;
	}

	if (index + 1 >= mapList.size()) {
		m = new map(mapId.childId(), &itemId, p->getLvl());
		mapList.push_back(m);
	} else {
		m = mapList[index + 1];
	}

	hardLock.unlock();

	return m;
}

int game::checkCleanup(map* m) {
	hardLock.lock();

	if (m->getPlayerSize() == 0 && findMap(m->getId()) == 0) {
		int index = findMap(m->getId());
		mapList.erase(mapList.begin() + index);
		delete (m);
	}
	hardLock.unlock();

	return 0;
}

int game::globalMessage(player* p, const char* msg) {
	hardLock.lock();

	char buffer[STD_LEN];
	global_message_op(buffer, STD_LEN, p, msg);

	for (unsigned int i = 0; i < mapList.size(); i++) {
		int n = mapList[i]->broadcast(buffer);
		if (n != 0) {
			logerr("%s global message broadcast failure\n",
					mapList[i]->getId()->getIdstr());
		}
	}

	hardLock.unlock();

	return 0;
}
