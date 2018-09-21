/*
 * player.cpp
 *
 *  Created on: Apr 9, 2018
 *      Author: thomasjansen
 */

#include "player.h"

player::player(Socket* f) :
	fd(f) {
	name = (char*) nullptr;
	lvl = 1;

	calculateHealth();
	curhp = maxhp;

	curxp = 0;
	nextxp = 100;

	attrs = new attr();

	state = STATE_OK;

	mainhand = offhand = (weapon*) nullptr;
	body = (armor*) nullptr;

	ostreamThread = new std::thread(&player::writerThread, this);

}

player::~player() {
	ostreamLock.lock();
	state = STATE_EXIT;
	ostreamCond.notify_all();
	ostreamLock.unlock();

	ostreamThread->join();

	delete (ostreamThread);

	char* buffer;
	while (ostream.size() != 0) {
		buffer = ostream.front();
		ostream.pop();
		free(buffer);
	}

	if (name) {
		free(name);
	}

	delete(attrs);

	item* it;
	while (inventory.size() != 0) {
		it = inventory.front();
		inventory.erase(inventory.begin());
		delete (it);
	}

	arrow* ar;
	while (quiver.size() != 0) {
		ar = quiver.front();
		quiver.pop();
		delete (ar);
	}

	delete (fd);
}

int player::read(char* buffer, int len) {
	return fd->read(buffer, len);
}

int player::read(char* buffer) {
	return fd->read(buffer, STD_LEN);
}

int player::findItem(const char* id) {
	item* it;
	for (unsigned int i = 0; i < inventory.size(); i++) {
		it = inventory[i];
		if (strcmp(id, it->getId()->getIdstr()) == 0) {
			return i;
		}
	}

	return -1;
}

void player::calculateHealth() {
	maxhp = 100 + (10 * (lvl - 1));
}

void player::writerThread() {
	char* buffer;
	int n;

	while (1) {
		std::unique_lock<std::mutex> ul(ostreamLock);
		while (ostream.size() == 0 && state != STATE_EXIT) {
			ostreamCond.wait(ul);
		}

		if (state == STATE_EXIT) {
			ul.unlock();
			return;
		}

		if (ostream.size() != 0) {
			buffer = ostream.front();
			ostream.pop();
			n = fd->write(buffer, strlen(buffer));
			free(buffer);
			if (n < 0) {
				logerr("%s writer failed\n", name);
				ostreamLock.unlock();
				return;
			}
		}
		ul.unlock();
	}
}

int player::addMessage(const char* msg) {
	ostreamLock.lock();

	char* buffer = (char*)malloc(strlen(msg) + 1);
	buffer = strcpy(buffer, msg);
	ostream.push(buffer);

	ostreamCond.notify_all();

	ostreamLock.unlock();

	return 0;


}

void player::setName(const char* buffer) {
	if (name) {
		free(name);
	}

	name = (char*)malloc(strlen(buffer) + 1);
	name = strcpy(name, buffer);
}

const char* player::getName() {
	return (const char*)name;
}

void player::setPt(point p) {
	pt = p;
}

point player::getPt() {
	return pt;
}

void player::setLvl(int l) {
	lvl = l;
}

int player::getLvl() {
	return lvl;
}

void player::setCurHp(int chp) {
	curhp = chp;
}

int player::getCurHp() {
	return curhp;
}

void player::setMaxHp(int mhp) {
	maxhp = mhp;
}

int player::getMaxHp() {
	return maxhp;
}

void player::setAttrs(attr* a) {
	(*attrs) = a;
}

attr* player::getAttrs() {
	return attrs;
}

int player::pickUp(item* it) {
	arrow* ar = dynamic_cast<arrow*>(it);
	if (ar) {
		quiver.push(ar);
	}
	else {
		inventory.push_back(it);
	}
	return 0;
}

item* player::drop(const char* id) {
	int index = findItem(id);
	if (index < 0) {
		return (item*) nullptr;
	}

	item* it = inventory[index];
	inventory.erase(inventory.begin() + index);

	if (it == mainhand) {
		mainhand->unequip();
		mainhand = (weapon*) nullptr;
	}
	else if (it == offhand) {
		offhand->unequip();
		offhand = (weapon*) nullptr;
	}
	else if (it == body) {
		body->unequip();
		body = (armor*) nullptr;
	}

	calculateHealth();

	return it;
}

int player::equip(const char* id, const char* part) {
	int index = findItem(id);
	if (index < 0) {
		return -1;
	}

	item* it = inventory[index];
	weapon* w = dynamic_cast<weapon*>(it);
	armor* a = dynamic_cast<armor*>(it);

	if ((w && w->isEquip()) || (a && a->isEquip())) {
		return -1;
	}

	if (w && strcmp(part, MAINHAND_OP) == 0) {
		if (mainhand) {
			mainhand->unequip();
		}
		mainhand = w;
		mainhand->equip();
	}
	else if (w && strcmp(part, OFFHAND_OP) == 0) {
		if (offhand) {
			offhand->unequip();
		}
		offhand = w;
		offhand->equip();
	}
	else if (a && strcmp(part, BODY_OP) == 0) {
		if (body) {
			body->unequip();
		}
		body = a;
		body->equip();
	}
	else {
		return -1;
	}

	calculateHealth();

	return 0;
}

int player::unequip(const char* part) {
	if (mainhand && strcmp(part, MAINHAND_OP) == 0) {
		mainhand->unequip();
		mainhand = (weapon*) nullptr;
	}
	else if (offhand && strcmp(part, OFFHAND_OP) == 0) {
		offhand->unequip();
		offhand = (weapon*) nullptr;
	}
	else if (body && strcmp(part, BODY_OP) == 0) {
		body->unequip();
		body = (armor*) nullptr;
	}
	else {
		return -1;
	}

	calculateHealth();

	return 0;
}

int player::melee() {
	int dmg = 0;
	if (mainhand) {
		dmg += mainhand->melee();
	}
	if (offhand) {
		dmg += offhand->melee();
	}

	return dmg;
}

int player::range() {
	if (quiver.size() == 0) {
		return -1;
	}

	bow* b = dynamic_cast<bow*>(mainhand);
	if (!b) {
		return -1;
	}

	arrow* ar = quiver.front();
	int dmg = b->rangeAttack(ar);
	if (ar->getNumberArrows() <= 0) {
		quiver.pop();
		delete (ar);
	}

	return dmg;
}

int player::takeDamage(int dmg) {
	if (dmg < 0) {
		return -1;
	}

	int ac = 0;

	if (body) {
		ac += body->getAc();
	}

	double n = (double)ac / ((double)ac + ((1 / (double)lvl) / AC_SKEW));

	int i = dmg - dmg * n;

	curhp -= i;

	return i;
}

void player::addXp(int xp) {
	curxp += xp;
}

bool player::isLevel() {
	return curxp >= nextxp;
}

void player::levelUp() {
	lvl++;

	nextxp += 100;

	calculateHealth();

	curhp = maxhp;
}

int player::getState() {
	ostreamLock.lock();

	int i = state;

	ostreamLock.unlock();

	return i;
}

int player::killed() {
	ostreamLock.lock();

	state = STATE_EXIT;

	ostreamCond.notify_all();

	ostreamLock.unlock();

	fd->shutdownSocket();

	return 0;
}
