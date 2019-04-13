/*
 * map.cpp
 *
 *  Created on: Apr 10, 2018
 *      Author: thomasjansen
 */

#include "map.h"

map::map(objid* m_id, objid* i_id, int l) :
		mapId(m_id), itemId(i_id), lvl(l) {
	pmap = new physmap();

	do {
		playerSpawn.randc(HEIGHT, WIDTH);
	} while (!isValidPoint(playerSpawn));

	initiateMonsters();

	for (unsigned int i = 0; i < 5; i++) {
		item* it = createItem(itemId->childId(), lvl);
		it->setPt(placeItem());
		itemList.push_back(it);
	}

}

map::~map() {
	monster* m;
	while (monsterList.size() != 0) {
		m = monsterList.front();
		monsterList.erase(monsterList.begin());
		delete (m);
	}

	item* it;
	while (itemList.size() != 0) {
		it = itemList.front();
		itemList.erase(itemList.begin());
		delete (it);
	}

	delete (pmap);
	delete (mapId);
}

void map::initiateMonsters() {
	monster* m;
	std::thread* t;
	int roomn = pmap->getRoomNumber() * 2;
	for (int i = 0; i < roomn; i++) {
		m = createMonster(monsterId.childId(), lvl);
		m->setPt(placeMonster());
		t = new std::thread(&map::monsterThread, this, m);
		m->setThread(t);
		monsterList.push_back(m);
	}
}

int map::findPlayer(const char* id) {
	for (unsigned int i = 0; i < playerList.size(); i++) {
		if (strcmp(id, playerList[i]->getName()) == 0) {
			return i;
		}
	}

	return -1;
}

int map::findPlayer(point pt) {
	for (unsigned int i = 0; i < playerList.size(); i++) {
		if (pt == playerList[i]->getPt()) {
			return i;
		}
	}

	return -1;
}

int map::findMonster(const char* id) {
	for (unsigned int i = 0; i < monsterList.size(); i++) {
		if (strcmp(id, monsterList[i]->getId()->getIdstr()) == 0) {
			return i;
		}
	}

	return -1;
}

int map::findMonster(point pt) {
	for (unsigned int i = 0; i < monsterList.size(); i++) {
		if (pt == monsterList[i]->getPt()) {
			return i;
		}
	}

	return -1;
}

int map::findItem(const char* id) {
	for (unsigned int i = 0; i < itemList.size(); i++) {
		if (strcmp(id, itemList[i]->getId()->getIdstr()) == 0) {
			return i;
		}
	}

	return -1;
}

int map::findItem(point pt) {
	for (unsigned int i = 0; i < itemList.size(); i++) {
		if (pt == itemList[i]->getPt()) {
			return i;
		}
	}

	return -1;
}

int map::unprotectedBroadcast(const char* buffer) {
	int n = 0;
	for (unsigned int i = 0; i < playerList.size(); i++) {
		if (playerList[i]->addMessage(buffer) < 0) {
			logerr("%s failed to add message", playerList[i]->getName());
			n = -1;
		}
	}

	return n;
}

int map::lock() {
	hardLock.lock();
	return 0;
}

int map::unlock() {
	hardLock.unlock();
	return 0;
}

point map::placePlayer() {
	int rad = 0;
	point pt;
	do {
		for (int i = rad * -1; i < rad + 1; i++) {
			for (int j = rad * -1; j < rad + 1; j++) {
				pt.setX(i + playerSpawn.getX());
				pt.setY(j + playerSpawn.getY());
				if (findPlayer(pt) < 0 && findMonster(pt) < 0
						&& isValidPoint(pt)) {
					return pt;
				}
			}
		}
		rad++;
	} while (rad < HEIGHT * WIDTH);

	return pt;
}

point map::placeMonster() {
	point pt;
	do {
		pt.randc(HEIGHT, WIDTH);
	} while (findPlayer(pt) != -1 || findMonster(pt) != -1 || !isValidPoint(pt));

	return pt;
}

