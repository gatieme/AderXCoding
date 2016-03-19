# coding=utf-8
# http://blog.csdn.net/lu597203933/article/details/38445315
from numpy import *

import bayes
if __name__ == "__main__" :
    listOPosts,listClasses = bayes.loadDataSet()
    myVocabList = bayes.createVocabList(listOPosts)
    print myVocabList
    print bayes.setOfWords2Vec(myVocabList,listOPosts[0])   
    print bayes.setOfWords2Vec(myVocabList,listOPosts[3])
    

    trainMatrix,trainCategory = bayes.getTrainMatrix()
    p0V,p1V,pAb = bayes.trainNB0(trainMatrix,trainCategory)
    print p0V
    print p1V
    print pAb
