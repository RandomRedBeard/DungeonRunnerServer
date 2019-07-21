/*
 * Socket.h
 *
 *  Created on: Nov 17, 2017
 *      Author: thomasjansen
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#if defined (_WIN32) || (_WIN64)
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <string>

#include "io.h"

#ifdef _WIN32
  #ifdef BUILDING_DLL
      #define DLL_PUBLIC __declspec(dllexport)
  #else
      #define DLL_PUBLIC __declspec(dllimport)
  #endif
#else
  #define DLL_PUBLIC
#endif

class DLL_PUBLIC Socket {
	int fd;
	struct sockaddr_in serv;
	unsigned int serv_len;
	int poll_wait;
	char op_sep;
public:
	Socket(int);
	Socket();
	Socket(std::string, int);
	~Socket();

	void setPollWait(int);
	void setOpSep(char);

	int read(char*, int);
	int write(const char*, int);
	int closeSocket();
	int shutdownSocket();
};

class DLL_PUBLIC ServerSocket {
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

#endif /* SOCKET_H_ */
