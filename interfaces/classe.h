// Interface do módulo classe.c
#ifndef CLASSE_H
#define CLASSE_H

#include <stdint.h>
#include "projeto.h"
#include "aluno.h"

// Tipo abstrato Classe
typedef struct classe Classe;

// Função que inicializa uma lista de classes
Classe *classe_inicializa();

// Função que insere uma nova classe no início da lista de classes
// @return 0 - SUCESSO
// @return 1 - ERRO
int classe_insere(Classe **classes,
                  uint8_t serie,
                  char turma,
                  string etapa,
                  string nomeProfessor);

// Função que remove uma classe existente, se não houver alunos matriculados nela
// @return 0 - SUCESSO
// @return 1 - ERRO
int classe_remove(Classe *classe, Classe **classes);

// Função que matricula um aluno em uma classe caso essa classe seja encontrada.
// @return 0 - SUCESSO
// @return 1 - ERRO
int matriculaAluno(
    Classe **classes,
    int matricula,
    string nome,
    int idade,
    uint8_t serie,
    char turma,
    string etapa);

// Função que remove um aluno de uma classe caso a classe seja encontrada, a quantidade de alunos da classe seja maior que 0 e o aluno seja encontrado.
// @return 0 - SUCESSO
// @return 1 - ERRO
int removeAluno(
    Classe **classes,
    int matricula,
    uint8_t serie,
    char turma,
    string etapa);

// Função para exibir as classes cadastradas
void exibir_classes(Classe *inicio);

// Função para exibir alunos numa classe.
void exibir_alunos(
    Classe *inicio,
    int serie,
    char turma,
    string etapa);

// Função para varrer a lista de classes buscando por um aluno e imprimir as informações da classe encontrada
void Pesquisar(Classe *classe, int matricula);

// Função que retorna a série de uma classe
uint8_t obter_serie_classe(Classe *classe);

// Função que retorna a próxima classe da lista
// @return Classe* - SUCESSO
// @return NULL - Não há próxima classe na lista
Classe *prox_classe(Classe *classe);

// Função para obter a lista de alunos de uma classe
// @return Aluno* - SUCESSO
// @return NULL - lista vazia
Aluno *obter_alunos_classe(Classe *classe);

#endif