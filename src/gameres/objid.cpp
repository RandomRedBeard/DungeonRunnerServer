/*
 * objid.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#include "objid.h"

objid::objid() {
	id_len = ID_LEN * sizeof(int);
	id = (int*) malloc(id_len);
	memset(id, 0, id_len);

	idmax_len = snprintf( NULL, 0, "%d", ID_MAX_LIM);
	idstr_len = idmax_len * ID_LEN;

	idstr = (char*) malloc(idstr_len + 1);

	resetIdstr();
}

objid::objid(int* tid) {
	id_len = ID_LEN * sizeof(int);
	id = (int*) malloc(id_len);
	memcpy(id, tid, id_len);

	idmax_len = snprintf( NULL, 0, "%d", ID_MAX_LIM);
	idstr_len = idmax_len * ID_LEN;

	idstr = (char*) malloc(idstr_len + 1);

	resetIdstr();
}

objid::~objid() {
	free(id);
	free(idstr);
}

void objid::resetIdstr() {
	memset(idstr, 0, idstr_len + 1);
	char* buffer = (char*) malloc(idmax_len + 1);

	for (unsigned int i = 0; i < ID_LEN; i++) {
		snprintf(buffer, idmax_len + 1, "%d", *(id + i));
		strcat(idstr, buffer);
	}

	free(buffer);
}

int objid::increment() {
	for (int i = ID_LEN - 1; i >= 0; i--) {
		(*(id + i))++;
		if (*(id + i) < ID_MAX_LIM) {
			resetIdstr();
			return 0;
		}
		*(id + i) = 0;
	}

	return -1;
}

const char* objid::getIdstr() {
	return (const char*) idstr;
}

objid* objid::childId() {
	lock.lock();

	objid* tid = new objid(id);
	int i = increment();

	lock.unlock();

	if (i < 0) {
		delete (tid);
		return (objid*) nullptr;
	}

	return tid;
}

bool objid::operator ==(objid* tid) {
	return strcmp(tid->getIdstr(), idstr) == 0;
}

bool objid::operator !=(objid* tid) {
	return strcmp(tid->getIdstr(), idstr) != 0;
}