point map::placeItem() {
	point pt;
	do {
		pt.randc(HEIGHT, WIDTH);
	} while (findItem(pt) != -1 || !isValidPoint(pt));

	return pt;
}

bool map::isValidPoint(point pt) {
	if (pmap->isvalid_dest(pt)) {
		return true;
	}

	return false;
}

int map::monsterKilled(player* p, monster* m) {
	char buffer[STD_LEN];

	killed_op(buffer, STD_LEN, p, m);
	int n = unprotectedBroadcast(buffer);
	if (n < 0) {
		logerr("%s monster killed broadcast failure\n", mapId->getIdstr());
	}

	distributeXp(p, m);

	n = findMonster(m->getId()->getIdstr());

	monsterList.erase(monsterList.begin() + n);

	point pt = m->getPt();

	delete (m);

	if (!prob(.3)) { //30% drop rate
		return 0;
	}

	item* it = createItem(itemId->childId(), lvl);
	it->setPt(pt);
	itemList.push_back(it);

	enter_map_op(buffer, STD_LEN, it);
	unprotectedBroadcast(buffer);

	return 0;
}

int map::distributeXp(player* p, monster* m) {
	int xp = m->getXp();
	char buffer[STD_LEN];
	int n;

	for (unsigned int i = 0; i < playerList.size(); i++) {
		playerList[i]->addXp(xp);
		if (playerList[i]->isLevel()) {
			playerList[i]->levelUp();

			levelup_op(buffer, STD_LEN, playerList[i]);
			n = unprotectedBroadcast(buffer);

			if (n < 0) {
				logerr("%s distribute xp broadcast failure\n",
						mapId->getIdstr());
			}
		}
	}

	return 0;
}

void map::monsterThread(monster* m) {
	using namespace std::literals::chrono_literals;
	char buffer[STD_LEN];
	int rval=0;
	std::mutex* mlock = m->getLock();
	std::condition_variable* cond = m->getCond();
	while (1) {
		std::unique_lock<std::mutex> ul(*mlock);

		while (1) {
			if (m->getState() == STATE_DEAD) {
				ul.unlock();
				return;
			}
			
			std::cv_status cv = cond->wait_for(ul, 1000ms);

			if (cv == std::cv_status::timeout) {
				break;
			}
		}

		ul.unlock();
		if (rval != 0) {
			logerr("%s monster thread monster lock failure %s\n", m->getName(),
					strerror(rval));
			return;
		}

		rval = lock();
		if (rval != 0) {
			logerr("%s monster thread lock failure %s\n", mapId->getIdstr(),
					strerror(rval));
			abort();
		}

		player* p = findClosestPlayer(m->getPt());
		if (!p) {
			rval = unlock();
			if (rval != 0) {
				logerr("%s monster thread unlock failure %s\n",
						mapId->getIdstr(), strerror(rval));
				abort();
			}
			continue;
		}

		point dest = getClosestPt(m->getPt(), p->getPt());

		if (!isValidPoint(dest) || findMonster(dest) != -1) {
			rval = unlock();
			if (rval != 0) {
				logerr("%s monster thread unlock failure %s\n",
						mapId->getIdstr(), strerror(rval));
				abort();
			}
			continue;
		}

		int index = findPlayer(dest);

		if (index != -1) {
			p = playerList[index];

			rval = p->getState();
			if (rval == STATE_EXIT || rval == STATE_DEAD) {
				rval = unlock();
				if (rval != 0) {
					logerr("%s monster thread unlock failure %s\n",
							mapId->getIdstr(), strerror(rval));
					abort();
				}
				continue;
			}

			int dmg = p->takeDamage(m->melee());

			melee_op(buffer, STD_LEN, m, p, dmg);
			rval = unprotectedBroadcast(buffer);

			if (rval < 0) {
				logerr("%s monster thread broadcast failure\n",
						mapId->getIdstr());
			}

			rval = p->getCurHp();

			if (rval <= 0) {
				p->killed();

				killed_op(buffer, STD_LEN, m, p);
				unprotectedBroadcast(buffer);
			}

			rval = unlock();
			if (rval != 0) {
				logerr("%s monster thread unlock failure %s\n",
						mapId->getIdstr(), strerror(rval));
				abort();
			}
			continue;
		}

		m->setPt(dest);

		move_op(buffer, STD_LEN, m);
		rval = unprotectedBroadcast(buffer);

		if (rval < 0) {
			logerr("%s monster thread broadcast failure\n", mapId->getIdstr());
		}

		rval = unlock();
		if (rval != 0) {
			logerr("%s monster thread unlock failure %s\n", mapId->getIdstr(),
					strerror(rval));
			abort();
		}
	}
}

