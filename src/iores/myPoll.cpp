#include "myPoll.h"

int mypoll(struct pollfd* pfd, int fds, int timeout) {
#ifdef _WIN32
	return WSAPoll(pfd, fds, timeout);
#else
	return poll(pfd, fds, timeout);
#endif
}