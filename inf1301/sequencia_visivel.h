/*------------------------------------------------------------------------------*/
/*------------------- MODULO SEQUENCIA VISIVEL ---------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: DANIEL CARLIER */
/* PROPÓSITO: Esse modulo foi criado para lidar com as colunas de cartas desordenadas.
   Esse modulo deve prover os testes feitos nessa área para a verificação de
   seu estado atual e o retorno do mesmo para outros módulos. */


#ifndef SEQUENCIA_VISIVEL_H
#define SEQUENCIA_VISIVEL_H
#include "cartas.h"
#include "LISTA.h"
#include <string.h>
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#endif

/***********************************************************************
*
*  $FC Função: cria_sequencia_visivel
*
*  $ED Descrição da função
*       Cria as listas referentes a sequencia visivel
*
*  $FV Valor retornado
*     LIS_tppLista contendo as listas referentes a sequencia visivel
*
***********************************************************************/
LIS_tppLista cria_sequencia_visivel ();

/***********************************************************************
*
*  $FC Função: testa_entrada_sequencia_visivel
*
*  $ED Descrição da função
*       Testa se a entrada no sequencia visivel é válida
*
*  $EP Parâmetros
*     $P pLista - Corresponde a uma cabeca de lista que representa a
*                 coluna onde se quer inserir as cartas com o elemento
*                 corrente definido para o ultimo elemento da lista.
*
*         bloco - Cabeça de lista de listas que representa o possivel
*                 comeco de um bloco de cartas a ser inserido.
*
*  $FV Valor retornado
*     (1) -> Entrada permitida
*     (0) -> Entrada negada
*
***********************************************************************/
int testa_entrada_sequencia_visivel (LIS_tppLista pLista, LIS_tppLista bloco);

/***********************************************************************
*
*  $FC Função: testa_saida_sequencia_visivel
*
*  $ED Descrição da função
*       Testa se a retirada de uma carta, ou um bloco de cartas, é possível
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que contém a coluna
*                 onde se quer retirar as cartas com o elemento
*                 corrente definido para o possivel inicio de um bloco.
*
*
*  $FV Valor retornado
*     (1) -> Saída permitida
*     (0) -> Falha na saída
*
***********************************************************************/
int testa_saida_sequencia_visivel (LIS_tppLista pLista);

#endif
