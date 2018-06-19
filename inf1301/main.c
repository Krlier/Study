/* Autor: Daniel Carlier */

#include "main.h"

int main (void) {
  int comando, retira_coluna, insere_coluna, numero, i;
  int num_carta, vit, sc;
  unsigned int seed = 0;
  char nai_carta[20];
  LIS_tppLista tabuleiro, coluna, insere;
  LIS_tpCondRet teste;
  void* p = NULL;

  printf ("Voce deseja comecar um novo jogo? \n");
  printf ("Aperte 1 comecar jogo \n");
  scanf ("%d", &comando);

  if (comando != 1)
    goto end;

  printf ("Se em algum momento voce desejar parar de jogar, aperte 0 para sair \n");
  tabuleiro = cria_tabuleiro (cria_sequencia_ordenada (),
                              cria_sequencia_visivel (),
                              cria_sequencia_extra ());

  if (tabuleiro == NULL)
    exit (1);

  coluna = cria_baralho ();

  printf ("Insira uma seed, aperte 0 caso voce nao queira escolher nenhuma \n");
  scanf ("%u", &seed);
  embaralhar (coluna, seed);

  if (arruma_tabuleiro (tabuleiro, coluna) != 1)
    exit (1);

  while (comando > 0) {
  start:

    IrInicioLista (tabuleiro);

    printf ("\n");
    for (i=1; i<=16; i++) {
      coluna = (LIS_tppLista) LIS_ObterValor (tabuleiro);
      IrInicioLista (coluna);
      teste = LIS_AvancarElementoCorrente (coluna, 0);

      if (i<5)
        printf ("Sequencia Ordenada %d: ", i);
      else if (i<9)
        printf ("Extra %d:\t ", i);
      else
        printf ("Sequencia Visivel %d: ", i);

      while (teste == LIS_CondRetOK) {
        num_carta = numero_carta (coluna);
        strcpy (nai_carta, naipe_carta (coluna));
        printf ("%d %s  ", num_carta, nai_carta);

        teste = LIS_AvancarElementoCorrente (coluna, 1);
      }

      LIS_AvancarElementoCorrente (tabuleiro, 1);
      printf ("\n");
    }
    printf ("\n");


    IrInicioLista (tabuleiro);
    coluna = (LIS_tppLista) LIS_ObterValor (tabuleiro);
    IrInicioLista (coluna);

    while (LIS_AvancarElementoCorrente (tabuleiro, 1) == LIS_CondRetOK) {
      coluna = (LIS_tppLista) LIS_ObterValor (tabuleiro);
      IrInicioLista (coluna);
    }

    printf ("Aperte o numero da coluna de onde voce quer retirar uma ou mais cartas \n");
    while ((sc = scanf (" %d", &retira_coluna)) != 1 && sc != EOF)
      getc (stdin);

    if ((retira_coluna < 0) || (retira_coluna > 16)) {
      printf ("Essa coluna nao existe \n");
      goto start;
    }
    else if (retira_coluna == 0)
      goto end;

    IrInicioLista (tabuleiro);
    LIS_AvancarElementoCorrente (tabuleiro, retira_coluna - 1);
    coluna = (LIS_tppLista) LIS_ObterValor (tabuleiro);
    IrFinalLista (coluna);

    if (LIS_ObterValor (coluna) == NULL) {
      printf ("Essa coluna esta vazia \n");
      goto start;
    }

    if (retira_coluna < 5) {
      printf ("Voce nao pode retirar cartas da coluna sequencia ordenada \n");
      goto start;
    }
    else if (retira_coluna < 9) {
      if (testa_saida_extra (coluna) == 0) {
        printf ("Essa coluna esta vazia \n");
        goto start;
      }
      else {
        num_carta = numero_carta (coluna);
        strcpy (nai_carta, naipe_carta (coluna));
        printf ("Voce esta movendo a carta %d %s \n", num_carta, nai_carta);
      }
    }
    else {
      printf ("Quantas cartas voce deseja mover? \n");
      scanf ("%d", &numero);

      IrFinalLista (coluna);
      LIS_AvancarElementoCorrente (coluna, -(numero - 1));
      teste = LIS_AvancarElementoCorrente (coluna, 0);
      p = LIS_ObterValor (coluna);

      printf ("Voce esta movendo a(s) carta(s) ");
      while (teste == LIS_CondRetOK) {
        num_carta = numero_carta (coluna);
        strcpy (nai_carta, naipe_carta (coluna));
        printf ("%d %s ", num_carta, nai_carta);
        teste = LIS_AvancarElementoCorrente (coluna, 1);
      }
      printf ("\n");
      IrInicioLista (coluna);
      LIS_ProcurarValor (coluna, p);

      if (testa_saida_sequencia_visivel (coluna) == 0) {
        printf ("Voce nao pode remover essas cartas ou a coluna esta vazia \n");
        goto start;
      }

      IrInicioLista (coluna);
      LIS_ProcurarValor (coluna, p);
    }


    printf ("Para qual coluna voce deseja mover essas cartas? \n");
    scanf ("%d", &insere_coluna);

    if ((insere_coluna < 0) || (insere_coluna > 16)) {
      printf ("Essa coluna nao existe \n");
      goto start;
    }
    else if (insere_coluna == 0)
      goto end;


    IrInicioLista (tabuleiro);
    LIS_AvancarElementoCorrente (tabuleiro, insere_coluna - 1);
    insere = (LIS_tppLista) LIS_ObterValor (tabuleiro);
    IrFinalLista (insere);

    if (insere_coluna < 5) {
      if (testa_entrada_sequencia_ordenada (insere, coluna) == 0)
        printf ("Voce nao pode inserir essa carta nessa coluna \n");
      else
        move_cartas (tabuleiro, retira_coluna, insere_coluna);
    }
    else if (insere_coluna < 9) {
      if (testa_entrada_extra (insere, coluna) == 0)
        printf ("Voce nao pode inserir essa carta nessa coluna \n");
      else
        move_cartas (tabuleiro, retira_coluna, insere_coluna);
    }
    else {
      if (testa_entrada_sequencia_visivel (insere, coluna) == 0)
        printf ("Voce nao pode inserir essa carta nessa coluna \n");
      else {
        IrInicioLista (coluna);
        LIS_ProcurarValor (coluna, p);
        move_cartas (tabuleiro, retira_coluna, insere_coluna);
      }
    }

    vit = vitoria (tabuleiro);

    if (vit == 1)
      break;

    printf ("Aperte qualquer tecla para fazer uma movimentacao ou 0 para sair \n");
    scanf ("%d", &comando);

    if (comando == 0)
      goto end;
  }

  end:
  printf ("Caso voce queira replicar esse jogo a seed utilizada foi %u \n", seed);

  return 0;
}
