/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
//////////////////////////////////////////////////////////////////////*/



/*///////////  Interfaces de bibliotecas  ////////////////////////////*/

#include <math.h>
#include <string.h>

#include "model.h"



/*///////////  Protótipos de funções  ////////////////////////////////*/

static void deletaCorpo (corpo *c);
static void lePalavra (FILE *arquivo, char *pal);



/*///////////  Funções  //////////////////////////////////////////////*/


/* Veja a documentação no arquivo interface model.h                   */

void inicia (parametros *p, corpo *c) {
   p->raio = 6.4e6;            
   p->massa = 6.02e16;
   p->tempo = 200;
   
   c->prox = malloc (sizeof (corpo));
   c = c->prox;
   c->nome = "blue";
   c->massa = 200;
   c->posx = 700;
   c->posy = 400;
   c->velx = 0;
   c->vely = 120;
   c->hp = 1;
   c->angulo = 180;
   c->cooldown = 0;

   c->prox = malloc (sizeof (corpo));
   c = c->prox;
   c->nome = "red";
   c->massa = 200;
   c->posx = 100;
   c->posy = 400;
   c->velx = 0;
   c->vely = -120;
   c->hp = 1;
   c->angulo = 0;
   c->cooldown = 0;

   c->prox = NULL;
}


/* Veja a documentação no arquivo interface model.h.                  */

void calculos (parametros *p, corpo *c, int *gameover, int *n, float dt) {
   calcAceleracoes (p, c, gameover, n);
   calcVelocidades (c, dt);
   calcPosicoes (c, dt);
   verificaTempoProjeteis (c, dt, n);
   c = c->prox;
   if (c->cooldown > 0) c->cooldown -= 1;
   c = c->prox;
   if (c->cooldown > 0) c->cooldown -= 1;
}


/* Libera a memória ocupada por c->prox.                              */

static void deletaCorpo (corpo *c) {
   corpo *lixo;
   lixo = c->prox;
   c->prox = lixo->prox;
   free (lixo);
}


/* Veja a documentação no arquivo interface model.h.                  */

void verificaTempoProjeteis (corpo *c, float dt, int *n) {
   for (c = c->prox->prox; c->prox != NULL;) {
      c->prox->hp -= dt;
      if (c->prox->hp <= 0) {
         deletaCorpo (c);
         *n = *n - 1;
      }
      else c = c->prox;
   }
}


/* Veja a documentação no arquivo interface model.h.                  */

void calcPosicoes (corpo *c, float dt) {
   corpo *a;
   for (a = c->prox; a != NULL; a = a->prox) {          /* calcula as posicoes de naves e projeteis */    
      a->posx += a->velx * dt;
      a->posy += a->vely * dt;
      a->posx = fmod (a->posx, 800.0);
      a->posy = fmod (a->posy, 800.0);
      if (a->posx < 0.0) a->posx += 800.0;
      if (a->posy < 0.0) a->posy += 800.0;      
   }   
}


/* Veja a documentação no arquivo interface model.h.                  */

void calcVelocidades (corpo *c, float dt) {
   corpo *a;
   for (a = c->prox; a != NULL; a = a->prox) {
      a->velx += a->ax * dt;
      a->vely += a->ay * dt;  
      a->ax = 0;
      a->ay = 0;
   }   
}


/* Veja a documentação no arquivo interface model.h.                  */

void calcAceleracoes (parametros *p, corpo *c, int *gameover, int *n) {
   float d, dx, dy, G = 6.67e-11;
   corpo *a, *b;

   
   for (a = c->prox; a->prox != NULL; a = a->prox) {                         /* aceleracoes trocadas entre projeteis e naves */
      for (b = a->prox; b != NULL; b = b->prox) {
         dx = a->posx - b->posx;
         dy = a->posy - b->posy;
         d = sqrt (dx * dx + dy * dy);

         if (a == c->prox && b == c->prox->prox && d < 40.0) {               /* colisao entre naves */
            *gameover = 3;
            return;
         }
         else if (a == c->prox && b != c->prox->prox && d < 27.0) {          /* colisao entre a primeira nave e projetil */
            *gameover = 1;
            return;
         }
         else if (a == c->prox->prox && d < 27.0) {                          /* colisao entre a segunda nave e projetil */
            *gameover = 2;
            return;
         }

         d = d * d * d;
         a->ax += G * -dx * b->massa / d;
         a->ay += G * -dy * b->massa / d;         
         
         b->ax += G * dx * a->massa / d;
         b->ay += G * dy * a->massa / d;
      }
   }

   for (a = c; a->prox != NULL;) {                                          /* aceleracoes exercidas pelo sol nos projeteis e naves */
      dx = 400.0 - a->prox->posx;
      dy = 400.0 - a->prox->posy;
      d = sqrt (dx * dx + dy * dy);

      if (a->prox == c->prox && d < 95) {                                   /* colisao entre a primeira nave e planeta */
         *gameover = 1;
         return;
      }
      else if (a->prox == c->prox->prox && d < 95) {                        /* colisao entre a segunda nave e planeta */
         *gameover = 2;
         return; 
      }
      else if (d < 75) {                                                    /* colisao entre projetil e planeta */
         deletaCorpo (a);
         *n = *n - 1;
      }
      else {
         d = d * d * d;
         a->prox->ax += G * dx * p->massa / d;
         a->prox->ay += G * dy * p->massa / d;
         a = a->prox;
      }
   }
}


