#ifndef _MYPOLL_H
#define _MYPOLL_H

#ifdef _WIN32
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <poll.h>
#endif

int mypoll(struct pollfd*, int, int);

#endif