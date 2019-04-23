/* Autores: 
// Mauricio Luiz Abreu Cardoso
// Luiz Fernando Antonelli Galati
// Adriano Tetsuaki Ogawa Santin
// 
// Data:
// 03/07/2016
//
///////////////////////////////////////////////////////////////////////*/



#ifndef _MODEL_H
#define _MODEL_H

#include <stdio.h>
#include <stdlib.h>



/* ////////// Definições de structs e tipos de dados //////////////////*/

typedef struct {
   float raio;
   float massa;
   float tempo;
} parametros;

typedef struct Corpo {
   char *nome;
   float massa;
   float posx;
   float posy;
   float velx;
   float vely;
   float hp;
   float ax;
   float ay;
   float angulo;
   int cooldown;
   struct Corpo *prox;
} corpo;



/* Recebe o endereço *p de uma variável do tipo parametros e uma lista
encadeada de corpos c, com cabeça e a princípio vazia. Inicia os valores
dos parâmetros do planeta e do jogo. Cria na lista c duas novas células
que representam naves, inicializando os valores das variáveis nelas
contidas.                                                              */

void inicia (parametros *p, corpo *c);


/* Função wrapper que chama as funções calcAceleracoes, calcVelocidades,
calcPosicoes e verificaTempoProjeteis. Também decrementa o cooldown das
duas naves, caso esses valores sejam maiores que 0.                    */

void calculos (parametros *p, corpo *c, int *gameover, int *n, float dt);


/* Recebe uma lista com cabeça c, tal que suas duas primeiras células 
representam as naves e as posteriores, os projéteis. Para cada um dos
projéteis, verifica o valor do seu tempo de vida restante: caso seja
negativo, libera a memória ocupada pelo projétil e atualiza o total de
projéteis na variável apontada por n.                                  */

void verificaTempoProjeteis (corpo *c, float dt, int *n);


/* Recebe um float dt e uma lista ligada com cabeça cuja primeira célula
é c. Calcula as novas posições e atualiza c.                           */

void calcPosicoes (corpo *c, float dt);


/* Recebe um float dt e uma lista ligada com cabeça c, tal que suas duas
primeiras células são naves e as restantes projéteis. Calcula as novas
velocidades e atualiza c.                                              */

void calcVelocidades (corpo *c, float dt);


/* Recebe o ponteiro de parametros p e uma lista ligada com cabeça c, tal
que suas duas primeiras células representam as naves e as posteriores,
os projéteis. Calcula as novas acelerações dos projéteis e atualiza c.
Deleta um projétil se ele colidir com o planeta, atualizando o valor de 
*n. Se as naves colidirem entre si, com o planeta ou com algum projétil,
atualiza a variável gameover.                                          */                 

void calcAceleracoes (parametros *p, corpo *c, int *gameover, int *n);


/* Recebe uma string arquivoentrada e uma string modo. Abre o arquivo
de nome arquivoentrada no modo descrito pela string mode e retorna um
ponteiro para o arquivo aberto.
Esta função é uma adaptação da função fopen da biblioteca padrão e foi
criada para evitar a repetição da verificação de erro (ponteiro == NULL)
ao longo das outras funções do programa.                               */            

FILE *abreArquivo (const char *arquivoentrada, const char *modo);


/* Recebe um arquivo "arquivo" que contem os dados do jogo. Insere em p,
n e tproj os valores contidos no arquivo, e aloca as naves e projéteis 
numa lista encadeada com cabeca, tal que as duas primeiras celulas são
naves e as restantes projéteis.                                        */ 

void leArquivo (FILE *arquivo, corpo *c, parametros *p, int *n, float *tproj);


/* Imprime no arquivo "arquivo" o conteudo de *p, tproj, n e de uma lista 
ligada com cabeça c tal que suas duas primeiras células são naves, e as
restantes são projéteis.                                               */

void escreveArquivo (FILE *arquivo, parametros *p, corpo *c, int n, float tproj);


#endif

