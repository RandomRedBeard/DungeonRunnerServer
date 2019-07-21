#pragma once

#include "point.h"
#include "attr.h"

struct HasId {
	virtual const char* getId() = 0;
};
struct HasPoint {
	virtual point getPt() = 0;
};

struct HasType {
	virtual const char* getType() = 0;
};

struct Movable : public HasId, public HasPoint, public HasType {
	virtual void setPt(point) = 0;
};

struct HasLevel {
	virtual int getLvl() = 0;
};

struct HasHealth {
	virtual int getCurHp() = 0;

	virtual int getMaxHp() = 0;
};

struct HasAttr {
	virtual attr* getAttrs() = 0;
};