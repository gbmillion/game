/*
 * class.h
 *
 *  Created on: Aug 31, 2021
 *      Author: user
 */

#ifndef CLASS_H_
#define CLASS_H_
// maybe add predefined classes at some point
struct item{
	char type[255];
	char trait[255];
	int amount;
};
struct class{
	char name[25];
	int Charisma;
	int Dexterity;
	int Stamina;
	int Wisdom;
	int Strength;
	int Intelligence;
	int Agility;
	int hp;
	int mana;
	struct item inventory[100];
};


#endif /* CLASS_H_ */
