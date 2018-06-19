/*------------------------------------------------------------------------------*/
/*----------------------- MODULO SEQUENCIA ORDENADA ----------------------------*/
/*------------------------------------------------------------------------------*/

/* AUTOR: JOÃO VICTOR GIRARD*/
/* PROPÓSITO: LOCAL FINAL DAS CARTAS*/

#include "sequencia_ordenada.h"


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
LIS_tppLista cria_sequencia_ordenada () {
  LIS_tppLista pLista, cell;
  void* p;
  int i;

#ifdef _DEBUG
  CNT_CONTAR( "FOU_CriaSequenciaOrdenada_A" ) ;
#endif

  pLista = LIS_CriarLista (LIS_ExcluirValor);

  for (i=0; i<4; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "FOU_CriaSequenciaOrdenada_B" ) ;
#endif
    cell = LIS_CriarLista (LIS_ExcluirValor);
    p = (void*) cell;
    LIS_InserirElementoApos (pLista, p);
  }

#ifdef _DEBUG
  CNT_CONTAR( "FOU_CriaSequenciaOrdenada_C" ) ;
#endif

  return pLista;
}


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
int testa_entrada_sequencia_ordenada (LIS_tppLista pLista, LIS_tppLista bloco) {
  int num, novo_num;
  char naipe[20], novo_naipe[20];
  void *p;

#ifdef _DEBUG
  CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_A" ) ;
  assert( pLista != NULL ) ;
  assert( bloco != NULL);
#endif

  IrFinalLista (pLista);
  p = LIS_ObterValor (pLista);

  if (p == NULL) {
#ifdef _DEBUG
    CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_B" ) ;
#endif
    if (numero_carta (bloco) == 1) {
#ifdef _DEBUG
      CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_C" ) ;
#endif
      return 1;
    }

#ifdef _DEBUG
    CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_D" ) ;
#endif

    return 0;
  }

#ifdef _DEBUG
  CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_E" ) ;
#endif

  num = numero_carta (pLista);
  novo_num = numero_carta (bloco);
  strcpy (naipe, naipe_carta (pLista));
  strcpy (novo_naipe, naipe_carta (bloco));

  if (novo_num == (num +1)) {
#ifdef _DEBUG
    CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_F" ) ;
#endif
    if (strcmp (naipe, novo_naipe) == 0) {
#ifdef _DEBUG
      CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_G" ) ;
#endif
      return 1;
    }

#ifdef _DEBUG
    CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_H" ) ;
#endif
  }

#ifdef _DEBUG
  CNT_CONTAR( "FOU_TestaEntradaSequenciaOrdenada_I" ) ;
#endif

  return 0;
}

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
int vitoria (LIS_tppLista pLista) {
  int i;
  LIS_tppLista sequencia_ordenada;

#ifdef _DEBUG
  CNT_CONTAR( "FOU_Vitoria_A" ) ;
  assert( pLista != NULL ) ;
#endif

  IrInicioLista (pLista);

  for (i=0; i<4; i++) {
#ifdef _DEBUG
    CNT_CONTAR( "FOU_Vitoria_B" ) ;
#endif
    sequencia_ordenada = (LIS_tppLista) LIS_ObterValor (pLista);
    IrFinalLista (sequencia_ordenada);

    if (numero_carta(sequencia_ordenada) != 13) {
#ifdef _DEBUG
      CNT_CONTAR( "FOU_Vitoria_C" ) ;
#endif
      return 0;
    }

#ifdef _DEBUG
    CNT_CONTAR( "FOU_Vitoria_D" ) ;
#endif

    LIS_AvancarElementoCorrente (pLista, 1);
  }

#ifdef _DEBUG
  CNT_CONTAR( "FOU_Vitoria_E" ) ;
#endif

  printf("Voce Venceu!\n");
  return 1;
}
