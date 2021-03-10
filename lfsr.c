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
   char seed[100]; //séquence de bits initiale du registre
   unsigned int tap;//bit situé à une position particulière
};

//debut constructeur
LFSR *create_lfsr(unsigned int N, char *seed, unsigned int tap){
   assert(N > 0 && seed != NULL && tap > 0 && tap < N);

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
   assert(lfsr!=NULL && N > 0);

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
   assert(lfsr!=NULL && tap > 0 && tap < get_N(lfsr));

   lfsr->tap = tap;

   return lfsr;
}//fin accesseurs en écriture

//debut destroy
void destroy_lfsr(LFSR *lfsr, unsigned int allocation_value){
   assert(lfsr != NULL && allocation_value > 0 && allocation_value < 2);
   switch(allocation_value){
   case 1://détruit lfsr
      free(lfsr);
      break;
   }
}//fin destroy

LFSR *initialisation(char *seed, unsigned int tap){
   assert(seed != NULL && tap > 0 && tap < strlen(seed));

   unsigned int N = strlen(seed);
   LFSR *lfsr = create_lfsr(N, seed, tap);

   return lfsr;
}

int operation(LFSR *lfsr){
   assert(lfsr != NULL);

   char *stateRegister = get_seed(lfsr);
   unsigned int indexTap = get_N(lfsr) - get_tap(lfsr) - 1;

   char firstChar = stateRegister[0], tapChar = stateRegister[indexTap];
   int bit = 0;
   for(unsigned int i = 0; i < get_N(lfsr)-1; i++){
      stateRegister[i] = stateRegister[i+1];
   }

   if(firstChar != tapChar){
      stateRegister[get_N(lfsr)-1] = '1';
      bit = 1;
      return bit;
   }else{
      stateRegister[get_N(lfsr)-1] = '0';
      bit = 0;
      return bit;
   }
}

/*int reverse_operation(LFSR *lfsr){
   assert(lfsr != NULL);

   char *stateRegister = get_seed(lfsr);
   unsigned int indexTap = get_N(lfsr) - get_tap(lfsr) - 2;

   char lastChar = stateRegister[get_N(lfsr) - 1], tapChar = stateRegister[indexTap];
   int bit = 0;
   for(unsigned int i = 0; i < get_N(lfsr) - 1; i++){
      stateRegister[i+1] = stateRegister[i];
   }

   if(lastChar == tapChar){
      stateRegister[0] = '0';
      bit = 0;
      return bit;
   }else{
      stateRegister[0] = '1';
      bit = 1;
      return bit;
   }
}*/

char *string(LFSR *lfsr){
   assert(lfsr != NULL);

   char *state_register = get_seed(lfsr);

   return state_register;
}

int generation(LFSR *lfsr, unsigned int k){
   assert(lfsr != NULL && k > 0);

   int var = 0;
   for(unsigned int i = 0; i < k; i++){
      if(operation(lfsr) == 1)
         var = var * 2 + 1;
      else
         var *= 2;
   }
   return var;
}

/*int reverse_generation(LFSR *lfsr, unsigned int k){
      assert(lfsr != NULL && k > 0);

   int var = generation(lfsr, k);
   while(k > 0){
      if(reverse_operation(lfsr) == 0)
         var = (var-1)/2;
      else
         var /= 2;
      k--;
   }
   return var;
}*/