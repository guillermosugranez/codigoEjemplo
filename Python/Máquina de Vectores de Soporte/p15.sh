#!/bin/bash

echo -e "\nPregunta 15. Probando mejor configuración de C para SPAM \n"

python3 simular_svm.py -t ./BasesDatos/csv/train_spam.csv -T ./BasesDatos/csv/test_spam.csv -K linear -C 0.01 -g 100
python3 simular_svm.py -t ./BasesDatos/csv/train_spam.csv -T ./BasesDatos/csv/test_spam.csv -K linear -C 0.1 -g 100
python3 simular_svm.py -t ./BasesDatos/csv/train_spam.csv -T ./BasesDatos/csv/test_spam.csv -K linear -C 1 -g 100
python3 simular_svm.py -t ./BasesDatos/csv/train_spam.csv -T ./BasesDatos/csv/test_spam.csv -K linear -C 10 -g 100

echo -e "\nFin del experimento.\n"