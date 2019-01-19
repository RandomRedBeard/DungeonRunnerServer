/*
 * globals.h
 *
 *  Created on: Jan 10, 2018
 *      Author: thomasjansen
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

//IO GLOBALS
extern int POLL_WAIT_TIMEOUT;

#define OP_SEP '\n'

//LOG GLOBALS
extern char* LOG_FILE;

//ID GLOBALS
extern unsigned int ID_LEN;
extern unsigned int ID_MAX_LIM;

//MAP GLOBALS
extern unsigned int HEIGHT;
extern unsigned int WIDTH;
extern unsigned int SQRT_ROOM_N;

#define VERT_WALL '|'
#define HORZ_WALL '-'
#define FLOOR '.'
#define HALLWAY_ENTRANCE '+'
#define HALLWAY_FLOOR '#'

#define STATE_OK 0
#define STATE_UNRECOVERABLE -1

//DAMAGE GLOBALS
extern double AC_SKEW;

#define DAMAGE_SEP ';'

//STD GLOBALS
#if defined (_WIN32) || (_WIN64)
const unsigned int STD_LEN = 128;
#else
extern unsigned int STD_LEN;// = 128;
#endif

//STATE GLOBALS
#define STATE_NORM 0
#define STATE_EXIT -1
#define STATE_DEAD 1

//PROTOCOL GLOBALS
#define POINT_SEP ';'
#define HEALTH_SEP ';'
#define ATTR_SEP ';'

#define JOIN_OP "Join"

#define PHYSMAP_OP "PhysicalMap"

#define PLAYER_LOGIN_OP "PlayerLogin"
#define PLAYER_LOGOFF_OP "PlayerLogoff"

#define GLOBAL_MESSAGE_OP "GlobalMessage"

#define TRAVEL_REQUEST_OP "RequestTravel"
#define ACCEPT_TRAVEL_OP "AcceptTravel"
#define ENTER_MAP_OP "EnterMap"
#define EXIT_MAP_OP "ExitMap"

#define MOVE_OP "Move"
#define MELEE_OP "Melee"
#define RANGE_OP "Range"
#define KILLED_OP "Killed"
#define PICKUP_OP "PickUp"
#define DROP_OP "Drop"
#define EQUIP_OP "Equip"
#define UNEQUIP_OP "Unequip"
#define LEVELUP_OP "LevelUp"
#define MISS_RANGE_OP "MissRange"
#define ALLOCATE_ATTR_OP "Allocate"

#define PLAYER_OP "Player"
#define MONSTER_OP "Monster"
#define WEAPON_OP "Weapon"
#define ARMOR_OP "Armor"
#define ARROW_OP "Arrow"
#define BOW_OP "Bow"
#define MAINHAND_OP "MainHand"
#define OFFHAND_OP "OffHand"
#define BODY_OP "Body"

//ARROW RELATED GLOBALS
extern unsigned int MIN_NUMBER_ARROWS;
extern unsigned int MAX_NUMBER_ARROWS;

//ATTR OPTS
#define STRENGTH "STR"
#define DEXTERITY "DEX"
#define INTELLIGENCE "INT"
#define VITALITY "VIT"

#endif /* GLOBALS_H_ */
