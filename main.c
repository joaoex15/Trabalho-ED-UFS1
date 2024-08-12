#include <stdio.h>
#include "interfaces/projeto.h"
#include "interfaces/classe.h"
#include "interfaces/aluno.h"

int main()
{
    // TESTE DOS METODOS CRIADOS
    Classe *classes = classe_inicializa();

    if (classe_insere(&classes, 1, 'A', "Médio", "Mai Ly"))
        exibir_erro();
    if (classe_insere(&classes, 2, 'B', "Fundamental II", "João"))
        exibir_erro();
    // FIM DO TESTE

    return 0;
}