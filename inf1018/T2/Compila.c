  /* Daniel Carlier 1511739 3WA
     Jorge Pumar Dodsworth 1212572 3WB*/

  typedef int (*funcp) (int x);

  int converte_hex_little (unsigned char vet[], int i, int idx) {
    vet[i] = idx & 0xFF; i++;
    vet[i] = (idx >> 8) & 0xFF; i++;
    vet[i] = (idx >> 16) & 0xFF; i++;
    vet[i] = (idx >> 24) & 0xFF; i++;

    return i;
  }

  funcp compila (FILE *myfp) {
    int  c;
    unsigned char codigo [1000];
    unsigned int linha [51];
    unsigned int linhaif; /* Contador da posição de um if para uma linha depois de sí próprio */
    unsigned int pos;
    int i = 8; /* Contador da posição do vetor codigo */
    int j = 1; /* Contador da posição do vetor linha */ 
    int k; /* Contador da posição do vetor linhaif */
    unsigned char v1 = 0xf0;
    unsigned char v2 = 0xf4;
    unsigned char v3 = 0xf8;
    unsigned char v4 = 0xfc;
    unsigned char var;

    /* Início do programa */
    codigo[0] = 0x55;
    codigo[1] = 0x48;
    codigo[2] = 0x89;
    codigo[3] = 0xe5;
    codigo[4] = 0x48;
    codigo[5] = 0x83;
    codigo[6] = 0xec;
    codigo[7] = 0x10;

    while ((c = fgetc (myfp)) != EOF) {
      switch (c) {
        /* Case de retorno */
      case 'r': {
        linha[j] = i; j++; /* Coloca no vetor linha na posição j qual o número dessa linha */
        codigo[i] = 0x8b; i++;
        codigo[i] = 0x45; i++;
        codigo[i] = 0xf0; i++; /*Passa v1 para o valor de retorno */
        codigo[i] = 0x48; i++;
        codigo[i] = 0x89; i++;
        codigo[i] = 0xec; i++;
        codigo[i] = 0x5d; i++;
        codigo[i] = 0xc3; i++;

        /* Lê resto da palavra "ret" */
        c = fgetc (myfp);
        c = fgetc (myfp);
        break;
      }
        /* Case de atribuicao */
      case 'p':
      case 'v': {
        int idx0, idx1, idx2;
        char var1, var2, op;
        fscanf (myfp, "%d = %c%d %c %c%d", &idx0, &var1, &idx1, &op, &var2,
                &idx2);

        linha[j] = i; j++; /* Coloca no vetor linha na posição j qual o número dessa linha */

        /* Caso em que os dois operandos não são iguais */
        if (var1 == 'v') {
          codigo[i] = 0x8b; i++; /* Move a variável em questão para %edi pra fazer a conta */
          codigo[i] = 0x7d; i++; /* %edi corresponde a 7d */

          if (idx1 == 1) {
            codigo[i] = v1;
            i++;
          }
          else if (idx1 == 2) {
            codigo[i] = v2;
            i++;
          }
          else if (idx1 == 3) {
            codigo[i] = v3;
            i++;
          }
          else {
            codigo[i] = v4;
            i++;
          }

          if (var2 == 'v') {
            /* Segunda variável */
            if (idx2 == 1)
              var = v1;
            else if (idx2 == 2)
              var = v2;
            else if (idx2 == 3)
              var = v3;
            else
              var = v4;

            /* Define a operação que será realizada pelas variáveis */
            if (op == '+') {
              codigo[i] = 0x03; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x2b; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else {
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
          }
          else if (var2 == 'p') {
            if (idx2 == 1)
              var = 0xf7;
            else
              var = 0xd7;

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = var; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = var; i++;
            }
            else {
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;

              if (idx2 == 1) {
                codigo[i] = 0xfe;
                i++; /*multiplica %esi e %edi*/
              }
              else {
                codigo[i] = 0xfa;
                i++; /*multiplica %edx e %edi*/
              }
            }
          }
          else { /* Variável com inteiro */

            /* Código de movl de um int para %ecx para fazer a conta com %edi */
            codigo[i] = 0xb9; i++;
            i = converte_hex_little (codigo, i, idx2);

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = 0xcf; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = 0xcf; i++;
            }
            else { /* op == '*' */
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0xf9; i++;
            }
          }
        }
        else if (var1 == 'p') {
          if (var2 == 'p') {
            /* Move para %edi o primeiro parametro a ser usado */
            if (idx1 == 1) {
              codigo[i] = 0x89; i++;
              codigo[i] = 0xf7; i++;
            }
            else {
              codigo[i] = 0x89; i++;
              codigo[i] = 0xd7; i++;
            }

            if (idx2 == 1)
              var = 0xf7;
            else
              var = 0xd7;

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = var; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = var; i++;
            }
            else {
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;

              if (idx2 == 1) {
                codigo[i] = 0xfe;
                i++; /*multiplica %esi e %edi*/
              }
              else {
                codigo[i] = 0xfa;
                i++; /*multiplica %edx e %edi*/
              }
            }
          }
          else if (var2 == 'v') {
            if (idx2 == 1) {
              var = v1;
            }
            else if (idx2 == 2){
              var = v2;
            }
            else if (idx2 == 3) {
              var = v3;
            }
            else {
              var = v4;
            }

            if(op == '+') {
              codigo[i] = 0x03; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else if(op == '-') {
              codigo[i] = 0x2b; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else { /*op == '*' */
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
          }
          else { /* Segundo operando for um inteiro */

            /* Código de movl de um int para %ecx para fazer a conta com %edi */
            codigo[i] = 0xb9; i++;
            i = converte_hex_little (codigo, i, idx2);

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = 0xcf; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = 0xcf; i++;
            }
            else { /* op == '*' */
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0xf9; i++;
            }
          }
        }
        /* Se o primeiro operando for um inteiro */
        else {
          codigo[i] = 0xbf; i++; /*Início do código de mover, move int para o %edi */
          i = converte_hex_little (codigo, i, idx1);

          if (var2 == '$') {
            /* Código de movl de um int para %ecx para fazer a conta com %edi */
            codigo[i] = 0xb9; i++;
            i = converte_hex_little (codigo, i, idx2);

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = 0xcf; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = 0xcf; i++;
            }
            else { /* op == '*' */
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0xf9; i++;
            }
          }
          else if (var2 == 'v') {
            if (idx2 == 1) {
              var = v1;
            }
            else if (idx2 == 2) {
              var = v2;
            }
            else if (idx2 == 3) {
              var = v3;
            }
            else {
              var = v4;
            }

            if (op == '+') {
              codigo[i] = 0x03; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x2b; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
            else {
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;
              codigo[i] = 0x7d; i++;
              codigo[i] = var; i++;
            }
          }
          /* Segundo operando é um parâmetro */
          else {
            if (idx2 == 1)
              var = 0xf7;
            else
              var = 0xd7;

            if (op == '+') {
              codigo[i] = 0x01; i++;
              codigo[i] = var; i++;
            }
            else if (op == '-') {
              codigo[i] = 0x29; i++;
              codigo[i] = var; i++;
            }
            else {
              codigo[i] = 0x0f; i++;
              codigo[i] = 0xaf; i++;

              if (idx2 == 1) {
                codigo[i] = 0xfe;
                i++; /*multiplica %esi e %edi*/
              }
              else {
                codigo[i] = 0xfa;
                i++; /*multiplica %edx e %edi*/
              }
            }
          }
        }
        /* Atribuir o %edi com a resposta da conta feita acima a seu devido lugar */
        if (c == 'p') {
          /* Codigo de mov */
          codigo[i] = 0x89;
          i++;

          if (idx0 == 1) {
            codigo[i] = 0xfe; /* %esi */
            i++;
          }
          else {
            codigo[i] = 0xfa; /* %edx */
            i++;
          }
        }
        else { /* Se for v */
          codigo[i] = 0x89; i++;
          codigo[i] = 0x7d; i++;

          if (idx0 == 1) {
            codigo[i] = v1;
            i++;
          }
          else if (idx0 == 2) {
            codigo[i] = v2;
            i++;
          }
          else if (idx0 == 3) {
            codigo[i] = v3; i++;
          }
          else {
            codigo[i] = v4; i++;
          }
        }

        break;
      }
        /* Case do if */
      case 'i': {

        int idx1, idx2, dest;
        char var1;
        fscanf (myfp, "f %c%d %d", &var1, &idx1, &idx2); /* Var1 -> parâmetro ou variável 
                                                            idx1 -> Número do operando
                                                            idx2 -> Linha para desvio */
        /* Move seja um parâmetro ou variável para o %edi */
        if(var1 == 'p'){
          if(idx1 == 1){
            codigo[i] = 0x89; i++;
            codigo[i] = 0xf7; i++;
          }
          else{
            codigo[i] = 0x89; i++;
            codigo[i] = 0xd7; i++;
          }
        }
        else{ /* var1 é uma variável */
          codigo[i] = 0x8b; i++;
          codigo[i] = 0x7d; i++;
          if(idx1 == 1){
            codigo[i] = v1; i++;
          }
          else if(idx1 == 2){
            codigo[i] = v2; i++;
          }
          else if(idx1 == 3){
            codigo[i] = v3; i++;
          }
          else{
            codigo[i] = v4; i++;
          }
        }
        codigo[i] = 0x83; i++; /* Compara se %edi não é zero */
        codigo[i] = 0xff; i++;
        codigo[i] = 0x00; i++;
        codigo[i] = 0x75; i++; /* Instrução para o jump not equal a zero*/
        linha[j] = i; j++; /* Coloca no vetor linha na posição j qual o número dessa linha */

        if(idx2 < (j-1)){ /* Linha para qual pular já foi lida (anterior ao if) */
          dest = 0xff - (linha[j-1] - linha[idx2]);
          /*dest = dest & 0xff;*/
          codigo[i] = dest; i++;
        }
        else{ /* Linha para qual pular ainda não foi lida */
          k = idx2; /* Linha para qual pular */
          pos = i; i++; /* Guarda a posição onde escrever no vetor código */
          linhaif = linha[j-1]; /* Recebe qual a linha do if atual */
        }
        break;
      }
      }
      if(k == (j-1)){ /* Linha para qual o if deve pular é essa */
        codigo[pos] = (linha[j-1] - linhaif) - 1;
      }
    }
    funcp f = (funcp)codigo; /*Transforma o vetor codigo em um funcp */
    return f;

  }
