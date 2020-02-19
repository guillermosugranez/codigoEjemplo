#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
@author: p92supeg
"""

import pandas as pd
import numpy as np
import sys
from time import time # importamos la función time para capturar tiempos

#import re # Ayuda a generar el nombre del fichero de salida (Expresiones regulares)

# Sickit-Learn
from sklearn import svm
from sklearn.model_selection import StratifiedShuffleSplit # Para los centroides de clasificacion
from sklearn.model_selection import GridSearchCV # Pregunta 9

import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix # Análisis de Resultados
import itertools # Matriz de confusion

import click
import pickle
import os

# Práctica 3
@click.command()
@click.option('--train_file', '-t', default=None, required=True, help=u'Fichero de train listo para entrenar.')
@click.option('--test_file', '-T', default=None, required=True, help=u'Fichero con los datos de test.  [required]')

@click.option('--kernel', '-K', default="rbf", show_default=True, help=u'Kernel usado en SVC [default: rbf].')
@click.option('--penalty', '-C', default=200.0, show_default=True, help=u'Valor de la penalización o coste [default: 200.0].')
@click.option('--gamma', '-g', default="auto", show_default=True, help=u'Valor de gamma [default: 200.0].')

# Pregunta 10 en adelante
@click.option('--kfold', '-k', default=10, show_default=True, help=u'Valor k del k-fold [default: 10].')

def simular_svm(train_file, test_file, kernel, penalty, gamma, kfold):
	
	tiempo_inicial = time()
	''' 
	Realiza el proceso completo de entrenamiento y test de una manera u otra según lo requiera la pregunta
	'''

	train_inputs, train_outputs = lectura_dataset(train_file)
	test_inputs, test_outputs = lectura_dataset(test_file)

	#=====================================================================================================================================

	
	# PREGUNTA 9 y 15
	model = entrenar_svm(train_inputs, train_outputs, kernel, penalty, float(gamma))
	#print(model.get_params())
	score, predicciones = predecir(model, test_inputs, test_outputs)

	#print(predicciones)
	#print(test_inputs)

	print("C = ", penalty)
	
	#=====================================================================================================================================
	
	'''
	# PREGUNTA 10 y 11

	Cs = np.logspace(-5, 15, num=11, base=2)
	Gs = np.logspace(-15, 3, num=9, base=2)

	optimo = GridSearchCV(estimator=svm.SVC(), param_grid=dict(C=Cs, gamma=Gs), n_jobs=-1, cv=5)
	optimo.fit(train_inputs, train_outputs.ravel())

	score = optimo.score(test_inputs, test_outputs)

	print(optimo.best_estimator_)

	'''
	#=====================================================================================================================================

	# PREGUNTA 12
	'''
	C_mejor_modelo, gamma_mejor_modelo = mejores_parámetros(train_inputs, train_outputs, kernel, kfold)

	print("\nLa mejor configuracion para predecir este dataset es: C = %f\tgamma = %f" % (float(C_mejor_modelo), float(gamma_mejor_modelo)))

	mejor_modelo = entrenar_svm(train_inputs, train_outputs, kernel, C_mejor_modelo, gamma_mejor_modelo) # Entreno el modelo con la mejor configuracion
	score = predecir(mejor_modelo, test_inputs, test_outputs)
	
	'''
	#=====================================================================================================================================
	# Pregunta 16

	class_names = ("No", "Si")

	# Calcular la matriz
	CM = confusion_matrix(y_true=test_outputs.astype(int).ravel(), y_pred=predicciones)
	np.set_printoptions(precision=2)

	# Dibujar la matriz
	plt.figure()
	plot_confusion_matrix(CM, classes=class_names, title='Matriz de Confusión')

	# Guardar la matriz en un archivo
	plt.savefig('Spam_confusion_matrix.png')

	#=====================================================================================================================================
	print("\nEl score de la prediccion fue:",score*100)

	tiempo_final = time()
	tiempo_ejecucion = tiempo_final - tiempo_inicial
	
	print("El tiempo de ejecucion del experimento fue: ", tiempo_ejecucion, " segundos.")

	return

def lectura_dataset(file, outputs=1):
	""" Realiza la lectura de datos.
		Recibe los siguientes parámetros:
			- file: nombre del fichero de entrenamiento.
		Devuelve:
			- inputs: matriz con las variables de entrada
			- outputs: matriz con las variables de salida
	"""

	#TODO: Completar el código de la función

	# En este caso no existe una primera fila con el número de patrones, entradas y salidas.
		# Se especifica el número de salidas con la variable outputs

	# Primero recojo todos los datos en matrices auxiliares
	df = pd.read_csv(file, header=None)

	#Todas las filas (:) desde la primera columna (0, se puede omitir) hasta -outputs (es decir, sin incluir las variables de salida)
	inputs = df.values[:, 0:-outputs]
	# Conjunto de elementos inverso al anterior
	outputs = df.values[:, -outputs:]

	# Comprobacion de forma
	'''
	print("X shape: ",X.shape)
	print("y shape: ",y.shape)
	'''

	return inputs, outputs

def entrenar_svm(train_inputs, train_outputs, kernel, penalty, gamma):

	svm_model = svm.SVC(kernel=kernel, C=penalty, gamma=gamma)
	svm_model.fit(train_inputs, train_outputs.ravel())

	return svm_model

def predecir(model, test_inputs, test_outputs):

	predicciones = model.predict(test_inputs)
	score = model.score(test_inputs, test_outputs)

	return score, predicciones 

def mejores_parámetros(train_inputs, train_outputs, kernel, kfold):

	sss = StratifiedShuffleSplit(n_splits=kfold, test_size=0.2, random_state=0)
	#print(sss.get_n_splits(train_inputs, train_outputs))

	puntuaciones = np.empty(kfold)

	Cs = np.logspace(-5, 15, num=11, base=2)
	Gs = np.logspace(-15, 3, num=9, base=2)

	max_puntuacion = 0
	mejor_modelo = 0
	C_mejor_modelo = 0
	gamma_mejor_modelo = 0

	xv, yv = np.meshgrid(Cs, Gs)
	for i in range(0, len(xv)):
		for j in range(0, len(yv)):
			#print(xv[i][j], yv[i][j])

			# Una configuración (kfold)
			it = 0

			# Barre todas las posibilidades de particion con la configuracion xv[i][j], yv[i][j]...
			for train_index, test_index in sss.split(train_inputs, train_outputs):
				#print("TRAIN:", train_index, "TEST:", test_index)
				X_train, X_test = train_inputs[train_index], train_inputs[test_index]
				y_train, y_test = train_outputs[train_index], train_outputs[test_index]
				model = entrenar_svm(X_train, y_train, kernel, xv[i][j], yv[i][j])
				puntuaciones[it] = predecir(model, X_test, y_test)
				#print("\nEl score de la prediccion fue:",puntuaciones[it]*100)

				it += 1

			# ... para luego hacer la media y...
			score = np.mean(puntuaciones)
			#print("El score medio de la prediccion es: ",score)

			# Si supera la mejor puntuacion media...
			if score > max_puntuacion:
				max_puntuacion = score # Cambia la mejor puntuacion, ...
				C_mejor_modelo = xv[i][j] # Apunto el coste usado y 
				gamma_mejor_modelo = yv[i][j] # gamma usado

	return C_mejor_modelo, gamma_mejor_modelo

def plot_confusion_matrix(cm, classes, normalize=False, title='Confusion matrix', cmap=plt.cm.Greens):
	
	"""
	This function prints and plots the confusion matrix.
	Normalization can be applied by setting `normalize=True`.
	"""

	'''
	if normalize:
		cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
		print("Normalized confusion matrix")
	else:
		print('Confusion matrix, without normalization')

	print(cm)
	'''

	plt.imshow(cm, interpolation='nearest', cmap=cmap)
	plt.title(title)
	plt.colorbar()
	tick_marks = np.arange(len(classes))
	plt.xticks(tick_marks, classes)
	plt.yticks(tick_marks, classes)

	fmt = '.2f' if normalize else 'd'
	thresh = cm.max() / 2.
	for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
		plt.text(j, i, format(cm[i, j], fmt), horizontalalignment="center", color="white" if cm[i, j] > thresh else "black")

	plt.ylabel('True label')
	plt.xlabel('Predicted label')
	plt.tight_layout()
	return

if __name__ == "__main__":
	simular_svm()
	sys.exit()