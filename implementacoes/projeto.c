#include <stdio.h>
#include <stdlib.h>
#include "../interfaces/projeto.h"

void exibir_erro()
{
    printf("Ocorreu um erro ao realizar essa operação!\n");
}

void limpar_terminal()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}