/*------------------------------------------------------------------------------*/
/*--------------------------------- MODULO CARTAS ------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH*/
/* PROPÓSITO: MÓDULO RESPONSÁVEL PELA ESTRUTURA BÁSICA DO TIPO CARTAS */

#include "cartas.h"

/* Struct que representa as cartas do baralho */
typedef struct carta Carta;

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
int numero_carta (LIS_tppLista pLista) {
  Carta* carta;
  void* p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_NumeroCarta_A" ) ;
  assert( pLista != NULL ) ;
#endif

  p = LIS_ObterValor (pLista);

  if (p == NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "CAR_NumeroCarta_B" ) ;
#endif
    return -1;
  }

  carta = (Carta*) p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_NumeroCarta_C" ) ;
#endif

  return carta->numero;
}

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
char* naipe_carta (LIS_tppLista pLista) {
  Carta* carta;
  void* p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_NaipeCarta_A" ) ;
  assert( pLista != NULL ) ;
#endif

  p = LIS_ObterValor (pLista);

  if (p == NULL) {
#ifdef _DEBUG
  CNT_CONTAR( "CAR_NaipeCarta_B" ) ;
#endif
    return NULL;
}

  carta = (Carta*) p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_NaipeCarta_C" ) ;
#endif

  return carta->naipe;
}

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

char* cor_carta (LIS_tppLista pLista) {
  Carta* carta;
  void* p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_CorCarta_A" ) ;
  assert( pLista != NULL ) ;
#endif

  p = LIS_ObterValor (pLista);

  if (p == NULL) {
#ifdef _DEBUG
  CNT_CONTAR( "CAR_CorCarta_B" ) ;
#endif
    return NULL;
  }

  carta = (Carta*) p;

#ifdef _DEBUG
  CNT_CONTAR( "CAR_CorCarta_C" ) ;
#endif

  return carta->cor;
}
