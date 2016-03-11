#!/usr/bin/python
# encoding=utf-8


#!coding:utf-8

import re
import sys
import urllib2
import argparse

import commands
import os
import subprocess

if __name__ == "__main__" :
    # 测试正则表达式

    reload(sys)
    sys.setdefaultencoding("utf-8")
    if len(sys.argv) > 1:               #  如果在程序运行时，传递了命令行参数

        #  打印传递的命令行参数的信息
        print "您输入的所有参数共 %d 个，信息为 sys.argv = %s" % (len(sys.argv), sys.argv)

        for i, eachArg in enumerate(sys.argv):

            print "[%d] = %s" % (i, eachArg)
    else:
    	print "Useage : read.py -r shell..."
    	exit(0)

    #  创建一个解析对象
    #  然后向该对象中添加你要关注的命令行参数和选项
    #  每一个add_argument方法对应一个你要关注的参数或选项
    #  最后调用parse_args()方法进行解析
    #  解析成功之后即可使用

    parser = argparse.ArgumentParser( )
    parser.add_argument("-r", "--run", dest = "shell_parser", help = "The file you want to read...")
    args = parser.parse_args( )

    shell = args.shell_parser



    try:
        #  首先执行shell脚本，并读取到返回值的信息
        #(status, output) = commands.getstatusoutput("ls")
        #print status, output
        
        #output = os.popen('ls')
        #print output.read()
        
        #print subprocess.call(["ls","-al"])
        
        #handle = subprocess.Popen("ls", shell=True, stdout=subprocess.PIPE)
        #print handle.communicate()[0] 
        output = subprocess.check_output("ls")
        
        #print all_text.decode("utf-8")
        #print all_text

        #匹配的信息如下
        #[ 2016-1-26 23:25:52]Process 18497 exited with code 0
        #[  2016-1-26 23:26:5]Process 18556 termed with signal 11(SIGSEGV)
        reStr = r'.*?(\d{4}-\d{1,2}-\d{1,2} \d{1,2}:\d{1,2}:\d{1,2})]Process (\d{1,5}) (exited with code \d|termed with signal \d{1,2}\((.*?)\))'
        #item[0] -=> [ 2016-1-26 23:25:52]
        #item[1] -=> pid
        #item[2] -=> Process 18497 exited with code 0 | Process 18556 termed with signal 11(SIGSEGV)
        #item[3] -=> "" | SIGSEGV

        non_exception = 0
        sigsegv_exception = 0
        pattern = re.compile(reStr, re.S)
        myItems = re.findall(pattern, output)
        print len(myItems)
        #print myItems
        for item in myItems:
        	#print item
        	if item[3] == "" :
        		non_exception += 1
        	elif item[3] == "SIGSEGV":
        		sigsegv_exception += 1
        print "无异常", non_exception
        print "SIGSEGV", sigsegv_exception

        if non_exception = 1 ：
            print "0"
        else 
            print "1", item[3]
    finally:
    	pass