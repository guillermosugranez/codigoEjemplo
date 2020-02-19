#!/bin/bash

python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.02 -g 0.02
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.02 -g 0.2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.02 -g 2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.02 -g 200

python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.2 -g 0.02
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.2 -g 0.2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.2 -g 2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 0.2 -g 200

python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 2 -g 0.02
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 2 -g 0.2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 2 -g 2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 2 -g 200

python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 200 -g 0.02
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 200 -g 0.2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 200 -g 2
python3 practica4.py -t ./BasesDatos/csv/dataset3.csv -k rbf -C 200 -g 200