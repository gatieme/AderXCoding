#!/usr/bin/env python
# encoding: utf-8


import sys

import argparse



if __name__ == "__main__":

    parser = argparse.ArgumentParser()

    # 设置dest = "echo"以后
    # 我们的parser可以从参数中读取出名为echo的参数
    # 我们在使用parse_args( )读取参数信息后，可以直接用args.echo读取该参数
    parser.add_argument(dest = "echo", help = "echo the string you use here")
    args = parser.parse_args()

    print "程序运行的所有参数信息"
    print "参数信息", args
    print "参数类型", type(args)

    print "显示字符串echo = ", args.echo   #   直接使用args.echo 即可读取参数的信息