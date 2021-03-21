/**
 * basic_cipher.h
 * 
 * Ce fichier contient les les prototypes
 * des fonctions pour le chiffrement basique d'images PNM.
 * 
 * \author: Dumoulin Peissone S193957
 * \date: 21/03/21
 * \projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __BASIC_CIPHER__
#define __BASIC_CIPHER__

/**
 * \file basic_cipher.h
 * \brief Librairie de chiffrement basique d'images PNM
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 16/03/2021
*/

/**
 * \fn int transform(PNM *image, char *seed, char *tap, unsigned k)
 * \brief Chiffre une image
 * 
 * \param image un pointeur sur PNM
 * \param seed La séquence de bits initiale du registre
 * \param tap Un bit situé à une position particulière
 * \param k Le nombre d'opérations à effectuer
 * 
 * \pre: image != NULL, seed != NULL, tap != NULL
 * \post: chiffrement réussi
 * 
 * \return:
 *    0 Succès
 */
int transform(PNM *image, char *seed, char *tap, unsigned k);

#endif // __basic_cipher__