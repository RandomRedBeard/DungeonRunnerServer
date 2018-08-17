/*
 * log.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: thomasjansen
 */

#include "log.h"

std::mutex logLock;

int initLog() {
	return 0;
}

int loginfo(std::string format, ...) {
	logLock.lock();
	va_list ap;

	FILE* fd = fopen( LOG_FILE, "a");

	if (!fd) {
		logLock.unlock();
		return -1;
	}

	va_start(ap, format);
	vfprintf(fd, format.c_str(), ap);
	va_end(ap);

	fclose(fd);

	logLock.unlock();

	return 0;
}

int logerr(std::string format, ...) {
	logLock.lock();

	va_list ap;

	FILE* fd = fopen( LOG_FILE, "a");

	if (!fd) {
		logLock.unlock();
		return -1;
	}

	fprintf(fd, "Error: ");

	va_start(ap, format);
	vfprintf(fd, format.c_str(), ap);
	va_end(ap);

	fclose(fd);

	logLock.unlock();

	return 0;
}



