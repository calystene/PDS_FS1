/*
 * nombres.h
 *
 *
 *  "@(#)nombres.h	1.1 (C) P. Durif 1994"
 *
 */
#ifndef _NOMBRES_
#define _NOMBRES_

#include <sys/types.h>  /* pour u_short et u_long */

typedef u_short NUM_BLOC ;

/*
 * le bloc 0 est le bloc de boot (inutilise ici)
 * le bloc 1 est le super bloc
 * le bloc 2 est le premier de la table des i-noeuds
 */
#define SUPER 1 /* numero de bloc du super bloc */

typedef u_short INOMBRE ;
/*
 * le INOMBRE 0 sert a representer les entrees de repertoire libre.
 *              Le inoeud correspondant n'est donc jamais utilise.
 *
 * le INOMBRE 1 etait utilise a l'origine pour chainer les blocs
 *              deffectueux du disque. Le inoeud correspondant
 *              n'est donc jamais utilise.
 *
 * Finallement, le premier INOMBRE effectivement utilise est le 2,
 * qui est toujours celui du repertoire racine du systeme de fichier.
 * Vous pouvez le verifier, sous Unix, en faisant par exemple "ls -id /"
 * ou encore "ls -id /usr" qui sont tous deux des systemes
 * de fichiers differents.
 */
#define I_ROOT 2  /* i-nombre racine */

#define NUM_NULL 0 /* numero de bloc ou de inoeud inexistant */


#endif
