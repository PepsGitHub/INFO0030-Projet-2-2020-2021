/**
 * verify.h
 * 
 * Ce fichier contient les prototypes de fonctions vérifiant d'autres fonctions
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 21/03/21
 * @projet: INFO0030 Projet 2
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __VERIFY__
#define __VERIFY__

/**
 * \file verify.h
 * \brief Librairie de vérification de fonctions
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 16/03/2021
*/

/**
 * \fn int manage_comments(FILE *fp)
 * \brief Permet de gérer une ligne pour savoir si on doit l'ignorer 
 *        (celles commençant par '#')
 * \param fp un pointeur sur FILE
 * 
 * \pre: fp != NULL
 * \post: la ligne est correctement ignorée
 * 
 * \return:
 *    0 Succès
 *    -1 Echec
 */

int manage_comments(FILE *fp);

/**
 * \fn int manage_format_input(PNM *image, char *format, char *input)
 * \brief Gère si le format correspond au format de l'input
 * 
 * \param image un pointeur sur PNM
 * \param format le format du fichier
 * \param input le nom du fichier en entrée
 * 
 * \pre: image != NULL, format != NULL, input != NULL
 * \post: format du fichier géré correctement
 * 
 * \return:
 *    0 Succès
 *    -1 Mauvais format passé en argument
 */

int manage_format_input(PNM *image, char *format, char *input);

/**
 * \fn int verify_output(char *output)
 * \brief Vérifie si l'output contient des caractères spéciaux interdits
 * 
 * \param output le nom du fichier en sortie
 * 
 * \pre: output != NULL
 * \post: output géré correctement
 * 
 * \return:
 *    0 Succès
 *    -1 Caractère invalide dans le nom du fichier
 */

int verify_output(char *output);

/**
 * \fn verify_seed(char *seed)
 * \brief Vérifie si la graine contient autre chose que des 0 ou des 1
 * 
 * \param seed une chaine de caractères représentant la graine
 * 
 * \pre: seed != NULL
 * \post: seed géré correctement
 * 
 * \return:
 *    0 Succès
 *    -1 Caractère invalide dans la graine
 */
int verify_seed(char *seed);

/**
 * \fn verify_tap(char *tap)
 * \brief Vérifie si le tap contient autre chose que des 0 ou des 1
 * 
 * \param tap une chaine de caractères représentant le tap
 * 
 * \pre: tap != NULL
 * \post: tap géré correctement
 * 
 * \return:
 *    0 Succès
 *    -1 Caractère invalide dans le tap
 */
int verify_tap(char *tap);

/**
 * \fn int verify_password(char *password)
 * \brief Vérifie si le mot de passe contient un autre caractère que ceux autorisés
 * 
 * \param password une chaine de caractères représentant le mot de passe
 * 
 * \pre: password != NULL
 * \post: mot de passe géré correctement
 * 
 * \return:
 *    0 Succès
 *    -1 Caractère invalide dans le mot de passe
 */
int verify_password(char *password);

#endif // __verify__