#!coding:utf-8
import networkx as nx
import matplotlib.pyplot as plt                 #导入科学绘图的matplotlib包

G = nx.random_graphs.barabasi_albert_graph(1000,3)   #生成一个n=1000，m=3的BA无标度网络
print G.degree(0)                                   #返回某个节点的度
print G.degree()                                     #返回所有节点的度
print nx.degree_histogram(G)    #返回图中所有节点的度分布序列（从1至最大度的出现频次）
degree =  nx.degree_histogram(G)          #返回图中所有节点的度分布序列
x = range(len(degree))                             #生成x轴序列，从1到最大度
y = [z / float(sum(degree)) for z in degree]  
#将频次转换为频率，这用到Python的一个小技巧：列表内涵，Python的确很方便：）
plt.loglog(x,y,color="blue",linewidth=2)           #在双对数坐标轴上绘制度分布曲线  
plt.show()        