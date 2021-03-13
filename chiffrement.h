/**
 * chiffrement.h
 * 
 * Ce fichier contient les fonctions associées au chiffrement basique d'images
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 10/03/21
 * @projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __CHIFFREMENT__
#define __CHIFFREMENT__

/**
 * \file chiffrement.h
 * \brief Librairie pour gérer le chiffrement d'images pnm
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 10/03/2021
*/

/**
 * \fn int transform(PNM *image, char *filename, char *seed, char *tap)
 * \brief chiffre une image
 * 
 * \param image un pointeur sur PNM
 * \param filename le chemin vers le fichier contenant l'image.
 * \param seed La séquence de bits initiale du registre
 * \param tap Un bit situé à une position particulière
 * 
 * \pre: image != NULL, filename != NULL, seed != NULL, tap != NULL
 * \post: chiffrement réussi
 * 
 * \return:
 *    0 Succès
 *    -2 Echec
 */
int transform(PNM *image, char *seed, char *tap, unsigned k);

LFSR *initialize_password(char *password, char *tap);

int binary(int k);

#endif // __chiffrement__