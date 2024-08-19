// Interface do módulo classe.c
#ifndef CLASSE_H
#define CLASSE_H

#include "projeto.h"
#include <stdint.h>
#include "aluno.h"
// Tipo abstrato Classe
typedef struct classe Classe;
typedef struct aluno Aluno;

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

// Função que inicializa uma lista de classes
Classe *classe_inicializa();

// Função que insere uma nova classe no início da lista de classes
//@return 0 - SUCESSO
//@return 1 - ERRO
int classe_insere(Classe **classes,
                  uint8_t serie,
                  char turma,
                  string etapa,
                  string nomeProfessor);

// Função que remove uma classe existente, se não houver alunos matriculados nela
//@return 0 - SUCESSO
//@return 1 - ERRO
int classe_remove(Classe *classe, Classe **classes);

// TODO: Adicionar Validações
	
// Função para exibir as classes cadastradas
void exibir_classes(Classe *inicio);

#endif