/*------------------------------------------------------------------------------*/
/*--------------------- MODULO SEQUENCIA ORDENADA ------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH */
/* PROPÓSITO: Esse modulo foi criado para lidar com a area das cartas ordenadas. Esse
   modulo deve prover os testes feitos nessa área para a verificação de seu
   estado atual e o retorno do mesmo para outros módulos. */

#ifndef SEQUENCIA_ORDENADA_H
#define SEQUENCIA_ORDENADA_H
#include <stdio.h>
#include <string.h>
#include "cartas.h"
#include "LISTA.h"
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#endif

/***********************************************************************
*
*  $FC Função: cria_sequencia_ordenada
*
*  $ED Descrição da função
*       Cria as listas referentes a sequencia ordenada
*
*  $FV Valor retornado
*     LIS_tppLista contendo as listas referentes a sequencia ordenada
*
***********************************************************************/
LIS_tppLista cria_sequencia_ordenada ();

/***********************************************************************
*
*  $FC Função: testa_entrada_sequencia_ordenada
*
*  $ED Descrição da função
*       Testa se a entrada no sequencia_ordenada é válida.
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que representa o sequencia ordenada.
*       bloco - Corresponde a uma cabeca de lista que representa a
*               coluna onde se quer inserir as cartas com o elemento
*               corrente definido para o ultimo elemento da lista.

*
*  $FV Valor retornado
*     (1) -> Entrada permitida
*     (0) -> Entrada negada
*
***********************************************************************/
int testa_entrada_sequencia_ordenada (LIS_tppLista pLista, LIS_tppLista bloco);

/***********************************************************************
*
*  $FC Função: vitoria
*
*  $ED Descrição da função
*       Testa se o jogo acabou, e se você foi vitorioso.
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que representa o sequencia ordenada.
*
*  $FV Valor retornado
*     (1) -> Vitória!
*     (0) -> Não ganhou
*
***********************************************************************/
int vitoria (LIS_tppLista pLista);

#endif
