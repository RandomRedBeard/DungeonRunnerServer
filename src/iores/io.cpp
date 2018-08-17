/*
 * s_io.c
 *
 *  Created on: Oct 3, 2017
 *      Author: thomasjansen
 */

#include "io.h"

int writeStream(const int fd, const char* buffer, int len) {
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLOUT;
	int nwritten = 0, pollerr, n;

	pollerr = POLLHUP | POLLNVAL | POLLERR;

	do {
		if (mypoll(&pfd, 1, POLL_WAIT_TIMEOUT) < 0) {
			return -1;
		}

		if (pfd.revents & pollerr) {
			return -1;
		}

		if ((n = send(fd, (buffer + nwritten), len, 0)) < 0) {
			return -1;
		}

		if (n == 0)
			break;

		len -= n;
		nwritten += n;


	} while (len > 0);

	return nwritten;
}

int readStream(const int fd, char* buffer, int len) {
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;

	int n, pollerr;

	pollerr = POLLHUP | POLLNVAL | POLLERR;

	n = mypoll(&pfd, 1, POLL_WAIT_TIMEOUT);

	if (n < 0) {
		return -1;
	}

	if (pfd.revents & pollerr) { //CLOSED Socket
		return -1;
	}

	if ((n = recv(fd, buffer, len, 0)) < 0) {
		return -1;
	}

	buffer[n] = '\0';
	return n;
}

int readln(const int fd, char* buffer, int len) {
	int ntaken = 0, n;
	while (ntaken < len) {
		n = readStream(fd, (buffer + ntaken), 1);
		if (n == 0)
			return n;
		if (n == -1)
			return n;
		if (*(buffer + ntaken) == OP_SEP)
			break;
		ntaken += n;
	}
	*(buffer + ntaken) = '\0';
	return ntaken;
}

