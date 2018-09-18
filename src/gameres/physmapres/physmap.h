/*
 * physmap.h
 *
 *  Created on: Mar 15, 2018
 *      Author: thomasjansen
 */

#ifndef PHYSMAP_H_
#define PHYSMAP_H_

#include <string.h>

#include "room.h"
#include "../probability.h"
#include "../../globals.h"

#include <vector>

class physmap {
	void rollRoomProb();
	void doRooms();
	void sprintRoom(room*, char*);
	void sprintAllRooms();
	bool* roomProb;
	char* sbuffer;
	std::vector<room*> rooms;
	void setHallway(int, int);
	room* findRoom(int);
	void hallway(point, point);
public:
	physmap();
	virtual ~physmap();
	const char* getBuffer();
	bool isvalid_dest(point);
	int getRoomNumber();
};

#endif /* PHYSMAP_H_ */
