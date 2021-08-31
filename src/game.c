/*
 ============================================================================
 Name        : game.c
 Author      : brad
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "class.h"
#include <string.h>
#include <time.h>
int itemdb_size=0;
struct item db[255];

#define DEBUG_STATE ;
void trap(int * hpp);
void item(struct item invent[100]);
void step(int * hpp, struct item  play[100]);
void gen_char(struct class *toon);
void combat(int * hpp, int monster_hp);
void itemdb( struct item db[255]);
void use(struct class * player);
int main(void) {
	int map[10][10];
	int i=0, e = 0;
	time_t t;
	itemdb(db);

	srand((unsigned) time(&t));
	//build a board with randomly assigned "monster" or value
	printf("Welcome to dungeon hack!\nCommands: i[inventory],x[exit],u[use]\n");
	for(i=0;i<10;++i){
		for(e=0;e<10;++e){
			//squares have a fifty fifty chance to have a random monster value on them
			if (rand() % 100 > 50 ){
				map[e][i]= rand() % 100;
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
	gen_char(&player);
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
		case 'a':
			//move in grid
			//call combat check
			e++;
			printf("You have went left[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			} else step(&health,player.inventory);
			break;
		case 's':
			i--;
			printf("You have gone back[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			}else step(&health,player.inventory);
			break;
		case 'd':
			e--;
			printf("You have gone right[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			}else step(&health,player.inventory);
			break;
		case 'w':
			i++;
			printf("You have gone forward[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
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
			use(&player);
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
}
void item(struct item invent[100]){
	time_t t;
	int i=0;
	srand((unsigned) time(&t));
	int item=rand() % itemdb_size;
	while (invent[i].amount=='1'){
		i++;
	}
	strcpy(invent[i].trait,db[item].trait);
	strcpy(invent[i].type,db[item].type);
	invent[i].amount=db[item].amount;
	printf("You have found a  %s.\n",invent[i].type);
#if defined DEBUG_STATE
	printf("%s\n%d\n",invent[i].trait,i);
#endif
}
void step(int * hpp, struct item play[100]){
	time_t t;
	srand((unsigned) time(&t));
	if (rand() % 100 < 30) trap(hpp);
	else if (rand() % 100 > 90) item(play);
}
void gen_char(struct class *toon){
	time_t t;
	srand((unsigned) time(&t));
	printf("Generating you player.\n");
	toon->Charisma=rand() % 20 ;
	toon->Dexterity=rand() % 20 ;
	toon->Stamina=rand() % 20 ;
	toon->Wisdom=rand() % 20 ;
	toon->Strength=rand() % 20 ;
	toon->Intelligence=rand() % 20 ;
	toon->Agility=rand() % 20 ;
	toon->hp=100+rand() % 20 ;
	toon->mana=100+rand() % 20 ;
#if defined DEBUG_STATE
	printf("Your hp is %d \n",toon->hp);
#endif
	printf("What would you like your character to be called?\n");
	fgets(toon->name, 25, stdin);
}
void combat(int * hpp, int monster_hp){
	time_t t;
	int hit_dmg=0, hp = *hpp;
	srand((unsigned) time(&t));
	while(monster_hp>0){
		if (rand() % 100 > 50){
			//monster hits you
			hit_dmg = rand() % 10 ;
			hp = hp - hit_dmg;
			printf("You have been hit for %d.\n",hit_dmg);
			hit_dmg=0;
			if(hp<=0){
				printf("You have died.\n");
				exit(0);
				break;
			} else {
				printf("Health:%d\n",hp);
			}
		} else {
			//you hit monster
			hit_dmg = rand() % 10 ;
			monster_hp = monster_hp - hit_dmg;
			printf("You have hit the monster for %d.\n",hit_dmg);
			hit_dmg=0;
		}
		if(monster_hp<=0){
			printf("The monster is dead.\n");
		}
	}
}
void itemdb( struct item db[255])
{
	int i=0,c,comma=0,letter=0;
    const char* fname = "item.csv";
    FILE* fp = fopen(fname, "r");
    if(!fp) {
        perror("Failed to load item db.\n");
        exit(1);
    }

    while ((c = fgetc(fp)) != EOF) { // loop until end of file
       if (c != ','){
#if defined DEBUG_STATE
    	  putchar(c); //load item db
#endif
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
	int c=0;
	printf("What inventory item do you wish to use?\n");
	c = getc(stdin);

	printf("%c\nYou use a %s, which increases your %s by %d points.\n",c,player->inventory[c].type,player->inventory[c].trait,player->inventory[c].amount);
}
