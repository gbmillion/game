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
int trap(int * hpp){
	time_t t;
	srand((unsigned) time(&t));
	int hp = *hpp,dmg=0;
	dmg = rand() % 10;
	hp = hp - dmg;
	printf("You have stepped on a trap, %d damage.\n", dmg);
}
int combat(int * hpp, int monster_hp){
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
				exit(1);
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
	return 0;
}
int main(void) {
	int map[10][10];
	int i=0, e = 0;
	int health=100;
	time_t t;
	srand((unsigned) time(&t));
	//build a board with randomly assigned "monster" or value
	for(i=0;i<10;++i){
		for(e=0;e<10;++e){
			//squares have a fifty fifty chance to have a random monster value on them
			if (rand() % 100 > 50 ){
				map[e][i]= rand() % 100;
				printf("%d",map[e][i]);
			} else {
				map[e][i]= 0;
			}
		}
	}
	int c = 0;
	//main game loop
	i=0, e = 0; //set starting position
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
			} else {
				if (rand() % 100 < 30) trap(&health);
			}
			break;
		case 's':
			i--;
			printf("You have gone back[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			}else {
				if (rand() % 100 < 30) trap(&health);
			}
			break;
		case 'd':
			e--;
			printf("You have gone right[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			}else {
				if (rand() % 100 < 30) trap(&health);
			}
			break;
		case 'w':
			i++;
			printf("You have gone forward[w,a,s,d].\n");
			if(map[e][i]>0){
				combat(&health,map[e][i]);
			}else {
				if (rand() % 100 < 30) trap(&health);
			}
			break;
		default:
			printf("[w,a,s,d]\n");
		}
	}

	return EXIT_SUCCESS;
}
