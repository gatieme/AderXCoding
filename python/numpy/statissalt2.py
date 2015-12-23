#!coding:utf-8

import re
import sys
import urllib2

import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as ss  

# 从xml中匹配出数据
def ReSaltStatisData( ):

    # 从xml中获取到数据集合
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
    return saltData


#  求数据均值的置信区间
#  理论基础:课本page53-2.3.3  大样本区间估计-一般总体均值的区间估计
def ConfidenceIntervalMean(data, ci = 0.025) :
	"""
	data --  待处理的数据
	ci   --  置信度
	"""
	# 首先计算均值, 方差, 标准差
	dataArray = np.array(data)
	mean = dataArray.mean( )			#  计算均值
	print "Mean = ", mean
	#  numpy进行统计时，方差和标准差的自由度默认为N， 但是可通过参数ddof调整ddof : int, optional
	#  “Delta Degrees of Freedom”: the divisor used in the calculation is N - ddof, 
	#  where N represents the number of elements. By default ddof is zero.
	#  http://docs.scipy.org/doc/numpy/reference/generated/numpy.var.html
	var = dataArray.var(ddof = 1)	#  计算方差, 自由度为N - 1
	print "Var  = ", var
	std = dataArray.std(ddof = 1)	#  计算标准差, 自由度为N - 1 
	print "Std  = ", std

	#(sqrt(n) *(x - u)) / S  近似服从于N(0, 1)
	#normal approximation interval
	#print ss.norm.ppf(0.975) = U0.025 = 1.96
	#q = (ci > 0.5) ? (ci : 1 - ci)
	if ci > 0.5 :
		q = ci
	else :
		q = 1 - ci
	scaled_crit = ss.norm.ppf(q) * std / np.sqrt(len(dataArray))   #  计算Uci * S / sqrt(N)
	low = mean - scaled_crit  											    #  计算置信下界
	up = mean + scaled_crit     											#  计算置信上界
 
	print "The Sample  confidence level %f%% per cent confidence interval is [%f, %f]" % (q * 100, low, up)

#  比较两个样本的显著性差异
#  即参总体样本的参数的显著性检验
#  相对于产量来说, 不同年份的数据信息
#  
#  可以使用同课本例3.1.1一样的方法  -- 此要求认为两个分布的方差相同
#  当然我们也可以采用3.2.2的方法 --  两个正态总体的显著性检验
#  以oldData为基准, 判断新的数据newData与oldData有没有显著性差异
def SignificantDifference(oldData, newData, ci = 0.025) :
	dataArrayOld = np.array(oldData)

	lenOld  = len(dataArrayOld)
	meanOld = dataArrayOld.mean( )			#  计算均值
	varOld  = dataArrayOld.var(ddof = 1)	#  计算方差, 自由度为N - 1
	stdOld  = dataArrayOld.std(ddof = 1)	#  计算标准差, 自由度为N - 1 
	print "The 2014 data : Length = %d, Mean = %f, Var = %f, Std = %f" % (lenOld, meanOld, varOld, stdOld)

	dataArrayNew = np.array(newData)
	lenNew  = len(dataArrayNew)
	meanNew = dataArrayNew.mean( )			#  计算均值
	varNew  = dataArrayNew.var(ddof = 1)	#  计算方差, 自由度为N - 1
	stdNew  = dataArrayNew.std(ddof = 1)	#  计算标准差, 自由度为N - 1 
	print "The 2015 data : Length = %d, Mean = %f, Var = %f, Std = %f" % (lenNew, meanNew, varNew, stdNew)

	#  求拒绝域
	#  H0 ： U = u   H1 : U != u
	#  如果H0成立, 那么P()
	if ci > 0.5 :
		q = ci
	else :
		q = 1 - ci
	t_ind, p_ind = scaled_crit = ss.ttest_ind(oldData, newData)
 	print t_ind, p_ind
 	#return t_stat, one_tailed_p_value, two_tailed_p_value, t_ind, p_ind




#  主函数
if __name__ == "__main__" :

    reload(sys)
    sys.setdefaultencoding("utf-8")
    a = 10
    b = 5
    saltData = ReSaltStatisData( )
    print "For three consecutive years(%d month) the monthly production of salt information :\n %s" % (len(saltData), saltData)
    
	#  求数据均值的置信区间
    ConfidenceIntervalMean(saltData, 0.025)

    #  比较之前数据和近期数据有无显著性差异
    data2015 = saltData[ 0:  10]
    data2014 = saltData[10 : 22]		#  2014年的数据
    data2013 = saltData[22 : 34]		#  2013年的数据
    print data2015 
    print data2014
    print data2013
    SignificantDifference(data2014, data2015)
