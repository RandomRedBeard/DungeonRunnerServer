/*
 * ServerSocket.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket( int port ) {
	sock = socket( AF_INET , SOCK_STREAM , 0 );
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons( port );
	serv_len = sizeof( serv );
}

ServerSocket::~ServerSocket() {
#ifdef _WIN32
	closesocket(sock);
#else
	close( sock );
#endif
}

int ServerSocket::bindSocket() {
	return bind( sock , ( struct sockaddr* )&serv , serv_len );
}

int ServerSocket::listenSocket( int n ) {
	return listen( sock , n );
}

Socket* ServerSocket::acceptSocket() {
	int f;
#ifdef _WIN32
	f = accept(sock, (struct sockaddr*) &serv, (int*)&serv_len);
#else
	f = accept(sock, (struct sockaddr*) &serv, (unsigned int*)&serv_len); 
#endif

	if (f < 0) {
		return (Socket*) nullptr;
	}

	return new Socket(f);
}
