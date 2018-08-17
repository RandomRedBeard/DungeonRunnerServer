/*
 * protocols.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#include "protocols.h"

int player_login_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c", PLAYER_LOGIN_OP, OP_SEP,
			p->getName(), OP_SEP);
}

int player_logoff_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c", PLAYER_LOGOFF_OP, OP_SEP,
			p->getName(), OP_SEP);
}

int global_message_op(char* buffer, int len, player* p, const char* message) {
	return snprintf(buffer, len, "%s%c%s%c%s%c", GLOBAL_MESSAGE_OP, OP_SEP,
			p->getName(), OP_SEP, message, OP_SEP);
}

int accept_travel_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%d%c%d%c", ACCEPT_TRAVEL_OP, OP_SEP,
			p->getPt().getX(), POINT_SEP, p->getPt().getY(), OP_SEP);
}

int physmap_op(char* buffer, int len, physmap* p) {
	return snprintf(buffer, len, "%s%c%d%c%d%c%s%c", PHYSMAP_OP, OP_SEP, HEIGHT,
			OP_SEP, WIDTH, OP_SEP, p->getBuffer(), OP_SEP);
}

int enter_map_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c",
	ENTER_MAP_OP, OP_SEP, PLAYER_OP, OP_SEP, p->getName(), OP_SEP,
			p->getPt().getX(), POINT_SEP, p->getPt().getY(), OP_SEP,
			p->getLvl(), OP_SEP, p->getCurHp(), HEALTH_SEP, p->getMaxHp(),
			OP_SEP);
}

int enter_map_op(char* buffer, int len, monster* m) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c",
	ENTER_MAP_OP, OP_SEP, MONSTER_OP, OP_SEP, m->getId()->getIdstr(),
	OP_SEP, m->getName(), OP_SEP, m->getPt().getX(), POINT_SEP,
			m->getPt().getY(), OP_SEP, m->getLvl(), OP_SEP, m->getCurHp(),
			HEALTH_SEP, m->getMaxHp(), OP_SEP, m->getAc(), OP_SEP);
}

int enter_map_op(char* buffer, int len, item* it) {
	weapon* w = dynamic_cast<weapon*>(it);
	armor* a = dynamic_cast<armor*>(it);
	arrow* ar = dynamic_cast<arrow*>(it);
	bow* b = dynamic_cast<bow*>(it);

	if (b) {
		return enter_map_op(buffer, len, b);
	}

	if (w) {
		return enter_map_op(buffer, len, w);
	}

	if (a) {
		return enter_map_op(buffer, len, a);
	}

	if (ar) {
		return enter_map_op(buffer, len, ar);
	}

	return -1;
}

int enter_map_op(char* buffer, int len, weapon* w) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c",
	ENTER_MAP_OP, OP_SEP, WEAPON_OP, OP_SEP, w->getId()->getIdstr(),
			OP_SEP, w->getName(), OP_SEP, w->getPt().getX(), POINT_SEP,
			w->getPt().getY(), OP_SEP, w->getLvl(), OP_SEP, w->getMaxDmg(),
			DAMAGE_SEP, w->getMinDmg(), OP_SEP);
}

int enter_map_op(char* buffer, int len, armor* a) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c",
	ENTER_MAP_OP, OP_SEP, ARMOR_OP, OP_SEP, a->getId()->getIdstr(),
	OP_SEP, a->getName(), OP_SEP, a->getPt().getX(), POINT_SEP,
			a->getPt().getY(), OP_SEP, a->getLvl(), OP_SEP, a->getAc(), OP_SEP);
}

int enter_map_op(char* buffer, int len, arrow* ar) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c",
	ENTER_MAP_OP, OP_SEP, ARROW_OP, OP_SEP, ar->getId()->getIdstr(),
	OP_SEP, ar->getName(), OP_SEP, ar->getPt().getX(), POINT_SEP,
			ar->getPt().getY(), OP_SEP, ar->getLvl(), OP_SEP, ar->getMaxDmg(),
			DAMAGE_SEP, ar->getMinDmg(), OP_SEP, ar->getNumberArrows(), OP_SEP);
}

int enter_map_op(char* buffer, int len, bow* b) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c",
			ENTER_MAP_OP, OP_SEP, BOW_OP, OP_SEP, b->getId()->getIdstr(),
			OP_SEP, b->getName(), OP_SEP, b->getPt().getX(), POINT_SEP,
			b->getPt().getY(), OP_SEP, b->getLvl(), OP_SEP, b->getMaxDmg(),
			DAMAGE_SEP, b->getMinDmg(), OP_SEP, b->getRangeMaxDmg(), DAMAGE_SEP,
			b->getRangeMinDmg(), OP_SEP);
}

int exit_map_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c", EXIT_MAP_OP, OP_SEP, p->getName(),
			OP_SEP);
}

int move_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%d%c%d%c", MOVE_OP, OP_SEP,
	PLAYER_OP, OP_SEP, p->getName(), OP_SEP, p->getPt().getX(),
	POINT_SEP, p->getPt().getY(), OP_SEP);
}

int move_op(char* buffer, int len, monster* m) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%d%c%d%c", MOVE_OP, OP_SEP,
	MONSTER_OP, OP_SEP, m->getId()->getIdstr(), OP_SEP, m->getPt().getX(),
			POINT_SEP, m->getPt().getY(), OP_SEP);
}

int melee_op(char* buffer, int len, player* p, monster* m, int dmg) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c", MELEE_OP,
			OP_SEP,
	PLAYER_OP, OP_SEP, p->getName(), OP_SEP, MONSTER_OP, OP_SEP,
			m->getId()->getIdstr(), OP_SEP, dmg, OP_SEP);
}

int melee_op(char* buffer, int len, monster* m, player* p, int dmg) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c", MELEE_OP, OP_SEP,
	MONSTER_OP, OP_SEP, m->getId()->getIdstr(), OP_SEP, PLAYER_OP,
	OP_SEP, p->getName(), OP_SEP, dmg, OP_SEP);
}

int range_op(char* buffer, int len, player* p, monster* m, int dmg) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c", RANGE_OP, OP_SEP,
			PLAYER_OP, OP_SEP, p->getName(), OP_SEP, MONSTER_OP, OP_SEP,
			m->getId()->getIdstr(), OP_SEP, dmg, OP_SEP);
}

int killed_op(char* buffer, int len, player* p, monster* m) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c", KILLED_OP, OP_SEP,
			PLAYER_OP, OP_SEP, p->getName(), OP_SEP, MONSTER_OP, OP_SEP,
			m->getId()->getIdstr(), OP_SEP, m->getXp(), OP_SEP);
}

int killed_op(char* buffer, int len, monster* m, player* p) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c", KILLED_OP, OP_SEP,
			MONSTER_OP, OP_SEP, m->getId()->getIdstr(), OP_SEP, PLAYER_OP,
			OP_SEP, p->getName(), OP_SEP);
}

int pickup_op(char* buffer, int len, player* p, item* it) {
	return snprintf(buffer, len, "%s%c%s%c%s%c", PICKUP_OP, OP_SEP,
			p->getName(), OP_SEP, it->getId()->getIdstr(), OP_SEP);
}

int drop_op(char* buffer, int len, player* p, item* it) {
	weapon* w = dynamic_cast<weapon*>(it);
	armor* a = dynamic_cast<armor*>(it);
	arrow* ar = dynamic_cast<arrow*>(it);
	bow* b = dynamic_cast<bow*>(it);

	if (b) {
		return drop_op(buffer, len, p, b);
	}

	if (w) {
		return drop_op(buffer, len, p, w);
	}

	if (a) {
		return drop_op(buffer, len, p, a);
	}

	if (ar) {
		return drop_op(buffer, len, p, ar);
	}

	return -1;
}

int drop_op(char* buffer, int len, player* p, weapon* w) {
	return snprintf(buffer, len,
			"%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c",
	DROP_OP, OP_SEP, p->getName(), OP_SEP, WEAPON_OP, OP_SEP,
			w->getId()->getIdstr(), OP_SEP, w->getName(), OP_SEP,
			w->getPt().getX(), POINT_SEP, w->getPt().getY(), OP_SEP,
			w->getLvl(), OP_SEP, w->getMaxDmg(), DAMAGE_SEP, w->getMinDmg(),
			OP_SEP);
}

int drop_op(char* buffer, int len, player* p, armor* a) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c",
	DROP_OP, OP_SEP, p->getName(), OP_SEP, ARMOR_OP, OP_SEP,
			a->getId()->getIdstr(), OP_SEP, a->getName(), OP_SEP,
			a->getPt().getX(), POINT_SEP, a->getPt().getY(), OP_SEP,
			a->getLvl(), OP_SEP, a->getAc(), OP_SEP);
}

int drop_op(char* buffer, int len, player* p, arrow* ar) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c",
			DROP_OP, OP_SEP, p->getName(), OP_SEP, ARROW_OP, OP_SEP,
			ar->getId()->getIdstr(), OP_SEP, ar->getName(), OP_SEP,
			ar->getPt().getX(), POINT_SEP, ar->getPt().getY(), OP_SEP,
			ar->getLvl(), OP_SEP, ar->getMaxDmg(), DAMAGE_SEP, ar->getMinDmg(),
			OP_SEP, ar->getNumberArrows(), OP_SEP);
}

int drop_op(char* buffer, int len, player* p, bow* b) {
	return snprintf(buffer, len,
			"%s%c%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c", DROP_OP, OP_SEP,
			p->getName(), OP_SEP, BOW_OP, OP_SEP, b->getId()->getIdstr(),
			OP_SEP, b->getName(), OP_SEP, b->getPt().getX(), POINT_SEP,
			b->getPt().getY(), OP_SEP, b->getLvl(), OP_SEP, b->getMaxDmg(),
			DAMAGE_SEP, b->getMinDmg(), OP_SEP, b->getRangeMaxDmg(), DAMAGE_SEP,
			b->getRangeMinDmg(), OP_SEP);
}

int equip_op(char* buffer, int len, player* p, const char* id,
		const char* eq_part) {
	return snprintf(buffer, len, "%s%c%s%c%s%c%s%c", EQUIP_OP, OP_SEP,
			p->getName(), OP_SEP, id, OP_SEP, eq_part,
			OP_SEP);
}

int unequip_op(char* buffer, int len, player* p, const char* eq_part) {
	return snprintf(buffer, len, "%s%c%s%c%s%c", UNEQUIP_OP, OP_SEP,
			p->getName(), OP_SEP, eq_part, OP_SEP);
}

int levelup_op(char* buffer, int len, player* p) {
	return snprintf(buffer, len, "%s%c%s%c%d%c", LEVELUP_OP, OP_SEP,
			p->getName(), OP_SEP, p->getLvl(), OP_SEP);
}

