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
};/*
Format goes as is:
type[string of name of type of item],trait[the class trait effected by the item],amount[item id number],
each item has a unique id number, with examples being:
potion,Wisdom,1
weapon,Strength,2
*/
struct class{
	char name[25];
	int Dexterity;//Implemented
	int Stamina;//Implemented
	int Wisdom;//Implemented
	int Strength;//Implemented
	int Intelligence;//Implemented
	int Agility;//Implemented
	int hp; //Implemented
	int mana; //Implemented
	struct item inventory[100];
};


#endif /* CLASS_H_ */
