/*------------------------------------------------------------------------------*/
/*------------------------------ MODULO EXTRA-----------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH */
/* PROPÓSITO: Esse modulo foi criado para lidar com os espacos extras. Nele devem
   estar os testes feitos para a verificacao de seu estado atual e o
   retorno do mesmo para outros modulos.  */

#ifndef EXTRA_H
#define EXTRA_H
#include <stdio.h>
#include "LISTA.h"
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#endif

/***********************************************************************
*
*  $FC Função: cria_sequencia_extra
*
*  $ED Descrição da função
*       Cria as listas referentes a coluna extra
*
*  $FV Valor retornado
*     LIS_tppLista contendo as listas referentes a coluna extra
*
***********************************************************************/
LIS_tppLista cria_sequencia_extra ();

/***********************************************************************
*
*  $FC Função: testa_entrada_extra
*
*  $ED Descrição da função
*       Essa função testa a entrada de um bloco, ou uma carta, em uma determinada
*       coluna do extra.
*
*  $EP Parâmetros
*     $P pLista - Corresponde a uma cabeca de lista que representa a
*               coluna onde se quer inserir as cartas com o elemento
*               corrente definido para o ultimo elemento da lista.
*       bloco - Cabeça de lista de listas que representa esses espaços
*               extras.
*
*  $FV Valor retornado
*     (1) -> Entrada permitida
*     (0) -> Entrada negada
*
***********************************************************************/
int testa_entrada_extra (LIS_tppLista pLista, LIS_tppLista bloco);

/***********************************************************************
*
*  $FC Função: testa_saida_extra
*
*  $ED Descrição da função
*       Essa função testa a saida de uma carta de uma determinada coluna
*       do extra.
*
*  $EP Parâmetros
*     $P pLista Cabeça de lista de listas que representa esses espaços
*               extras onde o elemento que se deseja retirar está
*               definido em pElemCorr.
*
*  $FV Valor retornado
*     (1) -> Saída permitida
*     (0) -> Saída negada
*
***********************************************************************/
int testa_saida_extra (LIS_tppLista pLista);

#endif
