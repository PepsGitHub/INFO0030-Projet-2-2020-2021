/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 16/03/21
 * @projet: INFO0030 Projet 2
 */

#define TRIPLET 3
#define MAGICNUMBERCHAR 2
#define LETTER 0
#define NUMBER 1

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
   char magicNumber[MAGICNUMBERCHAR]; /*Nombre qui caractérise le type de fichier*/
   unsigned short columns; //Nombre de pixels de hauteur
   unsigned short rows; //Nombre de pixels de largeur
   unsigned short maxValuePixel; //Valeur maximale que peut prendre un pixel
   unsigned short **matrix; /*Matrice contenant la valeur de chaque pixel de l'image*/
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

unsigned short get_columns(PNM *image){
   assert(image!=NULL);

   return image->columns;
}

unsigned short get_rows(PNM *image){
   assert(image!=NULL);

   return image->rows;
}

unsigned short get_maxValuePixel(PNM *image){
   assert(image!=NULL);

   return image->maxValuePixel;
}

unsigned short **get_matrix(PNM *image){
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

PNM *set_columns(PNM *image, unsigned short columns){
   assert(image!=NULL);

   image->columns = columns;

   return image;
}

PNM *set_rows(PNM *image, unsigned short rows){
   assert(image!=NULL);

   image->rows = rows;

   return image;
}

PNM *set_maxValuePixel(PNM *image, unsigned short maxValuePixel){
   assert(image!=NULL);

   image->maxValuePixel = maxValuePixel;

   return image;
}

PNM *set_matrix(PNM *image, unsigned short **matrix){
   assert(image!=NULL);

   image->matrix = matrix;

   return image;
}//fin accesseurs en ecriture

//debut create_matrix
int create_matrix(PNM *image){
   assert(image != NULL);
   image->matrix = malloc(image->rows * sizeof(unsigned short*));
   if(!image->matrix){
      destroy(image, 1);
      return -1;
   }

   if(get_magicNumber(image)[NUMBER] == '3'){
      for(unsigned short i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * TRIPLET * sizeof(unsigned short));

         if(!image->matrix[i]){
            destroy(image, 2);
            return -1;
         }
      }
   }else{
      for(unsigned short i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * sizeof(unsigned short));

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

   switch(get_magicNumber(image)[NUMBER]){
   case '1':
   case '2':
      for(unsigned short i = 0; i < get_rows(image); i++){
         for(unsigned short j = 0; j < get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%hu ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   case '3':
      for(unsigned short i = 0; i < get_rows(image); i++){
         for(unsigned short j = 0; j < TRIPLET * get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%hu ", &(image->matrix[i][j]));
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

   switch(get_magicNumber(image)[NUMBER]){
   case '1' :
      for(unsigned short i = 0; i < get_rows(image); i++){
         for(unsigned short j = 0; j < get_columns(image); j++){
            fprintf(fp,"%hu ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case '2' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned short i = 0; i < get_rows(image); i++){
         for(unsigned short j = 0;j < get_columns(image); j++){
            fprintf(fp,"%hu ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case '3' :
      fprintf(fp, "%hu\n", get_maxValuePixel(image));
      for(unsigned short i = 0;i < get_rows(image); i++){
         for(unsigned short j=0;j < TRIPLET * get_columns(image); j++){
            fprintf(fp,"%hu ", image->matrix[i][j]);
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
void destroy(PNM *image, unsigned short allocation_value){
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
      for(unsigned short i = 0; i < image->rows; i++)
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

   unsigned short columns = 0, rows = 0, maxValuePixel = 1;

   fscanf(fp, "%hu %hu\n", &columns, &rows);

   if(columns < 1 || rows < 1){
      fclose(fp);
      return -1;
   }

   set_columns(*image, columns);
   set_rows(*image, rows);

   manage_comments(fp);

   switch(get_magicNumber(*image)[NUMBER]){
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
      fscanf(fp,"%hu\n", &maxValuePixel);
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

   char letter = get_magicNumber(image)[LETTER], number = get_magicNumber(image)[NUMBER];

   fprintf(fp,"%c%c\n%hu %hu\n", letter, number, get_columns(image), get_rows(image));

   write_matrix(image, fp);

   fclose(fp);
   return 0;
}//fin write_pnm