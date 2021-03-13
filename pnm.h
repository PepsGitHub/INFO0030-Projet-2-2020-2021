/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * \author: Dumoulin Peissone S193957
 * \date: 05/03/21
 * \projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * \file pnm.h
 * \brief Librairie pour gérer les fichiers d'extension pnm (.pbm, .pgm, .ppm)
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 19/02/2021
 * 
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * \fn int load_pnm(PNM **image, char* filename)
 * \brief Charge une image PNM depuis un fichier
 * 
 * \param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * \param filename le chemin vers le fichier contenant l'image.
 *
 * \pre: image != NULL, filename != NULL
 * \post: image pointe vers l'image chargée depuis le fichier.
 *
 * \return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * \fn int write_pnm(PNM *image, char* filename)
 * \brief Sauvegarde une image PNM dans un fichier.
 * 
 * \param image un pointeur sur PNM.
 * \param filename le chemin vers le fichier de destination.
 *
 * \pre: image != NULL, filename != NULL
 * \post: le fichier filename contient l'image PNM image.
 *
 * \return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */

int write_pnm(PNM *image, char* filename);

/**
 * \fn PNM *create_pnm(void)
 * \brief Crée et alloue dynamiquement une variable de type opaque PNM*
 * 
 * \param /
 * 
 * \pre: /
 * \post: *image alloué
 * 
 * \return:
 *    image Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

PNM *create_pnm(void);

/**
 * \fn char *get_magicNumber(PNM *image)
 * \brief Accesseur en lecture pour le champ magicNumber de image*
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: accès en lecture au champ magicNumber de *image
 * 
 * \return:
 *    image->magicNumber Succès
 */

char *get_magicNumber(PNM *image);

/**
 * \fn unsigned int get_columns(PNM *image)
 * \brief Accesseur en lecture pour le champ columns de image*
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: accès en lecture au champ columns de *image
 * 
 * \return:
 *    image->columns Succès
 */

unsigned int get_columns(PNM *image);

/**
 * \fn unsigned int get_rows(PNM *image)
 * \brief Accesseur en lecture pour le champ rows de image*
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: accès en lecture au champ rows de *image
 * 
 * \return:
 *    image->rows Succès
 */

unsigned int get_rows(PNM *image);

/**
 * \fn unsigned int get_maxValuePixel(PNM *image)
 * \brief Accesseur en lecture pour le champ maxValuePixel de image*
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: accès en lecture au champ maxValuePixel de *image
 * 
 * \return:
 *    image->getMaxValuePixel Succès
 */

unsigned int get_maxValuePixel(PNM *image);

/**
 * \fn unsigned int *get_matrix(PNM *image)
 * \brief Accesseur en lecture pour le champ matrix de image*
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: accès en lecture au champ matrix de *image
 * 
 * \return:
 *    image->matrix Succès
 */

unsigned int **get_matrix(PNM *image);

/**
 * \fn PNM *set_magicNumber(PNM *image, char *magicNumber)
 * \brief Accesseur en écriture pour le champ magicNumber de *image
 * 
 * \param image un pointeur sur PNM
 * \param magicNumber nombre magique qui caractérise le type de fichier
                      ("P1"" pour pbm, "P2" pour pgm, "P3" pour ppm)
 * 
 * \pre: image != NULL
 * \post: accès en écriture au champ magicNumber de *image
 * 
 * \return:
 *    image Succès
 */

PNM *set_magicNumber(PNM *image, char *magicNumber);

/**
 * \fn PNM *set_columns(PNM *image, unsigned int columns)
 * \brief Accesseur en écriture pour le champ columns de *image
 * 
 * \param image un pointeur sur PNM
 * \param columns nombre de pixels de hauteur
 * 
 * \pre: image != NULL
 * \post: accès en écriture au champ columns de *image
 * 
 * \return:
 *    image Succès
 */

PNM *set_columns(PNM *image, unsigned int columns);

/**
 * \fn PNM *set_rows(PNM *image, unsigned int rows)
 * \brief Accesseur en écriture pour le champ rows de *image
 * 
 * \param image un pointeur sur PNM
 * \param rows nombre de pixels de largeur
 * 
 * \pre: image != NULL
 * \post: accès en écriture au champ rows de *image
 * 
 * \return:
 *    image Succès
 */

PNM *set_rows(PNM *image, unsigned int rows);

/**
 * \fn PNM *set_maxValuePixel(PNM *image, unsigned int maxValuePixel)
 * \brief Accesseur en écriture pour le champ maxValuePixel de *image
 * 
 * \param image un pointeur sur PNM
 * \param maxValuePixel valeur maximale que peut prendre un pixel
 * 
 * \pre: image != NULL
 * \post: accès en écriture au champ maxValuePixel de *image
 * 
 * \return:
 *    image Succès
 */

PNM *set_maxValuePixel(PNM *image, unsigned int maxValuePixel);

/**
 * \fn PNM *set_matrix(PNM *image, unsigned int *matrix)
 * \brief Accesseur en écriture pour le champ matrix de *image
 * 
 * \param image un pointeur sur PNM
 * \param matrix matrice contenant la valeur de chaque pixel de l'image
 * 
 * \pre: image != NULL
 * \post: accès en écriture au champ matrix de *image
 * 
 * \return:
 *    image Succès
 */

PNM *set_matrix(PNM *image, unsigned int **matrix);

/**
 * \fn int create_matrix(PNM *image)
 * \brief Crée et alloue dynamiquement la matrice de *image
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre: image != NULL
 * \post: matrice allouée
 * 
 * \return:
 *    image->matrix Succès
 *    -1 Erreur lors de l'allocation dynamique
 */

int create_matrix(PNM *image);

/**
 * \fn int load_matrix(PNM *image, FILE *fp)
 * \brief Lecture dans un fichier et remplissage de la matrice de *image
 * 
 * \param image un pointeur sur PNM
 * \param fp un pointeur sur FILE
 * 
 * \pre: image != NULL, fp != NULL
 * \post: matrice chargée
 * 
 * \return:
 *    0 Succès
 *    -3 Le contenu du fichier en input est mal formé
 */

int load_matrix(PNM *image, FILE *fp);

/**
 * \fn int write_matrix(PNM *image, FILE *fp)
 * \brief Ecriture de la matrice de *image dans un fichier
 * 
 * \param image un pointeur sur PNM
 * \param fp un pointeur sur FILE
 * 
 * \pre: image != NULL, fp != NULL
 * \post: matrice 
 * 
 * \return:
 *    0 Succès
 *    -2 L'image n'a pas pu être sauvée dans un fichier
 */

int write_matrix(PNM *image, FILE *fp);

/**
 * \fn void destroy(PNM *image, unsigned int allocation_value)
 * \brief Libère la mémoire en fonction de l'allocation
 * \param image un pointeur sur PNM
 * \param allocation_value le nombre de "couches" d'allocations
 * 
 * \pre: image != NULL, 0 < allocation_value < 4
 * \post: autant de libérations que d'allocations mémoires
 * 
 * \return:
 *    /
 */

void destroy(PNM *image, unsigned int allocation_value);

#endif // __PNM__

