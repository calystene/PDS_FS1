/*
 * volume.h
 *
 *  "@(#)volume.h	1.2 (C) P. Durif 1994"
 *
 * renvoient -1 si erreur, 0 si succes
 */
#ifndef _VOLUME_
#define _VOLUME_

#include "nombres.h"

#define BLOC_SIZE 64

typedef char VOL_BLOC [BLOC_SIZE] ;

/* Pour la creation d'un nouveau volume par fairefs() Un volume est
 *  implante par un fichier Unix, ces operations effectuent donc la *
 *  creation et la fermeture d'un fichier Unix.
 */
int vol_debut_creer  (const char *volume) ;
int vol_fin_creer    (void) ;


/* Lorsque le shell est lance, il commence par monter un volume
 * (i.e. ouverture du fichier Unix).
 * Quand il se termine, il le demonte (i.e. fermeture de fichier).
 */
int vol_monter   (const char *volume) ;
int vol_demonter (void) ;

/* Lit/ecrit le "n"ieme (numero logique) bloc volume dans/depuis la zone b */
int vol_lire   (NUM_BLOC n, VOL_BLOC b) ;
int vol_ecrire (NUM_BLOC n, VOL_BLOC b) ;

#endif
