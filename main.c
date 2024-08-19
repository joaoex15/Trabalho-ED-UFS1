#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces/projeto.h"
#include "interfaces/classe.h"
#include "interfaces/aluno.h"
#include "implementacoes/classe.c"
#include "implementacoes/pesquisar.c"
#include "implementacoes/aluno.c"
#include "implementacoes/projeto.c"



int matricula = 0;

void limpar_terminal() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux
    #endif
}

void adicionar_classe(Classe **classes) {
    uint8_t serie;
    char turma;
    char etapa[20];
    char nome_professor[100];
    limpar_terminal();

    printf("Digite a série (número): ");
    if (scanf("%hhu", &serie) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar(); // Consumir o caractere '\n' deixado pelo scanf

    printf("Digite a turma (letra): ");
    if (scanf("%c", &turma) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL) {
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0'; // Remover o '\n' da string

    printf("Digite o nome do professor: ");
    if (fgets(nome_professor, sizeof(nome_professor), stdin) == NULL) {
        printf("Erro ao ler nome do professor.\n");
        return;
    }
    nome_professor[strcspn(nome_professor, "\n")] = '\0';

    limpar_terminal();

    if (classe_insere(classes, serie, turma, etapa, nome_professor)) {
        exibir_erro();
    } else {
        printf("Classe adicionada com sucesso!\n");
    }
}

void adicionar_aluno(Classe **classes) {
    limpar_terminal();
    matricula++;
    int idade;
    char nome[40];
    uint8_t serie;
    char turma;
    char etapa[20];
    char nome_professor[100];
    Classe *classeAtual;
    int serieExiste = 0;

    printf("A matrícula do aluno será %d\n", matricula);
    
    printf("Digite o nome do aluno: ");
    if (fgets(nome, sizeof(nome), stdin) == NULL) {
        printf("Erro ao ler nome do aluno.\n");
        return;
    }
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a idade do aluno: ");
    if (scanf("%d", &idade) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    limpar_terminal();

    printf("Classes existentes no sistema:\n");
    exibir_classes(*classes);

    while (!serieExiste) {
        printf("Digite a série da classe do aluno (número): ");
        if (scanf("%hhu", &serie) != 1) {
            printf("Entrada inválida.\n");
            return;
        }
        getchar(); // Consumir o caractere '\n' deixado pelo scanf

        classeAtual = *classes;
        while (classeAtual != NULL) {
            if (classeAtual->serie == serie) {
                serieExiste = 1;
                break;
            }
            classeAtual = classeAtual->prox;
        }

        if (!serieExiste) {
            printf("Série não encontrada. Por favor, escolha uma série existente.\n");
        }
    }

    printf("Digite a turma da classe do aluno (letra): ");
    if (scanf("%c", &turma) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa da classe do aluno: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL) {
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0'; // Remover o '\n' da string

    printf("Digite o nome do professor da classe do aluno: ");
    if (fgets(nome_professor, sizeof(nome_professor), stdin) == NULL) {
        printf("Erro ao ler nome do professor.\n");
        return;
    }
    nome_professor[strcspn(nome_professor, "\n")] = '\0';

    if (matriculaAluno(classes, matricula, nome, idade, serie, turma, etapa, nome_professor)) {
        exibir_erro();
    } else {
        printf("Aluno adicionado com sucesso!\n");
        exibir_classes(*classes); // Exibir classes e alunos após adicionar um aluno
    }
}

void remover_aluno(Classe **classes) {
    limpar_terminal();

    int matricula;
    uint8_t serie;
    char turma;
    char etapa[20];
    char nome_professor[100];

    printf("Digite a matrícula do aluno a ser removido: ");
    if (scanf("%d", &matricula) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar(); // Consumir o caractere '\n' deixado pelo scanf

    printf("Digite a série da classe do aluno (número): ");
    if (scanf("%hhu", &serie) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    printf("Digite a turma da classe do aluno (letra): ");
    if (scanf("%c", &turma) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa da classe do aluno: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL) {
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0';

    printf("Digite o nome do professor da classe do aluno: ");
    if (fgets(nome_professor, sizeof(nome_professor), stdin) == NULL) {
        printf("Erro ao ler nome do professor.\n");
        return;
    }
    nome_professor[strcspn(nome_professor, "\n")] = '\0';

    if (removeAluno(classes, matricula, serie, turma, etapa, nome_professor)) {
        exibir_erro();
    } else {
        printf("Aluno removido com sucesso!\n");
    }
}



void pesquisar_aluno(Classe *classes) {
    limpar_terminal();

    char nome[40];
    printf("Digite o nome do aluno a ser pesquisado: ");
    if (fgets(nome, sizeof(nome), stdin) == NULL) {
        printf("Erro ao ler nome do aluno.\n");
        return;
    }
    nome[strcspn(nome, "\n")] = '\0';

    Pesquisar(classes, nome);
}

void limpar_memoria(Classe *classes) {
    Classe *classeAtual = classes;
    while (classeAtual != NULL) {
        Aluno *alunoAtual = classeAtual->alunos;
        while (alunoAtual != NULL) {
            Aluno *tempAluno = alunoAtual;
            alunoAtual = alunoAtual->proxAluno;
            free(tempAluno);
        }
        Classe *tempClasse = classeAtual;
        classeAtual = classeAtual->prox;
        free(tempClasse);
    }
}

void menu(Classe **classes) {
    int opcao;
    uint8_t serie;
    char turma;

    do {

        printf("\nMENU\n");
        printf("1. Adicionar classe\n");
        printf("2. Adicionar aluno\n");
        printf("3. Remover aluno\n");
        printf("4. Exibir classes\n");
        printf("5. Exibir alunos\n");
        printf("6. Pesquisar aluno\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            continue;
        }
        getchar(); // Consumir o caractere '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                adicionar_classe(classes);
                break;
            case 2:
                adicionar_aluno(classes);
                break;
            case 3:
                remover_aluno(classes);
                break;
            case 4:
                exibir_classes(*classes);
                break;
            case 5:
                limpar_terminal();
                printf("Digite a série da classe dos alunos: ");
                if (scanf("%hhu", &serie) != 1) {
                    printf("Entrada inválida.\n");
                    continue;
                }
                getchar(); // Consumir o caractere '\n' deixado pelo scanf

                printf("Digite a turma da classe dos alunos: ");
                if (scanf("%c", &turma) != 1) {
                    printf("Entrada inválida.\n");
                    continue;
                }
                getchar(); // Consumir o caractere '\n' deixado pelo scanf

                exibir_aluno(*classes, serie, turma);
                break;
            case 6:
                pesquisar_aluno(*classes);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 7);
}

int main() {
    Classe *classes = classe_inicializa();

    menu(&classes);

    limpar_memoria(classes);

    return 0;
}