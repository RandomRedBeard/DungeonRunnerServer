/*
 * point.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef POINT_H_
#define POINT_H_

#include <stdlib.h>
#include <math.h>

class point {
	int x, y, z;
public:
	point();
	point(int, int);
	point(int, int, int);

	void setPoint(int, int);
	void setPoint(int, int, int);

	void setX(int);
	int getX();
	void setY(int);
	int getY();
	void setZ(int);
	int getZ();

	void randc(int, int);
	void randc(int, int, int);
	
	double dist(point);
	int l1dist(point);
	
	void operator=(point);
	bool operator ==(point);
	bool operator !=(point);

	int index(int, int);
};

#endif /* POINT_H_ */
