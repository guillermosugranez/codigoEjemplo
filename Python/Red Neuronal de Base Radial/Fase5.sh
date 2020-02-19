#!/bin/bash

echo -e "\nInicio de la Fase 5 del experimento. Valores más pequeños de la ratio para Regresión.\n"

# sin
# quake
# parkinsons

#===============================================================================================================================================

# Regresión

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.02
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.03
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.04
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_sin.csv -t ./basesDatosPr3IMC/csv/train_sin.csv -x -r 0.05

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.02
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.03
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.04
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_quake.csv -t ./basesDatosPr3IMC/csv/train_quake.csv -x -r 0.05

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.02
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.03
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.04
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.05

#===============================================================================================================================================

echo -e "\nFin de la Fase 5 del experimento.\n"