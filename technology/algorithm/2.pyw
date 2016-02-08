#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
Created on Jul 12, 2014
python 科学计算学习：numpy快速处理数据测试
@author: 成坚Gatieme
'''


import string
import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':

    # 读取分治算法的数据
    dividefile = open("./divideoutput.txt", 'r')
    linesList = dividefile.readlines()
    dividefile.close()
    #for x in linesList:
    #    print x.split(',')
    datasize = [int(x.split(',')[0]) for x in linesList]
    #print datasize
    divideruntime = [int(x.split(',')[1]) for x in linesList]
    #print runtime

    # 读取扫描算法的数据
    grahamscanfile = open("./grahamscanoutput.txt", 'r')
    linesList = grahamscanfile.readlines()
    grahamscanfile.close()
    grahamscanruntime = [int(x.split(',')[1]) for x in linesList]


    # 读取扫描算法的数据
    bruteforcefile = open("./bruteforceoutput.txt", 'r')
    linesList = bruteforcefile.readlines()
    bruteforcefile.close()
    bruteforceruntime = [int(x.split(',')[1]) for x in linesList]

    #  设置图表的信息
    plt.figure(num = 1, figsize = (8, 6))
    plt.title("ConvexHull")
    plt.xlabel("datesize", size = 14)
    plt.ylabel("runtime", size = 14)

    plt.plot(datasize, bruteforceruntime,    color = 'r', linestyle = '-',  label = "bruteforce")
    plt.plot(datasize, grahamscanruntime, color = 'blue', linestyle = '--', label = "grahamscan")
    plt.plot(datasize, divideruntime,             color = 'black', linestyle = '-', label = "divide")




    #plt.xlim(0, 10000)
    #plt.ylim(0, 10000)
    #plt.title('ConvexHull')

    plt.legend(loc = "upper left")
    plt.savefig('convexhull.png', format='png')
    plt.show()
