/*
 * room.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: thomasjansen
 */

#include "room.h"

void room::setpt(point t, point b) {
	tl = t;
	br = b;
}

point room::getbr() {
	return br;
}

point room::gettl() {
	return tl;
}

void room::setnorth(point n) {
	north = n;
}

point room::getnorth() {
	return north;
}

void room::setsouth(point s) {
	south = s;
}

point room::getsouth() {
	return south;
}

void room::seteast(point e) {
	east = e;
}

point room::geteast() {
	return east;
}

void room::setwest(point w) {
	west = w;
}

point room::getwest() {
	return west;
}