player* map::findClosestPlayer(point pt) {
	if (playerList.size() == 0) {
		return (player*) nullptr;
	}

	int dist = pt.l1dist(playerList[0]->getPt());
	int pindex = 0;

	for (unsigned int i = 1; i < playerList.size(); i++) {
		int tdist = pt.l1dist(playerList[i]->getPt());
		if (tdist < dist) {
			dist = tdist;
			pindex = i;
		}
	}

	return playerList[pindex];
}

point map::getClosestPt(point src, point dest) {
	int xleft = abs(src.getX() - dest.getX());
	int yleft = abs(src.getY() - dest.getY());
	int xdir = 0;
	int ydir = 0;

	if (src.getX() < dest.getX()) {
		xdir = 1;
	} else if (src.getX() > dest.getX()) {
		xdir = -1;
	}

	if (src.getY() < dest.getY()) {
		ydir = 1;
	} else if (src.getY() > dest.getY()) {
		ydir = -1;
	}

	point pt = src;

	if (xleft > rand() % (yleft + 1)) {
		pt.setX(pt.getX() + xdir);
	} else {
		pt.setY(pt.getY() + ydir);
	}

	return pt;
}

bool map::check_range(player* p, monster* m, point* prev_ret) {
	point src(p->getPt().getX(), p->getPt().getY());
	point dest(m->getPt().getX(), p->getPt().getY());

	point target_vector(dest.getX() - src.getX(),
		dest.getY() - src.getY());

	double angle = atan((double)target_vector.getX() / (double)target_vector.getY());

	double x, y;
	double cursx, cursy;

	y = cos(angle);
	x = sin(angle);

	if (target_vector.getX() < 0 && x > 0) {
		x *= -1;
	}
	else if (target_vector.getX() > 0 && x < 0) {
		x *= -1;
	}

	if (target_vector.getY() < 0 && y > 0) {
		y *= -1;
	}
	else if (target_vector.getY() > 0 && y < 0) {
		y *= -1;
	}

	cursx = src.getX() + x;
	cursy = src.getY() + y;

	point curs(src.getX(),src.getY());
	point prev;

	do {
		prev.setPoint(curs.getX(), curs.getX());
		curs.setPoint(cursx, cursy);
		if (curs == dest) {
			return true;
		}
		cursx += x;
		cursy += y;
	} while (pmap->isvalid_dest(curs));

	prev_ret->setPoint(prev.getX(), prev.getY());

	return false;
}

