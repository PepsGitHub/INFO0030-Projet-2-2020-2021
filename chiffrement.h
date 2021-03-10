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

int transform(PNM *image, char *filename, char *seed, char *tap);

int reverse_transform(PNM *image, char *filename, char *seed, char *tap);

#endif // __chiffrement__