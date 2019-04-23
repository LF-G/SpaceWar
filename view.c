/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
/////////////////////////////////////////////////////////////////////*/



/*///////////  Interfaces de bibliotecas  ///////////////////////////*/

#include "view.h"



/*//////////////  Funções  //////////////////////////////////////////*/


/* Veja a documentação no arquivo interface view.h.                  */

void drawShips (WINDOW *w, corpo *c, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[]) {
   int ang;
   WClear (w);  

   SetMask (w, masks[0]);
   PutPic (w, pics[0], 0, 0, 800, 800, 0, 0);

   SetMask (w, masks[1]);
   PutPic (w, pics[1], 0, 0, 150, 150, 325, 325);

   c = c->prox; /* c possui o endereco da primeira nave */
   ang = (int) (c->angulo / 22.5);
   SetMask (w, bluesM[ang]);
   PutPic (w, blues[ang], 0, 0, 50, 50, c->posx-25, c->posy-25);
   
   c = c->prox;
   ang = (int) (c->angulo / 22.5);
   SetMask (w, redsM[ang]);
   PutPic (w, reds[ang], 0, 0, 50, 50, c->posx-25, c->posy-25);  

   SetMask (w, masks[2]);
   for (c = c->prox; c != NULL; c = c->prox) {
      PutPic (w, pics[2], 0, 0, 12, 12, c->posx-6, c->posy-6);
   }
}

/* Veja a documentação no arquivo interface view.h.                  */

void drawShipsEnd (WINDOW *w, corpo *c, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[], PIC exp[], MASK expM[], int gameover, int i) {
   int ang;
   WClear (w);  

   SetMask (w, masks[0]);
   PutPic (w, pics[0], 0, 0, 800, 800, 0, 0);

   SetMask (w, masks[1]);
   PutPic (w, pics[1], 0, 0, 150, 150, 325, 325);

   c = c->prox; /* c possui o endereco da primeira nave */
   if (gameover != 1 && gameover != 3) {
      ang = (int) (c->angulo / 22.5);
      SetMask (w, bluesM[ang]);
      PutPic (w, blues[ang], 0, 0, 50, 50, c->posx-25, c->posy-25);
   }
   else {
      SetMask (w, expM[i]);
      PutPic (w, exp[i], 0, 0, 50, 50, c->posx-25, c->posy-25);
   }
   c = c->prox;
   if (gameover != 2 && gameover != 3) {
      ang = (int) (c->angulo / 22.5);
      SetMask (w, redsM[ang]);
      PutPic (w, reds[ang], 0, 0, 50, 50, c->posx-25, c->posy-25);  
   }
   else {
      SetMask (w, expM[i]);
      PutPic (w, exp[i], 0, 0, 50, 50, c->posx-25, c->posy-25); 
   }
   SetMask (w, masks[2]);
   for (c = c->prox; c != NULL; c = c->prox) {
      PutPic (w, pics[2], 0, 0, 12, 12, c->posx-6, c->posy-6);
   }
}


/* Veja a documentação no arquivo interface view.h.                  */

void fimdejogo (WINDOW *w, corpo *c, float dt, PIC pics[], MASK masks[], PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[], PIC exp[], MASK expM[], int gameover) {
   PIC end;
   MASK endM;
   int i;
   if (gameover == 1) {
      for (i = 0; i <= 10; i++) {
         calcPosicoes (c, dt);
         drawShips (w, c, pics, masks, blues, reds, bluesM, redsM);
         SetMask (w, expM[i]);
         PutPic (w, exp[i], 0, 0, 50, 50, c->prox->posx-25, c->prox->posy-25);
         usleep(33333);
      }
      for (i = 11; i <= 36; i++) {
         calcPosicoes (c, dt);
         drawShipsEnd (w, c, pics, masks, blues, reds, bluesM, redsM, exp, expM, gameover, i);
         usleep(33333);
      }
      end = ReadPic (w, "images/gameover1.xpm", endM=NewMask(w, 800, 800));
      SetMask (w, endM);
      PutPic (w, end, 0, 0, 800, 800, 0, 0);
   }
   else if (gameover == 2) {
      for (i = 0; i <= 10; i++) {
         calcPosicoes (c, dt);
         drawShips (w, c, pics, masks, blues, reds, bluesM, redsM);
         SetMask (w, expM[i]);         
         PutPic (w, exp[i], 0, 0, 50, 50, c->prox->prox->posx-25, c->prox->prox->posy-25);
         usleep(33333);
      }
      for (i = 11; i <= 36; i++) {
         calcPosicoes (c, dt);
         drawShipsEnd (w, c, pics, masks, blues, reds, bluesM, redsM, exp, expM, gameover, i);
         usleep(33333);
      }
      end = ReadPic (w, "images/gameover2.xpm", endM=NewMask(w, 800, 800));
      SetMask (w, endM);
      PutPic (w, end, 0, 0, 800, 800, 0, 0);
   }
   else {
      for (i = 0; i <= 10; i++) {
         calcPosicoes (c, dt);
         drawShips (w, c, pics, masks, blues, reds, bluesM, redsM);
         SetMask (w, expM[i]);
         PutPic (w, exp[i], 0, 0, 50, 50, c->prox->posx-25, c->prox->posy-25);
         PutPic (w, exp[i], 0, 0, 50, 50, c->prox->prox->posx-25, c->prox->prox->posy-25);
         usleep(33333);
      }
      for (i = 11; i <= 36; i++) {
         calcPosicoes (c, dt);
         drawShipsEnd (w, c, pics, masks, blues, reds, bluesM, redsM, exp, expM, gameover, i);
         usleep(33333);
      }
      end = ReadPic (w, "images/gameover3.xpm", endM=NewMask(w, 800, 800));
      SetMask (w, endM);
      PutPic (w, end, 0, 0, 800, 800, 0, 0);
   }

   usleep(2000000);
   while (1) {
      if (WCheckKBD (w))
         break;
   }
}


