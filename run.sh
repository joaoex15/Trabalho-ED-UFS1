#!/bin/sh

gcc main.c ./implementacoes/aluno.c ./implementacoes/classe.c ./implementacoes/projeto.c -o projeto

if [ $? -eq 0 ]; then
    ./projeto
else
    echo "Erro na compilação. Não foi possível executar o programa."
fi