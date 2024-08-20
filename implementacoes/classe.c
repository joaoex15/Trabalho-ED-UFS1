#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../interfaces/classe.h"
#include "../interfaces/aluno.h"
#include "../interfaces/projeto.h"

struct classe
{
    uint8_t serie;
    char turma;
    char etapa[20];
    uint32_t qtd_alunos;
    char nome_professor[100];
    struct classe *prox;
    Aluno *alunos;
};

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

int matriculaAluno(
    Classe **classes,
    int matricula,
    string nome,
    int idade,
    uint8_t serie,
    char turma,
    string etapa)
{
    Classe *classeAtual = *classes;
    while (classeAtual != NULL)
    {
        if (classeAtual->serie == serie &&
            classeAtual->turma == turma &&
            strcmp(classeAtual->etapa, etapa) == 0)
        {
            break;
        }
        classeAtual = classeAtual->prox;
    }

    if (classeAtual == NULL)
        return 1;

    Aluno *novoAluno = cria_aluno(matricula, idade, nome);

    if (novoAluno == NULL)
        return 1;

    if (classeAtual->alunos == NULL)
    {
        classeAtual->alunos = novoAluno;
    }
    else
    {
        Aluno *alunoAtual = classeAtual->alunos;
        while (prox_aluno(alunoAtual) != NULL)
        {
            alunoAtual = prox_aluno(alunoAtual);
        }

        definir_prox_aluno(alunoAtual, novoAluno);
        definir_ant_aluno(novoAluno, alunoAtual);
    }

    classeAtual->qtd_alunos++;
    return 0;
}

int removeAluno(
    Classe **classes,
    int matricula,
    uint8_t serie,
    char turma,
    string etapa)
{
    Classe *classeAtual = *classes;
    while (classeAtual != NULL)
    {
        if (classeAtual->serie == serie &&
            classeAtual->turma == turma &&
            strcmp(classeAtual->etapa, etapa) == 0)
        {
            break;
        }
        classeAtual = classeAtual->prox;
    }

    if (classeAtual == NULL || classeAtual->alunos == 0)
        return 1;

    Aluno *alunoAtual = classeAtual->alunos;

    while (alunoAtual != NULL)
    {
        if (matricula_aluno(alunoAtual) == matricula)
        {
            if (ant_aluno(alunoAtual) != NULL)
                definir_prox_aluno(ant_aluno(alunoAtual), prox_aluno(alunoAtual));
            else
                classeAtual->alunos = prox_aluno(alunoAtual);

            if (prox_aluno(alunoAtual) != NULL)
                definir_ant_aluno(prox_aluno(alunoAtual), ant_aluno(alunoAtual));

            free(alunoAtual);
            classeAtual->qtd_alunos--;
            return 0;
        }

        alunoAtual = prox_aluno(alunoAtual);
    }
    return 1;
}

void exibir_classes(Classe *inicio)
{
    Classe *classe_atual = inicio;

    while (classe_atual != NULL)
    {
        printf("Classe %d%c/%s - Professor: %s, Quantidade de Alunos: %d\n", classe_atual->serie, classe_atual->turma, classe_atual->etapa,
               classe_atual->nome_professor, classe_atual->qtd_alunos);

        classe_atual = classe_atual->prox;
    }
    return;
}

void exibir_alunos(
    Classe *inicio,
    int serie,
    char turma,
    string etapa)
{
    Classe *classe_atual = inicio;

    while (classe_atual != NULL)
    {
        if (classe_atual->turma == turma &&
            classe_atual->serie == serie &&
            !strcmp(classe_atual->etapa, etapa))
        {
            limpar_terminal();
            if (classe_atual->alunos == NULL)
            {
                printf("Nao ha alunos cadastrados nessa classe.\n");
                return;
            }
            printf("Alunos matriculados na classe %d%c:\n", serie, turma);

            Aluno *aluno_atual = classe_atual->alunos;
            while (aluno_atual != NULL)
            {
                imprime_aluno(aluno_atual);
                aluno_atual = prox_aluno(aluno_atual);
            }
            return;
        }

        classe_atual = classe_atual->prox;
    }
    limpar_terminal();
    printf("Classe %d%c nao encontrada!\n", serie, turma);
    return;
}

void Pesquisar(Classe *classe, int matricula)
{
    Aluno *alunoAtual;
    int encontrou = 0;

    printf("Iniciando a pesquisa...\n");

    while (classe != NULL)
    {
        printf("Verificando classe: Serie %u, Turma %c\n", classe->serie, classe->turma);
        alunoAtual = classe->alunos;

        while (alunoAtual != NULL)
        {
            if (matricula_aluno(alunoAtual) == matricula)
            {
                printf("Aluno encontrado:\n");
                imprime_aluno(alunoAtual);
                printf("Serie: %u\n", classe->serie);
                printf("Turma: %c\n", classe->turma);
                printf("Etapa: %s\n", classe->etapa);
                printf("Nome do Professor: %s\n", classe->nome_professor);
                printf("------------------------\n");
                encontrou = 1;
            }
            alunoAtual = prox_aluno(alunoAtual);
        }

        classe = classe->prox;
    }

    if (!encontrou)
    {
        printf("Nenhum aluno com a matricula '%d' encontrado.\n", matricula);
    }
}

uint8_t obter_serie_classe(Classe *classe)
{
    return classe->serie;
}

Classe *prox_classe(Classe *classe)
{
    return classe->prox;
}

Aluno *obter_alunos_classe(Classe *classe)
{
    return classe->alunos;
}