int map::getPlayerSize() {
	int n = lock();
	if (n != 0) {
		logerr("%s get player size lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	int i = playerList.size();

	n = unlock();
	if (n != 0) {
		logerr("%s get player size unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return i;
}

objid* map::getId() {
	return mapId;
}

int map::broadcast(const char* buffer) {
	int rval = lock();
	if (rval != 0) {
		logerr("%s broadcast lock failure %s\n", mapId->getIdstr(),
				strerror(rval));
		abort();
	}

	int n = unprotectedBroadcast(buffer);

	rval = unlock();
	if (rval != 0) {
		logerr("%s broadcast unlock failure %s\n", mapId->getIdstr(),
				strerror(rval));
		abort();
	}

	return n;
}

int map::addPlayer(player* p) {
	int n = lock();
	if (n != 0) {
		logerr("%s add player lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	p->setPt(placePlayer());

	int len = accept_travel_op(NULL, 0, p) + physmap_op( NULL, 0, pmap) + 1;

	char* buffer = (char*)malloc(len);
	accept_travel_op(buffer, len, p);
	physmap_op((buffer + strlen(buffer)), len - strlen(buffer), pmap);

	p->addMessage(buffer);

	for (unsigned int i = 0; i < playerList.size(); i++) {
		enter_map_op(buffer, STD_LEN, playerList[i]);
		p->addMessage(buffer);
	}

	for (unsigned int i = 0; i < monsterList.size(); i++) {
		enter_map_op(buffer, STD_LEN, monsterList[i]);
		p->addMessage(buffer);
	}

	for (unsigned int i = 0; i < itemList.size(); i++) {
		enter_map_op(buffer, STD_LEN, itemList[i]);
		p->addMessage(buffer);
	}

	enter_map_op(buffer, STD_LEN, p);
	n = unprotectedBroadcast(buffer);

	free(buffer);

	if (n < 0) {
		logerr("%s add player broadcast failure\n", mapId->getIdstr());
	}

	playerList.push_back(p);

	n = unlock();
	if (n != 0) {
		logerr("%s add player unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::removePlayer(player* p) {
	int n = lock();
	if (n != 0) {
		logerr("%s remove player lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	int i = findPlayer(p->getName());

	if (i < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s remove player unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return -1;
	}

	playerList.erase(playerList.begin() + i);

	char buffer[STD_LEN];

	exit_map_op(buffer, STD_LEN, p);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s remove player broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s remove player unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerMove(player* p, point pt) {
	if (!isValidPoint(pt)) {
		return false;
	}

	if (pt.l1dist(p->getPt()) != 1) {
		return false;
	 }

	int n = lock();
	if (n != 0) {
		logerr("%s player move lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	if (findPlayer(pt) >= 0 || findMonster(pt) >= 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player move unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return false;
	}

	p->setPt(pt);

	char buffer[STD_LEN];

	move_op(buffer, STD_LEN, p);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player move broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player move unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerMeleeMonster(player* p, const char* id, int dmg) {
	int n = lock();
	if (n != 0) {
		logerr("%s player melee monster lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	int i = findMonster(id);

	if (i < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player melee monster unlock failure %s\n",
					mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return 0;
	}

	monster* m = monsterList[i];

	if (p->getPt().l1dist(m->getPt()) > 1) { //Validate Melee Dist
		n = unlock();
		if (n != 0) {
			logerr("%s player melee monster unlock failure %s\n",
					mapId->getIdstr(), strerror(n));
			abort();
		}
		return 0;
	}

	dmg = m->takeDamage(dmg);

	char buffer[STD_LEN];

	melee_op(buffer, STD_LEN, p, m, dmg);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player melee broadcast failure\n", mapId->getIdstr());
	}

	if (m->getCurHp() <= 0) {
		monsterKilled(p, m);
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player melee monster unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerRangeMonster(player* p, const char* id) {
	int n = lock();
	if (n != 0) {
		logerr("%s player range monster lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	/*
	* Define miss behavior for no id monster
	* Optional
	*/

	int i = findMonster(id);
	if (i < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player range monster unlock failure %s\n",
					mapId->getIdstr(), strerror(n));
			abort();
		}
		return -1;
	}

	monster* m = monsterList[i];

	char buffer[STD_LEN];
	/*
	* Get arrow to be fired
	*/

	arrow* to_fire = p->getFirstArrow();

	//No Arrow to fire
	//Harsh kick protocol
	if (!to_fire) {
		n = unlock();
		if (n != 0) {
			logerr("%s player range monster unlock failure %s\n",
				mapId->getIdstr(), strerror(n));
			abort();
		}
		return -1;
	}

	/*
	* Validate range with miss protocl
	*/

	point arrow_land;

	if (!check_range(p, m, &arrow_land)) {
		/*
		* p->range for quiver count
		*/
		p->range();

		/*
		* Get arrow that was shot
		* Arrow needs to be copied with new item_id
		*/
		arrow* to_fire_cp = new arrow(to_fire->getName(), itemId->childId(), to_fire->getLvl(),
			1, to_fire->getBaseMax(), to_fire->getBaseMin());

		to_fire_cp->setAttrs(to_fire->getAttrs());

		/*
		* to_fire_cp needs location
		*/
		to_fire_cp->setPt(arrow_land);

		//Add new arrow to item vec
		itemList.push_back(to_fire_cp);

		miss_range_op(buffer, STD_LEN, p, to_fire_cp);
		unprotectedBroadcast(buffer);
		loginfo("Miss: %s\n", buffer);

		n = unlock();
		if (n != 0) {
			logerr("%s player range monster unlock failure %s\n",
				mapId->getIdstr(), strerror(n));
			abort();
		}
		return 0;
	}

	// Dmg should be > 0 as quiver empty has already been checked
	int dmg = p->range();

	dmg = m->takeDamage(dmg);

	range_op(buffer, STD_LEN, p, m, dmg);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player range broadcast failure\n", mapId->getIdstr());
	 }

	if (m->getCurHp() <= 0) {
		monsterKilled(p, m);
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player range monster unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerPickup(player* p) {
	int n = lock();
	if (n != 0) {
		logerr("%s player pickup lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	int i = findItem(p->getPt());

	if (i < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player pickup unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
		}
		return false;
	}

	item* it = itemList[i];

	itemList.erase(itemList.begin() + i);
	p->pickUp(it);

	char buffer[STD_LEN];

	pickup_op(buffer, STD_LEN, p, it);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player pickup broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player pickup unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerDrop(player* p, const char* id) {
	int n = lock();
	if (n != 0) {
		logerr("%s player drop lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	item* it = p->drop(id);

	if (it == nullptr) {
		n = unlock();
		if (n != 0) {
			logerr("%s player drop unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return -1;
	}


	it->setPt(p->getPt());

	itemList.push_back(it);

	char buffer[STD_LEN];

	drop_op(buffer, STD_LEN, p, it);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player drop broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player drop unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerEquip(player* p, const char* id, const char* eq_part) {
	int n = lock();
	if (n != 0) {
		logerr("%s player equip lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	n = p->equip(id, eq_part);
	if (n < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player equip unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return -1;
	}

	char buffer[STD_LEN];

	equip_op(buffer, STD_LEN, p, id, eq_part);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player equip broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player equip unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerUnequip(player* p, const char* eq_part) {
	int n = lock();
	if (n != 0) {
		logerr("%s player unequip lock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	n = p->unequip(eq_part);
	if (n < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s player unequip unlock failure %s\n", mapId->getIdstr(),
					strerror(n));
			abort();
		}
		return -1;
	}

	char buffer[STD_LEN];

	unequip_op(buffer, STD_LEN, p, eq_part);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("%s player unequip broadcast failure\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s player unequip unlock failure %s\n", mapId->getIdstr(),
				strerror(n));
		abort();
	}

	return 0;
}

int map::playerAllocateAttr(player* p, const char* at) {
	int n = lock();
	if (n != 0) {
		logerr("%s allocate attr lock failure %s\n", p->getName(), strerror(n));
		abort();
	}

	if (p->allocateAttr(at) < 0) {
		n = unlock();
		if (n != 0) {
			logerr("%s allocate attr unlock failure %s\n", p->getName(), strerror(n));
			abort();
		}
		return -1;
	}

	char buffer[STD_LEN];

	allocate_attr_op(buffer, STD_LEN, p, at);
	n = unprotectedBroadcast(buffer);

	if (n < 0) {
		logerr("unprotected broadcast failure %s\n", mapId->getIdstr());
	}

	n = unlock();
	if (n != 0) {
		logerr("%s allocate attr unlock failure %s\n", p->getName(), strerror(n));
		abort();
	}

	return 0;
}
