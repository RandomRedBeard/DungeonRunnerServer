/*
 * objid.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef OBJID_H_
#define OBJID_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mutex>

#include "../globals.h"

class objid {
	std::mutex lock;
	int* id, id_len, idstr_len, idmax_len;
	char* idstr;

	void resetIdstr();
	int increment();
public:
	objid();
	objid(int*);
	virtual ~objid();

	const char* getIdstr();
	objid* childId();

	bool operator==(objid*);
	bool operator!=(objid*);
};

#endif /* OBJID_H_ */
