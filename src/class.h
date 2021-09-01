/*
 * class.h
 *
 *  Created on: Aug 31, 2021
 *      Author: user
 */

#ifndef CLASS_H_
#define CLASS_H_

#include <string.h>
//#define DEBUG_STATE ;
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
struct class{//base class template
	char name[25];
	int Dexterity;
	int Stamina;
	int Wisdom;
	int Strength;
	int Intelligence;
	int Agility;
	int hp;
	int mana;
	struct item inventory[100];
	char clas[25];
};
void load_clas(struct class *toon){//apply predefined class templates
	char class_name[25] = "mage";

	int error=strcmp(  class_name,  toon->clas );
#if defined DEBUG_STATE
	printf("%s equals %s %d : %d\n",class_name,  toon->clas,class_name[4], toon->clas[4]);
#endif
	if ( error == 0 ){
		toon->Dexterity=10;
		toon->Stamina=10;
		toon->Wisdom=10;
		toon->Strength=10;
		toon->Intelligence=18;
		toon->Agility=16;
#if defined DEBUG_STATE
		printf("Applied mage.\n");
#endif
	}
	strcpy(( char *) &class_name, (const char *)"fighter" );
	 error=strcmp(  class_name,  toon->clas );
	#if defined DEBUG_STATE
		printf("%s equals %s %d : %d\n",class_name,  toon->clas,class_name[4], toon->clas[4]);
	#endif
		if ( error == 0 ){
		toon->Dexterity=10;
		toon->Stamina=16;
		toon->Wisdom=10;
		toon->Strength=18;
		toon->Intelligence=10;
		toon->Agility=10;
#if defined DEBUG_STATE
		printf("Applied fighter.\n");
#endif
	}
		strcpy( ( char *)&class_name, (const char *)"healer");
	 error=strcmp(  class_name,  toon->clas );
	#if defined DEBUG_STATE
		printf("%s equals %s %d : %d\n",class_name,  toon->clas,class_name[4], toon->clas[4]);
	#endif
		if ( error == 0 ){
		toon->Dexterity=10;
		toon->Stamina=16;
		toon->Wisdom=18;
		toon->Strength=10;
		toon->Intelligence=10;
		toon->Agility=10;
#if defined DEBUG_STATE
		printf("Applied healer.\n");
#endif
	}
	strcpy( ( char *)&class_name, (const char *)"rouge" );
	 error=strcmp(  class_name,  toon->clas );
	#if defined DEBUG_STATE
		printf("%s equals %s %d : %d\n",class_name,  toon->clas,class_name[4], toon->clas[4]);
	#endif
		if ( error == 0 ){
		toon->Dexterity=18;
		toon->Stamina=10;
		toon->Wisdom=10;
		toon->Strength=10;
		toon->Intelligence=10;
		toon->Agility=16;
#if defined DEBUG_STATE
		printf("Applied rouge.\n");
#endif
	}
}
#endif /* CLASS_H_ */
