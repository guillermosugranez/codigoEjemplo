#!/bin/bash

python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 0.01 -g 200
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 0.1 -g 200
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 1 -g 200
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 10 -g 200
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 100 -g 200
python3 practica4.py -t ./BasesDatos/csv/dataset2.csv -k linear -C 1000 -g 200