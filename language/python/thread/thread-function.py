#!/usr/bin/python
# encoding=utf-8
# Filename: thread-function.py
# 
# 
# 创建线程要执行的函数
# 把这个函数传递进Thread对象里
# 让它来执行
 
import threading
import time
  
def threadFunc(num):
    global total, mutex
     
    # 打印线程名
    print threading.currentThread().getName()
  
    for x in xrange(0, int(num)):
        # 取得锁
        mutex.acquire()
        
        total = total + 1
        
        # 释放锁
        mutex.release()
  
def main(num):
    #定义全局变量
    global total, mutex
    total = 0
    # 创建锁
    mutex = threading.Lock()
     
    #定义线程池
    threads = []
    
    # 先创建线程对象
    for x in xrange(0, num):
        threads.append(threading.Thread(target=threadFunc, args=(100,)))
    
    # 启动所有线程
    for t in threads:
        t.start()
    # 主线程中等待所有子线程退出
    for t in threads:
        t.join()  
         
    # 打印执行结果
    print total
  
  
if __name__ == '__main__':
    # 创建40个线程
    main(40)