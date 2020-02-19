#!/bin/bash

echo -e "\nInicio de la Fase 1 del experimento. Obteniendo la mejor Arquitectura para todas las Bases de Datos.\n"

# vote
# nomnist
# parkinsons
# quake
# sin

# Regresión
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.05
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.10
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.20
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.25
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.50

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.05
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.10
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.20
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.25
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.50

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.05 -o 2
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.10 -o 2
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.20 -o 2
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.25 -o 2
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.50 -o 2


# Clasificacion

# Regularización L1
# eta = 10^-5

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.10 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.20 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.25 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.50 -e 0.00001 -c

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.10 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.20 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.25 -e 0.00001 -c
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.50 -e 0.00001 -c


echo -e "\nFin de la Fase 1 del experimento.\n"
