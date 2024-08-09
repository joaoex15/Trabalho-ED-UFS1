//Interface do módulo classe.c
#ifndef CLASSE_H
#define CLASSE_H

#include "projeto.h"

//Tipo abstrato Classe
typedef struct classe Classe;

//Função que insere uma nova classe no início da lista de classes
//@return 0 - SUCESSO
//@return 1 - ERRO
int classe_insere(Classe** primeiraClasse,
                  uint8_t serie,
                  char turma,
                  string etapa,
                  string nomeProfessor
                );

//Função que remove uma classe existente, se não houver alunos matriculados nela
//@return 0 - SUCESSO
//@return 1 - ERRO
int classe_remove(Classe* classe, Classe* primeiraClasse);

#endif