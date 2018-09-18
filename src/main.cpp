/*
 * main.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: thomasjansen
 */

//Unsure about def

//#define _CRT_RAND_S

#include <limits.h>

#include <thread>

#include "topt/topt.h"

#include "globals.h"
#include "log.h"
#include "iores/Socket.h"
#include "iores/ServerSocket.h"
#include "gameres/monsterres/monster.h"
#include "gameres/objid.h"
#include "gameres/point.h"
#include "gameres/probability.h"
#include "gameres/protocols.h"
#include "gameres/map.h"
#include "game.h"

#ifdef _WIN32
#pragma comment(lib,"Ws2_32.lib")
#endif

game g;

#define PORT_ARG 'p'
#define LOGFILE_ARG 'l'
#define TIMEOUT_ARG 't'
#define IDLEN_ARG 'L'
#define IDMAX_ARG 'M'
#define STDLEN_ARG 'S'
#define ACSKEW_ARG 'A'
#define HEIGHT_ARG 'H'
#define WIDTH_ARG 'W'
#define ROOM_NUMBER_ARG 'R'

#define ARGSTRING "p:l:t:L:M:S:A:H:W:R:"

int POLL_WAIT_TIMEOUT = -1;
char* LOG_FILE = (char*) "log.txt";
unsigned int ID_LEN = 2;
unsigned int ID_MAX_LIM = INT_MAX;
double AC_SKEW = .005;
#if !defined (_WIN32) || (_WIN64)
unsigned int STD_LEN = 128;
#endif
unsigned int HEIGHT = 25;
unsigned int WIDTH = 80;
unsigned int MAX_POINT_STR_LEN;
unsigned int SQRT_ROOM_N = 3;

unsigned int MIN_NUMBER_ARROWS = 1;
unsigned int MAX_NUMBER_ARROWS = 6;

int getPoint(char*, point*);
int getDamage(char*, int*, int*);
int getHealth(char*, int*, int*);

void readerThread(Socket*);
player* joinServer(Socket*);

int playerMove(player*, map*);
int playerMelee(player*, map*);
int playerRange(player*, map*);
int playerPickUp(player*, map*);
int playerDrop(player*, map*);
int playerEquip(player*, map*);
int playerUnequip(player*, map*);

int globalMessage(player*);

int main(int argc, char** argv) {
	int opt, port = 5000;
	while ((opt = tgetopt(argc, argv, ARGSTRING)) != -1) {
		switch (opt) {
		case PORT_ARG:
			port = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case LOGFILE_ARG:
			LOG_FILE = toptarg;
			break;
		case TIMEOUT_ARG:
			POLL_WAIT_TIMEOUT = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case IDLEN_ARG:
			ID_LEN = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case IDMAX_ARG:
			ID_MAX_LIM = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case STDLEN_ARG:
			//STD_LEN = strtol(optarg, NULL, 0); //atoi(optarg);
			break;
		case ACSKEW_ARG:
			AC_SKEW = strtod(toptarg, NULL);
			break;
		case HEIGHT_ARG:
			HEIGHT = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case WIDTH_ARG:
			WIDTH = strtol(toptarg, NULL, 0); //atoi(optarg);
			break;
		case ROOM_NUMBER_ARG:
			SQRT_ROOM_N = sqrt(strtol(toptarg, NULL, 0)); //atoi(optarg));
			break;
		}
	}

	MAX_POINT_STR_LEN = snprintf( NULL, 0, "%d%c%d", HEIGHT, POINT_SEP, WIDTH);
#if defined (_WIN32) || (_WIN64)
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

	ServerSocket* serv = new ServerSocket(port);
	if (serv->bindSocket() < 0) {
		opt = errno;
		printf("%s\n", strerror(opt));
		return -1;
	}

	serv->listenSocket(10);

	Socket* fd;
	std::thread t;

	while (1) {
		fd = serv->acceptSocket();
		if (!fd) {
			logerr("Failed to accept Socket\n");
			continue;
		}

		t = std::thread(&readerThread, fd);
		t.detach();
	}

	return -1;
}

int getPoint(char* buffer, point* pt) {
	if (strlen(buffer) > MAX_POINT_STR_LEN) {
		return -1;
	}
	char* after = strchr(buffer, POINT_SEP);
	if (!after) {
		return -1;
	}

	int ind = after - buffer;
	*(buffer + ind) = '\0';

	unsigned int bufferlen = strlen(buffer);
	unsigned int afterlen = strlen(after);

	for (unsigned int i = 0; i < bufferlen; i++) {
		if (!isdigit(*(buffer + i))) {
			return -1;
		}
	}

	for (unsigned int i = 0; i < afterlen; i++) {
		if (!isdigit(*(after + i))) {
			return -1;
		}
	}


		int x, y;
	x = strtol(buffer, NULL, 0);
	y = strtol(buffer + ind + 1, NULL, 0);

	pt->setPoint(x, y);
	return 0;
}

