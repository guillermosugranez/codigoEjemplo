#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@author: p92supeg
"""

import pandas as pd
import numpy as np
import sys

from sklearn.model_selection import StratifiedShuffleSplit # Divide de forma estratificada
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import StandardScaler # Estandarización de los datos

import re # Ayuda a generar el nombre del fichero de salida (Expresiones regulares)

import click
import pickle
import os

# Práctica 3
@click.command()
@click.option('--file', '-f', default=None, required=True, help=u'Fichero dataset listo para dividir.')
@click.option('--test', '-t', default=0.2, show_default=True, help=u'Ratio en tanto por uno de patrones que formarán parte del conjunto de Test [default: 0.2].')
@click.option('--standardization', '-s', default=False, is_flag=True, help=u'Indica si se van a estandarizar los datos. [default: False]') # Fase 3


def dividir_dataset(file, test, standardization):

	data = pd.read_csv(file, header=None)

	# Estandarizar los datos (entradas)
	if standardization:
		scaler = StandardScaler()
		scaler.fit(data)
		scaler.transform(data)

	# Separa las entradas de las salidas
	#Todas las filas (:) desde la primera columna (0, se puede omitir) hasta -outputs (es decir, sin incluir las variables de salida)
	X = data.values[:, 0:-1]

	# Conjunto de elementos inverso al anterior
	y = data.values[:, -1:]

	# Divide de forma estratificada los datos en conjunto de test y train
	sss = StratifiedShuffleSplit(n_splits=1, test_size=test)

	for train_index, test_index in sss.split(X, y):
		train_inputs, test_inputs = X[train_index], X[test_index]
		train_outputs, test_outputs = y[train_index], y[test_index]

	# Comprobacion de forma
	'''
	print(data.shape)
	
	print("train_inputs shape: ",train_inputs.shape)
	print("test_inputs shape: ",test_inputs.shape)
	print("train_outputs shape: ",train_outputs.shape)
	print("test_outputs shape: ",test_outputs.shape)
	'''
	
	nom_bd = nombre_bd(file)

	f=open("./BasesDatos/csv/train_"+nom_bd+".csv", "w")

	for i in range(0, train_inputs.shape[0]):
		for j in range(0, train_inputs.shape[1]):
			f.write("%f," %train_inputs[i][j])
		f.write("%d\n" %train_outputs[i])

	f.close()

	f=open("./BasesDatos/csv/test_"+nom_bd+".csv", "w")
	
	for i in range(0, test_inputs.shape[0]):
		for j in range(0, test_inputs.shape[1]):
			f.write("%f," %test_inputs[i][j])
		f.write("%d\n" %test_outputs[i])

	f.close()

def nombre_bd(file):

	""" Devuelve el nombre de la base de datos a partir de uno de sus ficheros
	:param file: fichero csv (separado por comas) que contiene los datos de test o train.
	:return: el nombre de la base de datos
	"""

	# Nombre de la base de datos (bd) a partir del fichero de test (siempre se especifica conjunto de test)
	patron = re.compile('(.*)(/csv/)(.*)(.csv)') # Genero un patrón con lo que quiero buscar
	matcher = patron.search(file) # Busca el patrón

	#antes_1 = matcher.group(1) # = 
	#antes_2 = matcher.group(2) # 
	nombre_bd = matcher.group(3) # Nombre de la base de datos
	#despues_4 = matcher.group(4) # = .csv

	#print("1: ", antes_1, "2: ", antes_2, "3: ",nombre_bd, "4: ", despues_4)

	return nombre_bd

if __name__ == "__main__":
	dividir_dataset()
	sys.exit()