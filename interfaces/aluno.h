// Interface do módulo aluno.h
#ifndef ALUNO_H
#define ALUNO_H

// Tipo abstrato Aluno
typedef struct aluno Aluno;

// Função que matricula um aluno em uma classe caso essa classe seja encontrada.
int matriculaAluno(
    Classe **classes, 
    int matricula, 
    string nome, 
    int idade,
    uint8_t serie,
    char turma,
    string etapa,
    string nome_professor);

// Função que remove um aluno de uma classe caso a classe seja encontrada, a quantidade de alunos da classe seja maior que 0 e o aluno seja encontrado. 
int removeAluno(
    Classe **classes, 
    int matricula,
    uint8_t serie,
    char turma,
    string etapa,
    string nome_professor);

// Função para exibir alunos numa classe.
void exibir_aluno( 
	Classe *inicio,
	int serie,
	char turma);

#endif