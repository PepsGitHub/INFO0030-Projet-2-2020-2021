/**
 * lfsr.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le chiffrement d'images PNM.
 * 
 * \author: Dumoulin Peissone S193957
 * \date: 16/03/21
 * \projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __LFSR__
#define __LFSR__

/**
 * \file lfsr.h
 * \brief Librairie pour gérer le chiffrement d'images pnm(.pbm, .pgm, .ppm)
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 16/03/2021
 * 
 * Déclaration du type opaque LFSR
 *
 */
typedef struct LFSR_t LFSR;

/**
 * \fn LFSR *create_lsfr(void)
 * \brief Crée et alloue dynamiquement une variable de type opaque LFSR*
 * 
 * \param N Le nombre de bits dans le registre
 * \param seed La séquence de bits initiale du registre
 * \param tap Un bit situé à une position particulière
 * 
 * \pre: seed != NULL, tap <= N
 * \post: *lfsr alloué
 * 
 * \return:
 *    lfsr Succès
 *    NULL Erreur lors de l'allocation dynamique
 */
LFSR *create_lfsr(unsigned int N, char *seed, unsigned int tap);

/**
 * \fn unsigned int get_N(LFSR *lfsr)
 * \brief Accesseur en lecture pour le champ N de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: accès en lecture au champ N de *lfsr
 * 
 * \return:
 *    lfsr->N Succès
 */
unsigned int get_N(LFSR *lfsr);

/**
 * \fn char *get_seed(LFSR *lfsr)
 * \brief Accesseur en lecture pour le champ seed de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: accès en lecture au champ seed de *lfsr
 * 
 * \return:
 *    lfsr->seed Succès
 */
char *get_seed(LFSR *lfsr);

/**
 * \fn unsigned int get_tap(LFSR *lfsr)
 * \brief Accesseur en lecture pour le champ tap de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: accès en lecture au champ tap de *lfsr
 * 
 * \return:
 *    lfsr->tap Succès
 */
unsigned int get_tap(LFSR *lfsr);

/**
 * \fn LFSR *set_N(LFSR *lfsr, unsigned int N)
 * \brief Accesseur en écriture pour le champ N de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * \param N le nombre de bits dans le registre
 * 
 * \pre: lfsr != NULL, N > 0
 * \post: accès en écriture au champ N de *lfsr
 * 
 * \return:
 *    lfsr Succès
 */
LFSR *set_N(LFSR *lfsr, unsigned int N);

/**
 * \fn LFSR *set_seed(LFSR *lfsr, char *seed)
 * \brief Accesseur en écriture pour le champ seed de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * \param seed la séquence de bits initiale du registre
 * 
 * \pre: lfsr != NULL, seed != NULL
 * \post: accès en écriture au champ seed de *lfsr
 * 
 * \return:
 *    lfsr Succès
 */
LFSR *set_seed(LFSR *lfsr, char *seed);

/**
 * \fn LFSR *set_tap(LFSR *lfsr, unsigned int tap)
 * \brief Accesseur en écriture pour le champ tap de *lfsr
 * 
 * \param lfsr un pointeur sur LFSR
 * \param tap un bit situé à une position particulière
 * 
 * \pre: lfsr != NULL, 0 < tap < lfsr->N
 * \post: accès en écriture au champ tap de *lfsr
 * 
 * \return:
 *    lfsr Succès
 */
LFSR *set_tap(LFSR *lfsr, unsigned int tap);

/**
 * \fn void destroy_lfsr(LFSR *lfsr)
 * \brief Libère la mémoire allouée à *lfsr
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: Libère un *lfsr alloué
 * 
 * \return:
 *    /
 */
void destroy_lfsr(LFSR *lfsr);

/**
 * \fn LFSR *initialize(char *seed, unsigned int tap)
 * \brief Crée un LFSR et remplit ses champs
 * 
 * \param seed la séquence de bits initiale du registre
 * \param tap un bit situé à une position particulière
 * 
 * \pre: lfsr != NULL
 * \post: lfsr créé et ses champs sont initialisés
 * 
 * \return:
 *    lfsr Succès
 */
LFSR *initialize(char *seed, unsigned int tap);

/**
 * \fn int operate(LFSR *lfsr)
 * \brief Réalise une opération sur le registre
 * 
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: opération réussie
 * 
 * \return:
 *    0 Le bit de poids faible après l'opération = 0
 *    1 Le bit de poids faible après l'opération = 1
 */
int operate(LFSR *lfsr);

/**
 * \fn char *string(LFSR *lfsr)
 * \brief Transforme le contenu actuel du registre en une chaîne de charactères
 * 
 * \param lfsr un pointeur sur LFSR
 * 
 * \pre: lfsr != NULL
 * \post: transformation réussie
 * 
 * \return:
 *    stateRegister Succès
 */
char *string(LFSR *lfsr);

/**
 * \fn int generate(LFSR *lfsr, unsigned int k)
 * \brief Réalise k opérations sur le registre
 * 
 * \param lfsr un pointeur sur LFSR
 * \param k le nombre d'opérations à effectuer sur le registre
 * 
 * \pre: lfsr != NULL, k > 0
 * \post: k opérations réussies
 * 
 * \return:
 *    var Une valeur entière représentant les k bits générés par chaque étape
 */
int generate(LFSR *lfsr, unsigned int k);

#endif // __lfsr__