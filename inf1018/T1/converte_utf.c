/* Autor: Daniel Carlier */

#include <stdlib.h>
#include <stdio.h>
#include "conv_utf.h"

unsigned int inverte_int(unsigned int i){
return(((i&0xff000000)>>24)| ((i&0xff0000)>>8) | ((i&0xff00)<<8) | ((i&0xff)<<24));    
  }

unsigned short inverte_short(unsigned short val){
return (val << 8) | ((val >> 8) & 0xFF);}

unsigned int shift_direita(unsigned int val, int n)
{
return(val = val >> n);}

int testa_arquivos(FILE *arq_entrada, FILE *arq_saida){
if(arq_entrada == NULL)
	{
	printf("Erro na leitura do arquivo \n");return (-1);
	}
if(arq_saida == NULL)
	{
	printf("Erro na gravação do arquivo de saida \n");return (-1);
	}	
return 0;
}





int utf8_16(FILE *arq_entrada, FILE *arq_saida){

if(testa_arquivos(arq_entrada,arq_saida) == (-1))
return (-1);

unsigned int num,U,U2;
unsigned short big1 = 0xFFFE;

/*Escreve o BOM (Byte Order Mark) no começo do arquivo*/
fwrite(&big1, 2, 1, arq_saida);  

while(!feof(arq_entrada)){             /*Enquanto o arquivo não chegar ao fim, faça: */  
	num=fgetc(arq_entrada);		 /*Recebe o primeiro byte a ser lido*/
	if(num <= 127){                  /* 127 corresponde ao maior valor possível para um byte na primeira
                                                 faixa do código UNICODE, isto é, 01111111*/
		U=inverte_int(num);U=shift_direita(U,16);	/*Inversão da ordem dos bytes para 
								impressão na ordenação Big Endian*/		
		fwrite(&U, 2, 1, arq_saida);	/*Escreve no arquivo de saída em UTF-16*/		
		      }
	else{
		if(num <= 223)     /*223 corresponde ao maior valor possível para o primeiro byte da segunda
				     faixa dos caracteres UNICODE, ou seja, 11011111, o que nos indica em qual 
				     faixa dos caracteres estamos trabalhando*/
		{
			U = (num - 192) * 64;       /*U corresponde ao código UNICODE*/
			num=fgetc(arq_entrada);     /*num  lê agora o segundo byte*/
			U = U + (num - 128);U=inverte_int(U);U=shift_direita(U,16);
			fwrite(&U, 2, 1, arq_saida);  /*Escreve no arquivo de saída em UTF-16*/
		}
		else{
			if(num <= 239)   /*239 Corresponde ao maior valor possível para o primeiro byte da
					   terceira faixa de caracteres UNICODE, indicando em qual faixa estamos*/
			{
				U = (num - 224)*4096;
				num=fgetc(arq_entrada);
				U = U + (num-128)*64;
				num=fgetc(arq_entrada);
				U = U + (num - 128);U=inverte_int(U);U=shift_direita(U,16);
				fwrite(&U, 2, 1, arq_saida);				
			}
			else
			{
				U = (num - 240)*262144;
				num=fgetc(arq_entrada);
				U = U + (num-128)*4096;
				num=fgetc(arq_entrada);
				U = U + (num-128)*64;
				num=fgetc(arq_entrada);
				U = U + (num - 128);
				U = U - 65536;
				U2=U;
				U=shift_direita(U,10); U2=U2 & 0x00003FF;U=U+55296;U2=U2+56320;
				U=inverte_int(U); U2=inverte_int(U2);
				U=shift_direita(U,16);U2=shift_direita(U2,16);
				fwrite(&U,2,1,arq_saida);fwrite(&U2,2,1,arq_saida);
				}
			   }
		    }
			
			}
return 0;
}




int utf16_8(FILE *arq_entrada, FILE *arq_saida){

if(testa_arquivos(arq_entrada,arq_saida) == (-1))
return (-1);

unsigned short num, num2;

num=fgetc(arq_entrada);		/*Verifica o BOM (Byte Order Mark) do arquivo de entrada*/
if(num != 254){			/* 254 corresponde em decimal a FE */
printf("BOM invalido ou inexistente \n");
return (-1);}
num=fgetc(arq_entrada);      /*Lê mais um byte só para pular o segundo byte (FF) do BOM */

while(!feof(arq_entrada)){	/*Enquanto não chega o final do arquivo, faça:*/
	num=fgetc(arq_entrada);num2=fgetc(arq_entrada); /*Lê dois bytes do arquivo*/
	num = num << 8;
	num = num + num2;     /*Armazena os dois bytes lidos em somente um short*/
	
	if(num >= 55296 && num < 56320){  /*Se "num" estiver dentro dessa faixa, seu código UNICODE será 
				            composto por um par consignado, logo, devemos ler seu par. */
		unsigned short num3, num4;
		num3=fgetc(arq_entrada);num4=fgetc(arq_entrada);
		num3 = num3 << 8;
		num3 = num3 + num4;
		
		/* Converte-se os dois valores, "num" e "num3", em seu correspondente na tabela UNICODE */
		int numero = (num - 55296)*1024 + (num3-56320)+65536;

		float j = ((float)numero / 262144) + 240; num=j; /*Converte-se o código Unicode nos bytes */
		num2 = ((numero / 4096) % 64) + 128;		/* necessários para a escrita em UTF-8 e, */
		num3 = ((numero / 64) % 64) + 128;		/* em seguida, escreve-os no arquivo de saida*/
		num4 = (numero % 64) + 128;
		fwrite(&num, 1, 1, arq_saida);
		fwrite(&num2, 1, 1, arq_saida);
		fwrite(&num3, 1, 1, arq_saida);
		fwrite(&num4, 1, 1, arq_saida);
	}
	else{ 
		if(num <= 127){					/*Se o valor lido for menor que 127 (007f)*/
				fwrite(&num, 1, 1, arq_saida);	/*ele só precisa de um byte para ser*/
			       }				/* escrito em UTF-8                 */
		else{
			if(num <= 2047)				/*Se for menor que 2047 (07ff), dois bytes */
			{
				num2=num;
				num = (num/64) + 192;
				num2 = (num2%64)+128;
				fwrite(&num, 1, 1, arq_saida);
				fwrite(&num2, 1, 1, arq_saida);
			}
			else{
					unsigned short num3 = num;	/*O restante, então, precisa de 3 bytes*/
					num2=num;
					num = (num/4096) + 224;
					num2 = ((num2/64)%64) + 128;
					num3 = (num3 % 64) + 128;
					fwrite(&num, 1, 1, arq_saida);
					fwrite(&num2, 1, 1, arq_saida);
					fwrite(&num3, 1, 1, arq_saida);
			    }
		    }
	 }
    }				    
return 0;
}
