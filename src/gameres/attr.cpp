#include "attr.h"

attr::attr() {
	strength = intelligence = dexterity = vitality = 0;
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

int attr::lock() {
	l.lock();
	return 0;
}

int attr::unlock() {
	l.unlock();
	return 0;
}

void attr::rand_stats(int lvl, int n) {
	int** buffer = (int**)malloc(sizeof(int*) * 4);
	*(buffer) = &strength;
	*(buffer + 1) = &dexterity;
	*(buffer + 2) = &intelligence;
	*(buffer + 3) = &vitality;

	int n1, n2, lim = 50 + rand() % 50;
	for (int i = 0; i < lim; i++) {
		n1 = rand() % 4;
		n2 = rand() % 4;
		int* temp = *(buffer + n1);
		*(buffer + n1) = *(buffer + n2);
		*(buffer + n2) = temp;
	}

	for (int i = 0; i < n; i++) {
		**(buffer + i) = (2 + rand() % 10) * lvl;
	}

	free(buffer);
}

void attr::operator=(attr* a) {
	strength = a->getStrength();
	dexterity = a->getDexterity();
	intelligence = a->getIntelligence();
	vitality = a->getVitality();
}

void attr::operator+=(attr* a) {
	strength += a->getStrength();
	dexterity += a->getDexterity();
	intelligence += a->getIntelligence();
	vitality += a->getVitality();
}

void attr::operator-=(attr* a) {
	strength -= a->getStrength();
	dexterity -= a->getDexterity();
	intelligence -= a->getIntelligence();
	vitality -= a->getVitality();
}

void attr::operator+=(int i) {
	strength += i;
	dexterity += i;
	intelligence += i;
	vitality += i;
}

void attr::operator-=(int i) {
	strength -= i;
	dexterity -= i;
	intelligence -= i;
	vitality -= i;
}
