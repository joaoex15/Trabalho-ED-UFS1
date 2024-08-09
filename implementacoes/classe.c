#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "classe.h"
#include "aluno.h"

struct classe {
    uint8_t serie;
    char turma;
    char etapa[20];
    uint32_t qtd_alunos;
    char nome_professor[100];
    struct classe* prox;
    Aluno* alunos;
};

int classe_insere(
    Classe** primeiraClasse,
    uint8_t serie,
    char turma,
    string etapa,
    string nomeProfessor
)
{
    Classe* novaClasse = (Classe*)malloc(sizeof(Classe));

    if(novaClasse == NULL) return 1;

    novaClasse->serie = serie;
    novaClasse->turma = turma;
    novaClasse->qtd_alunos = 0;
    novaClasse->prox = *primeiraClasse;
    novaClasse->alunos = NULL;
    strcpy(novaClasse->etapa, etapa);
    strcpy(novaClasse->nome_professor, nomeProfessor);

    *primeiraClasse = novaClasse;

    return 0;
}

int classe_remove(Classe* classe, Classe* primeiraClasse)
{
    if(classe->qtd_alunos) return 1;

    Classe* atual = primeiraClasse;
    Classe* anterior = NULL;

    while(atual != classe) {
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = atual->prox;
    free(atual);

    return 0;
}