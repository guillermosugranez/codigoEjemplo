#!/bin/bash

./practica2 -t ../dat/train_xor.dat -T ../dat/test_xor.dat -i 1000 -l 1 -h 75 -e 0.7 -m 1.0 -v 0.0 -d 1 -s -f
./practica2 -t ../dat/train_xor.dat -T ../dat/test_xor.dat -i 1000 -l 1 -h 75 -e 0.7 -m 1.0 -v 0.0 -d 1 -s -f -o

./practica2 -t ../dat/train_vote.dat -T ../dat/test_vote.dat -i 1000 -l 2 -h 10 -e 0.7 -m 1.0 -v 0.1 -d 1 -s -f
./practica2 -t ../dat/train_vote.dat -T ../dat/test_vote.dat -i 1000 -l 2 -h 10 -e 0.7 -m 1.0 -v 0.1 -d 1 -s -f -o

./practica2 -t ../dat/train_nomnist.dat -T ../dat/test_nomnist.dat -i 500 -l 1 -h 50 -e 0.7 -m 1.0 -v 0.1 -d 1 -s -f
./practica2 -t ../dat/train_nomnist.dat -T ../dat/test_nomnist.dat -i 500 -l 1 -h 50 -e 0.7 -m 1.0 -v 0.1 -d 1 -s -f -o