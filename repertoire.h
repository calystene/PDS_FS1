/*
 * repertoire.h
 *
 *  "@(#)repertoire.h	1.1 (C) P. Durif 1994"
 *
 */
#ifndef _REPERTOIRE_
#define _REPERTOIRE_

#include "nombres.h"

#define LONGMAXNOM 14

typedef struct ENTREE {
  INOMBRE i_nombre ;		/* NUM_NULL indique une entree libre */
  char nom [LONGMAXNOM] ;
} ENTREE ;

#endif
