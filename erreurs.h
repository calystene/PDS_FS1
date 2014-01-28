/*
 * erreurs.h
 *
 *  "@(#)erreurs.h	1.2 (C) P. Durif 1994"
 *
 */

enum ERREUR {
   OK,
   PARAMETRES_INCONSISTANTS,
   TABLE_INOEUDS_SATUREE,
   SYSTEME_DE_FICHIER_SATURE,
   LIEN_SUR_REPERTOIRE,
   REPERTOIRE_INEXISTANT,
   VOLUME_INEXISTANT,
   VOLUME_DEJA_MONTE,
   VOLUME_NON_MONTE,
   EXISTE_DEJA,
   FICHIER_INEXISTANT,
   PAS_UN_REPERTOIRE,
   PAS_UN_ORDINAIRE,
   PAS_UN_SYSTEME_DE_FICHIERS,
   REPERTOIRE_ACTIF,
   REPERTOIRE_NON_VIDE,
   LECTURE_IMPOSSIBLE,
   ECRITURE_IMPOSSIBLE,
   ACCES_FICHIER_HORS_LIMITE,
   OPERATION_IMPOSSIBLE
} ;

extern enum ERREUR erreur ;
void perreur (const char *chunk) ;
/* imprime un message d'erreur fonction de "chunk" et de la valeur
 *  de la variable "erreur" puis remet erreur a OK */
