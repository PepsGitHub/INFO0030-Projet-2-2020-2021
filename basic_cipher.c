/**
 * basic_cipher.c
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le chiffrement basique d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 16/03/21
 * @projet: INFO0030 Projet 2
 */

#define TRIPLET 3
#define NUMBER 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "basic_cipher.h"

int transform(PNM *image, char *seed, char *tap, unsigned k){
   assert(image != NULL && seed != NULL && tap != NULL);

   LFSR *lfsr = initialize(seed, (unsigned int)atoi(tap));

   unsigned short **matrix = get_matrix(image);

   switch(get_magicNumber(image)[NUMBER]){
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
   destroy_lfsr(lfsr);

   return 0;
}