/**
 * lfsr.c
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le chiffrement d'images PNM.
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
#include "cipher.h"

int transform(PNM *image, char *seed, char *tap, unsigned k){
   assert(image != NULL && seed != NULL && tap != NULL);

   LFSR *lfsr = initialize(seed, (unsigned int)atoi(tap));

   unsigned short **matrix = get_matrix(image);

   switch(get_magicNumber(image)[1]){
   case '1':
   case '2':
      for(unsigned short i = 0; i < get_rows(image); i++)
         for(unsigned short j = 0; j < get_columns(image); j++)
            matrix[i][j] ^= generate(lfsr, k);
      break;
   case '3':
      for(unsigned short i = 0; i < get_rows(image); i++)
         for(unsigned short j = 0; j < get_columns(image) * TRIPLET; j++)
            matrix[i][j] ^= generate(lfsr, k);
      break;
   }
   set_matrix(image, matrix);
   destroy_lfsr(lfsr, 1);

   return 0;
}

char *initialize_password(char *password, char *final){
   assert(password != NULL);

   char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   int binar = 0;
   char b[100] = "", buffer[7];

   for(int i = 0; password[i] != '\0'; i++){
      for(int j = 0; base64[j] != '\0'; j++){
         if(password[i] == base64[j]){
            binar = binary(j);
            sprintf(buffer, "%d", binar);
            for(int k = 0; k < 6; k++){
               if(buffer[k] == '\0'){
                  buffer[k+1] = '\0';
                  for(int l = k; l > 0; l--)
                     buffer[l] = buffer[l-1];
                  buffer[0] = '0';
               }
            }
            strcat(b, buffer);
         }
      }
   }
   strcpy(final, b);
   printf("seed: %s\n", final);

   return final;
}

int binary(int k){
   if (k == 0) 
      return 0;
   if (k == 1) 
      return 1;

   return (k % 2) + 10 * binary(k / 2);
}