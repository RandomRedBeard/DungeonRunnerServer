/*
 * protocols.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef PROTOCOLS_H_
#define PROTOCOLS_H_

#include "../globals.h"
#include "point.h"
#include "objid.h"
#include "player.h"
#include "monsterres/monster.h"
#include "itemres/itemgen.h"
#include "physmapres/physmap.h"

int player_login_op(char*, int, player*);
int player_logoff_op(char*, int, player*);

int global_message_op(char*, int, player*, const char*);

int accept_travel_op(char*, int, player*);

int physmap_op(char*, int, physmap*);

int enter_map_op(char*, int, player*);
int enter_map_op(char*, int, monster*);
int enter_map_op(char*, int, item*);
int enter_map_op(char*, int, weapon*);
int enter_map_op(char*, int, armor*);
int enter_map_op(char*, int, arrow*);
int enter_map_op(char*, int, bow*);

int exit_map_op(char*, int, player*);

int move_op(char*, int, player*);
int move_op(char*, int, monster*);

int melee_op(char*, int, player*, monster*, int);
int melee_op(char*, int, monster*, player*, int);

int range_op(char*, int, player*, monster*, int);

int miss_range_op(char*, int, player*, arrow*);

int killed_op(char*, int, player*, monster*);
int killed_op(char*, int, monster*, player*);

int pickup_op(char*, int, player*, item*);

int drop_op(char*, int, player*, item*);
int drop_op(char*, int, player*, weapon*);
int drop_op(char*, int, player*, armor*);
int drop_op(char*, int, player*, arrow*);
int drop_op(char*, int, player*, bow*);

int equip_op(char*, int, player*, const char*, const char*);

int unequip_op(char*, int, player*, const char*);

int levelup_op(char*, int, player*);

int allocate_attr_op(char*, int, player*, const char*);

#endif /* PROTOCOLS_H_ */