/* Veja a documentação no arquivo interface view.h.                  */

void imagensG (WINDOW *w, PIC pics[], MASK masks[]) {
   pics[0] = ReadPic (w, "images/Fundo.xpm", masks[0]=NewMask(w, 150, 150));
   pics[1] = ReadPic (w, "images/Earth150.xpm", masks[1]=NewMask(w, 150, 150));
   pics[2] = ReadPic (w, "images/shot.xpm", masks[2]=NewMask(w, 12, 12));
}


/* Veja a documentação no arquivo interface view.h.                  */

void imagensN (WINDOW *w, PIC blues[], PIC reds[], MASK bluesM[], MASK redsM[]) {
   reds[0] = ReadPic (w, "images/redship00.xpm", redsM[0]=NewMask(w, 50, 50));
   reds[1] = ReadPic (w, "images/redship01.xpm", redsM[1]=NewMask(w, 50, 50));
   reds[2] = ReadPic (w, "images/redship02.xpm", redsM[2]=NewMask(w, 50, 50));
   reds[3] = ReadPic (w, "images/redship03.xpm", redsM[3]=NewMask(w, 50, 50));
   reds[4] = ReadPic (w, "images/redship04.xpm", redsM[4]=NewMask(w, 50, 50));
   reds[5] = ReadPic (w, "images/redship05.xpm", redsM[5]=NewMask(w, 50, 50));
   reds[6] = ReadPic (w, "images/redship06.xpm", redsM[6]=NewMask(w, 50, 50));
   reds[7] = ReadPic (w, "images/redship07.xpm", redsM[7]=NewMask(w, 50, 50));
   reds[8] = ReadPic (w, "images/redship08.xpm", redsM[8]=NewMask(w, 50, 50));
   reds[9] = ReadPic (w, "images/redship09.xpm", redsM[9]=NewMask(w, 50, 50));
   reds[10] = ReadPic (w, "images/redship10.xpm", redsM[10]=NewMask(w, 50, 50));
   reds[11] = ReadPic (w, "images/redship11.xpm", redsM[11]=NewMask(w, 50, 50));
   reds[12] = ReadPic (w, "images/redship12.xpm", redsM[12]=NewMask(w, 50, 50));
   reds[13] = ReadPic (w, "images/redship13.xpm", redsM[13]=NewMask(w, 50, 50));
   reds[14] = ReadPic (w, "images/redship14.xpm", redsM[14]=NewMask(w, 50, 50));
   reds[15] = ReadPic (w, "images/redship15.xpm", redsM[15]=NewMask(w, 50, 50));

   blues[0] = ReadPic (w, "images/blueship00.xpm", bluesM[0]=NewMask(w, 50, 50));
   blues[1] = ReadPic (w, "images/blueship01.xpm", bluesM[1]=NewMask(w, 50, 50));
   blues[2] = ReadPic (w, "images/blueship02.xpm", bluesM[2]=NewMask(w, 50, 50));
   blues[3] = ReadPic (w, "images/blueship03.xpm", bluesM[3]=NewMask(w, 50, 50));
   blues[4] = ReadPic (w, "images/blueship04.xpm", bluesM[4]=NewMask(w, 50, 50));
   blues[5] = ReadPic (w, "images/blueship05.xpm", bluesM[5]=NewMask(w, 50, 50));
   blues[6] = ReadPic (w, "images/blueship06.xpm", bluesM[6]=NewMask(w, 50, 50));
   blues[7] = ReadPic (w, "images/blueship07.xpm", bluesM[7]=NewMask(w, 50, 50));
   blues[8] = ReadPic (w, "images/blueship08.xpm", bluesM[8]=NewMask(w, 50, 50));
   blues[9] = ReadPic (w, "images/blueship09.xpm", bluesM[9]=NewMask(w, 50, 50));
   blues[10] = ReadPic (w, "images/blueship10.xpm", bluesM[10]=NewMask(w, 50, 50));
   blues[11] = ReadPic (w, "images/blueship11.xpm", bluesM[11]=NewMask(w, 50, 50));
   blues[12] = ReadPic (w, "images/blueship12.xpm", bluesM[12]=NewMask(w, 50, 50));
   blues[13] = ReadPic (w, "images/blueship13.xpm", bluesM[13]=NewMask(w, 50, 50));
   blues[14] = ReadPic (w, "images/blueship14.xpm", bluesM[14]=NewMask(w, 50, 50));
   blues[15] = ReadPic (w, "images/blueship15.xpm", bluesM[15]=NewMask(w, 50, 50));
}


