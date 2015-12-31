#!/usr/bin/env python
#coding=utf-8

import sys

def func(depth):
    depth += 1
    print "Now the depth is %d" % depth
    func(depth)


if __name__ == "__main__" :

    #sys.setrecursionlimit(1000000)
    func(0)