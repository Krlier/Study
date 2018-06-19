/*------------------------------------------------------------------------------*/
/*------------------------------ MODULO EMBARALHAMENTO--------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH */
/* PROPÓSITO: Esse modulo serve para embaralhar as cartas do jogo antes do
   mesmo ser iniciado */

#ifndef EMBARALHAMENTO_H
#define EMBARALHAMENTO_H
#include <stdio.h>
#include <stdlib.h>
#include "LISTA.h"
#include "cartas.h"
#include <time.h>
#include <string.h>
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $FC Função: embaralhar
*
*  $ED Descrição da função
*       Essa função embaralha as cartas e devolve uma seed que representa
*       esse embaralhamento específico.
*
*  $EP Parâmetros
*     $P pLista - Cabeça de lista de listas que contém o elemento
*                 corrente apontando para a lista que pretende
*                 avaliar a carta.
*
*         seed - Corresponde a um número único para cada jogo criado diferente.
*
*
*  $FV Valor retornado
*     (seed) -> Saída da seed do jogo
*     (0) -> Falha no embaralhamento
*
***********************************************************************/
unsigned int embaralhar (LIS_tppLista pLista, unsigned int seed);

#endif
