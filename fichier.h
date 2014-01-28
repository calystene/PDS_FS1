/*
 * fichier.h
 *
 *
 *  "@(#)fichier.h	1.1 (C) P. Durif 1994"
 */
/* Toutes les primitives renvoient
 *     -1 en cas d'echec (primitive perreur())
 *
 * SAUF
 *     ouvrir() qui renvoie NULL en cas d'echec.
 *
 * DE PLUS
 *     lire() et ecrire() qui renvoient le nombre d'octets manipules
 *     ou -1 en cas d'echec.
 */
#include "fs.h"


typedef struct INFO {
   u_long taille ; /* en octets */
   u_short liens ;
   enum CATEGORIE type ;
   INOMBRE i_nombre ;
} INFO ;

int get_info   (const char *nom, INFO *info) ;
/* garnit la zone "info" avec les informations sur le fichier "nom" */

int creer_repertoire (const char *nom) ;
/* "nom" ne doit pas deja exister, les entrees "." et ".." sont
 *  crees automatiquement. */

int detruire_repertoire (const char *nom) ;
/* "nom" doit etre un repertoire vide (sauf "." et "..") qui ne se trouve
 *  pas sur le chemin du repertoire courant. */
/* Remarque : le repertoire racine ne peut jamais etre detruit
 *  puisqu'il se trouve toujours dans le chemin courant */

int creer_lien (const char *nouveau, const char *cible) ;
/* ajoute un lien sur "cible" dont le nom est "nouveau",
 *  "nouveau" ne doit pas deja exister
 *  "cible" doit etre un ORDINAIRE */

int detruire_lien   (const char *nom) ;
/* supprime un lien sur le INOEUD designe par nom
 *  "nom" doit etre ORDINAIRE
 *  si le nombre de liens devient nul, le fichier est effectivement
 *  detruit */  


enum MODE {LECTURE = 0x01, ECRITURE = 0x02, LECTURE_ECRITURE = 0x03} ;
enum OPERATION {OUVERTURE, CREATION} ;

typedef struct	FICHIER {
   INOMBRE 	i ;
   enum MODE 	mode ;
   u_long 	pointeur ; /* position courante en octets dans le
			      fichier */ 
} FICHIER ;

FICHIER *ouvrir (const char *nom, enum MODE mode, enum OPERATION o) ;
/* en CREATION, le fichier est ORDINAIRE et ne peut ecraser
 *  qu'un fichier ORDINAIRE. */
/* en OUVERTURE, le fichier doit exister et ce peut etre un ORDINAIRE 
 *  ou un REPERTOIRE (mais alors, seulement en LECTURE). */
/* les operations : */
/* OUVERTURE : le fichier doit deja exister, les trois modes (LECTURE,
 *  ECRITURE, LECTURE_ECRITURE) sont autorises */
/* CREATION : le fichier est eventuellement cree, dans tous les cas
 *  il est vide. Le "mode" doit etre ECRITURE ou LECTURE_ECRITURE. */

int fermer (FICHIER *f) ;
/* desalloue la structure designe par "f" */

int lire   (FICHIER *f, void *zone, u_long taille) ;
/* lit au plus "taille" octets dans zone depuis la position courante
 *  de "f". */
/* La position courante de "f" est incrementee de "taille". */
/* Renvoit le nombre d'octets lus ou -1 si erreur */

int ecrire (FICHIER *f, const void *zone, u_long taille) ;
/* ecrit au plus "taille" octets de "zone" dans le fichier a partir de
 *  la position courante de "f". */
/* La position courante de "f" est incrementee de "taille". */
/* Renvoit le nombre d'octets ecrits ou -1 si erreur */

int positionner (FICHIER *f, u_long pointeur) ;
/* la position courante du fichier est mise a "pointeur". */
