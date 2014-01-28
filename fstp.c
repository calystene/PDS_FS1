/*-* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                                        Philippe Marquet --- <marquet@lifl.fr>
                                        13 Feb 1998
    File:  fstp.c
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef lint
static const char *WHAT_STRING = "" ;
#endif /* lint */

#include <stdlib.h>
#include <stdio.h>

#include "fs.h"
#include "erreurs.h"

static NUM_BLOC get_numero_logique (NUM_BLOC numRel, INOEUD_OCCUPE
				    *inoeud)  
/* traduit le numero relatif en numero logique */
{
  return NUM_NULL ;
}

int lire_bloc (INOMBRE i_nombre, BLOC *b, NUM_BLOC numRel)
/* lit dans "b", le bloc RELATIF "numRel" c'est-a-dire le "numRel"ieme
 *  bloc du inoeud "i_nombre". Il faut donc d'abord transformer ce
 *  numero relatif en numero de bloc volume. */
/* S'il n'y a pas de bloc volume alloue au bloc alors la zone "b" est
 *  mise a zero et tout se passe normalement. */
/* Renvoie le nombre d'octets significatifs lus ou -1 si erreur. */ 

{
  bzero (b, BLOC_SIZE) ; 
  return BLOC_SIZE ; 
}

