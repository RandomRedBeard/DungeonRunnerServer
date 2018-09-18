/*
 * Socket.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: thomasjansen
 */

#include "Socket.h"

Socket::Socket(int f) :
		fd(f) {
}

Socket::Socket() {
	fd = -1;
}

Socket::Socket(std::string addr, int port) {
	fd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(addr.c_str());
	serv.sin_port = htons(port);
	serv_len = sizeof(serv);

	connect(fd, (sockaddr*)&serv, serv_len);
}

Socket::~Socket() {
	closeSocket();
}

int Socket::read(char* buffer, int len) {
	return readln(fd, buffer, len);
}

int Socket::write(const char* buffer, int len) {
	return writeStream(fd, buffer, len);
}

int Socket::closeSocket() {
#if defined (_WIN32) || (_WIN64)
	return closesocket(fd);
#else
	return close(fd);
#endif
}

int Socket::shutdownSocket() {
	return shutdown(fd, 2);
}
