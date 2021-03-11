/**
 * main.c
 * 
 * Ce fichier contient les fonctions associées au chiffrement basique d'images
 *
 * @author: Dumoulin Peissone S193957
 * @date: 10/03/21
 * @projet: INFO0030 Projet 2
 */
#define TRIPLET 3

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "chiffrement.h"

unsigned int binary(unsigned int n){
   if(n == 0)
      return 0;
   else if(n == 1)
      return 1;
   else{
      return (n % 2) + 10 * binary(n/2);
   }
}

int transform(PNM *image, char *filename, char *seed, char *tap){
   assert(image != NULL && filename != NULL && seed != NULL && tap != NULL);

   FILE *fp = fopen(filename, "w");
   if(!fp)
      return -1;


   LFSR *lfsr = initialisation(seed, (unsigned int)atoi(tap));

   generation(lfsr, 32);

   char *test = (char*)malloc(sizeof(char) * get_N(lfsr));

   for(unsigned int i = 0; i < get_N(lfsr); i++){
      test[i] = string(lfsr)[i];
   }
   printf("test: %s\n", test);

   char letter = get_magicNumber(image)[0], number = get_magicNumber(image)[1];
   fprintf(fp,"%c%c\n%hu %hu\n", letter, number, 
           get_columns(image), get_rows(image));

   switch(get_magicNumber(image)[1]){
   case '1' :
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image); i++){
         fprintf(fp,"%u ", get_matrix(image)[i] ^ atoi(test));
      }
      break;
   case '2' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image); i++){
         fprintf(fp,"%u ", binary(get_matrix(image)[i]) ^ atoi(test));
      }
      break;
   case '3' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image) * TRIPLET; i++){
         fprintf(fp,"%u ", binary(get_matrix(image)[i]) ^ atoi(test));
      }
      break;
   default :
      destroy_lfsr(lfsr, 1);
      destroy(image, 2);
      return -2;
   }

   destroy_lfsr(lfsr, 1);
   destroy(image, 2);
   fclose(fp);
   return 0;
}

void reverse_transform(PNM *image, char *input, char *output, char *seed, 
char *tap){
   assert(input != NULL && output != NULL && seed != NULL && tap != NULL);

   load_pnm(&image, output);
   write_pnm(image, input);
   destroy(image, 2);
}

char* XORCipher(char* data, char* key, int dataLen, int keyLen) {
	char* output = (char*)malloc(sizeof(char) * dataLen);

	for (int i = 0; i < dataLen; ++i) {
		output[i] = data[i] ^ key[i % keyLen];
	}

	return output;
}

char* text = "The quick brown fox jumps over the lazy dog.";
char* key = "secret";
int dataLen = strlen(text);
int keyLen = strlen(key);
char* cipherText = XORCipher(text, key, dataLen, keyLen);
char* plainText = XORCipher(cipherText, key, dataLen, keyLen);