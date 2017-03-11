#!/usr/bin/env python
#!encoding=utf-8

import matplotlib.pyplot as plt  
import numpy as np  
  

  
def f(t):  
    return np.exp(-t) * np.cos(2 * np.pi * t)  
  
if __name__ == '__main__' :
    t1 = np.arange(0, 5, 0.1)  
    t2 = np.arange(0, 5, 0.02)  
      
    plt.figure(12)  
    plt.subplot(221)  
    plt.plot(t1, f(t1), 'bo', t2, f(t2), 'r--')  
      
    plt.subplot(222)  
    plt.plot(t2, np.cos(2 * np.pi * t2), 'r--')  
      
    plt.subplot(212)  
    plt.plot([1, 2, 3, 4], [1, 4, 9, 16])  
      
    plt.show()  