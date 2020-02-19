#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 28 12:37:04 2016

@author: Guillermo Sugráñez Pérez
"""

# TODO Incluir todos los import necesarios
import pickle
import os

import click
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math

from sklearn.model_selection import StratifiedShuffleSplit # Para los centroides de clasificacion
from sklearn.cluster import KMeans
from scipy.spatial.distance import cdist, pdist, squareform
from sklearn.linear_model import LogisticRegression
from sklearn.feature_extraction import DictVectorizer # Sirve para hacer que las salidas de clasificación sean 1-J
from sklearn.metrics import accuracy_score # Para el CCR
from sklearn.metrics import mean_squared_error # Para el MSE en regresión
from scipy.linalg import expm # Exponencial de una matriz
from scipy.linalg import inv # Exponencial de una matriz
from sklearn.metrics import brier_score_loss # MSE clasificación
from sklearn.preprocessing import LabelBinarizer # MSE clasificacion
import re # Ayuda a generar el nombre del fichero de salida (Expresiones regulares)
from time import time # importamos la función time para capturar tiempos
from sklearn.metrics import precision_score # CCR Fase 4
from sklearn.metrics import confusion_matrix # Análisis de Resultados

import itertools # Matriz de confusion

# TODO incluir el resto de parámetros...

# Generales
@click.command()
@click.option('--train_file', '-t', default=None, help=u'Fichero con los datos de entrenamiento.')
@click.option('--test_file', '-T', default=None, required=True, help=u'Fichero con los datos de test.  [required]')
@click.option('--n_outputs', '-o', default=1, help=u'Número de variables que se tomarán como salidas (todas al final de la matriz).   [default: 1]')
@click.option('--ratio_rbf', '-r', default=0.1, help=u'Ratio (en tanto por uno) de neuronas RBF con respecto al total de patrones.  [default: 0.1]')

# Clasificacion
@click.option('--eta', '-e', default=0.01, help=u'Valor del parámetro de regularización para la Regresión Logística..   [default: 0.01]')
@click.option('--l2', '-l', default=False, is_flag=True, help=u'Activar para utilizar la regularización de L2 en lugar de la regularización L1 (regresión logística). [default: False]')
@click.option('--classification', '-c', default=False, is_flag=True, help=u'Activar para problemas de clasificación.  [default: False]')

# Parámetros propios añadidos
@click.option('--experiments', '-x', default=False, is_flag=True, help=u'Indica si se van a imprimir los resultados en un fichero de texto para su posterior análisis.   [default: 0]')
@click.option('--kmeans', '-k', default=False, is_flag=True, help=u'Indica si se van usar inicializacion de los centroides con k-means++.   [default: 0]') # Fase 3
@click.option('--zeta', '-z', default=False, is_flag=True, help=u'Indica si se va a tratar un problema de clasificación como si fuera de regresión.   [default: 0]') # Fase 3

# KAGGLE
@click.option('--model_file', '-m', default="", show_default=True, help=u'Fichero en el que se guardará o desde el que se cargará el modelo (si existe el flag p).') # KAGGLE
@click.option('--pred', '-p', is_flag=True, default=False, show_default=True, help=u'Activar el modo de predicción.') # KAGGLE

def entrenar_rbf_total(train_file, test_file, classification, ratio_rbf, l2, eta, n_outputs, model_file, pred, experiments, kmeans, zeta):
	"""
	Modelo de aprendizaje supervisado mediante red neuronal de tipo RBF.
	Ejecución de 5 semillas.
	"""
	if not pred:
		
		# Comprobaciones inciales	

		if train_file is None:
			print("No se ha especificado el conjunto de entrenamiento (-t)")
			return

		if zeta and classification:
			print("ERROR! Las opciones -z y -c son incompatibles entre sí.")
			return

		train_inputs, train_outputs, test_inputs, test_outputs = lectura_datos(train_file, test_file, n_outputs)

		# Nombre de la base de datos (bd) a partir del fichero de test (siempre se especifica conjunto de test)
		patron = re.compile('(test_)([a-zA-Z]+)(.csv)') # aGenero un patrón con lo que quiero buscar
		matcher = patron.search(test_file) # Busca el patrón

		# matcher.group(1) = test_ 
		nombre_bd = matcher.group(2) # Nombre de la base de datos
		# matcher.group(3) = .csv

		# Calcular el Número de RBFs
		num_rbf = train_inputs.shape[0] * ratio_rbf

		# Inicializa los vectores para almacenar los resultados
		train_mses = np.empty(5)
		train_ccrs = np.empty(5)
		test_mses = np.empty(5)
		test_ccrs = np.empty(5)
		v_porcentaje_reduccion = np.empty(5)

		centros = 0
		radios = 0
		kmedias = 0

		if not experiments: # Modo de Ejecución normal.

			# PARA CADA SEMILLA

			for s in range(100,600,100):
				print("-----------")
				print("Semilla: %d" % s)
				print("-----------")
				np.random.seed(s)

				#================================================================================================================

				# ENTRENAR RED RBF

				v_porcentaje_reduccion[s//100-1], logreg, coeficientes, radios, train_matriz_r, kmedias = \
					entrenar_rbf(train_inputs, train_outputs, classification, num_rbf, l2, eta, n_outputs, kmeans, zeta, \
								 model_file and "{}/{}.pickle".format(model_file, s//100) or "")

				#================================================================================================================

				# PREDECIR Y OBTENER MÉTRICAS

				"""
				TODO: Calcular las distancias de los centroides a los patrones de test
					  y la matriz R de test
				"""

				test_distancias = kmedias.transform(test_inputs)
				test_matriz_r = calcular_matriz_r(test_distancias, radios)

				if not classification: # Regresion

					## MÉTRICAS DE TRAIN

					train_ccrs[s//100-1], train_mses[s//100-1] = predecir_regresion(train_matriz_r, coeficientes, train_outputs, zeta)

					# MÉTRICAS DE TEST

					test_ccrs[s//100-1], test_mses[s//100-1] = predecir_regresion(test_matriz_r, coeficientes, test_outputs, zeta)

					#============================================================================

				else: # Clasificacion

					## MÉTRICAS DE TRAIN

					train_ccrs[s//100-1], train_mses[s//100-1] = predecir_clasificacion(train_matriz_r, logreg, train_outputs, nombre_bd, s)

					# MÉTRICAS DE TEST

					test_ccrs[s//100-1], test_mses[s//100-1] = predecir_clasificacion(test_matriz_r, logreg, test_outputs, nombre_bd, s)

					#============================================================================

				# PRESENTACIÓN DE LOS RESULTADOS (por cada semilla)

				print("MSE de entrenamiento: %f" % train_mses[s//100-1])
				print("MSE de test: %f" % test_mses[s//100-1])
				if classification or zeta: # Se activará también para la fase 4 si se indica (zeta)
					print("CCR de entrenamiento: %.2f%%" % train_ccrs[s//100-1])
					print("CCR de test: %.2f%%" % test_ccrs[s//100-1])

			print("*********************")
			print("Resumen de resultados")
			print("*********************")
			print("MSE de entrenamiento: %f +- %f" % (np.mean(train_mses), np.std(train_mses)))
			print("MSE de test: %f +- %f" % (np.mean(test_mses), np.std(test_mses)))
			if classification or zeta:
				print("CCR de entrenamiento: %.2f%% +- %.2f%%" % (np.mean(train_ccrs), np.std(train_ccrs)))
				print("CCR de test: %.2f%% +- %.2f%%" % (np.mean(test_ccrs), np.std(test_ccrs)))

		else: # Modo imprimir resultados para análisis

			# Generar Nombre del fichero de Salida (Solo se reflejarán los parámetros que influyan en el análisis)
			if not classification or zeta:
				nombreFicheroSalida = "%s: {k = %s _ z = %s} _ r = %.4f" % (nombre_bd, kmeans, zeta, ratio_rbf) # Sin extension

			else: # Clasificacion
				nombreFicheroSalida = "%s: {k = %s _ L2 = %s _ } _ r = %.2f _ e = %.10f" % (nombre_bd, kmeans, l2, ratio_rbf, eta) # Sin extension

			# Nota: Si z = True, quiere decir que el problema es de clasificacion, pero se trata como si fuera de regresion.
			#		Si es false quiere decir que el problema es un problema de regresión normal

			print(nombreFicheroSalida)
			nombreFicheroSalidaRuta = "Resultados/" + nombreFicheroSalida
			f=open(nombreFicheroSalidaRuta,"w")

			tiempo_inicial = time()

			for s in range(100,600,100):
				'''
				print("Semilla: %d" % s)
				'''

				# Obtener datos por semilla
				np.random.seed(s)
				v_porcentaje_reduccion[s//100-1], logreg, coeficientes, radios, train_matriz_r, kmedias = \
					entrenar_rbf(train_inputs, train_outputs, classification, num_rbf, l2, eta, n_outputs, kmeans, zeta, \
								 model_file and "{}/{}.pickle".format(model_file, s//100) or "")

				#================================================================================================================

				# PREDECIR Y OBTENER MÉTRICAS

				"""
				TODO: Calcular las distancias de los centroides a los patrones de test
					  y la matriz R de test
				"""

				test_distancias = kmedias.transform(test_inputs)
				test_matriz_r = calcular_matriz_r(test_distancias, radios)

				if not classification: # Regresion

					## MÉTRICAS DE TRAIN

					train_ccrs[s//100-1], train_mses[s//100-1] = predecir_regresion(train_matriz_r, coeficientes, train_outputs, zeta)

					# MÉTRICAS DE TEST

					test_ccrs[s//100-1], test_mses[s//100-1] = predecir_regresion(test_matriz_r, coeficientes, test_outputs, zeta)

					#============================================================================

				else: # Clasificacion

					## MÉTRICAS DE TRAIN

					train_ccrs[s//100-1], train_mses[s//100-1] = predecir_clasificacion(train_matriz_r, logreg, train_outputs, nombre_bd, s)

					# MÉTRICAS DE TEST

					test_ccrs[s//100-1], test_mses[s//100-1] = predecir_clasificacion(test_matriz_r, logreg, test_outputs, nombre_bd, s)

					#============================================================================

			tiempo_final = time()
			 
			tiempo_ejecucion = tiempo_final - tiempo_inicial

			print("Número de RBFs utilizadas: %d" % num_rbf)
			print("El tiempo de ejecucion fue: %.5f segundos.\n" % tiempo_ejecucion) #En segundos

			# Calcular la media y desviación típica considerando todas las semillas
			if classification or zeta:
				# Incluye el CCR (De entrenamiento y test)
				f.write("%s;%f;%f;%f;%f;%.2f;%.2f;%.2f;%.2f;%d;%d;%.5f\n" % (nombreFicheroSalida, np.mean(train_mses), np.std(train_mses), np.mean(test_mses), np.std(test_mses), np.mean(train_ccrs), np.std(train_ccrs), np.mean(test_ccrs), np.std(test_ccrs), num_rbf, np.mean(v_porcentaje_reduccion), tiempo_ejecucion))
			else:
				# Solo MSE (De entrenamiento y test)
				f.write("%s;%f;%f;%f;%f;%d;%.5f\n" % (nombreFicheroSalida, np.mean(train_mses), np.std(train_mses), np.mean(test_mses), np.std(test_mses), num_rbf, tiempo_ejecucion))

			f.close() # Se cierra el archivo

	else:
		# KAGGLE
		if model_file is None:
			print("No se ha indicado un fichero que contenga el modelo (-m).")
			return

		# Obtener predicciones para el conjunto de test
		predictions = predict(test_file, model_file)

		# Imprimir las predicciones en formato csv
		print("Id,Category")
		for prediction, index in zip(predictions, range(len(predictions))):
			s = ""
			s += str(index)

			if isinstance(prediction, np.ndarray):
				for output in prediction:
					s += ",{}".format(output)
			else:
				s += ",{}".format(int(prediction))

			print(s)

def softmax(x):
    """Compute softmax values for each sets of scores in x."""
    e_x = np.exp(x - np.max(x))
    return e_x / e_x.sum()

def entrenar_rbf(train_inputs, train_outputs, classification, num_rbf, l2, eta, n_outputs, kmeans, zeta, model_file=""):
	""" Modelo de aprendizaje supervisado mediante red neuronal de tipo RBF.
		Una única ejecución.
		Recibe los siguientes parámetros:
			- train_file: nombre del fichero de entrenamiento.
			- test_file: nombre del fichero de test.
			- classification: True si el problema es de clasificacion.
			- ratio_rbf: Ratio (en tanto por uno) de neuronas RBF con 
			  respecto al total de patrones.
			- l2: True si queremos utilizar L2 para la Regresión Logística. 
			  False si queremos usar L1 (para regresión logística).
			- eta: valor del parámetro de regularización para la Regresión 
			  Logística.
			- n_outputs: número de variables que se tomarán como salidas 
			  (todas al final de la matriz).
		Devuelve:
			- train_mse: Error de tipo Mean Squared Error en entrenamiento. 
			  En el caso de clasificación, calcularemos el MSE de las 
			  probabilidades predichas frente a las objetivo.
			- test_mse: Error de tipo Mean Squared Error en test. 
			  En el caso de clasificación, calcularemos el MSE de las 
			  probabilidades predichas frente a las objetivo.
			- train_ccr: Error de clasificación en entrenamiento. 
			  En el caso de regresión, devolvemos un cero.
			- test_ccr: Error de clasificación en test. 
			  En el caso de regresión, devolvemos un cero.
	"""

	coeficientes = 0
	logreg = 0
	porcentaje_reduccion = 0 # Aqui guardamos el número de parámetros de la regresión logística

	#=======================================================================================

	## APRENDIZAJE DE LOS PESOS DE CAPA DE ENTRADA A CAPA OCULTA

	# 1) Aplicacion del algoritmo de clustering para determinar los centros ()
	kmedias, centros = clustering(classification, train_inputs, train_outputs, num_rbf, kmeans)
	train_distancias = cdist(train_inputs, centros)

	## APRENDIZAJE DE LOS PESOS DE CAPA OCULTA A CAPA DE SALIDA (Pesos de salida)

	# 2)  Ajuste de los radios de las RBF (Necesario para el paso siguiente)
	radios = calcular_radios(centros, num_rbf)

	# 3) Cálculo de la Matriz R (Pesos)
	train_matriz_r = calcular_matriz_r(train_distancias, radios)

	if classification:
		porcentaje_reduccion, logreg = logreg_clasificacion(train_matriz_r, train_outputs, eta, l2)
	else:
		coeficientes = invertir_matriz_regresion(train_matriz_r, train_outputs)

	#================================================================================================

	# # # # KAGGLE # # # #
	if model_file != "":
		save_obj = {
			'classification': classification,
			'radios': radios,
			'kmedias': kmedias
		}
		if not classification:
			save_obj['coeficientes'] = coeficientes
		else:
			save_obj['logreg'] = logreg

		dir = os.path.dirname(model_file)
		if not os.path.isdir(dir):
			os.makedirs(dir)

		with open(model_file, 'wb') as f:
			pickle.dump(save_obj, f)

	# # # # # # # # # # #

	return porcentaje_reduccion, logreg, coeficientes, radios, train_matriz_r, kmedias

	
def lectura_datos(fichero_train, fichero_test, outputs):
	""" Realiza la lectura de datos.
		Recibe los siguientes parámetros:
			- fichero_train: nombre del fichero de entrenamiento.
			- fichero_test: nombre del fichero de test.
			- outputs: número de variables que se tomarán como salidas 
			  (todas al final de la matriz).
		Devuelve:
			- train_inputs: matriz con las variables de entrada de 
			  entrenamiento.
			- train_outputs: matriz con las variables de salida de 
			  entrenamiento.
			- test_inputs: matriz con las variables de entrada de 
			  test.
			- test_outputs: matriz con las variables de salida de 
			  test.
	"""

	#TODO: Completar el código de la función

	# En este caso no existe una primera fila con el número de patrones, entradas y salidas.
		# Se especifica el número de salidas con la variable outputs

	# Primero recojo todos los datos en matrices auxiliares
	train_df = pd.read_csv(fichero_train, header=None)
	test_df = pd.read_csv(fichero_test, header=None)

	#Todas las filas (:) desde la primera columna (0, se puede omitir) hasta -outputs (es decir, sin incluir las variables de salida)
	train_inputs = train_df.values[:, 0:-outputs]
	# Conjunto de elementos inverso al anterior
	train_outputs = train_df.values[:, -outputs:]

	# Para el test
	test_inputs = test_df.values[:, 0:-outputs]
	# Conjunto de elementos inverso al anterior
	test_outputs = test_df.values[:, -outputs:]

	return train_inputs, train_outputs, test_inputs, test_outputs

def inicializar_centroides_clas(train_inputs, train_outputs, num_rbf):
	""" Inicializa los centroides para el caso de clasificación.
		Debe elegir los patrones de forma estratificada, manteniendo
		la proporción de patrones por clase.
		Recibe los siguientes parámetros:
			- train_inputs: matriz con las variables de entrada de 
			  entrenamiento.
			- train_outputs: matriz con las variables de salida de 
			  entrenamiento.
			- num_rbf: número de neuronas de tipo RBF.
		Devuelve:
			- centroides: matriz con todos los centroides iniciales
						  (num_rbf x num_entradas).
	"""
	
	#TODO: Completar el código de la función

	'''
		- StratifiedShuffleSplit
			- Te separa lo que le des (entradas y salidas) en dos grupos estratificados (cada uno)
			- El tamaño de cada grupo resultante se puede especificar por separado
			- Si solo se especifica el tamaño de un grupo, el tamaño del otro será el complementario
			- Te devuelve índices
	'''

	# Los centroides, junto con los radios forman las neuronas de RBF
	# A partir de los radios, de los centroides y los patrones que van llegando (salidas de la capa de entrada), podemos ir cualculando las salidas (pesos) de la capa oculta a capa de salida
	# Hay que separar el conjunto de train (sus entradas y sus salidas) en dos grupos estratificados

	# Numero total de patrones
	num_patrones = train_inputs.shape[0]

	# Se define el conjunto de test (en la funcionc StratifiedShuffleSplit) como el conjunto de los centroides
	num_patrones_centroides = int(num_rbf)

	num_patrones_train = num_patrones - num_patrones_centroides # El conjunto mas grande

	# Esto inicializa el objeto sss con la configuracion para poder usar los metodos
	sss = StratifiedShuffleSplit(n_splits=1, train_size=num_patrones_train, test_size=num_patrones_centroides)

	# En esta funcion, el train_outputs solo sirve para poder estratificar correctamente los dos conjuntos. No se tiene en cuenta para nada mas

	for train_index, centroides_index in sss.split(train_inputs, train_outputs):
		#print("TRAIN:", train_index, "CENTROIDES:", centroides_index)
		train_inputs, centroides = train_inputs[train_index], train_inputs[centroides_index]
		train_outputs, centroides_outputs = train_outputs[train_index], train_outputs[centroides_index]

	'''
	print("El numero de centroides es: %d" % centroides.shape[0])
	for indice in range(len(centroides)):
		print(centroides[indice], centroides_outputs[indice])
	'''

	'''
	print("El numero de train es: %d" % train_outputs.shape[0])
	for indice in range(len(train_inputs)):
		print(train_inputs[indice], train_outputs[indice])
	'''

	'''
		- El cálculo de los centroides no afecta al conjunto de entrenamiento.
		- Todo lo que se haga dentro de la función (con los conjuntos de datos), no se verá reflejado fuera de ella
		- En vez de pasar argumentos por referencia se devuelven con el return.
	'''
	
	#print("\nLOS CENTROIDES SON\n")
	#print(centroides)

	#print("\nLOS TRAIN SON\n")
	#print(train_inputs)

	return centroides

def clustering(classification, train_inputs, train_outputs, num_rbf, kmeans):
	""" Realiza el proceso de clustering. En el caso de la clasificación, se
		deben escoger los centroides usando inicializar_centroides_clas()
		En el caso de la regresión, se escogen aleatoriamente.
		Recibe los siguientes parámetros:
			- classification: True si el problema es de classification.
			- train_inputs: matriz con las variables de entrada de 
			  entrenamiento.
			- train_outputs: matriz con las variables de salida de 
			  entrenamiento.
			- num_rbf: número de neuronas de tipo RBF.
		Devuelve:
			- kmedias: objeto de tipo sklearn.cluster.KMeans ya entrenado.
			- distancias: matriz (num_patrones x num_rbf) con la distancia 
			  desde cada patrón hasta cada rbf.
			- centros: matriz (num_rbf x num_entradas) con los centroides 
			  obtenidos tras el proceso de clustering.
	"""

	#TODO: Completar el código de la función

	'''
	- Los resultados dependen de la inicializacion de los centroides:
		- En regresion, escogemos aleatoriamente n1 patrones.
		- En clasificacion, escogemos aleatoriamente, y de forma estratificada, n1 patrones.

	- array[i:j,:]: Devuelve otro ndarray con la submatriz correspondiente a 
					las filas desde la i hasta la j-1 y todas las columnas.

	- Cuando hago el shuffle, se tiene en cuenta la semilla al principio
	'''
	# =================================================================================================

	# SEPARO EL CONJUNTO DE ENTREANAMIENTO EN 2 CONJUNTOS SEPARADOS (Inicializar centroides)

	if not classification: # Regresion
		
		# Primero se cambia el orden de los patrones del conjunto de entrenamiento de forma aleatoria
		np.random.shuffle(train_inputs)

		# Ahora se cogen los patrones correspondientes como centroides
		centroides = train_inputs[:int(num_rbf) , :]
		centroides_outputs = train_outputs[:int(num_rbf) , :]

		#train_inputs = train_inputs[int(num_rbf): , :]
		#train_outputs = train_outputs[int(num_rbf): , :]

	else: # Clasificacion
		centroides = inicializar_centroides_clas(train_inputs, train_outputs, num_rbf)

	'''
	#print("El numero de centroides es: %d" % centroides.shape[0])
	#print("El numero de centroides_outputs es: %d" % centroides_outputs.shape[0])
	#print("El numero de train_inputs es: %d" % train_inputs.shape[0])
	#print("El numero de train_outputs es: %d" % train_outputs.shape[0])

	#print(centroides)
	#print(centroides_outputs)
	#print(train_inputs)
	#print(train_outputs)
	'''

	# =================================================================================================

	# K-MEANS

	'''
	- Se le pasa los centroides inciales (centroides)
	- n_init = 1	-	Significa que los centroides solo se inicializaran una vez
	- 
	'''

	#print(centroides.shape)
	#print(train_inputs.shape)
	#print(centroides)

	if kmeans:
		kmedias = KMeans(n_init=1, max_iter=500, n_clusters=int(num_rbf), init="k-means++").fit(train_inputs)
	else:
		kmedias = KMeans(n_init=1, max_iter=500, n_clusters=int(num_rbf), init=centroides).fit(train_inputs)

	centroides = (kmedias.cluster_centers_)

	#print(centroides)
	# print(kmedias)

	# print("\nCentroides\n")
	# print(centroides)
	# print("\nKmedias\n")
	# print(kmedias.cluster_centers_)

	# =================================================================================================

	# matriz (num_patrones x num_rbf) con la distancia desde cada patrón hasta cada rbf.

	'''
	* cdist(a1, a2) Calcula la distancia entre cada par de elementos de las dos colecciones de entrada.
		- Es como pdist pero con dos arrays
	- La distancia de un patrón a la RBF esta determinada por la distancia a su centroide

	'''

	##print("El numero de distancias es: %d" % distancias.shape[0])
	#print(distancias)

	'''
	EJEMPLOS

	-PDIST

	points = np.array([[0,1],[1,1],[3,5], [15, 5]])
	dist_condensed = pdist(points)
	print(dist_condensed)
	dist = squareform(dist_condensed)
	
	- CDIST

	points_1 = np.array([[1,2],[1,3]])
	points_5 = np.array([[5,6],[5,7],[5,8]])

	distancias = cdist(points_1, points_5)
	print(distancias)
	'''

	# =================================================================================================

	return kmedias, centroides

def calcular_radios(centroides, num_rbf):
	""" Calcula el valor de los radios tras el clustering.
		Recibe los siguientes parámetros:
			- centros: conjunto de centroides.
			- num_rbf: número de neuronas de tipo RBF.
		Devuelve:
			- radios: vector (num_rbf) con el radio de cada RBF.
	"""

	'''
	Ejemplo
	x = np.array([[3, 3], [5, 10], [11, 12]])

	d_condensed = pdist(x)
	d = squareform(d_condensed)
	s_distancias = np.sum(d, axis=1)
	r = s_distancias / (2 * (int(x.shape[0]) -1))

	print(r)
	'''

	dist_condensed = pdist(centroides)
	dist = squareform(dist_condensed)

	## print("El numero de filas es: %d" % dist.shape[0])

	# Crea un array con la suma de todas las distancias a todos los demas centroides
	suma_distancias = np.sum(dist, axis=1)

	## Ahora hay que dividir cada distancia por el numero de centroides menos 1 y por la mitad
	radios = suma_distancias / (2 * (int(centroides.shape[0]) -1))
	#print(radios)

	#TODO: Completar el código de la función

	return radios

def calcular_matriz_r(distancias, radios):
	""" Devuelve el valor de activación de cada neurona para cada patrón 
		(matriz R de salidas de la RBF en la presentación)
		Recibe los siguientes parámetros:
			- distancias: matriz (num_patrones x num_rbf) con la distancia 
			  desde cada patrón hasta cada rbf.
			- radios: array (num_rbf) con el radio de cada RBF.
		Devuelve:
			- matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
			  activación (out) de cada RBF para cada patrón. Además, añadimos
			  al final, en la última columna, un vector con todos los 
			  valores a 1, que actuará como sesgo.
	"""

	#TODO: Completar el código de la función

	a = distancias ** 2 # Matriz de distancia elevada al cuadrado (numerador)
	b = radios ** 2 # Matriz de radios elevada al cuadrado (denominador)
	b = -2 * b # Multiplico por dos y hago negativo

	aux = a / b
	aux = np.exp(aux)

	#aux = np.random.rand(3,5)

	#print("Matriz r sin modificar")
	#print(aux)

	# Hay que añadir una columna de 1 al final

	N = aux.shape[0] # Dimension de la matriz
	#print("Numero de filas %d" % N)
	M = aux.shape[1] # Dimension de la matriz
	#print("Numero de columnas %d" % M)
	matriz_r = np.ones((N,M+1))
	#print(matriz_r)
	matriz_r[:,:-1] = aux

	return matriz_r

def invertir_matriz_regresion(matriz_r, train_outputs):
	""" Devuelve el vector de coeficientes obtenidos para el caso de la 
		regresión (matriz beta en las diapositivas)
		Recibe los siguientes parámetros:
			- matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
			  activación (out) de cada RBF para cada patrón. Además, añadimos
			  al final, en la última columna, un vector con todos los 
			  valores a 1, que actuará como sesgo.
			- train_outputs: matriz con las variables de salida de 
			  entrenamiento.
		Devuelve:
			- coeficientes: vector (num_rbf+1) con el valor del sesgo y del 
			  coeficiente de salida para cada rbf.
	"""

	#TODO: Completar el código de la función

	# Ejemplo simple de correcto funcionamiento

	'''
	A = np.array([[1,0],[0,1],[-1,1]])

	print("Matriz Original")
	print(A)

	T = A.T
	print("Transpuesta")
	print(T)

	R = np.dot(T,A)

	I = np.linalg.inv(R)
	print("Inversa")
	print(I)

	R = np.dot(I,T)
	print("Pseudoinversa")
	print(R)

	M = np.dot(R,A)
	print("Comprobacion")
	print(M)
	'''
	
	A = matriz_r

	#print("Matriz Original")
	#print(A)

	T = A.T
	#print("Transpuesta")
	#print(T)

	#R = np.dot(T,A)
	R = np.dot(T,A)

	I = np.linalg.pinv(R)
	#print("Inversa")
	#print(I)

	R = np.dot(I,T)
	#print("Pseudoinversa")
	#print(R)

	M = np.dot(R, A)
	#print("Comprobacion")

	# Da el mismo resultado:
	#R = np.linalg.pinv(matriz_r) # Hago la Pseudoinversa

	coeficientes = np.dot(R, train_outputs)

	return coeficientes

def logreg_clasificacion(matriz_r, train_outputs, eta, l2):
	""" Devuelve el objeto de tipo regresión logística obtenido a partir de la
		matriz R.
		Recibe los siguientes parámetros:
			- matriz_r: matriz (num_patrones x (num_rbf+1)) con el valor de 
			  activación (out) de cada RBF para cada patrón. Además, añadimos
			  al final, en la última columna, un vector con todos los 
			  valores a 1, que actuará como sesgo.
			- train_outputs: matriz con las variables de salida de 
			  entrenamiento.
			- eta: valor del parámetro de regularización para la Regresión 
			  Logística.
			- l2: True si queremos utilizar L2 para la Regresión Logística. 
			  False si queremos usar L1.
		Devuelve:
			- logreg: objeto de tipo sklearn.linear_model.LogisticRegression ya
			  entrenado.
	"""

	#TODO: Completar el código de la función

	# Creación del modelo de regresión logística
	if l2:
		logreg = LogisticRegression(penalty='l2', C=1/eta, solver='liblinear').fit(matriz_r, train_outputs.ravel()) # Ajustamos el modelo a los datos de entrenamiento
	else:
		logreg = LogisticRegression(penalty='l1', C=1/eta, solver='liblinear').fit(matriz_r, train_outputs.ravel()) # Liblinear es el que permite L2 y L1

	# Cuenta el número de coeficientes de la regresión logística
	C = logreg.coef_

	num_parametros = 0 # Inicialización (Contador a 0)
	for i in range(0, C.shape[0]): # Recorre numero de filas
		for j in range(0, C.shape[1]): # Recorre numero de columnas
			if abs(C[i][j]) >= 0.00001: # Solo se tienen en cuenta los que superen este margen (10^-5)
				num_parametros += 1

	total_num_parametros = C.shape[0] * C.shape[1]
	#print("El numero total de coeficientes (R.logistica) debe ser %d" %(total_num_parametros), C.shape, "y es: %d" % num_parametros)
	#print(num_parametros)

	porcentaje_reduccion = 100 - ((num_parametros / total_num_parametros) * 100) # Indica qué porcentaje de parámetros se ha reducido después de la regularización

	# .ravel() no hace nada difrente, solo que si no lo pongo salta un error

	return porcentaje_reduccion, logreg


def predict(test_file, model_file):
	""" Calcula las predicciones para un conjunto de test que recibe como parámetro. Para ello, utiliza un fichero que
	contiene un modelo guardado.
	:param test_file: fichero csv (separado por comas) que contiene los datos de test.
	:param model_file: fichero de pickle que contiene el modelo guardado.
	:return: las predicciones para la variable de salida del conjunto de datos proporcionado.
	"""
	test_df = pd.read_csv(test_file, header=None)
	test_inputs = test_df.values[:, :]

	with open(model_file, 'rb') as f:
		saved_data = pickle.load(f)

	radios = saved_data['radios']
	classification = saved_data['classification']
	kmedias = saved_data['kmedias']

	test_distancias = kmedias.transform(test_inputs)
	test_r = calcular_matriz_r(test_distancias, radios)

	if classification:
		logreg = saved_data['logreg']
		test_predictions = logreg.predict(test_r)
	else:
		coeficientes = saved_data['coeficientes']
		test_predictions = np.dot(test_r, coeficientes)

	return test_predictions

def predecir_regresion(matriz_r, coeficientes, outputs, zeta):

	"""
	TODO: Obtener las predicciones de entrenamiento y de test y calcular
		  el CCR. Calcular también el MSE, comparando las probabilidades 
		  obtenidas y las probabilidades objetivo
	"""

	CCR = 0
	MSE = 0
	predicciones = 0

	#============================================================================

	# CCR (No tiene sentido en regresión)

	# MSE
	predicciones = np.dot(matriz_r, coeficientes)
	MSE = mean_squared_error(y_true=outputs, y_pred=predicciones)

	'''
	plt.figure()
	# Dibujar una línea
	plt.plot(predicciones);

	# Guardar la matriz en un archivo
	plt.savefig('regresion.png')
	'''
	

	# CCR (Solo para la Fase 4 del Experimento)
	if zeta:
		# Prueba adicional de la fase 4 del experimento
		predicciones = predicciones.astype(int) # Aproxima al número entero más próximo cada predicción del array
		outputs = outputs.astype(int) # Aproxima al número entero más próximo cada predicción del array
		CCR = accuracy_score(y_true=outputs, y_pred=predicciones) * 100 # Calcula el CCR

		'''
		class_names = ['A', 'B', 'C', 'D', 'E', 'F']

		CM_test = confusion_matrix(y_true=outputs.ravel(), y_pred=predicciones)
		np.set_printoptions(precision=2)

		# Dibujar la matriz
		plt.figure()
		plot_confusion_matrix(CM_test, classes=class_names, title='Matriz de Confusión')

		# Guardar la matriz en un archivo
		plt.savefig('Nomnist_Confusion_Matrix_.png')
		'''

	return  CCR, MSE

def predecir_clasificacion(matriz_r, logreg, outputs, nombre_bd, semilla):

	"""
	TODO: Obtener las predicciones de entrenamiento y de test y calcular
		  el CCR. Calcular también el MSE, comparando las probabilidades 
		  obtenidas y las probabilidades objetivo
	"""

	CCR = 0
	MSE = 0
	predicciones = 0
	#============================================================================

	# CCR
	predicciones = logreg.predict_proba(matriz_r) # uso predict_proba para poder utilizar mas adelante softmax (divide la etiqueta clase entre los posibles valores de clase)
	CCR = logreg.score(matriz_r, outputs)*100

	# ANÁLISIS DE RESULTADOS. MATRIZ DE CONFUSIÓN

	# Solo si la base de datos es nomnist:
	if nombre_bd == 'nomnist':

		# Apuntar las etiquetas de clase
		class_names = ['A', 'B', 'C', 'D', 'E', 'F'] 

		# Calcular la matriz
		CM = confusion_matrix(y_true=outputs.astype(int).ravel(), y_pred=predicciones.argmax(axis=1))
		np.set_printoptions(precision=2)

		# Dibujar la matriz
		plt.figure()
		plot_confusion_matrix(CM, classes=class_names, title='Matriz de Confusión')

		# Guardar la matriz en un archivo
		plt.savefig('Nomnist_Confusion_Matrix_'+str(semilla)+'.png')

	# MSE

	# Hay dos casos posibles (clasificacion binaria o multiclase)
	if predicciones.shape[1] == 2:
		predicciones = logreg.predict(matriz_r) # Caso de clasificacion binaria
	else:
		for x in range(0,len(predicciones)):
			predicciones[x] = softmax(predicciones[x]) # Hago que la suma de las probabilidades de pertenecer a cada una de las clases sea igual a 1 (consistencia probabilistica)
		
		# Transformo las salidas a representacion 1 - j
		lb = LabelBinarizer()
		outputs = lb.fit_transform(outputs)

	# Calculo la puntación de Brier con la función del MSE
	MSE = mean_squared_error(y_true=outputs, y_pred=predicciones)

	return CCR, MSE

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
	entrenar_rbf_total()
	sys.exit()
