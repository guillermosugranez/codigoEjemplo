#!/bin/bash

python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 0.01
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 0.1
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 1
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 10
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 100
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 150
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k rbf -C 1 -g 200