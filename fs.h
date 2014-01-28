/*
 * fs.h
 *
 *
 *  "@(#)fs.h	1.3 (C) P. Durif 1994"
 */
/* La plupart des primitives renvoie -1 en cas d'erreur sauf celle qui
 *  renvoient un INOMBRE auquel cas c'est NUM_NULL qui est renvoye. */
/* "nom" designe un nom compose (contenant eventuellement des '/') 
 * "simple" designe un nom simple (ne contenant pas de '/') */
#ifndef _FS_
#define _FS_

#include "volume.h"
#include "nombres.h"
#include "repertoire.h"

typedef struct 	SUPER_BLOC {
  u_short	nb_blocs ;
  u_short	nb_inoeuds ;
  INOMBRE	i_contigu ; /* a partir de ce i_nombre, tous les i_noeuds
			       sont libres */ 
  INOMBRE   	i_chaine ;
  NUM_BLOC   	b_contigu ; /* a partir de ce bloc, tous les blocs
			       sont libres */ 
  NUM_BLOC   	b_chaine ;
  char   	magique [20] ; /* signature du systeme de fichier */
} SUPER_BLOC ;

enum CATEGORIE 	{ORDINAIRE, REPERTOIRE} ;

typedef struct 	INOEUD_OCCUPE {
  enum CATEGORIE type ;
  u_short	liens ; /* nombre d'entrees de repertoire referencant
			   ce inoeud */ 
  u_long   	taille ; /* taille logique en octets du fichier */
#define NB_BLOCS_DIRECTS 7
  NUM_BLOC	direct [NB_BLOCS_DIRECTS] ; /* les 7 premiers blocs
					       du fichier */ 
  NUM_BLOC	indirect ; /* bloc d'indirection pour les blocs
			      suivants */ 
  NUM_BLOC 	double_indirect ; /* bloc de double indirection ... */ 
} INOEUD_OCCUPE ;

typedef struct 	INOEUD_LIBRE {
  INOMBRE i_suiv ; /* liste chainee des inoeuds libres */
} INOEUD_LIBRE ;

typedef union {
  INOEUD_OCCUPE	occupe ;
  INOEUD_LIBRE  libre ;
} INOEUD ;

typedef struct 	BLOC_LIBRE {
  NUM_BLOC 	b_suiv ; /* liste chainee des blocs libres */
} BLOC_LIBRE ;

/*
 * Nombre de inoeuds par bloc
 */
#define INOEUDS_PAR_BLOC (BLOC_SIZE/sizeof (INOEUD [1]))

/*
 * Nombre d'entrees de repertoire par bloc
 */
#define ENTREES_PAR_BLOC (BLOC_SIZE / sizeof(struct ENTREE [1]))

/*
 * Nombre de numeros de bloc par bloc (pour les blocs d'indirection)
 */
#define NUMEROS_PAR_BLOC (BLOC_SIZE / sizeof (NUM_BLOC))


/*
 * Pour uniformiser les entrees sorties
 */
typedef union 	BLOC {
  VOL_BLOC	opaque ; /* fixe la taille du BLOC */
  BLOC_LIBRE	bloc_libre ;
  SUPER_BLOC 	super_bloc ;
  INOEUD 	inoeuds [INOEUDS_PAR_BLOC] ;
  ENTREE 	entrees [ENTREES_PAR_BLOC] ;
  NUM_BLOC 	blocs [NUMEROS_PAR_BLOC] ;
} BLOC ;

#if BLOC_SIZE < 64
/* malheureusement, on ne peut pas ecrire #if BLOC_SIZE != sizeof (BLOC),
 * il faut faire ce test a l'execution dans fairefs() par exemple
 */
#   error BLOC_SIZE : valeur probablement insuffisante.
#endif

/* numero de bloc volume contenant le i-noeud d'indice i_nombre */
#define IBLOC(i_nombre)  (((i_nombre) / INOEUDS_PAR_BLOC) + SUPER + 1)

/* indice physique du i-nombre dans son bloc */
#define INDICE(i_nombre) ((i_nombre) % INOEUDS_PAR_BLOC)


int lire_bloc (INOMBRE i_nombre, BLOC *b, NUM_BLOC numRel) ;
/* lit dans "b", le bloc RELATIF "numRel" c'est-a-dire le "numRel"ieme
 *  bloc du inoeud "i_nombre". Il faut donc d'abord transformer ce
 *  numero relatif en numero de bloc volume. */
/* S'il n'y a pas de bloc volume alloue au bloc alors la zone "b" est
 *  mise a zero et tout se passe normalement. */
/* Renvoie le nombre d'octets significatifs lus ou -1 si erreur. */ 

int ecrire_bloc (INOMBRE i_nombre, BLOC *b, NUM_BLOC numRel, u_short lg) ;
/* ecrit le BLOC "b" dans le "numRel"ieme bloc de "i_nombre". La
 *  taille du fichier peut s'en trouver augmentee. */
/* !!! Une ecriture peut amener a allouer un bloc physique pour les
 *  donnees, mais aussi un ou deux blocs d'indirection. */
/* Renvoie le nombre d'octets ecrits ("lg") ou -1 si erreur.  */

