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
  VOL_BLOC b;
  VOL_BLOC bb;
  int q,r;
  
  if(numRel < NB_BLOCS_DIRECTS)
    {
      return (inoeud)->direct[numRel];
    }  
  numRel -= NB_BLOCS_DIRECTS;
  
  if(numRel < NUMEROS_PAR_BLOC)
    {
      vol_lire(inoeud->indirect,b);
      return b[numRel];
    }
  numRel -= NUMEROS_PAR_BLOC;
  
  return NUM_NULL;
}

int lire_bloc (INOMBRE i_nombre, BLOC *b, NUM_BLOC numRel)
/* lit dans "b", le bloc RELATIF "numRel" c'est-a-dire le "numRel"ieme
 *  bloc du inoeud "i_nombre". Il faut donc d'abord transformer ce
 *  numero relatif en numero de bloc volume. */
/* S'il n'y a pas de bloc volume alloue au bloc alors la zone "b" est
 *  mise a zero et tout se passe normalement. */
/* Renvoie le nombre d'octets significatifs lus ou -1 si erreur. */ 

{/*
  NUM_BLOC numLog;
  INOMBRE i_nombre;
  INOEUD *inoeud;
  int nb_octetsLu;
 */
  /* On nous fournit un INOMBRE, on doit instancier dans b l'adresse du bloc de numero relatif numRel */ 
  /*
  if(lire_inoeud(i_nombre, inoeud)) 
    {
      
    }
  else
    {
      //erreur
    }
  numLog = get_numero_logique(numRel, b);
  */
  
  bzero (b, BLOC_SIZE) ; 
  return BLOC_SIZE ; 
}

