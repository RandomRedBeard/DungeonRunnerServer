#include "attr.h"

attr::attr() {
	strength = intelligence = dexterity = vitality = 1;
}

void attr::setStrength(int s) {
	strength = s;
}

int attr::getStrength() {
	int i = strength;
	return i;
}

void attr::setIntelligence(int i) {
	intelligence = i;
}

int attr::getIntelligence() {
	int i = intelligence;
	return i;
}

void attr::setDexterity(int d) {
	dexterity = d;
}

int attr::getDexterity() {
	int i = dexterity;
	return i;
}

void attr::setVitality(int v) {
	vitality = v;
}

int attr::getVitality() {
	int i = vitality;
	return i;
}

void attr::operator=(attr* a) {
	strength = a->getStrength();
	dexterity = a->getDexterity();
	intelligence = a->getIntelligence();
	vitality = a->getVitality();
}
