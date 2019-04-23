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

#include "controller.h"



/*///////////  Protótipos de funções  ////////////////////////////////*/

static void acelera (corpo *c);
static void antihorario (corpo *c);
static void horario (corpo *c);
static void shoot (corpo *c, corpo *nave2, int *n);



/*//////////////  Funções  ///////////////////////////////////////////*/


/* Veja a documentação no arquivo interface controller.h.             */

void inputs (WINDOW *w, corpo *c, int *n) {
   KeySym sym;
   WGetKey (w);
   sym = WLastKeySym ();
   switch (sym) {
      case XK_w:
      case XK_W:
         acelera (c->prox->prox);
         break;
      case XK_a:
      case XK_A:
         antihorario (c->prox->prox);
         break;
      case XK_d:
      case XK_D:
         horario (c->prox->prox);
         break;
      case XK_s:
      case XK_S:
         shoot (c->prox->prox, c->prox->prox, n);
         break;
      case XK_Up:
         acelera (c->prox);
         break;
      case XK_Left:
         antihorario (c->prox);
         break;
      case XK_Right:
         horario (c->prox);
         break;
      case XK_Down:
         shoot (c->prox, c->prox->prox, n);
         break;
      default:
      break;
   }
}


/* Aumenta a velocidade da nave c.                                   */

static void acelera (corpo *c) {
   float pi = 3.14159265359;
   float rad;
   rad = (2 * pi * c->angulo)/360.0;
   c->velx += 20 * cos (rad);
   c->vely -= 20 * sin (rad);
}


/* Gira nave c 22.5 graus no sentido anti-horário.                  */

static void antihorario (corpo *c) {
   c->angulo += 22.5;
   c->angulo = fmod (c->angulo, 360.0);
   if (c->angulo < 0.0) c->angulo += 360.0;
}


/* Gira a nave c 22.5 graus no sentido horário.                     */

static void horario (corpo *c) {
   c->angulo -= 22.5;
   c->angulo = fmod (c->angulo, 360.0);
   if (c->angulo < 0.0) c->angulo += 360.0;
}


/* Recebe uma nave c e uma nave nave2 tal que nave2->prox é onde será
inserido o projétil. Se *n < 10, o projétil é criado na posição à 
frente da nave que atirou e a velocidade do projétil é a velocidade da
nave mais a velocidade do tiro na direção para a qual a nave está
apontando. O cooldown da nave é levado a 15. A nave não pode atirar 
enquanto o coldown for mair que 0.                                  */

static void shoot (corpo *c, corpo *nave2, int *n) {
   if (*n >= 0 && *n <= 9 && c->cooldown == 0) {
      corpo *novo;
      float pi = 3.14159265359;
      float rad;
      rad = (2 * pi * c->angulo)/360.0;

      /* agora c possui endereco da segunda nave */
      novo = malloc (sizeof (corpo));
      novo->massa = 10.0;
      novo->velx = c->velx + (45 * cos (rad));
      novo->vely = c->vely - (45 * sin (rad));
      novo->posx = c->posx + (45 * cos (rad));
      novo->posy = c->posy - (45 * sin (rad));
      novo->hp = 10.0;

      novo->prox = nave2->prox;
      nave2->prox = novo;
      *n = *n + 1;

      c->cooldown = 15;
   }
}

