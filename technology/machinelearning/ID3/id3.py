# -*- coding: utf-8 -*
from math import log
import operator 

#  计算给定数据集的熵
def calcShannonEnt(dataSet):
    """
    dataset : 待处理的数据集
    """
    numEntries = len(dataSet)  #得到数据集总数
    labelCounts = {}
    
    for featVec in dataSet:
        currentLabel = featVec[-1]  #-1表示最后一列
        
        #这边处理可能不好理解，初始不在字典中先设为0，再加1，以后再字典中就直接加1
        #我们可能处理是if no in dictionary，设为1，else +1
        if currentLabel not in labelCounts.keys():
            labelCounts[currentLabel] = 0        

        labelCounts[currentLabel] +=1
    
    shannonEnt = 0.0
    for key in labelCounts:
        prob = float(labelCounts[key])/numEntries
        shannonEnt -= prob*log(prob,2)
    return shannonEnt
     
    


#按照给定特征划分数据集
def splitDataSet(dataSet,axis,value):
    """
    dataSet  待划分的数据集
    axis     划分数据集的特征--数据的第几列
    value    需要返回的特征值
    """

    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reduceFeatVec = featVec[:axis]#featVec[:axis],axis=0时返回[]
            reduceFeatVec.extend(featVec[axis+1:])
            retDataSet.append(reduceFeatVec)
    return retDataSet

# 选择最好的数据集划分方式
def chooseBestFeatureToSplit(dataSet):

    numFeatures = len(dataSet[0]) - 1   #最后一个是类别，特征数是每一行数目减去1   
    baseEntropy = calcShannonEnt(dataSet)#计算数据集原始信息熵
    bestInfoGain = 0.0; bestFeature = -1
    
    for i in range(numFeatures):       
    
        featList = [example[i] for example in dataSet]#example[i]代表第i列的特征值，在for循环获取这一列的所有值
        uniqueVals = set(featList) #set是一个无序不重复集跟其他语言一样，这样得到i这一列不同的特征值
        newEntropy = 0.0
    
        for value in uniqueVals:#根据不同的特征值分类计算所占百分比
            subDataSet = splitDataSet(dataSet, i, value)
            prob = len(subDataSet)/float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)     
    
        infoGain = baseEntropy - newEntropy #这是信息增益，是两个信息差   
    
        if (infoGain > bestInfoGain):       
            bestInfoGain = infoGain         
            bestFeature = i
    
    return bestFeature 

def majorityCnt(classList):
    classCount={}
    for vote in classList:
        if vote not in classCount.keys():
            classCount[vote] = 0
        classCount[vote] += 1
    #这个sorted跟sort的区别前面提到，这个是重新建了一个数组，sort是在原有的基础上
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(1), reverse=True)
    
    return sortedClassCount[0][0]

def createTree(dataSet,labels):
    classList = [example[-1] for example in dataSet]#得到分类这边是yes no
    
    if classList.count(classList[0]) == len(classList): #这边说明都是同一个属性了，不好再分了
        return classList[0]
    
    if len(dataSet[0]) == 1: 
        return majorityCnt(classList)
    
    bestFeat = chooseBestFeatureToSplit(dataSet)
    bestFeatLabel = labels[bestFeat]
    
    myTree = {bestFeatLabel:{}}
    
    del(labels[bestFeat])
    featValues = [example[bestFeat] for example in dataSet]
    uniqueVals = set(featValues)
    
    for value in uniqueVals:#分类 递归
        subLabels = labels[:]  #:表示全部     
        myTree[bestFeatLabel][value] = createTree(splitDataSet(dataSet, bestFeat, value),subLabels)
    
    return myTree 

def classify(inputTree,featLabels,testVec):
    firstStr = inputTree.keys()[0]
    secondDict = inputTree[firstStr]
    featIndex = featLabels.index(firstStr)
    key = testVec[featIndex]
    valueOfFeat = secondDict[key]
    if isinstance(valueOfFeat, dict): #判断valueOfFeat是不是字典类型，也就是判断是不是还有子集，有在进行递归判断
        classLabel = classify(valueOfFeat, featLabels, testVec)
    else: 
        classLabel = valueOfFeat
    return classLabel


def createDataSet():
    dataSet = [[1, 1, 'yes'],
    [1, 1, 'yes'],
    [1, 0, 'no'],
    [0, 1, 'no'],
    [0, 1, 'no']]
    labels = ['no surfacing','flippers']
    return dataSet, labels
    
#创建数据集
def createDataSetFromTXT(filename):
    dataSet = []; labels = [] 
    fr = open(filename)
    linenumber=0
    for line in fr.readlines():
        line = line.strip()
        listFromLine = line.strip().split()
        lineset = []
        for cel in listFromLine:
            lineset.append(cel)
            
        if(linenumber==0):
            labels=lineset
        else:
            dataSet.append(lineset)
            
        linenumber = linenumber+1
    return dataSet,labels