#ifndef ATTR_H_
#define ATTR_H_

#include <stdlib.h>

#include <mutex>

class attr {
	std::mutex l;
	int strength, intelligence, dexterity, vitality;
public:
	attr();

	void setStrength(int);
	int getStrength();
	void setIntelligence(int);
	int getIntelligence();
	void setDexterity(int);
	int getDexterity();
	void setVitality(int);
	int getVitality();

	int lock();
	int unlock();

	void rand_stats(int, int);

	void operator=(attr*);
	void operator+=(attr*);
	void operator-=(attr*);

	void operator+=(int);
	void operator-=(int);
};

#endif
