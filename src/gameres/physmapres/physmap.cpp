/*
 * physmap.cpp
 *
 *  Created on: Mar 15, 2018
 *      Author: thomasjansen
 */

#include "physmap.h"

physmap::physmap() {
	sbuffer = (char*) malloc(HEIGHT * WIDTH + 1);
	memset(sbuffer, ' ', HEIGHT * WIDTH);
	sbuffer[HEIGHT * WIDTH] = '\0';
	doRooms();
}

physmap::~physmap() {
	free(sbuffer);
	free(roomProb);
	while (rooms.size() != 0) {
		room* r = rooms.front();
		rooms.erase(rooms.begin());
		delete (r);
	}
}

void physmap::sprintRoom(room* r, char* buffer) {
	int width = r->getbr().getY() - r->gettl().getY() + 1;
	int height = r->getbr().getX() - r->gettl().getX();

	point p;

	for (unsigned int i = 0; i < width; i++) {
		p.setPoint(r->gettl().getX(), r->gettl().getY() + i);
		buffer[p.index(HEIGHT, WIDTH)] = HORZ_WALL;
		p.setPoint(r->getbr().getX(), r->gettl().getY() + i);
		buffer[p.index(HEIGHT, WIDTH)] = HORZ_WALL;
	}
	for (int i = 1; i < height; i++) {
		p.setPoint(r->gettl().getX() + i, r->gettl().getY());
		buffer[p.index(HEIGHT, WIDTH)] = VERT_WALL;
		p.setPoint(r->gettl().getX() + i, r->getbr().getY());
		buffer[p.index(HEIGHT, WIDTH)] = VERT_WALL;
	}

	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height; j++) {
			p.setPoint(r->gettl().getX() + j, r->gettl().getY() + i);
			buffer[p.index(HEIGHT, WIDTH)] = FLOOR;
		}
	}

	if (r->geteast().getX() != -1) {
		buffer[r->geteast().index(HEIGHT, WIDTH)] = HALLWAY_ENTRANCE;
	}
	if (r->getsouth().getX() != -1) {
		buffer[r->getsouth().index(HEIGHT, WIDTH)] = HALLWAY_ENTRANCE;
	}
	if (r->getwest().getX() != -1) {
		buffer[r->getwest().index(HEIGHT, WIDTH)] = HALLWAY_ENTRANCE;
	}
	if (r->getnorth().getX() != -1) {
		buffer[r->getnorth().index(HEIGHT, WIDTH)] = HALLWAY_ENTRANCE;
	}
}

void physmap::sprintAllRooms() {
	for (unsigned int i = 0; i < rooms.size(); i++) {
		sprintRoom(rooms[i], sbuffer);
	}
}

void physmap::doRooms() {
	rollRoomProb();
	int maxrh = HEIGHT / SQRT_ROOM_N;
	int maxrw = WIDTH / SQRT_ROOM_N;

	int midpth = maxrh / 2;
	int midptw = maxrw / 2;

	int roomCnt = 0;

	for (unsigned int i = 0; i < SQRT_ROOM_N; i++) {
		for (int j = 0; j < SQRT_ROOM_N; j++) {
			if (!roomProb[roomCnt]) {
				roomCnt++;
				continue;
			}
			int tmidpth = midpth + (maxrh * (i));
			int tmidptw = midptw + (maxrw * (j));

			point p; //length
			p.setX(3 + rand() % (maxrh - 4)); //max height = 5
			p.setY(3 + rand() % (maxrw - 4)); //max width = 71

			point tl(tmidpth - (p.getX() / 2), tmidptw - (p.getY() / 2));
			point br(tl.getX() + p.getX(), tl.getY() + p.getY());

			room* r = new room();
			r->setpt(tl, br);
			rooms.push_back(r);
			roomCnt++;
		}
	}

	int roomindex = 0;
	for (unsigned int i = 0; i < SQRT_ROOM_N * SQRT_ROOM_N; i++) {
		if (roomProb[i]) {
			setHallway(roomindex, i);
			roomindex++;
		}
	}

	sprintAllRooms();
}