int getDamage(char* buffer, int* xd, int* nd) {
	char* after = strchr(buffer, DAMAGE_SEP);
	if (!after) {
		return -1;
	}

	int ind = after - buffer;
	*(buffer + ind) = '\0';

	unsigned int bufferlen = strlen(buffer);
	unsigned int afterlen = strlen(after);

	for (unsigned int i = 0; i < bufferlen; i++) {
		if (!isdigit(*(buffer + i))) {
			return -1;
		}
	}

	for (unsigned int i = 0; i < afterlen; i++) {
		if (!isdigit(*(after + i))) {
			return -1;
		}
	}

	*xd = strtol(buffer, NULL, 0);
	*nd = strtol(buffer + ind + 1, NULL, 0);

	return 0;
}

int getHealth(char* buffer, int* chp, int* mhp) {
	char* after = strchr(buffer, HEALTH_SEP);
	if (!after) {
		return -1;
	}

	int ind = after - buffer;
	*(buffer + ind) = '\0';

	unsigned int bufferlen = strlen(buffer);
	unsigned int afterlen = strlen(after);

	for (unsigned int i = 0; i < bufferlen; i++) {
		if (!isdigit(*(buffer + i))) {
			return -1;
		}
	}

	for (unsigned int i = 0; i < afterlen; i++) {
		if (!isdigit(*(after + i))) {
			return -1;
		}
	}

	*chp = strtol(buffer, NULL, 0);
	*mhp = strtol(buffer + ind + 1, NULL, 0);

	return 0;
}

void readerThread(Socket* fd) {
	srand(time(0));
	player* p = joinServer(fd);
	if (!p) {
		delete (fd);
		return;
	}

	if (g.addPlayer(p) < 0) {
		delete (p);
		return;
	}
	map* m = g.getLowestMap(p);
	if (!m) {
		g.removePlayer(p);
		delete (p);
		return;
	}

	if (m->addPlayer(p) < 0) {
		g.checkCleanup(m);
		g.removePlayer(p);
		delete (p);
	}

	char buffer[STD_LEN];
	while (p->read(buffer) > 0) {
		if (strcmp(buffer, MOVE_OP) == 0) {
			if (playerMove(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, MELEE_OP) == 0) {
			if (playerMelee(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, RANGE_OP) == 0) {
			if (playerRange(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, PICKUP_OP) == 0) {
			if (playerPickUp(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, DROP_OP) == 0) {
			if (playerDrop(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, EQUIP_OP) == 0) {
			if (playerEquip(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, UNEQUIP_OP) == 0) {
			if (playerUnequip(p, m) < 0) {
				break;
			}
		} else if (strcmp(buffer, TRAVEL_REQUEST_OP) == 0) {
			if (m->removePlayer(p) < 0) {
				break;
			}

			m = g.getNextMap(p, m);
			if (!m) {
				break;
			}

			if (m->addPlayer(p) < 0) {
				break;
			}
		} else if (strcmp(buffer, GLOBAL_MESSAGE_OP) == 0) {
			if (globalMessage(p) < 0) {
				break;
			}
		} else {
			printf("%s\n", buffer);
			break;
		}
	}

	if (m) {
		m->removePlayer(p);
		g.checkCleanup(m);
	}

	g.removePlayer(p);

	delete (p);
}

player* joinServer(Socket* fd) {
	char join[STD_LEN], name[STD_LEN];
	if (fd->read(join, STD_LEN) < 0) {
		return (player*) nullptr;
	}

	if (strcmp(join, JOIN_OP) != 0) {
		return (player*) nullptr;
	}

	if (fd->read(name, STD_LEN) < 0) {
		return (player*) nullptr;
	}

	player* p = new player(fd);
	p->setName(name);

	return p;
}

int playerMove(player* p, map* m) {
	char pointBuffer[STD_LEN];
	if (p->read(pointBuffer) < 0) {
		return -1;
	}

	point pt;
	if (getPoint(pointBuffer, &pt) < 0) {
		return -1;
	}

	return m->playerMove(p, pt);
}

int playerMelee(player* p, map* m) {
	char type[STD_LEN], id[STD_LEN];
	if (p->read(type) < 0) {
		return -1;
	}

	if (p->read(id) < 0) {
		return -1;
	}

	if (strcmp(type, MONSTER_OP) == 0) {
		return m->playerMeleeMonster(p, id, p->melee());
	}

	return -1;
}

int playerRange(player* p, map* m) {
	char type[STD_LEN], id[STD_LEN];
	if (p->read(type) < 0) {
		return -1;
	}

	if (p->read(id) < 0) {
		return -1;
	}

	if (strcmp(type, MONSTER_OP) == 0) {
		return m->playerRangeMonster(p, id, p->range());
	}

	return -1;
}

int playerPickUp(player* p, map* m) {
	return m->playerPickup(p);
}

int playerDrop(player* p, map* m) {
	char id[STD_LEN];

	if (p->read(id) < 0) {
		return -1;
	}

	return m->playerDrop(p, id);
}

int playerEquip(player* p, map* m) {
	char id[STD_LEN], part[STD_LEN];

	if (p->read(id) < 0) {
		return -1;
	}

	if (p->read(part) < 0) {
		return -1;
	}

	return m->playerEquip(p, id, part);
}

int playerUnequip(player* p, map* m) {
	char part[STD_LEN];

	if (p->read(part) < 0) {
		return -1;
	}

	return m->playerUnequip(p, part);
}

int globalMessage(player* p) {
	char buffer[STD_LEN];
	if (p->read(buffer) < 0) {
		return -1;
	}

	return g.globalMessage(p, buffer);
}
