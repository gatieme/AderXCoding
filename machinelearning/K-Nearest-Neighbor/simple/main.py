# coding=utf-8
import knn  
from numpy import *   
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__" :
    
    # create the dataset
    dataSet, labels = knn.createDataSet()  
    print dataSet
    # set the K value of KNN
    k = 3  
    # classify using kNN 
    ## test1 data(1.2, 1.0)
    testX = array([1.2, 1.0])   

    outputLabel = knn.kNNClassify(testX, dataSet, labels, k)  
    print "Your input is:", testX, "and classified to class: ", outputLabel  
    ## test1  data(0.1, 0.3)
    testX = array([0.1, 0.3])  
    outputLabel = knn.kNNClassify(testX, dataSet, labels, k)  
    print "Your input is:", testX, "and classified to class: ", outputLabel  
    
    