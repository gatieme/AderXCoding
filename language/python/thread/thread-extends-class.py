#!/usr/bin/python
# encoding=utf-8
# 
# 
# Filename: thread-extends-class.py
# 直接从Thread继承，
# 创建一个新的class，
# 把线程执行的代码放到这个新的 class里
# 
# 

import threading
import time
  
class ThreadImpl(threading.Thread):
    """
    """
    
    def __init__(self, num):
        """
        num 线程执行的次数
        """
        threading.Thread.__init__(self)
        self.m_num = num
  
    def run(self):
        global total, mutex
         
        # 打印线程名
        print threading.currentThread().getName()
  
        for x in xrange(0, int(self.m_num)):
            
            # 取得锁
            mutex.acquire()
            
            #print threading.currentThread().getName()
            total = total + 1
            
            # 释放锁
            mutex.release()



if __name__ == '__main__':
    
    #定义全局变量
    global total, mutex
    total = 0
    
    #  创建线程锁
    mutex = threading.Lock()
     
    #  定义线程池
    threads = []
    
    # 创建线程对象
    for x in xrange(0, 40) :    
        #  将每个线程加入线程池中
        threads.append(ThreadImpl(10))
    
    # 启动线程
    for t in threads :
        t.start()
    
    # 等待子线程结束
    for t in threads :
        t.join()  
     
    # 打印执行结果
    print total