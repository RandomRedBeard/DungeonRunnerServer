#include "attr.h"

attr::attr() {
	strength = intelligence = dexterity = vitality = 1;
}

void attr::setStrength(int s) {
	lock.lock();
	strength = s;
	lock.unlock();
}

int attr::getStrength() {
	lock.lock();
	int i = strength;
	lock.unlock();
	return i;
}

void attr::setIntelligence(int i) {
	lock.lock();
	intelligence = i;
	lock.unlock();
}

int attr::getIntelligence() {
	lock.lock();
	int i = intelligence;
	lock.unlock();
	return i;
}

void attr::setDexterity(int d) {
	lock.lock();
	dexterity = d;
	lock.unlock();
}

int attr::getDexterity() {
	lock.lock();
	int i = dexterity;
	lock.unlock();
	return i;
}

void attr::setVitality(int v) {
	lock.lock();
	vitality = v;
	lock.unlock();
}

int attr::getVitality() {
	lock.lock();
	int i = vitality;
	lock.unlock();
	return i;
}

void attr::operator=(attr* a) {
	lock.lock();
	strength = a->getStrength();
	dexterity = a->getDexterity();
	intelligence = a->getIntelligence();
	vitality = a->getVitality();
	lock.unlock();
}
