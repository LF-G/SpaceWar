/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
//
/////////////////////////////////////////////////////////////////////////*/


#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "view.h"


/* Lê os inputs do teclado, interpreta a ação que deve ser feita e chama a
função adequada para mudar o ângulo das naves, acelerá-las, desacelerá-las
ou introduzir projéteis.                                                 */

void inputs (WINDOW *w, corpo *c, int *n);


#endif

