#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../interfaces/classe.h"
#include "../interfaces/aluno.h"

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

struct aluno
{
    int matricula;
    char nome[40];
    int idade;
    struct aluno *proxAluno;
    struct aluno *antAluno;
};

int matriculaAluno(
    Classe **classes, 
    int matricula, 
    string nome, 
    int idade,
    uint8_t serie,
    char turma,
    string etapa,
    string nome_professor) 
{
    Classe *classeAtual = *classes;
    while (classeAtual != NULL) {
        if (classeAtual->serie == serie &&
            classeAtual->turma == turma &&
            strcmp(classeAtual->etapa, etapa) == 0 &&
            strcmp(classeAtual->nome_professor, nome_professor) == 0) {
            break;
        }
        classeAtual = classeAtual->prox;
    }

    if (classeAtual == NULL)
        return 1;

    Aluno *novoAluno = (Aluno*) malloc(sizeof(Aluno));
    if (novoAluno == NULL)
        return 1;
    
    novoAluno->matricula = matricula;
    novoAluno->idade = idade;
    strcpy(novoAluno->nome, nome);
    novoAluno->proxAluno = NULL;
    novoAluno->antAluno = NULL;

    if (classeAtual->alunos == NULL) {
        classeAtual->alunos = novoAluno;
    } else {
        Aluno *alunoAtual = classeAtual->alunos;
        while (alunoAtual->proxAluno != NULL) {
            alunoAtual = alunoAtual->proxAluno;
        }

        alunoAtual->proxAluno = novoAluno;
        novoAluno->antAluno = alunoAtual;
    }

    classeAtual->qtd_alunos++;
    return 0;
}


int removeAluno(
    Classe **classes, 
    int matricula,
    uint8_t serie,
    char turma,
    string etapa,
    string nome_professor) 
{
    Classe *classeAtual = *classes;
    while (classeAtual != NULL) {
        if (classeAtual->serie == serie &&
            classeAtual->turma == turma &&
            strcmp(classeAtual->etapa, etapa) == 0 &&
            strcmp(classeAtual->nome_professor, nome_professor) == 0) {
            break;
        }
        classeAtual = classeAtual->prox;
    }
    
    if (classeAtual == NULL || classeAtual->alunos == 0)
        return 1;

    Aluno *alunoAtual = classeAtual->alunos;

    while (alunoAtual != NULL) {
        if (alunoAtual->matricula == matricula) {
            if (alunoAtual->antAluno != NULL)
                alunoAtual->antAluno->proxAluno = alunoAtual->proxAluno;
            else
                classeAtual->alunos = alunoAtual->proxAluno;

            if (alunoAtual->proxAluno != NULL)
                alunoAtual->proxAluno->antAluno = alunoAtual->antAluno;

            free(alunoAtual);
            classeAtual->qtd_alunos--;
            return 0;
        }

        alunoAtual = alunoAtual->proxAluno;
    }
    return 1;
}


void exibir_aluno( 
    Classe *inicio,
	uint8_t serie,
	char turma)
{
	Classe *classe_atual = inicio;
	
	while(classe_atual != NULL) {
		if(classe_atual->turma == turma && classe_atual->serie == serie) {
			printf("Alunos matriculados na classe %d%c:\n", serie, turma);

			Aluno* aluno_atual = classe_atual->aluno;
		    while(aluno_atual != NULL) {
				printf("Nome: %s, Idade: %d, Matricula: %d\n", aluno_atual->nome, 
                        aluno_atual->idade, aluno_atual->matricula);
				aluno_atual = aluno_atual->prox;
			}
			return;
		}
		
		classe_atual = classe_atual->prox;
	}
	    printf("Classe %d%c nao encontrada!\n", serie, turma);
        return;
}