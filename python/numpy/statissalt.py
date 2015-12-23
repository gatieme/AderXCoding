#!coding:utf-8

import re
import sys
import urllib2
import matplotlib.pyplot as plt
import numpy as np


# 从xml中匹配出数据
def ReSaltStatisData( ):

    # 这段HTML代码是从博客列表页面中摘取出来的单个博客的信息， 我们要从中摘取出
    file = open("./data.xml", 'r')
    linesList = file.read()
    file.close()
    #print linesList.decode('GBK').encode('utf-8')

    reData = r'''<record>\s*<field name=".*?">(.*?)</field>\s*<field name=".*?">(\d*).*?(\d*)</field>\s*<field name=".*?">(.*?)</field>\s*</record>'''

    pattern = re.compile(reData, re.S)
    myItems = re.findall(pattern, linesList)

    saltData = []
    #print len(myItems) / 4
    #print myItems
    for item in myItems:
        name = item[0].replace("\n", "")
        year = item[1].replace("\n", "")
        month = item[2].replace("\n", "")
        data = float(item[3].replace("\n", ""))
        #print name, year, month, data
        saltData.append(data)

    #print len(saltData)
    return sorted(saltData[0:36])


#  经验累计分布函数cumulative distribution function
def ShowCDFPlot(data, step):
    """
    step  步长
    """
    minData = int(min(data) / 100) * 100
    maxData = int(max(data) / 100 + 1) * 100
    print "min = ", minData, "max = ", maxData
    #print "min = ", int(minData / 100) * 100, "max = ", int(maxData / 100 + 1) * 100


    #  生成X轴的数据，从minData~maxData，步长为step
    xdata = range(minData, maxData + step,  step)

    #  生成y的数据，Count(x < xdata)
    ydata = []
    pos = 0
    count = 0
    for num in data:
        #print "num = ", num, "data = ", xdata[pos]
        if num < xdata[pos]:  #  如果当前的元素比下标小
            count = count + 1
        else:
            ydata.append(count)
            #print "Count(X < %f) = %d [pos = %d]" % (xdata[pos], count, pos)
            pos = pos + 1
    while pos < len(xdata):
        ydata.append(count)
        pos += 1

    print "xdata =", xdata
    print "ydata =", ydata

    #  设置图表的信息
    plt.figure(num = 1, figsize = (8, 6))
    plt.title("Cumulative Distribution Function")
    plt.xlabel("alt", size = 14)
    plt.ylabel("count", size = 14)

    plt.plot(xdata, ydata, color = 'r', linestyle = '-', label = "cdf")

    plt.legend(loc = "upper left")
    #plt.savefig('cdf.pdf', format = 'pdf')
    plt.savefig('cdf.png', format = 'png')
    #plt.show()


#  直方图(Histogram
#def ShowHistogramPlot(data):

    ax1 = plt.subplots(1, figsize = (8, 4))
    plt.title("Histogram")
    plt.legend(loc = "upper left")
    plt.savefig('hist.png', format = 'png')

    plt.hist(data)

#def ShowBoxPlot(data):

    ax2 = plt.subplots(1, figsize = (8, 4))
    plt.boxplot(data)

    plt.title("Boxplot")
    plt.legend(loc = "upper left")
    plt.savefig('box.png', format = 'png')

    plt.show()

#  主函数
if __name__ == "__main__" :

    reload(sys)
    sys.setdefaultencoding("utf-8")

    saltData = ReSaltStatisData( )
    print saltData

    ShowCDFPlot(saltData, 50)
    #ShowHistogramPlot(saltData)
    #ShowBoxPlot(saltData)
