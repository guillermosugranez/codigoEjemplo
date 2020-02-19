#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 12:37:04 2016

@author: p92supeg
"""

# TODO Incluir todos los import necesarios
import pickle
import os

# Incluidos
import click
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import svm
#import math

import re # Ayuda a generar el nombre del fichero de salida (Expresiones regulares)

# Práctica 3
@click.command()
@click.option('--train_file', '-t', default=None, required=False, help=u'Fichero con los datos de entrenamiento.')
@click.option('--test_file', '-T', default=None, required=False, help=u'Fichero con los datos de test.  [required]')
@click.option('--classification', '-c', default=False, is_flag=True, help=u'Activar para problemas de clasificación.  [default: False]')
@click.option('--n_outputs', '-o', default=1, help=u'Número de variables que se tomarán como salidas (todas al final de la matriz).   [default: 1]')

# KAGGLE
@click.option('--model_file', '-m', default="", show_default=True, help=u'Fichero en el que se guardará o desde el que se cargará el modelo (si existe el flag p).') # KAGGLE
@click.option('--pred', '-p', is_flag=True, default=False, show_default=True, help=u'Activar el modo de predicción.') # KAGGLE

# Practica 4
@click.option('--kern', '-k', default="rbf", show_default=True, help=u'Kernel usado en SVC [default: rbf].')
@click.option('--penalty', '-C', default=200.0, show_default=True, help=u'Valor de la penalización o coste [default: 200.0].')
@click.option('--margen', '-g', default=200.0, show_default=True, help=u'Valor de gamma [default: 200.0].')

def svc(train_file, test_file, classification, n_outputs, model_file, pred, kern, penalty, margen):

	#print("El valor del parámetro C es: %f" %penalty)
	
	# Cargar el dataset
	data = pd.read_csv(train_file, header=None)
	X = data.iloc[:,:-1].values
	y = data.iloc[:,-1].values

	# Entrenar el modelo SVM
	
	svm_model = svm.SVC(kernel=kern, C=penalty, gamma=margen)
	svm_model.fit(X, y)

	# Obtengo el nombre de la base de datos
	nom_bd = nombre_bd(train_file)
	#print(nom_bd)

	# Creo el nombre del fichero de salida
	nombreFicheroSalida = "%s; {C = %.2f _ G = %.2f} _ k = %s" % (nom_bd, penalty, margen, kern) # Sin extension
	#print("El nombre del fichero de salida es: %s" % nombreFicheroSalida)
	nombreFicheroSalidaRuta = "Resultados/" + nombreFicheroSalida
	print("Creado el archivo ", nombreFicheroSalidaRuta)
	#f=open(nombreFicheroSalidaRuta,"w")

	# Representar los puntos
	plt.figure(1)
	plt.clf()
	plt.scatter(X[:, 0], X[:, 1], c=y, zorder=100, cmap=plt.cm.Paired, edgecolors='black')

	# Representar el hiperplano separador
	plt.axis('tight')

	# Extraer límites
	x_min = X[:, 0].min()
	x_max = X[:, 0].max()
	y_min = X[:, 1].min()
	y_max = X[:, 1].max()

	# Crear un grid con todos los puntos y obtener el valor Z devuelto por la SVM
	XX, YY = np.mgrid[x_min:x_max:500j, y_min:y_max:500j]
	Z = svm_model.decision_function(np.c_[XX.ravel(), YY.ravel()])

	# Hacer un plot a color con los resultados
	Z = Z.reshape(XX.shape)
	plt.pcolormesh(XX, YY, Z > 0, cmap=plt.cm.Paired)
	plt.contour(XX, YY, Z, colors=['k', 'k', 'k'], linestyles=['--', '-', '--'], levels=[-.5, 0, .5])

	# Guarda una copia de la imagen
	plt.savefig(nombreFicheroSalidaRuta+'.png')

	# Muestra la imagen
	#plt.show()

	return

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
	svc()
