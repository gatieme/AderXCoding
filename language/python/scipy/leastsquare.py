#!/usr/bin/env python
#coding=utf-8

import sys

import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as ss 

#  普通最小二乘法
def OridinaryLeastSquareEstimation(xData, yData, ci, test) :
    #  求出回归方程
    length = len(xData)
    xArray = np.array(x)
    xMean = xArray.mean( )            #  计算均值

    yArray = np.array(y)
    yMean = yArray.mean( )            #  计算均值

    print "xMean = %f, yMean = %f" % (xMean, yMean)

    Lxx = 0.0
    Lyy = 0.0
    Lxy = 0.0
    for pos in range(0, length):
        Lxx += np.power(xArray[pos] - xMean, 2)
        Lyy += np.power(yArray[pos] - yMean, 2)
        Lxy += xArray[pos] * yArray[pos]
    #Lxx = xArray.var(ddof = 0) * length   
    Lxy -= length * xMean * yMean
    print "Lxx = %f, Lyy = %f, Lxy = %f" % (Lxx, Lyy, Lxy)
    B1 = Lxy / Lxx
    B0 = yMean - B1 * xMean
    print "B0 = %f, B1 = %f" % (B0, B1)
    print "回归方程 y = %f + %f * x" % (B0, B1)

#def  FStatistic(ci = 0.025)
    #  检验其显著性
    #  求出y的估计值
    yEstimation = []
    for pos in range(0, length):
        yEstimation.append(B1 * xArray[pos] + B0)
    print  yEstimation
    
    St = Lyy
    Sr = np.power(B1, 2) * Lxx
    Se = St - Sr
    print "总平方和St = %f, 回归平方和Sr = %f, 残差平方和Se = %f" % (St, Sr, Se) 
    var = Se / (length - 2)
    print "方差的估计值var = %f, 标准差std = %f" % (var, np.sqrt(var))


    #  计算F统计量
    F = Sr / (Se / (length - 2))
    # F的上a分位点
    Fppf = ss.f.ppf(0.95, dfn = 1, dfd = length - 2)  # F的上a分位点
    print "F统计量 = %f, F的上%f分位数 = %f" % (F, ci, Fppf)
    if F > Fppf :
        print "回归方程效果显著, X与Y呈明显的线性关系"
    else :
        print "回归方程效果不显著, X与Y不呈线性关系"


    # 做点预测
    print "预测x = %d时, y = %f" % (test , B0 + B1 * test)
    print B0 + B1 * test + 2*np.sqrt(var), B0 + B1 * test - 2*np.sqrt(var)
        #  设置图表的信息
    plt.figure(num = 1, figsize = (8, 6))
    plt.title("OridinaryLeastSquareEstimation")
    plt.xlabel("x", size = 14)
    plt.ylabel("y", size = 14)
    
    #ax = fig.add_subplot(111)
    plt.plot(x, y, color='b', linestyle='', marker='.')
    plt.plot(x, yEstimation, color='r', linestyle='-', marker='.')
    plt.legend(loc = "upper left")

    #plt.savefig('cdf.pdf', format = 'pdf')
    plt.savefig('cdf.png', format = 'png')
    #plt.show()

if __name__ == "__main__" :
    x = [ 0.1, 0.3, 0.4, 0.55, 0.70, 0.80, 0.95]
    y = [  15,  18,  19,   21, 22.6, 23.8,   26]
    #x = [1,  2,  3,  4,  5]
    #y = [5, 10, 20, 20, 40]

    OridinaryLeastSquareEstimation(x, y, 0.95, 0.50)
    
