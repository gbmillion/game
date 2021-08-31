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
	int amount;//item id number, not amount
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
	char clas[25];
};
void load_clas(struct class *toon){
	char class_name[25] = "mage";
	if ( strcmp(  &class_name,  &toon->clas ) == 0 ){
		toon->Dexterity=10;
		toon->Stamina=10;
		toon->Wisdom=10;
		toon->Strength=10;
		toon->Intelligence=18;
		toon->Agility=16;
	}
	class_name[25] = "fighter";
	if ( strcmp(  &class_name,  &toon->clas ) == 0 ){
		toon->Dexterity=10;
		toon->Stamina=16;
		toon->Wisdom=10;
		toon->Strength=18;
		toon->Intelligence=10;
		toon->Agility=10;
	}
	class_name[25] = "healer";
	if ( strcmp(  &class_name,  &toon->clas ) == 0 ){
		toon->Dexterity=10;
		toon->Stamina=16;
		toon->Wisdom=18;
		toon->Strength=10;
		toon->Intelligence=10;
		toon->Agility=10;
	}
	class_name[25] = "rouge";
	if ( strcmp(  &class_name,  &toon->clas ) == 0 ){
		toon->Dexterity=18;
		toon->Stamina=10;
		toon->Wisdom=10;
		toon->Strength=10;
		toon->Intelligence=10;
		toon->Agility=16;
	}
}
#endif /* CLASS_H_ */
