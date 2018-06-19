/*------------------------------------------------------------------------------*/
/*------------------------------ MODULO CARTAS----------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH */
/* PROPÓSITO: Esse modulo foi criado para lidar com a struct cartas. Essa
   struct deve representar as cartas referentes ao jogo FreeCell, e as
   funcoes criadas por esse modulo servem para lidar com essa struct. */

#ifndef CARTAS_H
#define CARTAS_H
#include <stdio.h>
#include "LISTA.h"
#include <string.h>
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#endif

/* Struct que representa as cartas do baralho */
typedef struct carta {
  char naipe[20];
  char cor[20];
  int numero;
} Carta;


/***********************************************************************
*
*  $FC Função: Numero_Carta
*
*  $ED Descrição da função
*     Função para pegar o numero da carta.
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que contém o elemento
*                 corrente apontando para a lista que pretende
*                 avaliar a carta.
*
*  $FV Valor retornado
*     (-1) -> Erro
*     (carta->numero) -> Número da carta lido
*
***********************************************************************/
int numero_carta (LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: naipe_carta
*
*  $ED Descrição da função
*     Função para pegar o naipe da carta
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que contém o elemento
*                 corrente apontando para a lista que pretende
*                 avaliar a carta.
*
*  $FV Valor retornado
*     (NULL) -> Erro
*     (carta->naipe) -> Naipe da carta lido
*
***********************************************************************/
char* naipe_carta (LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: cor_carta
*
*  $ED Descrição da função
*      Função para pegar a cor da carta
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que contém o elemento
*                 corrente apontando para a lista que pretende
*                 avaliar a carta.
*
*  $FV Valor retornado
*     (NULL) -> Erro
*     (carta->cor) -> Naipe da carta lido
*
***********************************************************************/
char* cor_carta (LIS_tppLista pLista);

#endif
