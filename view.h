/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
//
//////////////////////////////////////////////////////////////////////////*/


#ifndef _VIEW_H
#define _VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "xwc.h"
#include "model.h"


/* Recebe uma janela w, a lista encadeada com cabeça c - tal que as duas
primeiras células de c contêm as naves e as restantes os projéteis -, 
vetores de pics e vetores de masks. Limpa a janela w e desenha nela o fundo,
a terra na posição de coordenadas [400, 400] e as naves nas posições
descritas na lista ligada c. Pics e masks contêm as images de fundo, do
planeta e dos projéteis. Blues e bluesM, as imagens da nave azul, e reds e
redsM, as imagens da nave vermelha.                                       */

void drawShips (WINDOW *w, corpo *c, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[]);


/* Funciona como a função drawShips, porém só depois que o jogo acabou.
Dependendo do valor de gameover, imprime as imagens de explosão na posição
da(s) nave(s) que foram destruídas.                                       */

void drawShipsEnd (WINDOW *w, corpo *c, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[], PIC exp[], MASK expM[], int gameover, int i);


/* Recebe as imagens das naves e de uma explosão e o inteiro gameover. Faz a 
animação de explosão da(s) nave(s) que foram destruídas e, dependendo do 
valor da variável gameover, imprime na tela uma mensagem de fim de jogo.  */

void fimdejogo (WINDOW *w, corpo *c, float dt, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[], PIC exp[], MASK expM[], int gameover);


/* Inicializa os vetores pics e masks com as imagens do fundo, do planeta 
e dos projéteis.                                                          */

void imagensG (WINDOW *w, PIC pics[], MASK masks[]);


/* Inicializa os vetores blues, bluesM, reds e redsM com as imagens de ambas
as naves.                                                                 */
 
void imagensN (WINDOW *w, PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[]);


/* Inicializa os vetores exp e expM com as imagens de explosão.           */

void imagensEX (WINDOW *w, PIC exp[], MASK expM[]);


#endif

