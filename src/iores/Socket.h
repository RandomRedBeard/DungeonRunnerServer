/*
 * Socket.h
 *
 *  Created on: Nov 17, 2017
 *      Author: thomasjansen
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <string>

#include "io.h"

class Socket {
	int fd;
	struct sockaddr_in serv;
	unsigned int serv_len;
public:
	Socket(int);
	Socket();
	Socket(std::string, int);
	~Socket();
	int read(char*, int);
	int write(const char*, int);
	int closeSocket();
	int shutdownSocket();
};

#endif /* SOCKET_H_ */
