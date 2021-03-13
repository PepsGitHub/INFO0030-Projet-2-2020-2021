/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Dumoulin Peissone S193957
 * @date: 10/03/21
 * @projet: INFO0030 Projet 2
 */
#define STRING_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "verify.h"
#include "chiffrement.h"


int main(int argc, char *argv[]) {

   char *input = NULL, *output = NULL, *seed = NULL, *tap = NULL, *password = NULL;
   PNM *image;

   char *optstring = ":i:o:s:t:p:";
   int val;
   while((val=getopt(argc, argv, optstring))!=EOF){
      switch(val){
      case 'i':
         input = optarg;
         printf("input: %s\n", input);
         break;
      case 'o':
         output = optarg;
         printf("output: %s\n", output);
         break;
      case 's':
         seed = optarg;
         printf("seed: %s\n", seed);
         break;
      case 't':
         tap = optarg;
         printf("tap: %s\n", tap);
         break;
      case 'p':
         password = optarg;
         printf("password: %s\n", password);
         break;
      case '?':
         printf("option inconnue: %c\n", optopt);
         return -1;
      case ':':
         printf("argument manquant: %c\n", optopt);
         return -2;
      }
   }

   char inputX[STRING_SIZE] = "x", outputX[STRING_SIZE] = "x";
   char inputX2[STRING_SIZE] = "x-advanced", outputX2[STRING_SIZE] = "x-advanced";
   strcat(inputX, input);
   strcat(outputX, output);
   strcat(inputX2, input);
   strcat(outputX2, output);

   if(strcmp(outputX, input) != 0 && strcmp(outputX2, input) != 0){
      //appel de load_pnm et checking des valeurs de retour
      switch(load_pnm(&image, input)){
         case 0:
            printf("Tout s'est bien passé et l'image est ");
            printf("correctement chargée en mémoire dans *image\n");
            break;
         case -1:
            printf("Il est impossible d'allouer suffisamment ");
            printf("de mémoire pour l'image\n");
            return 0;
         case -2:
            printf("Le nom du fichier en input est mal formé\n");
            destroy(image, 3);
            return 0;
         case -3:
            printf("Le contenu du fichier en input est mal formé\n");
            return 0;
         default:
            printf("Valeur de retour inconnue\n");
            return 0;
      }
   }

 //permet de gérer les caractères interdits dans l'output
   if(verify_output(output)){
      destroy(image, 3);
      printf("Le nom du fichier output passé en argument ");
      printf("n'est pas valide\n");
      return -1;
   }

   //permet de gérer les caractères autres que 0 et 1 dans la graine
   if(seed != NULL){
      if(verify_seed(seed)){
         destroy(image, 3);
         printf("La graine passée en argument ");
         printf("n'est pas valide\n");
         return -1;
      }
   }

   //permet de gérer que tap est la représentation d'un nombre
   if(verify_tap(tap)){
      destroy(image, 3);
      printf("Le tap passé en argument ");
      printf("n'est pas valide\n");
      return -1;
   }

   //permet de gérer que le mot de passe est correct
   if(password != NULL){
      if(verify_password(password)){
         destroy(image, 3);
         printf("Le mot de passe en argument ");
         printf("n'est pas valide\n");
         return -1;
      }
   }

   if(password != NULL){
      char *final = (char *) malloc((sizeof(char) * strlen(password) * 6) + 1);
      seed = initialize_password(password, final);
      free(final);
   }

   printf("%d\n", strcmp(inputX, output));
   printf("%d\n", strcmp(inputX2, output));
   printf("%d\n", strcmp(outputX, input));
   printf("%d\n", strcmp(outputX2, input));

   unsigned k = 32;
   //permet de chiffrer/déchiffrer l'image si besoin
   if(strcmp(inputX, output) == 0 || strcmp(inputX2, output) == 0)
      transform(image, seed, tap, k);
   else if(strcmp(outputX, input) == 0 || strcmp(outputX2, input) == 0){
      load_pnm(&image, input);
      transform(image, seed, tap, k);
      write_pnm(image, output);
      destroy(image, 3);
      return 0;
   }
   //appel de write_pnm et checking des valeurs de retour
   switch(write_pnm(image, output)){
      case 0:
         printf("Tout s'est bien passé et l'image a pu être correctement ");
         printf("sauvée dans un fichier\n");
         break;
      case -1:
         printf("Le nom du fichier output passé en argument ");
         printf("n'est pas valide\n");
         return 0;
      case -2:
         printf("L'image n'a pas pu être sauvée dans un fichier\n");
         return 0;
      default:
         printf("Valeur de retour inconnue\n");
         return 0;
   }
   if(password != NULL){
      //free(seed);
   }
   destroy(image, 3);
   
   return 0;
}

