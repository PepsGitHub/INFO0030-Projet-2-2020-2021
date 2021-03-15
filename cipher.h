/**
 * cipher.h
 * 
 * Ce fichier contient les les prototypes
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
#ifndef __CIPHER__
#define __CIPHER__

/**
 * \fn int transform(PNM *image, char *filename, char *seed, char *tap)
 * \brief chiffre une image
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

/**
 * \fn char *initialize_password(char *password, char *passwordBinary)
 * \brief Permet de gérer un mot de passe pour advanced_cipher
 * 
 * \param password Le mot de passe passé en argument
 * \param passwordBinary La conversion du mot de passe en binaire
 * 
 * \pre: password != NULL
 * \post: Conversion du mot de passe en binaire réussie
 * 
 * \return:
 *    passwordBinary Succès
 */
char *initialize_password(char *password, char *passwordBinary);

/**
 * \fn int binary(int position)
 * \brief Permet de convertir la position d'un caractère du mot de passe en nombre binaire
 * 
 * \param position
 * 
 * \pre: position >= 0
 * \post: Conversion en binaire réussie
 * 
 * \return:
 *    passwordBinary Succès
 */
int binary(int position);

#endif // __cipher__