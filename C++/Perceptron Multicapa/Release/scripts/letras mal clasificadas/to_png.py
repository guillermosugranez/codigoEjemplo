#!/usr/bin/env python3

import numpy as np
import csv
import matplotlib.pyplot as plt

with open('patrones_mal_clasificados.csv', 'r') as csv_file:
	for data in csv.reader(csv_file):
		# The first column is the label
		label = data[0]
		fname = data[785]
		str(fname)

		# The rest of columns are pixels
		pixels = data[1:785]

		# Make those columns into a array of 8-bits pixels
		# This array will be of 1D with length 784
		# The pixel intensity values are integers from 0 to 255
		pixels = np.array(pixels, dtype='float32')

		# Reshape the array into 28 x 28 array (2-dimensional array)
		pixels = pixels.reshape((28, 28))

		# Plot
		plt.title('Label is {label}'.format(label=label))

		#plt.imshow(pixels, cmap='gray')
		#plt.show()
		# plt.imsave(pixels, fname, cmap='gray', format='svg')
		plt.imsave(label+fname, pixels)

		#break # This stops the loop, I just want to see one