/*
 * item.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "../point.h"
#include "../objid.h"
#include "../attr.h"

class item {
	char* name;
	point pt;
	objid* id;
	int lvl;

	attr* attrs;
public:
	item();
	item(const char*, objid*, int);
	virtual ~item();

	virtual void setName(const char*);
	virtual const char* getName();
	virtual void setPt(point);
	virtual point getPt();
	virtual void setId(objid*);
	virtual objid* getId();
	virtual void setLvl(int);
	virtual int getLvl();

	void setAttrs(attr*);
	attr* getAttrs();
};

#endif /* ITEM_H_ */