/* Veja a documentação no arquivo interface model.h.                  */                   

FILE *abreArquivo (const char *arquivoentrada, const char *modo) {
   FILE *arquivotexto;
   arquivotexto = fopen (arquivoentrada, modo);
   if (arquivotexto == NULL) {
      printf ("Falha ao abrir o arquivo.\n");
      exit (EXIT_FAILURE);
   }
   return arquivotexto;
}


/* Veja a documentação no arquivo interface model.h.                  */

void leArquivo (FILE *arquivo, corpo *c, parametros *p, int *n, float *tproj) {
   int i, j;
   char *pal = malloc (30 * sizeof (char));      

   for (i = 0; i <= 2; i++) {                                      /* recebe os parametros do planeta e tempo */
      lePalavra (arquivo, pal);
      if (i == 0) p->raio = atof (pal);            
      else if (i == 1) p->massa = atof (pal);
      else  p->tempo = atof (pal);      
   }

   for (i = 1, j = 0; j <= 1; i++) {                               /* recebe os parametros das naves */
      lePalavra (arquivo, pal);
      
      if (i == 1) {
         c->prox = malloc (sizeof (corpo));
         c = c->prox;
         c->nome = malloc ((strlen (pal) + 1) * sizeof (char));
         strcpy (c->nome, pal);         
      }
      else if (i == 2) c->massa = atof (pal);
      else if (i == 3) c->posx = atof (pal);
      else if (i == 4) c->posy = atof (pal);
      else if (i == 5) c->velx = atof (pal);
      else {
         c->vely = atof (pal);
         c->hp = 1.0;
         i = 0;
         j++;         
      }      
   }
   /* c possui o endereco da segunda nave */

   lePalavra (arquivo, pal);                                       /* recebe o total de projeteis */
   *n = atoi (pal);  
   lePalavra (arquivo, pal);                                       /* recebe o tempo dos projeteis */
   *tproj = atof (pal);

   for (i = 1, j = 2; i <= 5 && j < *n + 2; i++) {                 /* recebe os parametros dos projeteis */
      lePalavra (arquivo, pal);
      
      if (i == 1) { 
         c->prox = malloc (sizeof (corpo));
         c = c->prox;
         c->massa = atof (pal);
      }
      else if (i == 2) c->posx = atof (pal);
      else if (i == 3) c->posy = atof (pal);
      else if (i == 4) c->velx = atof (pal);
      else {
         c->vely = atof (pal);
         c->hp = *tproj;
         i = 0;
         j++;         
      }
   }  

   c->prox = NULL;
   free (pal);
}


/* Recebe um arquivo "arquivo" e a string pal. Aloca em pal uma string
de caracteres (que não podem ser de controle) provenientes do arquivo. */

static void lePalavra (FILE *arquivo, char *pal) {
   int c = 0, i = 0;
   do {
      c = getc (arquivo);
      pal[i++] = c;
   } while (!(c >= 0 && c <= 32));
   pal[i - 1] = '\0';
}


/* Veja a documentação no arquivo interface model.h.                   */                

void escreveArquivo (FILE *arquivo, parametros *p, corpo *c, int n, float tproj) {
   int i = 0;
   c = c->prox;
   fprintf (arquivo, "%.3f ", p->raio);                                     /* imprime os parametros de entrada */
   fprintf (arquivo, "%.3f ", p->massa);
   fprintf (arquivo, "%.3f\n", p->tempo);

   for (i = 0; i <= 1; i++, c = c->prox) {                                  /*  imprime os dados das naves  */
      fprintf (arquivo, "%s ", c->nome);
      fprintf (arquivo, "%.3f ", c->massa);
      fprintf (arquivo, "%.3f ", c->posx);
      fprintf (arquivo, "%.3f ", c->posy);
      fprintf (arquivo, "%.3f ", c->velx);
      fprintf (arquivo, "%.3f\n", c->vely);      
   }
   if (c != NULL) {                                                         /* verifica se ha projeteis */
      fprintf (arquivo, "%d ", n);
      fprintf (arquivo, "%.3f\n", tproj);
 
      for (; c != NULL; c = c->prox) {                                      /*  imprime os dados dos projeteis  */
         fprintf (arquivo, "%.3f ", c->massa);
         fprintf (arquivo, "%.3f ", c->posx);
         fprintf (arquivo, "%.3f ", c->posy);
         fprintf (arquivo, "%.3f ", c->velx);
         fprintf (arquivo, "%.3f\n", c->vely);
      }
      fprintf (arquivo, "\n");
   }
}

