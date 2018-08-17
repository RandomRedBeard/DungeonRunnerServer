/*
 * itemgen.h
 *
 *  Created on: Apr 14, 2018
 *      Author: thomasjansen
 */

#include "item.h"

#include "weapon.h"
#include "shortsword.h"
#include "longsword.h"
#include "axe.h"

#include "armor.h"
#include "leatherarmor.h"
#include "ironarmor.h"
#include "steelarmor.h"

#include "arrow.h"
#include "woodarrow.h"

#include "bow.h"
#include "woodbow.h"

#define NUMBER_OF_ITEMS 4
#define NUMBER_OF_WEAPONS 3
#define NUMBER_OF_ARMORS 3
#define NUMBER_OF_ARROWS 1
#define NUMBER_OF_BOWS 1

item* createItem(objid*, int);

weapon* createWeapon(objid*, int);

armor* createArmor(objid*, int);

arrow* createArrow(objid*, int);

bow* createBow(objid*, int);


