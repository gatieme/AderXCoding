#!/usr/bin/env python
# encoding: utf-8
# echo.py

import sys

if __name__ == "__main__":
    print "您运行程序时输入的运行信息有 %s, 类型 %s"  % (sys.argv, len(sys.argv))
    print "命令行参数的长度", len(sys.argv)

    print "输出每一个参数的信息"
    for i, eachArg in enumerate(sys.argv):
        print "[%d] = %s" % (i, eachArg)