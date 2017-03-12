#!/usr/bin/env python
# encoding: utf-8
# echo.py

import numpy as NP
from matplotlib import pyplot as PLT

# just create some random data
fnx = lambda : NP.random.randint(3, 10, 10)
y = NP.row_stack((fnx(), fnx(), fnx()))   
# this call to 'cumsum' (cumulative sum), passing in your y data, 
# is necessary to avoid having to manually order the datasets
x = NP.arange(10) 
y_stack = NP.cumsum(y, axis=0)   # a 3x10 array

fig = PLT.figure()
ax1 = fig.add_subplot(111)

ax1.fill_between(x, 0, y_stack[0,:], facecolor="#CC6666", alpha=.7)
ax1.fill_between(x, y_stack[0,:], y_stack[1,:], facecolor="#1DACD6", alpha=.7)
ax1.fill_between(x, y_stack[1,:], y_stack[2,:], facecolor="#6E5160")

PLT.show()