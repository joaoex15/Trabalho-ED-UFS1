#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aluno.c"
#include "../interfaces/classe.h"
#include "../interfaces/aluno.h"




void Pesquisar(Classe *d, const char *nome) {
    Aluno *alunoAtual;
    int encontrou = 0;

    printf("Iniciando a pesquisa...\n");

    // Percorre a lista de classes
    while (d != NULL) {
        printf("Verificando classe: Série %u, Turma %c\n", d->serie, d->turma);
        alunoAtual = d->alunos;

        // Percorre a lista de alunos na classe atual
        while (alunoAtual != NULL) {
            if (strcmp(alunoAtual->nome, nome) == 0) {
                // Aluno encontrado, imprime todas as informações
                printf("Aluno encontrado:\n");
                printf("Nome: %s\n", alunoAtual->nome);
                printf("Matrícula: %d\n", alunoAtual->matricula);
                printf("Idade: %d\n", alunoAtual->idade);
                printf("Série: %u\n", d->serie);
                printf("Turma: %c\n", d->turma);
                printf("Etapa: %s\n", d->etapa);
                printf("Nome do Professor: %s\n", d->nome_professor);
                printf("------------------------\n");
                encontrou = 1;
            }
            alunoAtual = alunoAtual->proxAluno;
        }

        d = d->prox; // Vai para a próxima classe
    }

    if (!encontrou) {
        printf("Nenhum aluno com o nome '%s' encontrado.\n", nome);
    }
}