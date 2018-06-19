/*------------------------------------------------------------------------------*/
/*-------------------------------- MODULO EXTRA---------------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JORGE PUMAR DODSWORTH*/
/* PROPÓSITO: GERENCIAR AS CÉLULAS EXTRAS*/

#include "extra.h"

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
LIS_tppLista cria_sequencia_extra () {
  LIS_tppLista pLista, cell;
  void* p;
  int i;

#ifdef _DEBUG
  CNT_CONTAR( "EXT_CriaSequenciaExtra_A" ) ;
#endif

  pLista = LIS_CriarLista (LIS_ExcluirValor);

  for (i=0; i<4; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "EXT_CriaSequenciaExtra_B" ) ;
#endif
    cell = LIS_CriarLista (LIS_ExcluirValor);
    p = (void*) cell;
    LIS_InserirElementoApos (pLista, p);
  }

#ifdef _DEBUG
  CNT_CONTAR( "EXT_CriaSequenciaExtra_C" ) ;
#endif

  return pLista;
}


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
 *       bloco - Cabeça de lista de listas que representa os espaços
 *               extras.
 *
 *  $FV Valor retornado
 *     (1) -> Entrada permitida
 *     (0) -> Entrada negada
 *
 ***********************************************************************/
int testa_entrada_extra (LIS_tppLista pLista, LIS_tppLista bloco) {
  LIS_tpCondRet ret;
  void* p;

#ifdef _DEBUG
  CNT_CONTAR( "EXT_TestaEntradaExtra_A" ) ;
  assert( pLista != NULL ) ;
  assert( bloco != NULL);
#endif

  p = LIS_ObterValor (bloco);
  IrFinalLista (bloco);

  if ((p == NULL) || (p != LIS_ObterValor (bloco))) {
#ifdef _DEBUG
    CNT_CONTAR( "EXT_TestaEntradaExtra_B" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "EXT_TestaEntradaExtra_C" ) ;
#endif

  ret = LIS_AvancarElementoCorrente (pLista, 0);
  if (ret != LIS_CondRetOK) {
#ifdef _DEBUG
    CNT_CONTAR( "EXT_TestaEntradaExtra_D" ) ;
#endif
    return 1;
  }

#ifdef _DEBUG
  CNT_CONTAR( "EXT_TestaEntradaExtra_E" ) ;
#endif

  return 0;
}

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
int testa_saida_extra (LIS_tppLista pLista) {

#ifdef _DEBUG
  CNT_CONTAR( "EXT_TestaSaidaExtra_A" ) ;
  assert( pLista != NULL ) ;
#endif

  if (LIS_ObterValor(pLista) == NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "EXT_TestaSaidaExtra_B" ) ;
#endif
    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "EXT_TestaSaidaExtra_C" ) ;
#endif

  return 1;
}
