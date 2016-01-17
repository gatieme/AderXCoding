K最近邻 k-Nearest Neighbor, KNN 简单示例
=======

 这里我们用kNN来分类一个大点的数据库，包括数据维度比较大和样本数比较多的数据库。
 这里我们用到一个手写数字的数据库，数据在digits文件夹中，有训练数据和测试数据
 这个数据库包括数字0-9的手写体。每个数字大约有200个样本。每个样本保持在一个txt文件中。
 手写体图像本身的大小是32x32的二值图，转换到txt文件保存后，内容也是32x32个数字，0或者1，
 
 如下：
![image](https://github.com/gatieme/AderXCoding/blob/master/machinelearning/K-Nearest-Neighbor/recognition/handwritedigits.png)

数据库解压后有两个目录：目录trainingDigits存放的是大约2000个训练数据，testDigits存放大约900个测试数据。
这里我们还是新建一个kNN.py脚本文件，文件里面包含四个函数，
一个用来生成将每个样本的txt文件转换为对应的一个向量，
一个用来加载整个数据库，一个实现kNN分类算法。最后就是实现这个加载，测试的函数。

#程序结构
-------

##knn.py
-------
kNNClassify(newInput, dataSet, labels, k)
"""
进行KNN分类
"""  

img2vector
"""
将手写数字的文本位图转换为数组
"""  

loadDataSet
"""
加载数据, 本质上是KNN的训练算法
"""  

```


##main.py
-------
测试的主函数

#运行结果
-------

![image](https://github.com/gatieme/AderXCoding/blob/master/machinelearning/K-Nearest-Neighbor/recognition/result.png)