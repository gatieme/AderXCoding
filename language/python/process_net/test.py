# -*- coding: utf-8 -*-
"""
Created on Tue Jun 10 10:20:13 2014

@author: lifeix

[python监控linux性能以及进程消耗的性能(http://blog.csdn.net/startupmount/article/details/29825045)
"""

from collections import OrderedDict
import time
import os

def cpuinfo():
    lines = open('/proc/stat').readlines()
    for line in lines:
        ln = line.split()
        if ln[0].startswith('cpu'):
            return ln;
    return []
W = cpuinfo()
one_cpuTotal=long(W[1])+long(W[2])+long(W[3])+long(W[4])+long(W[5])+long(W[6])+long(W[7])
one_cpuused=long(W[1])+long(W[2])+long(W[3])

def CPUinfo():
    ''''' Return the information in /proc/CPUinfo
    as a dictionary in the following format:
    CPU_info['proc0']={...}
    CPU_info['proc1']={...}
    '''
    CPUinfo=OrderedDict()
    procinfo=OrderedDict()

    nprocs = 0
    f = open('/proc/cpuinfo')
    for line in f.readlines():
        if not line.strip():
            # end of one processor
            CPUinfo['proc%s' % nprocs] = procinfo
            nprocs=nprocs+1
            # Reset
            procinfo=OrderedDict()
        else:
            if len(line.split(':')) == 2:
                procinfo[line.split(':')[0].strip()] = line.split(':')[1].strip()
            else:
                procinfo[line.split(':')[0].strip()] = ''

    return CPUinfo



def meminfo():
    ''''' Return the information in /proc/meminfo
    as a dictionary '''
    meminfo=OrderedDict()

    f = open('/proc/meminfo')
    for line in f.readlines():
        meminfo[line.split(':')[0]] = line.split(':')[1].strip()
    return meminfo

f = open("sysinfo.log",'a')
def logSysInfo(cpu,mem,line):
    f.write('\ncpu:%s -------mem: %s------mongocpu:%s'%(cpu,mem,line))
    f.flush();

def process_info():
    #获取drm_processes 的进程号
    textlist = os.popen('top -bcn 1 -p 12023').readlines()
    line = ''
    for t in textlist:
        if t.find('12023'):
            line = t
    line = line.split(' ')
    #此处的值按照自己的需求去取
    return line[15]
if __name__=='__main__':
    CPUinfo = CPUinfo()
    for processor in CPUinfo.keys():
        print(CPUinfo[processor]['model name'])
        f.write("cpu:%s"%CPUinfo[processor]['model name'])
    #meminfo = meminfo()
    #print('Total memory: {0}'.format(meminfo['MemTotal']))


    try:
        while True:
            line = process_info()
            time.sleep(2)
            mi = meminfo()
            print('Free memory: {0}'.format(mi['MemFree']))
            W = cpuinfo()
            two_cpuTotal=long(W[1])+long(W[2])+long(W[3])+long(W[4])+long(W[5])+long(W[6])+long(W[7])
            two_cpuused=long(W[1])+long(W[2])+long(W[3])
            cpuused=float(two_cpuused-one_cpuused)/(two_cpuTotal-one_cpuTotal)
            print ('%.2f%%'%(cpuused*100))
            print line
            cpu = '%.2f%%'%(cpuused*100)
            logSysInfo(cpu,format(mi['MemFree']),line)
    except KeyboardInterrupt, e:
        print ("\ncpumonit exited")
        f.close()
f.close()

