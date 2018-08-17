/*
 * log.h
 *
 *  Created on: Nov 16, 2017
 *      Author: thomasjansen
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string>
#include <mutex>

#include "globals.h"

int initLog();

int loginfo(std::string, ...);

int logerr(std::string, ...);

#endif /* LOG_H_ */
