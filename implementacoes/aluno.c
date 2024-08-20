#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../interfaces/aluno.h"
#include "../interfaces/projeto.h"

struct aluno
{
    int matricula;
    char nome[40];
    int idade;
    struct aluno *proxAluno;
    struct aluno *antAluno;
};

Aluno *cria_aluno(int matricula, int idade, string nome)
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));

    if (novoAluno == NULL)
        return NULL;

    novoAluno->matricula = matricula;
    novoAluno->idade = idade;
    strcpy(novoAluno->nome, nome);
    novoAluno->proxAluno = NULL;
    novoAluno->antAluno = NULL;

    return novoAluno;
}

Aluno *prox_aluno(Aluno *aluno)
{
    return aluno->proxAluno;
}

Aluno *ant_aluno(Aluno *aluno)
{
    return aluno->antAluno;
}

void definir_prox_aluno(Aluno *aluno, Aluno *proxAluno)
{
    aluno->proxAluno = proxAluno;
}

void definir_ant_aluno(Aluno *aluno, Aluno *antAluno)
{
    aluno->antAluno = antAluno;
}

int matricula_aluno(Aluno *aluno)
{
    return aluno->matricula;
}

void imprime_aluno(Aluno *aluno)
{
    printf("Nome: %s\n", aluno->nome);
    printf("Matrícula: %d\n", aluno->matricula);
    printf("Idade: %d\n", aluno->idade);
}