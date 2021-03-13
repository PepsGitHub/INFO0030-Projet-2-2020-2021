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

int transform(PNM *image, char *seed, char *tap, unsigned k){
   assert(image != NULL && seed != NULL && tap != NULL);

   LFSR *lfsr = initialize(seed, (unsigned int)atoi(tap));

   unsigned int **matrix = get_matrix(image);

   for(unsigned int i = 0; i < get_rows(image); i++)
      for(unsigned int j = 0; j < get_columns(image); j++)
         matrix[i][j] ^= generate(lfsr, k);

   set_matrix(image, matrix);
   destroy_lfsr(lfsr, 1);

   return 0;
}

char *initialize_password(char *password, char *final){
   assert(password != NULL);

   char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   int nombre = 0, binar = 0;
   char b[100] = "", buffer[7];

   for(int i = 0; password[i] != '\0'; i++){
      for(int j = 0; base64[j] != '\0'; j++){
         if(password[i] == base64[j]){
            nombre = j;
            binar = binary(nombre);
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