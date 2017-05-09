#!/usr/bin/python
# -*- coding: <encoding name> -*-

#  [Python Matplot中文显示完美解决方案](http://blog.csdn.net/kesalin/article/details/71214038)
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontManager
from pylab import mpl
import subprocess

def get_matplot_zh_font():
    fm = FontManager()
    mat_fonts = set(f.name for f in fm.ttflist)

    output = subprocess.check_output('fc-list :lang=zh -f "%{family}\n"', shell=True)
    zh_fonts = set(f.split(',', 1)[0] for f in output.split('\n'))
    available = list(mat_fonts & zh_fonts)

    print '*' * 10, 'avaliable', '*' * 10
    for f in available:
        print f
    return available

def set_matplot_zh_font():
    available = get_matplot_zh_font()
    if len(available) > 0:
        mpl.rcParams['font.sans-serif'] = [available[0]]
        mpl.rcParams['axes.unicode_minus'] = False


if __name__ == "__main__" :
    get_matplot_zh_font( )
