/*
 * crypt.h
 *
 *  Created on: Sep 2, 2021
 *      Author: user
 */

#ifndef CRYPT_H_
#define CRYPT_H_
//enable debug statements and cheats
#define DEBUG_STATE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mcrypt.h>
int encrypt(char * input);
int decrypt(char * input);

int decrypt(char * input){
	unsigned char *key;
	key = malloc(16);
	MCRYPT crypt;
	int i=0,iv_size=0,key_size=0,c,err=0;
	unsigned char *buff;
	const char* fname = input;
	const char* fname2 = ".tmp";
	//select crypto  algorithm & mode
	crypt = mcrypt_module_open("twofish", NULL, "cfb", NULL);
	iv_size = (mcrypt_enc_get_iv_size) (crypt);
	key_size = (mcrypt_enc_get_key_size) (crypt);
	//load key from file
	FILE * kfp = fopen(".key","r");
    if(!kfp) {
        perror("Failed to load key file.\n");
        exit(1);
    }
	i = fread( key, key_size, 1,kfp);
	if(i<=0)exit(1);
	fclose(kfp);
	i=0;
	buff = malloc(iv_size);
	//Initialize crypto
	mcrypt_generic_init( crypt, key, key_size, buff);
	if (crypt == MCRYPT_FAILED) exit(1);
	//open up input & output files
	FILE * fp = fopen(fname, "r");
    if(!fp) {
        perror("Failed to load input file.\n");
        exit(1);
    }
	FILE * fp2 = fopen(fname2, "w");
    if(!fp2) {
        perror("Failed to load output file.\n");
        exit(1);
    }
    //loop until end of file for input
    while ((c = fgetc(fp)) != EOF) {
#if defined DEBUG_STATE
    	printf("[%d:",c);
#endif
    	err = mdecrypt_generic( crypt, &c, 1);//decrypt file stream
#if defined DEBUG_STATE
    	printf("%d]\n",c);
#endif
    	fputc(c,fp2);
    	if (err != 0)exit(1);
    }
    fclose(fp2);
    fclose(fp);
	return 0;
}
int encrypt (char * input){
	unsigned char *key;
	key = malloc(16);
	time_t t;
	MCRYPT crypt;
	int i=0,iv_size=0,key_size=0,c,err=0;
	unsigned char *buff;
	const char* fname = input;
	const char* fname2 = ".tmp";

	//pick the crypto  algorithm & mode
	crypt = mcrypt_module_open("twofish", NULL, "cfb", NULL);
	iv_size = (mcrypt_enc_get_iv_size) (crypt);
	key_size = (mcrypt_enc_get_key_size) (crypt);
	//randomly genorate key based on time for seeding
	srand((unsigned) time(&t));
	for (i=0; i < key_size;i++){
		key[i] = rand() % 127;
	}

	buff = malloc(iv_size);
	//Initialize crypto
	mcrypt_generic_init( crypt, key, key_size, buff);
	if (crypt == MCRYPT_FAILED) exit(1);
	//save key to file
	FILE* fp = fopen(".key", "w");
	if(!fp) {
		perror("Failed to open key file.\n");
		exit(1);
	}
	i = fwrite( key, key_size,  1, fp );
	if (i<0)exit (1);
    fclose(fp);
    //open files
	fp = fopen(fname, "r");
    if(!fp) {
        perror("Failed to load input file.\n");
        exit(1);
    }
	FILE * fp2 = fopen(fname2, "w");
    if(!fp2) {
        perror("Failed to load output file.\n");
        exit(1);
    }//loop until end of input file
    while ((c = fgetc(fp)) != EOF) {
#if defined DEBUG_STATE
    	printf("[%d:",c);
#endif
    	err = mcrypt_generic( crypt, &c, 1);//encrypt file stream
#if defined DEBUG_STATE
    	printf("%d]\n",c);
#endif
    	fputc(c,fp2);
    	if (err != 0)exit(1);
    }
    fclose(fp2);
    fclose(fp);
    //this is where we replace the original with the encrypted version
	fp = fopen(fname, "w");
    if(!fp) {
        perror("Failed to load input file.\n");
        exit(1);
    }
	fp2 = fopen(fname2, "r");
    if(!fp2) {
        perror("Failed to load output file.\n");
        exit(1);
    }
    while ((c = fgetc(fp2)) != EOF) {
    	fputc(c,fp);
    	if (err != 0)exit(1);
    }
    fclose(fp2);
    fclose(fp);

	return 0;
}


#endif /* CRYPT_H_ */
