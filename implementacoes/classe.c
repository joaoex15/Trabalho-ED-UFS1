#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../interfaces/classe.h"
#include "../interfaces/aluno.h"


Classe *classe_inicializa()
{
    return NULL;
}

int classe_insere(
    Classe **classes,
    uint8_t serie,
    char turma,
    string etapa,
    string nomeProfessor)
{
    Classe *novaClasse = (Classe *)malloc(sizeof(Classe));

    if (novaClasse == NULL)
        return 1;

    novaClasse->serie = serie;
    novaClasse->turma = turma;
    novaClasse->qtd_alunos = 0;
    novaClasse->prox = *classes;
    novaClasse->alunos = NULL;
    strcpy(novaClasse->etapa, etapa);
    strcpy(novaClasse->nome_professor, nomeProfessor);

    *classes = novaClasse;

    return 0;
}

int classe_remove(Classe *classe, Classe **classes)
{
    if (classe->qtd_alunos)
        return 1;

    Classe *atual = *classes;
    Classe *anterior = NULL;

    while (atual != classe)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior != NULL)
        anterior->prox = atual->prox;
    else
        *classes = atual->prox;
    free(atual);

    return 0;
}

void exibir_classes(Classe *inicio)
{
	Classe *classe_atual = inicio;

	while(classe_atual != NULL){
		printf("Classe %d%c - Professor: %s, Quantidade de Alunos: %d\n", classe_atual->serie, classe_atual->turma,
		        classe_atual->nome_professor, classe_atual->qtd_alunos);
		
		classe_atual = classe_atual->prox;
	}
	return;
}