/*
 * s_io.h
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#ifndef IO_H_
#define IO_H_

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <sys/socket.h>
#endif

#include <stdio.h>
#include <errno.h>

#include "myPoll.h"

int writeStream(const int, const char*, int, int);

int readStream(const int, char*, int, int);

int readln(const int, char*, int, int, char);

int printHello();

#endif /* IO_H_ */
