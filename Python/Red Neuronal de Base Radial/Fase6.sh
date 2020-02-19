#!/bin/bash

echo -e "\nInicio de la Fase 6 del experimento. Valores más pequeños de la ratio para Regresión de parkinsons.\n"

# sin
# quake
# parkinsons

#===============================================================================================================================================

# Regresión

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0002
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0003
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0004
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0005
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0006
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0007
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0008
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.0009

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.002
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.003
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.004
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.005
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.006
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.007
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.008
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.009
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_parkinsons.csv -t ./basesDatosPr3IMC/csv/train_parkinsons.csv -x -r 0.01

#===============================================================================================================================================

echo -e "\nFin de la Fase 6 del experimento.\n"