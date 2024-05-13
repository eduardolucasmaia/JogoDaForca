#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<time.h>
#include <sys/stat.h>
#include "forca.h"

//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char palavrasecretaIngles[TAMANHO_PALAVRA_INGLES];
char descricaoPalavra[TAMANHO_DESCRICAO_PALAVRA];
char descricaoPalavraIngles[TAMANHO_DESCRICAO_PALAVRA_INGLES];
char significadoPalavra[TAMANHO_SIGNIFICADO_PALAVRA];

char lista[180][TAMANHO_SIGNIFICADO_PALAVRA];


 char chutes[26];
int chutesDados = 0;

void abertura() {
    printf("***************\n");
    printf(" Jogo da Forca \n");
    printf("***************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra) {
    int achou = 0;

    for(int j = 0; j < chutesDados; j++) { //chute
        if(chutes[j] == letra) {
            achou = 1; //chute correto
            break;
        }
    }
    return achou;
}

void desenhaForca() {
    int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecretaIngles); i++) { //estou vendo a letra secreta

        int achou = jaChutou(palavrasecretaIngles[i]);

        if(achou) {
            printf("%c ", palavrasecretaIngles[i]);
        } else {
            printf("_ ");
        }
    }
        printf("\n");
}

void escolhePalavra() {	
	char nivel;
    printf("Qual o nivel da dificuldade das perguntas (Basico[b,1]  intermediario[i,2]  Avancado[a,3]): ");
    scanf(" %c", &nivel);
		
    FILE* f;
 	struct stat sb;
 	
	if(nivel == 'b' || nivel == 'B' ||nivel == '1') {	
    	f = fopen("basico.txt", "r"); //abre arquivo
    	stat("basico.txt", &sb);
    	printf("Nivel: Basico\n\n");
	}
    else if(nivel == 'i' || nivel == 'I' ||nivel == '2') {	
    	f = fopen("intermediario.txt", "r"); //abre arquivo
    	stat("intermediario.txt", &sb);
    	printf("Nivel: Intermediario\n\n");
	}
    else if(nivel == 'a' || nivel == 'A' ||nivel == '3') {	
    	f = fopen("avancado.txt", "r"); //abre arquivo
    	stat("avancado.txt", &sb);
    	printf("Nivel: Avancado\n\n");
	}	
    else {
        printf("Desculpe, banco de dados n�o dispon�vel");
        exit(1);
    }

  	char *file_contents = malloc(sb.st_size);

	int i = 0;
  	while (fscanf(f, "%[^\n] ", file_contents) != EOF) {
    	strcpy(lista[i], file_contents);
    	i++;
  	}
  	
  	//for (int j = 0; j < i; j++) {
        //printf("%s\n", lista[j]); // Print each word in the matrix
    //}
    
    int qtdDePalavras = i / 6;

    srand(time(0));
    int randomico = rand() % qtdDePalavras; //calcula um numero aleatorio

    strcpy(descricaoPalavra ,lista[randomico * 6]);
    strcpy(descricaoPalavraIngles ,lista[(randomico * 6) + 1]);
    strcpy(palavrasecreta ,lista[(randomico * 6) + 2]);
    strcpy(palavrasecretaIngles ,lista[(randomico * 6) + 3]);
    strcpy(significadoPalavra ,lista[(randomico * 6) + 4]);
    
    //printf("%s\n", descricaoPalavra);
    //printf("%s\n", descricaoPalavraIngles);
    //printf("%s\n", palavrasecreta);
    //printf("%s\n", palavrasecretaIngles);
    //printf("%s\n", significadoPalavra);
    
    fclose(f);
        
    printf("Word hint: %s\n\n",descricaoPalavraIngles);
    printf("Dica da palavra: %s\n\n",descricaoPalavra);
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecretaIngles); i++) {
        if(!jaChutou(palavrasecretaIngles[i])) {
            return 0;
        }
    }
    return 1;
}
int chutesErrados() {
    int erros = 0;
    for(int i = 0; i < chutesDados; i++) {
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecretaIngles); j++) {
            if(chutes[i] == palavrasecretaIngles[j]) {

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou() {
    return chutesErrados() >= 5;
}

// ! O PROGRAMA COMECA AQUI !

int main() {
    setlocale(LC_ALL,"PORTUGUESE");
    
    abertura();
    escolhePalavra();

    do {
        desenhaForca();
        chuta();
    } while(!acertou() && !enforcou());

    if(acertou()) {
        printf("Parabens, voce ganhou!\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("Puxa, voce foi enforcado!\n");
        printf("A palavra certa era %s.\n",palavrasecretaIngles);
        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    
    printf("Sua descricao e: %s\n\n",significadoPalavra);
    
    system("PAUSE");
    return 0;
}
