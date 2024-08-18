#include <stdio.h>
#include "interfaces/projeto.h"
#include "interfaces/classe.h"
#include "interfaces/aluno.h"
#include "implementacoes/pesquisar.c"
#include "implementacoes/classe.c"
#include "implementacoes/projeto.c"
#include "implementacoes/aluno.c"
int main()
{
    // TESTE DOS METODOS CRIADOS
    Classe *classes = classe_inicializa();

    if (classe_insere(&classes, 1, 'A', "Médio", "Mai Ly"))
        exibir_erro();
    if (classe_insere(&classes, 2, 'B', "Fundamental II", "João"))
        exibir_erro();
    printf("ola mundo");
    // FIM DO TESTE

    return 0;
}