/* Veja a documentação no arquivo interface view.h.                  */

void imagensEX (WINDOW *w, PIC exp[], MASK expM[]) {
   exp[0] = ReadPic (w, "images/explosion/exp00.xpm", expM[0]=NewMask(w, 50, 50));
   exp[1] = ReadPic (w, "images/explosion/exp01.xpm", expM[1]=NewMask(w, 50, 50));
   exp[2] = ReadPic (w, "images/explosion/exp02.xpm", expM[2]=NewMask(w, 50, 50));
   exp[3] = ReadPic (w, "images/explosion/exp03.xpm", expM[3]=NewMask(w, 50, 50));
   exp[4] = ReadPic (w, "images/explosion/exp04.xpm", expM[4]=NewMask(w, 50, 50));
   exp[5] = ReadPic (w, "images/explosion/exp05.xpm", expM[5]=NewMask(w, 50, 50));
   exp[6] = ReadPic (w, "images/explosion/exp06.xpm", expM[6]=NewMask(w, 50, 50));
   exp[7] = ReadPic (w, "images/explosion/exp07.xpm", expM[7]=NewMask(w, 50, 50));
   exp[8] = ReadPic (w, "images/explosion/exp08.xpm", expM[8]=NewMask(w, 50, 50));
   exp[9] = ReadPic (w, "images/explosion/exp09.xpm", expM[9]=NewMask(w, 50, 50));
   exp[10] = ReadPic (w, "images/explosion/exp10.xpm", expM[10]=NewMask(w, 50, 50));
   exp[11] = ReadPic (w, "images/explosion/exp11.xpm", expM[11]=NewMask(w, 50, 50));
   exp[12] = ReadPic (w, "images/explosion/exp12.xpm", expM[12]=NewMask(w, 50, 50));
   exp[13] = ReadPic (w, "images/explosion/exp13.xpm", expM[13]=NewMask(w, 50, 50));
   exp[14] = ReadPic (w, "images/explosion/exp14.xpm", expM[14]=NewMask(w, 50, 50));
   exp[15] = ReadPic (w, "images/explosion/exp15.xpm", expM[15]=NewMask(w, 50, 50));
   exp[16] = ReadPic (w, "images/explosion/exp16.xpm", expM[16]=NewMask(w, 50, 50));
   exp[17] = ReadPic (w, "images/explosion/exp17.xpm", expM[17]=NewMask(w, 50, 50));
   exp[18] = ReadPic (w, "images/explosion/exp18.xpm", expM[18]=NewMask(w, 50, 50));
   exp[19] = ReadPic (w, "images/explosion/exp19.xpm", expM[19]=NewMask(w, 50, 50));
   exp[20] = ReadPic (w, "images/explosion/exp20.xpm", expM[20]=NewMask(w, 50, 50));
   exp[21] = ReadPic (w, "images/explosion/exp21.xpm", expM[21]=NewMask(w, 50, 50));
   exp[22] = ReadPic (w, "images/explosion/exp22.xpm", expM[22]=NewMask(w, 50, 50));
   exp[23] = ReadPic (w, "images/explosion/exp23.xpm", expM[23]=NewMask(w, 50, 50));
   exp[24] = ReadPic (w, "images/explosion/exp24.xpm", expM[24]=NewMask(w, 50, 50));
   exp[25] = ReadPic (w, "images/explosion/exp25.xpm", expM[25]=NewMask(w, 50, 50));
   exp[26] = ReadPic (w, "images/explosion/exp26.xpm", expM[26]=NewMask(w, 50, 50));
   exp[27] = ReadPic (w, "images/explosion/exp27.xpm", expM[27]=NewMask(w, 50, 50));
   exp[28] = ReadPic (w, "images/explosion/exp28.xpm", expM[28]=NewMask(w, 50, 50));
   exp[29] = ReadPic (w, "images/explosion/exp29.xpm", expM[29]=NewMask(w, 50, 50));
   exp[30] = ReadPic (w, "images/explosion/exp30.xpm", expM[30]=NewMask(w, 50, 50));
   exp[31] = ReadPic (w, "images/explosion/exp31.xpm", expM[31]=NewMask(w, 50, 50));
   exp[32] = ReadPic (w, "images/explosion/exp32.xpm", expM[32]=NewMask(w, 50, 50));
   exp[33] = ReadPic (w, "images/explosion/exp33.xpm", expM[33]=NewMask(w, 50, 50));
   exp[34] = ReadPic (w, "images/explosion/exp34.xpm", expM[34]=NewMask(w, 50, 50));
   exp[35] = ReadPic (w, "images/explosion/exp35.xpm", expM[35]=NewMask(w, 50, 50));
   exp[36] = ReadPic (w, "images/explosion/exp36.xpm", expM[36]=NewMask(w, 50, 50));
}

