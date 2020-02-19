#!/bin/bash

echo -e "\nInicio de la Fase 2 del experimento. Valor óptimo del parámetro eta para los problemas de clasificación y determinación de la mejor regularización\n"


# vote
# nomnist
# iris

#===================================================================================================================================

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -c -r 0.05 -e 0.0000000001

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -c -r 0.05 -e 0.0000000001

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -c -r 0.05 -e 0.0000000001

#===================================================================================================================================

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_iris.csv -t ./basesDatosPr3IMC/csv/train_iris.csv -x -r 0.05 -c -l -e 0.0000000001

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_vote.csv -t ./basesDatosPr3IMC/csv/train_vote.csv -x -r 0.05 -c -l -e 0.0000000001

python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.1
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.01
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.0001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.00001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.0000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.00000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.000000001
python3 rbf.py -T ./basesDatosPr3IMC/csv/test_nomnist.csv -t ./basesDatosPr3IMC/csv/train_nomnist.csv -x -r 0.05 -c -l -e 0.0000000001

#===================================================================================================================================

echo -e "\nFin de la Fase 2 del experimento.\n"