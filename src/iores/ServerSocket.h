/*
 * ServerSocket.h
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#if defined (_WIN32) || (_WIN64)
#include <WinSock2.h>
#endif

#include "Socket.h"

class ServerSocket {
	int sock;
	struct sockaddr_in serv;
	unsigned int serv_len;
public:
	ServerSocket( int );
	virtual ~ServerSocket();
	int bindSocket();
	int listenSocket( int );
	Socket* acceptSocket();
};

#endif /* SERVERSOCKET_H_ */
