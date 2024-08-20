// Interface do módulo aluno.h
#ifndef ALUNO_H
#define ALUNO_H

#include "projeto.h"

// Tipo abstrato Aluno
typedef struct aluno Aluno;

// Função que cria um registro de aluno e retorna um ponteiro para ele
// @return Aluno* - SUCESSO
// @return NULL - ERRO
Aluno *cria_aluno(int matricula, int idade, string nome);

// Função para obter o próximo aluno da turma
// @return Aluno* - SUCESSO
// @return NULL - Não há um pŕoximo aluno na turma
Aluno *prox_aluno(Aluno *aluno);

// Função para obter o aluno anterior da turma
// @return Aluno* - SUCESSO
// @return NULL - Não há um aluno anterior na turma
Aluno *ant_aluno(Aluno *aluno);

// Função que define o próximo aluno da lista
void definir_prox_aluno(Aluno *aluno, Aluno *proxAluno);

// Função que define o aluno anterior da lista
void definir_ant_aluno(Aluno *aluno, Aluno *antAluno);

// Função para obter a matrícula de um aluno
int matricula_aluno(Aluno *aluno);

// Função para imprimir informações do aluno
void imprime_aluno(Aluno *aluno);

#endif