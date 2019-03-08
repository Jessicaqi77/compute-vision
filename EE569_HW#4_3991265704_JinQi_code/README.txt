#EE569 Homework Assignment #4
#Date April 28,2018
#Name: Jin Qi
#ID: 3991265704
#EMAIL: jinqi@usc.edu

Compiled on OS X10.10.5 Spyder platform using python language
IDE: Spyder
Language; python


Problem1_b
File name:Lenet5.py
Function:Recognize MNIST written dataset by applying CNN network based on LeNet5 network structure.
Parameter:
          Learning rate: line 77(rate = 0.001)
          Batch size: line 13(BATCH_SIZE=128)
          Iteration times: line 12(EPOCHS = 50)
         
Problem1_c
File name:improve.py
Function:Recognize MNIST written dataset by applying improved CNN network based on LeNet5 network structure I designed.
Parameter:
          Learning rate: line 79(rate = 0.001)
          Iteration times: line 12(EPOCHS = 50)
          Batch size: line 13(BATCH_SIZE=128)

Problem_2_a_method_a:
File name: saak.py（the main file of the code, others in the Saak file are associated files）
Function: Recognize MNIST written dataset by applying Saak transform. Firstly I using saak transform transfer the data size from N*M to 1*1*C. C is the dimensions of feature. Then apply Ftest and PCA to reduce feature function. Finally I use SVM and RF to classify data separately.
associated .py files all included in Saak file.
Parameter:
          Training data amount: line 414(num_images)
          Testing data amount: line 424( num_test)
          PCA output feature size:line 118(start_dim)
