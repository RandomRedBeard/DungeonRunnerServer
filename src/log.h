/*
 * log.h
 *
 *  Created on: Nov 16, 2017
 *      Author: thomasjansen
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>

#include <string>
#include <mutex>

#include "globals.h"

int loginfo(std::string, ...);

int logerr(std::string, ...);

#endif /* LOG_H_ */
