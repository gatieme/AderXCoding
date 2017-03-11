#!/usr/bin/env python
#!encoding=utf-8

#coding:utf-8  
  
import matplotlib  
import matplotlib.pyplot as plt  
  


if __name__ == '__main__':
    for i,color in enumerate("rgby"):  
        plt.subplot(221+i,axisbg=color)  
      
    plt.show()  