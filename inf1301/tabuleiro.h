/*------------------------------------------------------------------------------*/
/*------------------------------ MODULO TABULEIRO-------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH */
/* PROPÓSITO: Esse modulo serve para criar o tabuleiro, o baralho e lidar
   com as acoes que precisam ser executadas sobre o mesmo */

#ifndef TABULEIRO_H
#define TABULEIRO_H
#include <stdio.h>
#include <stdlib.h>
#include "LISTA.h"
#include "cartas.h"
#include "sequencia_visivel.h"
#include "extra.h"
#include "sequencia_ordenada.h"
#include <assert.h>
#ifdef _DEBUG
#include "Conta.h"
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $FC Função: cria_baralho
*
*  $ED Descrição da função
*       Essa função inicializa o baralho.
*
*  $FV Valor retornado
*     (pLista) -> Retorna o baralho criado.
*     (NULL) ->  Erro na criação do baralho.
*
***********************************************************************/
LIS_tppLista cria_baralho ();

/***********************************************************************
*
*  $FC Função: cria_tabuleiro
*
*  $ED Descrição da função
*       Essa função inicializa o tabuleiro.
*
*  $FV Valor retornado
*     (pLista) -> Retorna o tabuleiro criado.
*
***********************************************************************/
LIS_tppLista cria_tabuleiro (LIS_tppLista seq_ordenada,
                             LIS_tppLista seq_visivel, LIS_tppLista extra);

/***********************************************************************
*
*  $FC Função: arruma_tabuleiro
*
*  $ED Descrição da função
*       Essa função arruma as cartas no tabuleiro e deleta a lísta que
*       referencia o baralho.
*
*  $EP Parâmetros
*     $P tabuleiro - Corresponde a uma cabeca de lista que representa
*                    o tabuleiro.
*       baralho - Cabeça de lista de listas que representa o baralho.
*
*  $FV Valor retornado
*     (1) -> Tabuleiro arrumado.
*
***********************************************************************/
int arruma_tabuleiro (LIS_tppLista pLista, LIS_tppLista baralho);

/***********************************************************************
*
*  $FC Função: conta_espacos_vazios
*
*  $ED Descrição da função
*       Essa funcao determina quantas cartas podem ser movimentadas
*       de uma so vez baseado no numero de espacos vazios do tabuleiro,
*       a conta segue com base nessa equacao (Extra+1)*2*Cascade.
*
*  $EP Parâmetros
*     $P pLista - Corresponde a uma cabeca de lista que representa
*                    o tabuleiro.
*
*  $FV Valor retornado
*     Numero de cartas que podem ser movidas.
*
***********************************************************************/
int conta_espacos_vazios (LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: move_cartas
*
*  $ED Descrição da função
*       Essa funcao movimenta as cartas do tabuleiro.
*
*  $EP Parâmetros
*     $P tabuleiro - Corresponde a uma cabeca de lista que representa
*                    o tabuleiro.
*        s - Corresponde a coluna na qual as cartas serão retiradas.
*        e - Corresponde a coluna na qual as cartas serão inseridas.
*
*  $FV Valor retornado
*     (1) -> Cartas movidas com sucesso.
*     (0) -> Erro ao mover cartas.
*
***********************************************************************/
int move_cartas (LIS_tppLista pLista, int s, int e);

#endif
