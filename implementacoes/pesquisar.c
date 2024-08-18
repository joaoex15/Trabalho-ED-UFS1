#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aluno.c"
#include "../interfaces/classe.h"
#include "../interfaces/aluno.h"




void Pesquisar(struct classe *d, char *nome) {
    struct aluno *alunoatual;
    int suc = 0;

    // Percorre a lista de classes
    while (d != NULL) {
        alunoatual = d->alunos;

        // Percorre a lista de alunos na classe atual
        while (alunoatual != NULL) {
            if (strcmp(alunoatual->nome, nome) == 0) {
                printf("Aluno encontrado: %s\n", alunoatual->nome);
                printf("Matrícula: %d\n", alunoatual->matricula);
                printf("Idade: %d\n", alunoatual->idade);
                printf("Série: %u\n", d->serie);
                printf("Turma: %c\n", d->turma);
                printf("Etapa: %s\n", d->etapa);
                printf("Nome do Professor: %s\n", d->nome_professor);
                suc = 1;
            }
            alunoatual = alunoatual->proxAluno;
        }

        d = d->prox;
    }

    if (!suc) {
        printf("Aluno %s não encontrado.\n", nome);
    }
}
