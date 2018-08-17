/*
 * room.h
 *
 *  Created on: Jan 16, 2018
 *      Author: thomasjansen
 */

#ifndef ROOM_H_
#define ROOM_H_

#include "../point.h"

class room {
	point tl, br;
	point north, south, west, east;
public:
	void setpt(point, point);
	point gettl();
	point getbr();
	void setnorth(point);
	point getnorth();
	void setsouth(point);
	point getsouth();
	void seteast(point);
	point geteast();
	void setwest(point);
	point getwest();
};

#endif /* ROOM_H_ */
