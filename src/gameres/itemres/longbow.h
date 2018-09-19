#ifndef LONGBOW_H_
#define LONGBOW_H_

#include "bow.h"

class longbow: public bow {
public:
	longbow(objid*, int, const int baseMax = 4, const int baseMin = 2,
		const int rangeMax = 9, const int rangeMin = 3);
};

#endif
