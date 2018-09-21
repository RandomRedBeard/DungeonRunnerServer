#ifndef ATTR_H_
#define ATTT_H_

#include <mutex>

class attr {
	std::mutex lock;

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

	void operator=( attr* );
};

#endif
