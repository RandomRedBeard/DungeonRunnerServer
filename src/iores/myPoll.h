#ifndef _MYPOLL_H
#define _MYPOLL_H

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <poll.h>
#endif

int mypoll(struct pollfd*, int, int);

#endif