void physmap::rollRoomProb() {
	int numberOfRooms = SQRT_ROOM_N * SQRT_ROOM_N;
	int val = (int) sqrt(numberOfRooms);
	int reduc = val - 1;
	int numberOfAllowed = (reduc * reduc) + 2;
	int numberAllowedFalse = numberOfRooms - numberOfAllowed;

	roomProb = (bool*) malloc(numberOfRooms);
	for (unsigned int i = 0; i < numberOfRooms; i++) {
		if (prob(numberAllowedFalse / (numberOfRooms * 1.0))) {
			roomProb[i] = false;
			numberAllowedFalse--;
		} else {
			roomProb[i] = true;
		}
	}
}

const char* physmap::getBuffer() {
	return (const char*) sbuffer;
}

void physmap::setHallway(int roomIndex, int roomProbIndex) {
	room* r = rooms[roomIndex];
	int tindex = roomProbIndex;
	int mod = tindex % SQRT_ROOM_N;

	for (; mod < SQRT_ROOM_N - 1; mod++) {
		tindex++;
		if (roomProb[tindex]) { //There is a room

			point p(
					r->gettl().getX() + 1
							+ rand()
									% (r->getbr().getX() - r->gettl().getX() - 1),
					r->getbr().getY());

			r->seteast(p);
			room* dest = findRoom(tindex);
			p.setPoint(
					dest->gettl().getX() + 1
							+ rand()
									% (dest->getbr().getX()
											- dest->gettl().getX() - 1),
					dest->gettl().getY());
			dest->setwest(p);

			hallway(point(r->geteast().getX(), r->geteast().getY() + 1),
					point(dest->getwest().getX(), dest->getwest().getY() - 1));

			break;
		}
	}

	tindex = roomProbIndex;
	mod = tindex / SQRT_ROOM_N;

	for (; mod < SQRT_ROOM_N - 1; mod++) {
		tindex += SQRT_ROOM_N;
		if (roomProb[tindex]) {
			point p(r->getbr().getX(),
					r->gettl().getY() + 1
							+ rand()
									% (r->getbr().getY() - r->gettl().getY() - 1));

			r->setsouth(p);
			room* dest = findRoom(tindex);

			p.setPoint(dest->gettl().getX(),
					dest->gettl().getY() + 1
							+ rand()
									% (dest->getbr().getY()
											- dest->gettl().getY() - 1));
			
			dest->setnorth(p);

			hallway(point(r->getsouth().getX() + 1, r->getsouth().getY()),
					point(dest->getnorth().getX() - 1,
							dest->getnorth().getY()));
			break;
		}
	}

}

room* physmap::findRoom(int probIndex) {
	int roomIndex = 0;
	for (unsigned int i = 0; i < probIndex; i++) {
		if (roomProb[i]) {
			roomIndex++;
		}
	}

	return rooms[roomIndex];
}

void physmap::hallway(point p1, point p2) {
	int xleft = abs(p1.getX() - p2.getX());
	int yleft = abs(p1.getY() - p2.getY());
	int xdir = 0;
	int ydir = 0;

	if (p1.getX() < p2.getX()) {
		xdir = 1;
	} else if (p1.getX() > p2.getX()) {
		xdir = -1;
	}

	if (p1.getY() < p2.getY()) {
		ydir = 1;
	} else if (p1.getY() > p2.getY()) {
		ydir = -1;
	}

	point index = p1;

	while (index != p2) {
		sbuffer[index.index(HEIGHT, WIDTH)] = HALLWAY_FLOOR;
		if (xleft > rand() % (yleft + 1)) {
			index.setX(index.getX() + xdir);
			xleft--;
		} else {
			index.setY(index.getY() + ydir);
			yleft--;
		}
	}
	sbuffer[p2.index(HEIGHT, WIDTH)] = HALLWAY_FLOOR;
}

bool physmap::isvalid_dest(point p) {
	if (p.getX() < 0 || p.getY() < 0 || p.getX() >= HEIGHT
			|| p.getY() >= WIDTH) {
		return false;
	}

	int index = p.index(HEIGHT, WIDTH);

	if (sbuffer[index] == FLOOR || sbuffer[index] == HALLWAY_ENTRANCE
			|| sbuffer[index] == HALLWAY_FLOOR) {
		return true;
	}

	return false;
}

int physmap::getRoomNumber() {
	return rooms.size();
}

