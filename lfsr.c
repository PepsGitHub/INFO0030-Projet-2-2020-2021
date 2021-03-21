/**
 * lfsr.c
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le chiffrement d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

#define TRIPLET 3
#define SEED_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "lfsr.h"
#include "seatest.h"

/**
 * Définition du type opaque LFSR
 *
 */
struct LFSR_t{
   unsigned int N;//nombre de bits dans le registre
   char seed[SEED_SIZE]; //séquence de bits initiale du registre
   unsigned int tap;//bit situé à une position particulière
};

//debut constructeur
LFSR *create_lfsr(unsigned int N, char *seed, unsigned int tap){
   assert(seed != NULL && tap <= N);

   LFSR *lfsr = malloc(sizeof(LFSR));
   if(!lfsr)
      return NULL;

   set_N(lfsr, N);
   set_seed(lfsr, seed);
   set_tap(lfsr, tap);

   return lfsr;
}//fin constructeur

//debut accesseurs en lecture
unsigned int get_N(LFSR *lfsr){
   assert(lfsr != NULL);

   return lfsr->N;
}

char *get_seed(LFSR *lfsr){
   assert(lfsr != NULL);

   return lfsr->seed;
}

unsigned int get_tap(LFSR *lfsr){
   assert(lfsr != NULL);

   return lfsr->tap;
}//fin accesseurs en lecture

//debut accesseurs en ecriture
LFSR *set_N(LFSR *lfsr, unsigned int N){
   lfsr->N = N;

   return lfsr;
}

LFSR *set_seed(LFSR *lfsr, char *seed){
   assert(lfsr!=NULL && seed != NULL);

   for(unsigned int i = 0; i < get_N(lfsr); i++)
      lfsr->seed[i] = seed[i];

   return lfsr;
}

LFSR *set_tap(LFSR *lfsr, unsigned int tap){
   lfsr->tap = tap;

   return lfsr;
}//fin accesseurs en écriture

//debut destroy
void destroy_lfsr(LFSR *lfsr){
   assert(lfsr != NULL);

   free(lfsr);
}//fin destroy

//debut initialize
LFSR *initialize(char *seed, unsigned int tap){
   assert(seed != NULL);
   
   unsigned int count = 0;
   for(unsigned int i = 0; seed[i] != '\0'; i++)
      count++;
   unsigned int N = count;
   LFSR *lfsr = create_lfsr(N, seed, tap);

   return lfsr;
}//fin initialize

//debut operate
int operate(LFSR *lfsr){
   assert(lfsr != NULL);

   char *stateRegister = get_seed(lfsr);
   unsigned int indexTap = get_N(lfsr) - get_tap(lfsr) - 1;

   char firstChar = stateRegister[0], tapChar = stateRegister[indexTap];
   for(unsigned int i = 0; i < get_N(lfsr)-1; i++){
      stateRegister[i] = stateRegister[i+1];
   }

   if(firstChar != tapChar){
      stateRegister[get_N(lfsr)-1] = '1';
      return 1;
   }else{
      stateRegister[get_N(lfsr)-1] = '0';
      return 0;
   }
}//fin operate

//debut string
char *string(LFSR *lfsr){
   assert(lfsr != NULL);

   return get_seed(lfsr);
}//fin string

//debut generate
int generate(LFSR *lfsr, unsigned int k){
   assert(lfsr != NULL && k > 0);

   int var = 0;
   for(unsigned int i = 0; i < k; i++){
      if(operate(lfsr) == 1)
         var = var * 2 + 1;
      else
         var *= 2;
   }
   return var;
}//fin generate