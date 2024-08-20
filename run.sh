#!/bin/sh

gcc main.c ./implementacoes/aluno.c ./implementacoes/classe.c ./implementacoes/projeto.c -o main

if [ $? -eq 0 ]; then
    ./main
else
    echo "Erro na compilação. Não foi possível executar o programa."
fi