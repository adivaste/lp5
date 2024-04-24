#boston housing assign6

import numpy as np
import tensorflow as tf
from tensorflow import keras
from sklearn import preprocessing
from keras import models,layers

(X_train, Y_train), (X_test, Y_test) = keras.datasets.boston_housing.load_data()


print("Training data shape:", X_train.shape)
print("Test data shape:", X_test.shape)
print("Train output data shape:", Y_train.shape)
print("Actual Test output data shape:", Y_test.shape)

##Normalize the data

X_train=preprocessing.normalize(X_train)
X_test=preprocessing.normalize(X_test)

#Model Building

model = models.Sequential()
model.add(layers.Dense(128,activation='relu',input_shape= X_train[0].shape))
model.add(layers.Dense(64,activation='relu'))
model.add(layers.Dense(32,activation='relu'))
model.add(layers.Dense(1))

model.summary()

model.compile(optimizer='rmsprop',loss='mse',metrics=['mae'])

history = model.fit(X_train,Y_train,epochs=2,batch_size=1,verbose=1,validation_data=(X_test,Y_test))

results = model.evaluate(X_test, Y_test)
print(results)
# Predict prices for the test set
# predictions = model.predict(X_test)

# import numpy as np

# Predict prices for the entire dataset
# all_predictions = model.predict(X_test)  # or X_train if you want to predict on the training set

# Calculate the average predicted price
average_predicted_price = np.mean(model.predict(X_test))

print("Average predicted price:", average_predicted_price)
