/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
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
#include <getopt.h>

#include "pnm.h"
#include "lfsr.h"
#include "verify.h"

/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   char magicNumber[2]; /*Nombre qui caractérise le type de fichier
                      (1 pour pbm, 2 pour pgm, 3 pour ppm)*/
   unsigned int columns; //Nombre de pixels de hauteur
   unsigned int rows; //Nombre de pixels de largeur
   unsigned int maxValuePixel; //Valeur maximale que peut prendre un pixel
   unsigned int **matrix; //Matrice contenant la valeur de chaque pixel de l'image
};

//debut constructeur
PNM *create_pnm(){
   PNM *image = malloc(sizeof(PNM));
   if(!image)
      return NULL;

   return image;
}//fin constructeur

//debut accesseurs en lecture
char *get_magicNumber(PNM *image){
   assert(image!=NULL);

   return image->magicNumber;
}

unsigned int get_columns(PNM *image){
   assert(image!=NULL);

   return image->columns;
}

unsigned int get_rows(PNM *image){
   assert(image!=NULL);

   return image->rows;
}

unsigned int get_maxValuePixel(PNM *image){
   assert(image!=NULL);

   return image->maxValuePixel;
}

unsigned int **get_matrix(PNM *image){
   assert(image!=NULL);

   return image->matrix;
}//fin accesseurs en lecture

//debut accesseurs en ecriture
PNM *set_magicNumber(PNM *image, char *magicNumber){
   assert(image!=NULL);

   for(unsigned i = 0; i < 2; i++)
      image->magicNumber[i] = magicNumber[i];
   image->magicNumber[2] = '\0';

   return image;
}

PNM *set_columns(PNM *image, unsigned int columns){
   assert(image!=NULL);

   image->columns = columns;

   return image;
}

PNM *set_rows(PNM *image, unsigned int rows){
   assert(image!=NULL);

   image->rows = rows;

   return image;
}

PNM *set_maxValuePixel(PNM *image, unsigned int maxValuePixel){
   assert(image!=NULL);

   image->maxValuePixel = maxValuePixel;

   return image;
}

PNM *set_matrix(PNM *image, unsigned int **matrix){
   assert(image!=NULL);

   image->matrix = matrix;

   return image;
}//fin accesseurs en ecriture

//debut create_matrix
int create_matrix(PNM *image){
   assert(image != NULL);
   image->matrix = malloc(image->rows * sizeof(unsigned int*));
   if(!image->matrix){
      destroy(image, 1);
      return -1;
   }

   if(get_magicNumber(image)[1] == '3'){
      for(unsigned int i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * TRIPLET * sizeof(unsigned int));

         if(!image->matrix[i]){
            destroy(image, 2);
            return -1;
         }
      }
   }else{
      for(unsigned int i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * sizeof(unsigned int));

         if(!image->matrix[i]){
            destroy(image, 2);
            return -1;
         }
      }
   }

   return 0;
}//fin create_matrix

//debut load_matrix
int load_matrix(PNM *image, FILE *fp){
   assert(image != NULL && fp != NULL);

   switch(get_magicNumber(image)[1]){
   case '1':
   case '2':
      for(unsigned int i = 0; i < get_rows(image); i++){
         for(unsigned int j = 0; j < get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%u ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   case '3':
      for(unsigned int i = 0; i < get_rows(image); i++){
         for(unsigned int j = 0; j < 3 * get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%u ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   default:
      destroy(image, 3);
      return -3;
   }
   return 0;
}//fin load_matrix

//debut write_matrix
int write_matrix(PNM *image, FILE *fp){
   assert(image != NULL && fp != NULL);

   switch(get_magicNumber(image)[1]){
   case '1' :
      for(unsigned int i=0;i<get_rows(image);i++){
         for(unsigned int j=0;j<get_columns(image);j++){
            fprintf(fp,"%u ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case '2' :
      fprintf(fp, "%u\n", get_maxValuePixel(image));
      for(unsigned int i=0;i<get_rows(image);i++){
         for(unsigned int j=0;j<get_columns(image);j++){
            fprintf(fp,"%u ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case '3' :
      fprintf(fp, "%u\n", get_maxValuePixel(image));
      for(unsigned int i=0;i<get_rows(image);i++){
         for(unsigned int j=0;j<3*get_columns(image);j++){
            fprintf(fp,"%u ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   default :
      destroy(image, 3);
      return -2;
   }
   return 0;
}//fin write_matrix

//debut destroy
void destroy(PNM *image, unsigned int allocation_value){
   assert(image != NULL && allocation_value > 0 && allocation_value < 4);
   switch (allocation_value){
   case 1://détruit pnm
      free(image);
      break;
   case 2://détruit la matrice et pnm
      free(image->matrix);
      free(image);
      break;
   case 3:
      for(unsigned int i = 0;i < image->rows;i++)
         free(image->matrix[i]);
      free(image->matrix);
      free(image);
   }
}//fin destroy

//debut load_pnm
int load_pnm(PNM **image, char* filename){

   assert(image != NULL && filename != NULL);
   
   *image = create_pnm();

   FILE *fp = fopen(filename, "r");
   if(!fp)
      return -2;

   manage_comments(fp);

   char magicNumber[2];
   
   fscanf(fp, "%s\n", magicNumber);

   if((!strcmp(magicNumber, "P1")) ||
      (!strcmp(magicNumber, "P2")) ||
      (!strcmp(magicNumber, "P3"))){
      set_magicNumber(*image, magicNumber);
   }else{
      destroy(*image, 3);
      fclose(fp);
      return -3;
   }

   manage_comments(fp);

   unsigned int columns = 0, rows = 0, maxValuePixel = 1;

   fscanf(fp, "%u %u\n", &columns, &rows);

   if(columns < 1 || rows < 1){
      fclose(fp);
      return -1;
   }

   set_columns(*image, columns);
   set_rows(*image, rows);

   manage_comments(fp);

   switch(get_magicNumber(*image)[1]){
   case '1' :
      set_maxValuePixel(*image, maxValuePixel);
      create_matrix(*image);
      if(load_matrix(*image, fp)){
         destroy(*image, 3);
         fclose(fp);
         return -3;
      }
      break;
   case '2' :
   case '3' :
      fscanf(fp,"%u\n", &maxValuePixel);
      set_maxValuePixel(*image, maxValuePixel);
      create_matrix(*image);
      if(load_matrix(*image, fp)){
         destroy(*image, 3);
         fclose(fp);
         return -3;
      }
      break;
   default :
      printf("ce type de fichier n'existe pas");
      fclose(fp);
      return -3;
   }
   manage_comments(fp);
   fclose(fp);
   return 0;
}//fin load_pnm

//debut write_pnm
int write_pnm(PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "w");
   if(!fp)
      return -1;

   /*char letter = get_magicNumber(image)[0], number = get_magicNumber(image)[1];

   fprintf(fp,"%c%c\n%u %u\n", letter, number, 
           get_columns(image), get_rows(image));
   write_matrix(image, fp);*/
   fprintf(fp,"%s\n%u %u\n", get_magicNumber(image), get_columns(image), get_rows(image));

   write_matrix(image, fp);

   fclose(fp);
   return 0;
}//fin write_pnm