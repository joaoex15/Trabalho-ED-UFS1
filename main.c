#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interfaces/projeto.h"
#include "interfaces/classe.h"
#include "interfaces/aluno.h"

int matricula = 0;

void adicionar_classe(Classe **classes)
{
    uint8_t serie;
    char turma;
    char etapa[20];
    char nome_professor[100];
    limpar_terminal();

    printf("Digite a serie (numero): ");
    if (scanf("%hhu", &serie) != 1)
    {
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    printf("Digite a turma (letra): ");
    if (scanf("%c", &turma) != 1)
    {
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL)
    {
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0';

    printf("Digite o nome do professor: ");
    if (fgets(nome_professor, sizeof(nome_professor), stdin) == NULL)
    {
        printf("Erro ao ler nome do professor.\n");
        return;
    }
    nome_professor[strcspn(nome_professor, "\n")] = '\0';

    limpar_terminal();

    if (classe_insere(classes, serie, turma, etapa, nome_professor))
    {
        exibir_erro();
    }
    else
    {
        printf("Classe adicionada com sucesso!\n");
    }
}

void adicionar_aluno(Classe **classes)
{
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

    printf("Matricula do aluno sera: %d\n", matricula);

    printf("Digite o nome do aluno: ");
    if (fgets(nome, sizeof(nome), stdin) == NULL)
    {
        limpar_terminal();
        printf("Erro ao ler nome do aluno.\n");
        return;
    }
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a idade do aluno: ");
    if (scanf("%d", &idade) != 1)
    {
        limpar_terminal();
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    limpar_terminal();

    printf("Classes existentes no sistema:\n");
    exibir_classes(*classes);

    while (!serieExiste)
    {
        printf("Digite a serie da classe do aluno (numero): ");
        if (scanf("%hhu", &serie) != 1)
        {
            printf("Entrada invalida.\n");
            return;
        }
        getchar();

        classeAtual = *classes;
        while (classeAtual != NULL)
        {
            if (obter_serie_classe(classeAtual) == serie)
            {
                serieExiste = 1;
                break;
            }
            classeAtual = prox_classe(classeAtual);
        }

        if (!serieExiste)
        {
            printf("Serie não encontrada. Por favor, escolha uma serie existente.\n");
        }
    }

    printf("Digite a turma da classe do aluno (letra): ");
    if (scanf("%c", &turma) != 1)
    {
        limpar_terminal();
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa da classe do aluno: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL)
    {
        limpar_terminal();
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0';

    limpar_terminal();
    if (matriculaAluno(classes, matricula, nome, idade, serie, turma, etapa))
    {
        exibir_erro();
    }
    else
    {
        printf("Aluno adicionado com sucesso!\n");
        exibir_classes(*classes);
    }
}

void remover_aluno(Classe **classes)
{
    limpar_terminal();
    printf("Classes existentes:\n");
    exibir_classes(*classes);
    printf("\n");  

    int matricula;
    uint8_t serie;
    char turma;
    char etapa[20];
    char nome_professor[100];

    printf("Digite a serie da classe do aluno (numero): ");
    if (scanf("%hhu", &serie) != 1)
    {
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    printf("Digite a turma da classe do aluno (letra): ");
    if (scanf("%c", &turma) != 1)
    {
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    printf("Digite a etapa da classe do aluno: ");
    if (fgets(etapa, sizeof(etapa), stdin) == NULL)
    {
        printf("Erro ao ler etapa.\n");
        return;
    }
    etapa[strcspn(etapa, "\n")] = '\0';

    Classe *classeAtual = *classes;
    while (classeAtual != NULL) {
        if (obter_serie_classe(classeAtual) == serie &&
            obter_turma_classe(classeAtual) == turma &&
            strcmp(obter_etapa_classe(classeAtual), etapa) == 0) {
            break;
        }
        classeAtual = prox_classe(classeAtual);
    }
    
    if (classeAtual == NULL) {
        limpar_terminal();
        printf("Classe nao encontrada.\n");
        return;
    } else if (obter_alunos_classe(classeAtual) == NULL){
        limpar_terminal();
        printf("Não ha alunos cadastrados nessa classe.\n");
        return;
    }

    exibir_alunos(
        classeAtual,
        obter_serie_classe(classeAtual),
        obter_turma_classe(classeAtual),
        obter_etapa_classe(classeAtual)
    );
    printf("Digite a matricula do aluno a ser removido: ");
    if (scanf("%d", &matricula) != 1) {
        printf("Entrada invalida.\n");
        return;
    }
    getchar();

    limpar_terminal();
    if (removeAluno(classes, matricula, serie, turma, etapa))
    {
        exibir_erro();
    }
    else
    {
        printf("Aluno removido com sucesso!\n");
    }
}

void pesquisar_aluno(Classe *classes)
{
    limpar_terminal();

    int num_matricular;
    printf("Digite o numero  da matricula do  aluno a ser pesquisado: ");
    scanf("%d", &num_matricular);
    pesquisar(classes, num_matricular);
}

void limpar_memoria(Classe *classes)
{
    Classe *classeAtual = classes;
    while (classeAtual != NULL)
    {
        Aluno *alunoAtual = obter_alunos_classe(classeAtual);
        while (alunoAtual != NULL)
        {
            Aluno *tempAluno = alunoAtual;
            alunoAtual = prox_aluno(alunoAtual);
            free(tempAluno);
        }
        Classe *tempClasse = classeAtual;
        classeAtual = prox_classe(classeAtual);
        free(tempClasse);
    }
}

void menu(Classe **classes)
{
    int opcao;
    uint8_t serie;
    char turma;
    char etapa[20];

    do
    {

        printf("\nMENU\n");
        printf("1. Adicionar classe\n");
        printf("2. Adicionar aluno\n");
        printf("3. Remover aluno\n");
        printf("4. Exibir classes\n");
        printf("5. Exibir alunos\n");
        printf("6. Pesquisar aluno\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida.\n");
            continue;
        }
        getchar();
        if (opcao == 4 && *classes == NULL)
        {
            limpar_terminal();
            printf("Nao ha classes cadastradas.\n");
            continue;
        }
        else if ((opcao == 5 || opcao == 6) && *classes == NULL)
        {
            limpar_terminal();
            printf("Nao ha alunos cadastrados.\n");
            continue;
        }

        switch (opcao)
        {
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
            limpar_terminal();
            exibir_classes(*classes);
            break;
        case 5:
            limpar_terminal();
            printf("Digite a serie da classe dos alunos: ");
            if (scanf("%hhu", &serie) != 1)
            {
                printf("Entrada invalida.\n");
                continue;
            }
            getchar();

            printf("Digite a turma da classe dos alunos: ");
            if (scanf("%c", &turma) != 1)
            {
                printf("Entrada invalida.\n");
                continue;
            }
            getchar();

            printf("Digite a etapa da classe dos alunos: ");
            if (scanf("%s", etapa) != 1)
            {
                printf("Entrada invalida.\n");
                continue;
            }
            getchar();

            exibir_alunos(*classes, serie, turma, etapa);
            break;
        case 6:
            pesquisar_aluno(*classes);
            break;
        case 7:
            limpar_terminal();
            printf("Saindo...\n\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 7);
}

int main()
{
    Classe *classes = classe_inicializa();

    menu(&classes);

    limpar_memoria(classes);

    return 0;
}