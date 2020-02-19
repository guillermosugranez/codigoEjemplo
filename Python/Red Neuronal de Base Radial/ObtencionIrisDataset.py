import pandas as pd
import numpy as np
import sys

from sklearn.model_selection import StratifiedShuffleSplit # Para los centroides de clasificacion
from sklearn.preprocessing import MinMaxScaler

def funcion():

	data = pd.read_csv("./basesDatosPr3IMC/csv/iris.csv", header=None)

	print(data.shape)

	sss = StratifiedShuffleSplit(n_splits=1, test_size=0.25)

	#Todas las filas (:) desde la primera columna (0, se puede omitir) hasta -outputs (es decir, sin incluir las variables de salida)
	train_inputs = data.values[:, 0:-1]

	# Normaliza los datos (Aconsejable en algoritmos que usan medidas de distancia)
	df = pd.DataFrame(train_inputs)
	min_max_scaler = MinMaxScaler()
	np_scaled = min_max_scaler.fit_transform(df)
	df_normalized = pd.DataFrame(np_scaled)
	train_inputs = np.array(df_normalized)

	# Conjunto de elementos inverso al anterior
	train_outputs = data.values[:, -1:]

	for train_index, test_index in sss.split(train_inputs, train_outputs):
		#print("TRAIN:", train_index, "CENTROIDES:", centroides_index)
		train_inputs, test_inputs = train_inputs[train_index], train_inputs[test_index]
		train_outputs, test_outputs = train_outputs[train_index], train_outputs[test_index]

	'''
	print(train_inputs.shape)
	print(test_inputs.shape)
	print(train_outputs.shape)
	print(test_outputs.shape)
	'''
	
	f=open("train_iris.csv", "w")

	for i in range(0, train_inputs.shape[0]):
		for j in range(0, train_inputs.shape[1]):
			f.write("%f," %train_inputs[i][j])
		f.write("%s\n" %train_outputs[i])

	f.close()

	f=open("test_iris.csv", "w")
	
	for i in range(0, test_inputs.shape[0]):
		for j in range(0, test_inputs.shape[1]):
			f.write("%f," %test_inputs[i][j])
		f.write("%s\n" %test_outputs[i])

	f.close()

if __name__ == "__main__":
	funcion()
	sys.exit()