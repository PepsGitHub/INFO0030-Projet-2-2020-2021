/**
 * advanced_cipher.h
 * 
 * Ce fichier contient les les prototypes
 * des fonctions pour le chiffrement avancé d'images PNM.
 * 
 * \author: Dumoulin Peissone S193957
 * \date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __ADVANCED_CIPHER__
#define __ADVANCED_CIPHER__

/**
 * \file advanced_cipher.h
 * \brief Librairie de chiffrement avancé d'images PNM
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 21/03/2021
*/

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

#endif // __advanced_cipher__