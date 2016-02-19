#!/usr/bin/env python
#coding=utf-8
#

import urllib2
import sys
import re


def AccessHtmlUrl(url):

    req = urllib2.Request(url)                # 建立页面请求

    req.add_header("User-Agent", "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)")


    try:
        
        cn = urllib2.urlopen(req)

        page = cn.read( )

        unicodePage = page.decode("utf-8")

        cn.close( )

        return unicodePage

    except urllib2.URLError, e:
        
        if hasattr(e, "reason"):

            print "Failed to reach the server"

            print "The reason:", e.reason

        elif hasattr(e, "code"):

            print "The server couldn't fulfill the request"

            print "Error code:", e.code


            print "Return content:", e.read()

        else:

            pass  #其他异常的处理


def ReHtmlPage( ):
    page  = """
<li><a href="http://en.wikipedia.org/wiki/C%2B%2B_Standard_Library" target="_blank">C++ Standard Library<i class="icon-link"></i></a>：是一系列类和函数的集合，使用核心语言编写，也是C++ISO自身标准的一部分。</li>
"""
    reHtml = r'<li><a href="(.*?)" target="_blank">(.*?)<i class="icon-link"></i></a>(.*?)</li>'

    pattern = re.compile(reHtml, re.S)

    myItems = re.findall(pattern, unicodePage)

    datas = ""
    for item in myItems:

        datas += "[" + item[1] +"](" + item[0] + ") : " + item[2] + "\n"
    return datas

def WriteReData(datas):
    """
    item[0] : url
    item[1] : library name
    item[2] : description

    -=> ![item_1](item_0) : item_2
    """

    file_object = open('thefile.txt', 'w')
    file_object.write(datas)
    file_object.close( )

if __name__ == "__main__" :
    
    reload(sys)  
    sys.setdefaultencoding('utf8')   
    
    unicodePage = AccessHtmlUrl("http://www.cplusplus.me/2182.html")

    datas = ReHtmlPage()
    WriteReData(datas)