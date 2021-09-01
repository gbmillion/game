/*
 ============================================================================
 Name        : game.c
 Author      : George Million
 Version     : 1.0
 Copyright   :  copyrighted 2021
 Description : randomly genorated 10x10 dungeon crawling game.
 Features: four playable classes, plus a randomly genorated one of your choice, usable items , dynamic traps,
 	 	 	 six character attributes, active combat,

 Bugs:
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "class.h"
#include <string.h>
#include <time.h>

//items database
int itemdb_size=0;
struct item db[255];

//enable debug statements and cheats
//#define DEBUG_STATE ;

//functions
void trap(int * hpp);
void item(struct item invent[100]);
void step(int * hpp, struct item  play[100]);
void gen_char(struct class *toon);
void combat(int * hpp, int monster_hp, struct class * player);
void itemdb( struct item db[255]);
void use(struct class * player);
void potion( int * trait, int buff);

int main(void) {
	//10x10 map
	int map[10][10];
	int i=0, e = 0;
	time_t t;

	itemdb(db);//load items

	srand((unsigned) time(&t));
	//build a board with randomly assigned "monster" or value
	printf("Welcome to dungeon hack!\nCommands: i[inventory],x[exit],u[use]\n");
	for(i=0;i<10;++i){
		for(e=0;e<10;++e){
			//squares have a fifty fifty chance to have a random monster value on them
			if (rand() % 100 > 50 ){
				map[e][i]= rand() % 100;//monsters hp up to 100
#if defined DEBUG_STATE
				printf("%d",map[e][i]);
#endif
			} else {
				map[e][i]= 0;
			}
		}
	}
	printf("Generated 10x10 map.\n");
#if defined DEBUG_STATE
	printf("\n");
#endif
	struct class player;
	gen_char(&player);//genorate player and class
#if defined DEBUG_STATE
	printf("Your hp is %d \n",player.hp);
	int x=0;
#endif
	int c = 0,in=0;
	int health=player.hp;
	//main game loop
	i=0, e = 0; //set starting position
#if defined DEBUG_STATE
	printf("Cheats: t[test found items],l[list item db]\n");
#endif
	printf("Use the w,a,s,d keys to travel.\n");
	while (1){
		c = getchar();
		//each movement has a 30 percent chance of hitting a trap
		switch(c){
		//move in grid
		//call combat check
		case 'a':
			e++;
			printf("You have went left[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i],&player);
			} else step(&health,player.inventory);
			break;
		case 's':
			i--;
			printf("You have gone back[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i],&player);
			}else step(&health,player.inventory);
			break;
		case 'd':
			e--;
			printf("You have gone right[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i],&player);
			}else step(&health,player.inventory);
			break;
		case 'w':
			i++;
			printf("You have gone forward[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i],&player);
			}else step(&health,player.inventory);
			break;
		case 'i':
			//list inventory
			while (player.inventory[in].amount=='1') {
				printf("%d: %s\n",in,player.inventory[in].type);
				in++;
			}
			in=0;
			break;
		case 'x':
			exit(0);
		case 'u':
			use(&player);//use item in inventory
			break;
#if defined DEBUG_STATE
		case 't':
			item(player.inventory);
			break;
		case 'l':
			while (x<=itemdb_size){
				printf("%s,%s,%d\n",db[x].trait,db[x].type,db[x].amount);
				x++;
			}
			x=0;
			break;
#endif
		default:
			printf("[w,a,s,d]\n");
		}
	}

	return EXIT_SUCCESS;
}
void trap(int * hpp){
	time_t t;
	srand((unsigned) time(&t));
	int hp = *hpp,dmg=0;
	dmg = rand() % 10;
	hp = hp - dmg;
	printf("You have stepped on a trap, %d damage.\n", dmg);
}//just apply trap dmg
void item(struct item invent[100]){
	time_t t;
	int i=0;
	srand((unsigned) time(&t));
	int item=rand() % itemdb_size;
	while (invent[i].amount=='1'){
		i++;
	}//count items in items db
	strcpy(invent[i].trait,db[item].trait);
	strcpy(invent[i].type,db[item].type);
	invent[i].amount=db[item].amount;//load item into db
	printf("You have found a  %s.\n",invent[i].type);
#if defined DEBUG_STATE
	printf("%s\n%d\n",invent[i].trait,i);
#endif
}
void step(int * hpp, struct item play[100]){
	time_t t;
	srand((unsigned) time(&t));
	if (rand() % 100 < 30) trap(hpp);//30% to hit trap
	else if (rand() % 100 > 90) item(play);//10% chance to get item
}
void gen_char(struct class *toon){
	time_t t;
	int i=0, n;
	char num=-1;
	srand((unsigned) time(&t));
	printf("Generating you player.\n");//start off as randomly generated class
	toon->Dexterity=rand() % 20 ;
	toon->Stamina=100+rand() % 20 ;
	toon->Wisdom=rand() % 20 ;
	toon->Strength=rand() % 20 ;
	toon->Intelligence=rand() % 20 ;
	toon->Agility=rand() % 20 ;
	toon->hp=100+rand() % 20 ;
	toon->mana=100+rand() % 20 ;
#if defined DEBUG_STATE
	printf("Your hp is %d \n",toon->hp);
#endif
	printf("What would you like your class to be called(Presets: mage,fighter,healer,rouge)?\n");
	fgets(toon->clas, 25, stdin);
	i=0;
    while (toon->clas[i] != '\n' )//sanitize input to lower case letters only
    {
		n = sscanf(&toon->clas[i], "%[a-z]", &num);
		if (n != 1) {
			printf("Error! You can only enter lower case letters:\n");
			fgets(toon->clas, 25, stdin);
			i=-1;
			num = -1;

		}
		i++;
    }
    i=0;
	while(1){//chop the new line off the clas char
		if (toon->clas[i]==10){
			toon->clas[i]=0;
			break;
		} else i++;
	}
	printf("What would you like your character to be called?\n");
	fgets(toon->name, 25, stdin);
	i=0;
    while (toon->name[i] != '\n' )//sanitize input to lower case letters only
    {
		n = sscanf(&toon->name[i], "%[a-z]", &num);
		if (n != 1) {
			printf("Error! You can only enter lower case letters:\n");
			fgets(toon->clas, 25, stdin);
			i=-1;
			num = -1;

		}
		i++;
    }
    i=0;
	load_clas(toon);//apply class template to generated class
}
void combat(int * hpp, int monster_hp, struct class * player){
	time_t t;
	int hit_dmg=0, hp = *hpp, heal=0;
	srand((unsigned) time(&t));
	while(monster_hp>0){//combat loop until monster dead
		if (rand() % 100 > 50){
				//monster hits you
			if(player->Dexterity < rand() % 20){//use dex to determine if you avoid an attack
				hit_dmg = rand() % 10 ;
				hp = hp - hit_dmg;
				printf("You have been hit for %d.\n",hit_dmg);
				hit_dmg=0;
			} else {
				printf("You jump out of the way, avoiding damage.\n");
			}
			if(hp<=0){//check players hp & exit if dead
				printf("You have died.\n");
				exit(0);
				break;
			} else {
				printf("Health:%d\n",hp);
			}
		} else {
			//you hit monster (or heal yourself)
			if(player->Wisdom < rand()%20){
				player->Stamina = player->Stamina - 10;
				if (player->Stamina <= 0 ) hit_dmg = player->Strength * rand() % 5 ;
					else hit_dmg = player->Strength * rand() % 10 ;
				// if you're out of stamina you do half damage
				monster_hp = monster_hp - hit_dmg;
				printf("You have hit the monster for %d.\n",hit_dmg);
				hit_dmg=0;
			} else {
				heal = rand() % 10;
				printf("The gods have favor on you, healing you for %d.\n", heal);
				player->hp = player->hp + heal;
			}
		}
		//cast a spell
		if(player->Intelligence>rand() % 20 ){
			if (player->mana > 0){
				hit_dmg = rand() % 10 ;
				monster_hp = monster_hp - hit_dmg;
				printf("Your spell  has hit the monster for %d.\n",hit_dmg);
				hit_dmg=0;
				player->mana = player->mana - 10;
			}

		}
		if (player->Agility > rand ()%20){//check agil for chance of additional attack
			printf("You dodge a blow and are granted an additional attack.\n");

			//hit_dmg = player->Strength * rand() % 10 ;//i don't know why this is producing a negative number
			hit_dmg = player->Strength;
			monster_hp = monster_hp - hit_dmg;
			printf("You have hit the monster for %d.\n",hit_dmg);
#if defined DEBUG_STATE
			printf("%d str %d monster_hp %d hit_dmg\n",player->Strength, monster_hp, hit_dmg);
#endif
			hit_dmg=0;
		}
		if(monster_hp<=0){//you have killed the monster, reset player
			printf("The monster is dead.\n");
			player->mana = 100;
			player->Stamina = 100;
			player->hp=100;
		}
	}
}
void itemdb( struct item db[255])
{
	int i=0,c,comma=0,letter=0;
    const char* fname = "item.db";//data base must be in comma separated value list format (may encrypt or encode to prevent editing)
    FILE* fp = fopen(fname, "r");
    if(!fp) {
        perror("Failed to load item db.\n");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF) { // loop until end of file
       if (c != ','){
#if defined DEBUG_STATE
    	  putchar(c);
#endif//load item db
    	   if (comma == 0 ) {
    		   db[i].type[letter]=c;
    		   letter++;
    	   } else if (comma == 1){
    		   db[i].trait[letter]=c;
    		   letter++;
    	   } else if (comma == 2){
    		   db[i].amount=c;
    	   }
       }  else {
    	   letter=0;
    	   comma++;
#if defined DEBUG_STATE
    	   putchar(c); //load item db
#endif
       }
       if (c == '\n' ) {
    	   comma=0;//forgot this little guy
    	   i++;
       }
    }
#if defined DEBUG_STATE
    printf("%s",db[i].trait);
    printf("%s",db[i].type);
    printf("itemdb_size %d\n",i);
#endif
    itemdb_size=i;
    if (ferror(fp)) {
#if defined DEBUG_STATE
        puts("I/O error when loading item db.\n");
#endif
    } else if (feof(fp)) {
#if defined DEBUG_STATE
        puts("Item db loaded.\n");
#endif
    }
    fclose(fp);
}
void use(struct class * player){
	int i=0,c=0;
	time_t t;
	//use item and call function for right item ID
	srand((unsigned) time(&t));
	printf("What inventory item do you wish to use?\n");
	c = getc(stdin);
	c = getchar();// i don't know why both of these lines are need but it wont grab a char if they're not there
	c = c-48;//convert from ascii to decimal
	int item_type = player->inventory[c].amount - 48;

#if defined DEBUG_STATE
	printf("%d - 48 = %d",player->inventory[c].amount,item_type);
#endif
	if(item_type == 1) {
		//item type one is potions
		i= rand() % 3;
		char lhs[255];
		strcpy(lhs,player->inventory[c].trait);
		char rhs[255];
		strcpy(rhs,(char *)"Agility");
		if( strcmp( (char *)&lhs, (char *)&rhs ) == 0){
			potion(&player->Agility,i);
		}
		strcpy(rhs,(char *)"Dexterity");
		if( strcmp( (char *)&lhs, (char *)&rhs ) == 0){
			potion(&player->Dexterity,i);
		}
		strcpy(rhs,(char *)"Stamina");
		if( strcmp((char *) &lhs,(char *) &rhs ) == 0){
			potion(&player->Stamina,i);
		}
		strcpy(rhs,(char *)"Wisdom");
		if( strcmp((char *) &lhs,(char *) &rhs ) == 0){
			potion(&player->Wisdom,i);
		}
		strcpy(rhs,(char *)"Strength");
		if( strcmp( (char *)&lhs,(char *) &rhs ) == 0){
			potion(&player->Strength,i);
		}
		strcpy(rhs,(char *)"Intelligence");
		if( strcmp((char *) &lhs, (char *)&rhs ) == 0){
			potion(&player->Intelligence,i);
		}
		printf("You use a %s, which increases your %s by %d points.\n",player->inventory[c].type,player->inventory[c].trait,i);
		//remove item from inventory
		player->inventory[c].trait[0]='\0';
		player->inventory[c].type[0]='\0';

	}
}

void potion( int * trait, int buff){
	//apply potion
	trait = trait + buff;
}

