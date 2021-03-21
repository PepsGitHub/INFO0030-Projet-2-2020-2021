/**
 * verify.c
 * 
 * Ce fichier contient les prototypes des fonctions pour gérer les cas
 * particuliers
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "verify.h"

//debut manage_format_input
int manage_format_input(PNM *image, char *format, char *input){
   assert(image != NULL && format != NULL && input != NULL);

   switch (get_magicNumber(image)[1]){
   case '1':
      if(strcmp(format, "PBM")){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PBM et non %s\n", input, format);
         destroy(image, 2);
         return -1;
      }else{
         printf("Bon format passé en argument. ");
         printf("Le fichier %s est bien du type PBM\n", input);
         return 0;
      }
      break;
   case '2':
      if(strcmp(format, "PGM")){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PGM et non %s\n", input, format);
         destroy(image, 2);
         return -1;
      }else{
         printf("Bon format passé en argument. ");
         printf("Le fichier %s est bien du type PGM\n", input);
         return 0;
      }
      break;
   case '3':
      if(strcmp(format, "PPM")){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PPM et non %s\n", input, format);
         destroy(image, 2);
         return -1;
      }else{
         printf("Bon format passé en argument. ");
         printf("Le fichier %s est bien du type PPM\n", input);
         return 0;
      }
      break;
   default:
      printf("Incapable de lire ce type de format: %s\n", format);
      return -1;
      break;
   }
   return 0;
}
//fin manage_format_input

//debut verify_filename_output
int verify_output(char *output){
   assert(output != NULL);

   char *invalidCharacter = "/\\:*?\"<>|";

   for(int i=0; output[i] != '\0';i++){
      for(int j=0; invalidCharacter[j] != '\0'; j++){
         if(output[i]==invalidCharacter[j]){
            printf("Caractère invalide dans le nom du fichier: '%c'\n",
                   output[i]);
            return -1;
         }
      }
   }
   return 0;
}//fin verify_filename

//debut manage_comments
int manage_comments(FILE *fp){
   assert(fp != NULL);

   int character = 0;

   char special_character = '#';
   while((character = fgetc(fp)) != EOF && (character == special_character)){
      if(character == special_character)
         fscanf(fp, "%*[^\n] ");
   }

   if(character == EOF)
      return -1;
   
   ungetc(character, fp);
   return 0;
}//fin manage_comments

//debut_verify_seed()
int verify_seed(char *seed){
   assert(seed != NULL);

   for(int i = 0; seed[i] != '\0'; i++){
      if(seed[i] != '0' && seed[i] != '1'){
         printf("Charactère invalide dans la graine: '%c'\n", seed[i]);
         return -1;
      }
   }
   return 0;
}//fin verify_seed()

//debut verify_tap()
int verify_tap(char *tap){
   assert(tap != NULL);

   if(atoi(tap) == 0){
      return -1;
   }

   return 0;
}//fin verify_tap()

int verify_password(char *password){
   assert(password != NULL);

   char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   for(int i = 0; password[i] != '\0'; i++){
      for(int j = 0; password[i] != base64[j] && base64[j] != '\0'; j++){
         if(j == 63)
            return -1;
      }
   }
   return 0;
}
