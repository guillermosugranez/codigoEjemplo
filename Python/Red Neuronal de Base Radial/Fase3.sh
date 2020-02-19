#!/bin/bash

echo -e "\nInicio de la Fase 3 del experimento. Comparación de la inicialización de los Centroides con semilla vs Kmeans++.\n"

# vote
# nomnist
# parkinsons
# quake
# sin

#===============================================================================================================================================

# Clasificación
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -e 0.001 -c -l -k
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -e 0.01 -c -l -k

# Regresión
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.05 -k
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.05 -k
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.05 -o 2 -k

#===============================================================================================================================================

# Clasificación
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -e 0.001 -c -l
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -e 0.01 -c -l

# Regresión
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.05
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.05
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.05 -o 2

#===============================================================================================================================================

echo -e "\nFin de la Fase 3 del experimento.\n"