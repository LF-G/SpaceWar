/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
//
/////////////////////////////////////////////////////////////////////*/


#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "model.h"
#include "controller.h"


int main (int argc, char **argv) {
   float dt = 1.0/30.0;
   int gameover = 0, n = 0;
   int erro;
   parametros p;
   corpo c, *lixo;
   c.prox = NULL;    

#ifdef NOXPM
   puts("Este programa só funciona com a biblioteca Xpm!");
#else           

   WINDOW *w;
   PIC pics[3];
   MASK masks[3]; 

   PIC blues[16], reds[16];
   MASK bluesM[16], redsM[16];
   PIC exp[37];
   MASK expM[37];
      
   inicia (&p, &c);
   w = InitGraph (800, 800, "Space War");
   imagensG (w, pics, masks);
   imagensN (w, blues, reds, bluesM, redsM);
   imagensEX (w, exp, expM);
   usleep (100000);
   InitKBD (w);

   erro = system ("play bensound-epic.ogg &");
   if (erro == -1) {
      printf ("Erro!");
      exit (EXIT_FAILURE);
   }

   drawShips (w, &c, pics, masks, blues, reds, bluesM, redsM);   
   while (gameover == 0) {
      if (WCheckKBD (w))
         inputs (w, &c, &n);
      calculos (&p, &c, &gameover, &n, dt);
      drawShips (w, &c, pics, masks, blues, reds, bluesM, redsM);
      usleep(33333);
   }

   erro = system ("killall play");
   if (erro == -1) {
      printf ("Erro!");
      exit (EXIT_FAILURE);
   }
   fimdejogo (w, &c, dt, pics, masks, blues, reds, bluesM, redsM, exp, expM, gameover);   
   CloseGraph ();

   while (c.prox != NULL) {      /* libera a memória das naves e projéteis */
      lixo = c.prox;
      c.prox = lixo->prox;
      free (lixo);
   }
   

#endif
   return 0;
}

