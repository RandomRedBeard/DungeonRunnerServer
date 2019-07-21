#pragma once

#include <mutex>

#include "../globals.h"
#include "player.h"
#include "monsterres/monster.h"
#include "physmapres/physmap.h"

#include "generics.h"

class ProtocolMapper {

	int writeOp(char* buffer, int len, const char* op) {
		return snprintf(buffer, len, "%s%c", op, OP_SEP);
	}

	int hasPoint(char* buffer, int len, HasPoint* h) {
		return snprintf(buffer, len, "%d%c%d%c",
			h->getPt().getX(), POINT_SEP, h->getPt().getY(), OP_SEP);
	}

	int hasId(char* buffer, int len, HasId* h) {
		return snprintf(buffer, len, "%s%c", h->getId(), OP_SEP);
	}

	int hasType(char* buffer, int len, HasType* h) {
		return snprintf(buffer, len, "%s%c", h->getType(), OP_SEP);
	}

	int hasHealth(char* buffer, int len, HasHealth* h) {
		return snprintf(buffer, len, "%d%c%d%c",
			h->getCurHp(), HEALTH_SEP, h->getMaxHp(), OP_SEP);
	}

	int hasAttr(char* buffer, int len, HasAttr* h) {
		h->getAttrs()->lock();
		int taken = snprintf(buffer, len, "%d%c%d%c%d%c%d%c",
			h->getAttrs()->getStrength(), ATTR_SEP,
			h->getAttrs()->getDexterity(), ATTR_SEP,
			h->getAttrs()->getIntelligence(), ATTR_SEP,
			h->getAttrs()->getVitality(), OP_SEP);
		h->getAttrs()->unlock();
		return taken;
	}

	int player_s(char* buffer, int len, player* p) {
		int taken = hasType(buffer, len, p);
		taken += hasId(buffer + taken, len - taken, p);
		taken += hasPoint(buffer + taken, len - taken, p);
		taken += hasHealth(buffer + taken, len - taken, p);
		taken += hasAttr(buffer + taken, len - taken, p);
		return taken;
	}

	int message(char* buffer, int len, const char* message_buffer) {
		return snprintf(buffer, len, "%s%c", message_buffer, OP_SEP);
	}

	int physmap_s(char* buffer, int len, physmap* p) {
		return snprintf(buffer, len, "%d%c%d%c%s%c", HEIGHT, OP_SEP,
			WIDTH, OP_SEP, p->getBuffer(), OP_SEP);
	}

public:
	int move_op(char* buffer, int len, Movable* m) {
		int taken = writeOp(buffer, len, MOVE_OP);

		taken += hasType(buffer + taken, len - taken, m);

		taken += hasId(buffer + taken, len - taken, m);

		return hasPoint(buffer + taken, len - taken, m) + taken;
	}

	int enter_op(char* buffer, int len, player* p) {
		int taken = writeOp(buffer, len, ENTER_MAP_OP);

		return player_s(buffer + taken, len - taken, p) + taken;
	}

	int login_op(char* buffer, int len, HasId* h) {
		int taken = writeOp(buffer, len, PLAYER_LOGIN_OP);
		return hasId(buffer + taken, len - taken, h);
	}

	int logoff_op(char* buffer, int len, HasId* h) {
		int taken = writeOp(buffer, len, PLAYER_LOGOFF_OP);
		return hasId(buffer + taken, len - taken, h);
	}

	int global_message_op(char* buffer, int len, HasId* h, const char* message_buffer) {
		int taken = writeOp(buffer, len, GLOBAL_MESSAGE_OP);
		taken += hasId(buffer + taken, len - taken, h);
		return message(buffer + taken, len - taken, message_buffer) + taken;
	}

	int physmap_op(char* buffer, int len, physmap* p) {
		int taken = writeOp(buffer, len, PHYSMAP_OP);

		return physmap_s(buffer + taken, len - taken, p);
	}


};