int lire_inoeud (INOMBRE i_nombre, INOEUD *inoeud) ;
/* charge le inoeud "i_nombre" en memoire centrale a l'adresse
 *  "inoeud" Renvoie -1 en cas d'erreur.  */

int vider_inoeud_ordinaire (INOMBRE i_nombre) ;
/* tous les blocs du inoeud sont liberes et sa taille est mise a
 *  zero. */
/* Le inoeud doit etre ORDINAIRE. */
/* Renvoie -1 en cas d'erreur. */

INOMBRE chercher_entree (INOMBRE irep, const char *simple) ;
/* cherche le INOMBRE associe au nom "simple" dans le repertoire
 *  "irep". */
/* Verifications :
 *   "simple" ne doit pas contenir de caractere '/'
 *   "irep" qui doit designer un REPERTOIRE */
/* Renvoie le INOMBRE de simple ou NUM_NULL en cas d'erreur. */

int creer_entree_ordinaire (INOMBRE irep, INOMBRE isimple, const char
			    *simple) ; 
/* cree une entree dans "irep" pour le lien ("isimple", "simple") et
 *  incremente le compteur de liens de "isimple" */
/* Verifications :
 *   "irep" designe un REPERTOIRE
 *   "isimple" designe un ORDINAIRE
 *   "simple" ne doit pas deja exister dans "irep"
 *   "simple" ne doit pas contenir de caractere '/' */
/* Renvoie -1 en cas d'erreur. */

int creer_entree_repertoire (INOMBRE irep, const char *simple) ;
/* cree dans "irep" un nouveau repertoire de nom "simple" */
/* Verifications :
 *   "irep" designe un REPERTOIRE
 *   "simple" ne doit pas deja exister dans "irep"
 *   "simple" ne doit pas contenir de caractere '/' */
/* Renvoie -1 en cas d'erreur. */

int supprimer_entree_ordinaire (INOMBRE irep, const char *simple) ;
/* supprime l'entree "simple" du repertoire "irep",
 *  de plus, si le i-noeud de "simple" n'a plus de liens, il est
 *  detruit et sa place est recuperee. */
/* Verifications :
 *   "irep" doit etre un REPERTOIRE
 *   "simple" doit exister dans irep
 *   "simple" doit etre un nom de fichier ORDINAIRE
 *   "simple" ne doit pas contenir de caractere '/' */
/* Renvoie -1 en cas d'erreur. */

int supprimer_entree_repertoire (INOMBRE irep, const char *simple) ;
/* supprime l'entree "simple" du repertoire "irep",
 * detruit et recupere la place du repertoire "simple". */
/* Verifications :
 *   "irep" doit etre un REPERTOIRE
 *   "simple" doit etre un nom de REPERTOIRE
 *           qui ne contient que "." et ".." et qui ne se trouve pas
 *           dans le chemin courant.
 *   "simple" ne doit pas contenir de caractere '/' */
/* Renvoie -1 en cas d'erreur. */

INOMBRE creer_inoeud_ordinaire (void) ;
/* alloue et initialise a vide un nouvel inoeud ORDINAIRE. */
/* Le compteur de liens de ce inoeud est bien entendu nul puisqu'il
 *  n'est designe par aucun repertoire. */
/* Renvoie le INOMBRE alloue ou NUM_NULL. */
/* Cette primitive sert a obtenir un nouvel i-noeud lors de
 *  l'ouverture (ouvrir()) en creation d'un fichier inexistant, il
 *  suffit ensuite d'associer un nom au i-noeud en avec la primitive
 *  creer_entree_ordinaire().  */

int changer_de_chemin_courant (const char *nom) ;
/* le nouveau chemin courant est donne par "nom" qui peut etre un nom
 *  absolu ou relatif. */ 
/* En interne, on peut gerer une pile des inombres successifs du
 *  chemin courant pour assurer qu'on ne detruit pas un repertoire du
 *  chemin courant. */
/* "nom" doit etre un REPERTOIRE */
/* Renvoie -1 en cas d'erreur. */

INOMBRE localiser (const char *nom) ;
/* renvoie le INOMBRE correspondant au "nom", NUM_NULL si impossible */
/* La recherche est absolue ou relative suivant que "nom" commence par
 *  '/' ou pas. */

int monter (const char *fs) ;
/* demande le montage du volume de nom "fs" (vol_monter()) puis
 *  verifie l'information magique du super bloc, enfin, initialise le
 *  repertoire courant sur le repertoire racine. */
/* Renvoie -1 en cas d'erreur.  */

int demonter (void) ;
/* demonte le volume courant et vide la pile du chemin courant. */
/* Renvoie -1 en cas d'erreur. */


int fairefs (const char *volume, u_short nb_blocs, u_short nb_inoeuds) ;
/* construit un nouveau systeme de fichiers sur le "volume" indique.
 *  "nb_blocs" est le nombre total de blocs volume,
 *  "nb_inoeuds" est le nombre total de inoeuds. */
/* Remarques :
 *   - il faut au moins de la place pour "." et ".." de I_ROOT.
 *   - en principe, un meme programme ne devrait pas utiliser a la fois
 *     cette primitive et les autres de ce module. */
/* Renvoie -1 en cas d'erreur. */

#endif
