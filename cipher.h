/**
 * cipher.h
 * 
 * Ce fichier contient les les prototypes
 * des fonctions pour le chiffrement d'images PNM.
 * 
 * \author: Dumoulin Peissone S193957
 * \date: 10/03/21
 * \projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __CIPHER__
#define __CIPHER__

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

char *initialize_password(char *password, char *final);

int binary(int k);

#endif // __cipher__