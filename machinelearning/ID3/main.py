# coding=utf-8
import id3

import id3plot
import pickle
if __name__ == "__main__" :
  #  myDat,labels = id3.createDataSet()
  #  print myDat

  #  shan = id3.calcShannonEnt(myDat)
  #  print shan

  #  myTree = id3.createTree(myDat,labels)
  #  print myTree

  #  id3plot.createPlot(myTree)

    data, labels = id3.createDataSetFromTXT("dataset.txt")
    print "data is ", data
    print "label is", labels

    #计算给定数据集的香农熵
    shan = id3.calcShannonEnt(data)
    print shan

    #选择最好的数据集划分方式
    col = id3.chooseBestFeatureToSplit(data)
    print col
    Tree = id3.createTree(data, labels)
    print Tree

    id3plot.createPlot(Tree)