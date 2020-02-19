#!/bin/bash

echo -e "\nPregunta 9. Comprobando si el score se modifica cuando generamos un conjunto de train/test diferente \n"

python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s
python3 simular_svm.py -t ./BasesDatos/csv/train_dataset3.csv -T ./BasesDatos/csv/test_dataset3.csv
python3 dividir_dataset.py -f ./BasesDatos/csv/dataset3.csv -s

echo -e "\nFin del experimento.\n"