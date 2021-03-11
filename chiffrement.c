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

int transform(PNM *image, char *filename, char *seed, char *tap){
   assert(image != NULL && filename != NULL && seed != NULL && tap != NULL);

   FILE *fp = fopen(filename, "w");
   if(!fp)
      return -1;


   LFSR *lfsr = initialisation(seed, (unsigned int)atoi(tap));

   int generationNumber = generation(lfsr, 32);
   char letter = get_magicNumber(image)[0], number = get_magicNumber(image)[1];
   fprintf(fp,"%c%c\n%hu %hu\n", letter, number, 
           get_columns(image), get_rows(image));

   switch(get_magicNumber(image)[1]){
   case '1' :
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image); i++){
         if(get_matrix(image)[i] != (unsigned int)generationNumber)
            get_matrix(image)[i] = (unsigned int)generationNumber;

         fprintf(fp,"%u ", get_matrix(image)[i]);
      }
      break;
   case '2' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image); i++){
         if(get_matrix(image)[i] != (unsigned int)generationNumber)
            get_matrix(image)[i] = (unsigned int)generationNumber;
            
         fprintf(fp,"%u ", get_matrix(image)[i]);
      }
      break;
   case '3' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned int i = 0; i < get_rows(image) * get_columns(image) * TRIPLET; i++){
         if(get_matrix(image)[i] != (unsigned int)generationNumber)
            get_matrix(image)[i] = (unsigned int)generationNumber;
            
         fprintf(fp,"%u ", get_matrix(image)[i]);
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