#!/bin/bash

make clean
make #compiler le compilateur

#s'il y a pas de fichier en argument ou y a trop de fichiers tests en arguments, donner juste un seul fichier test
if [ $# -ne 1 ]
then

    echo Donner un fichier test, un seul !
else
    #executable du compilateur myml
    ./myml  < $1
    echo "--------------Code 3 adresse-----------------"
    gcc -o executable  test.c #compiler de fichier generé par myml
    ./executable
fi
