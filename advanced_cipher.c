/**
 * advanced_cipher.c
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le chiffrement avancé d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 16/03/21
 * @projet: INFO0030 Projet 2
 */

#define BITS 7

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "advanced_cipher.h"

char *initialize_password(char *password, char *passwordBinary){
   assert(password != NULL);
   char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   int binar = 0;
   char buffer[BITS];

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
            strcat(passwordBinary, buffer);
         }
      }
   }
   printf("seed: %s\n", passwordBinary);

   return passwordBinary;
}

int binary(int position){
   assert(position >= 0);
   
   if (position == 0) 
      return 0;
   if (position == 1) 
      return 1;

   return (position % 2) + 10 * binary(position / 2);
}