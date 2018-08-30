#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TAM 51

/* Considerações sobre o trabalho

		Teve-se dificuldade com relação à manipulação de strings, por não ter sido tão explorado durante o semestre. Mas
	durante o desenvolvimento do projeto foi possível perceber, graças às consultas constantes em referências, manuais e apostilas sobre a linguagem,
	que, o importante é sempre buscar conhecimento.
	
 */
// Autor: Christian Alves

typedef struct dna DNA;

struct dna {
    char fitaA[TAM];
    char fitaB[TAM];
};

// Funcoes
void lerSequencia(DNA *);
bool validarSequencia(char []);
void mostrarSequencia(DNA);
void sequenciaComplementar(DNA *);
void procurarCodon(DNA);
void procurar(DNA, char []);
int leituraFrame(int, char [], char []);
char* inverter(char []);

int main() {


    DNA dna;
    char opcao;

    while(1) {
        printf("Descobrindo sequencias DNA\n");
        printf("1. Ler sequencia\n2. Mostrar sequencia\n3. Procurar codon\n4. Sair\n");
        scanf("%c", &opcao);
        getchar();

        switch(opcao) {
            case '1': lerSequencia(&dna); break;
            case '2': mostrarSequencia(dna); break;
            case '3': procurarCodon(dna); break;
            case '4': printf("FLWS!"); return 0;
            default: printf("Opcao invalida.\n");
        }
    }

    return 0;
}

void mostrarSequencia(DNA dna) {
    int i;

    printf("Mostrar sequencia\n");

    printf("3' %s 5'\n", dna.fitaA);
    printf("5' %s 3'\n", dna.fitaB);
    printf("\n");
}

void lerSequencia(DNA *dna) {
    char sequencia[TAM]; // = "TACACGTTAGCATAGTACGTTACGGGATCGCTCTAGCTAGCTAGCTACGCTAGCTAGCTACGCTAGCTAGCTACGCT";

    printf("Ler sequencia\n");
    scanf ("%50[^\n]", sequencia);
    __fpurge(stdin);
    if (validarSequencia(sequencia)) {
        strcpy(dna->fitaA,sequencia);
        sequenciaComplementar(dna);
    }
    else {
        printf("Sequencia invalida.");
    }
    printf("\n");
}

bool validarSequencia(char sequencia[]) {
	
	/*
	Função de validação da sequencia digitada pelo usuario.
	Regra(s):
	* Deve conter 3 ou mais caracteres;
	* Deve conter caracteres válidos (A, T, C, G);
	
	*/

    if (strlen(sequencia) < 3) {
        return false;
    }

    int i=0;
    while (sequencia[i] != '\0'){
        if (strchr("ATGC",sequencia[i]) == NULL) {
            return false;
        }
        i++;
    }
    return true;
}

bool validarBase(char base[]) {
	/*
	Função de validação de base (códon a ser encontrado na sequencia)
	Regra(s):
	* Deve conter 3 caracteres;
	* Deve conter caracteres válidos (A, T, C, G);
	*/
	
    if (strlen(base) != 3)
        return false;

    return validarSequencia(base);
}

void sequenciaComplementar(DNA *dna) {
	/*
	Função que gera a sequência complementar à sequencia digitada pelo usuário.
	Regra(s):
	* Para cada caracter, gera-se outro equivalente:
		A <-> T
		C <-> G
	*/
	
    int i;
    i=0;
    while (dna->fitaA[i] != '\0') {
        switch(dna->fitaA[i]) {
            case 'A': dna->fitaB[i] = 'T'; break;
            case 'T': dna->fitaB[i] = 'A'; break;
            case 'C': dna->fitaB[i] = 'G'; break;
            case 'G': dna->fitaB[i] = 'C'; break;
        }
        i++;
    }
}

void procurarCodon(DNA dna) {
    int i, j;
    char base[4];

    if (!validarSequencia(dna.fitaA)) {
        printf("Digite uma sequencia primeiro.\n");
        return;
    }

    printf("Procurar codon\n");
    printf("Bases (=3): ");
    scanf ("%3[^\n]", base);
    __fpurge(stdin);

    if (validarSequencia(base)) {
        procurar(dna, base);
    }
    else {
        printf("Bases invalidas.");
    }
    printf("\n");
}

void procurar(DNA dna, char base[]) {
    int i;
    printf("Strand Sense\n");
    for (i=0 ; i<3; i++) {
        printf("Total: %d\n", leituraFrame(i,dna.fitaA,base));
    }
    printf("\n");
    int tam = strlen(dna.fitaB);
    char aux[tam+1];

    strcpy(dna.fitaB, inverter(dna.fitaB));
    printf("Strand Anti-Sense\n");
    for (i=0 ; i<3; i++) {
        printf("Total: %d\n", leituraFrame(i,dna.fitaB,base));
    }
}

char * inverter(char fita[]) {
    int i, j, tam;
    tam = strlen(fita);
    char aux[tam+1];
    char *inverso = aux;
    for (i=0, j=tam-1; i<tam; i++, j--) {
        aux[j] = fita[i];
    }
    return inverso;
}

int leituraFrame(int frame, char fita[], char base[]) {
    int i=frame, total = 0, tam = strlen(fita)+1;

    printf("Leitura +%d\nPosicoes: ", frame+1);

    while (i+3<tam) {
        char aux[] = {fita[i], fita[i+1], fita[i+2], '\0'};
        if (strcmp(aux,base)==0) {
            printf("%d; ", i+1);
            total++;
        }
        i+=3;
    }

    printf("\n");
    return total;
}
