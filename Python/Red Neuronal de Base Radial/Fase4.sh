#!/bin/bash

echo -e "\nInicio de la Fase 4 del experimento. Probando los problemas de Clasificación como si fueran de Regresión.\n"

# vote
# nomnist
# iris

#===============================================================================================================================================

# Clasificación
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -e 0.001 -r 0.05 -c -l
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -e 0.01 -r 0.05 -c -l
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -e 0.01 -r 0.05 -c -l

# Regresión
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -z
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -z
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -z

#===============================================================================================================================================

echo -e "\nFin de la Fase 4 del experimento.\n"