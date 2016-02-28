#!/usr/bin/env python
#coding=utf-8

import webbrowser

"""
    python的webbrowser模块支持对浏览器进行一些操作
    主要有以下三个方法：
        webbrowser.open(url, new=0, autoraise=True)
        webbrowser.open_new(url)
        webbrowser.open_new_tab(url)

    在webbrowser.py文件中，我们可以看到源码：
    ########################################################
        def open(url, new=0, autoraise=True):
            for name in _tryorder:
                browser = get(name)
                if browser.open(url, new, autoraise):
                    return True
            return False

        def open_new(url):
            return open(url, 1)

        def open_new_tab(url):
            return open(url, 2)
    ########################################################
    可以看出后面两个方法，都是建立在第一个方法open()方法上面的。
    所以我们需要了解webbrowser.open()方法：
        webbrowser.open(url, new=0, autoraise=True)
            在系统的默认浏览器中访问url地址，如果new=0,url会在同一个
            浏览器窗口中打开；如果new=1，新的浏览器窗口会被打开;new=2
            新的浏览器tab会被打开。

    而webbrowser.get()方法可以获取到系统浏览器的操作对象。
    webbrowser.register()方法可以注册浏览器类型，而允许被注册的类型名称如下：
    Type Name Class Name Notes 
    'mozilla' Mozilla('mozilla')   
    'firefox' Mozilla('mozilla')   
    'netscape' Mozilla('netscape')   
    'galeon' Galeon('galeon')   
    'epiphany' Galeon('epiphany')   
    'skipstone' BackgroundBrowser('skipstone')   
    'kfmclient' Konqueror() (1) 
    'konqueror' Konqueror() (1) 
    'kfm' Konqueror() (1) 
    'mosaic' BackgroundBrowser('mosaic')   
    'opera' Opera()   
    'grail' Grail()   
    'links' GenericBrowser('links')   
    'elinks' Elinks('elinks')   
    'lynx' GenericBrowser('lynx')   
    'w3m' GenericBrowser('w3m')   
    'windows-default' WindowsDefault (2) 
    'macosx' MacOSX('default') (3) 
    'safari' MacOSX('safari') (3) 
    'google-chrome' Chrome('google-chrome')   
    'chrome' Chrome('chrome')   
    'chromium' Chromium('chromium')   
    'chromium-browser' Chromium('chromium-browser')

Notes:
   1. “Konqueror” is the file manager for the KDE desktop environment for Unix, and only makes sense to use if KDE is running. Some way of reliably detecting KDE would be nice; the KDEDIR variable is not sufficient. Note also that the name “kfm” is used even when using the konqueror command with KDE 2 — the implementation selects the best strategy for running Konqueror. 
   2. Only on Windows platforms. 
   3. Only on Mac OS X platform. 


"""

__author__ = {'name' : 'Hongten',
              'mail' : 'hongtenzone@foxmail.com',
              'blog' : 'http://www.cnblogs.com/',
              'QQ': '648719819',
              'created' : '2013-09-20'}

#global var
URL = None

def ove_open(url):
    '''webbrowser.open().'''
    if url is not None and url != '':
        return webbrowser.open(url)
    else:
        print('the URL is None or Empty!')

def ove_open_new(url):
    '''webbrowser.open_new().'''
    if url is not None and url != '':
        return webbrowser.open_new(url)
    else:
        print('the URL is None or Empty!')

def ove_open_new_tab(url):
    '''webbrowser.open_new_tab().'''
    if url is not None and url != '':
        return webbrowser.open_new_tab(url)
    else:
        print('the URL is None or Empty!')

def ove_get():
    return webbrowser.get()

def test_open():
    ove_open(URL)

def test_open_new():
    ove_open_new(URL)

def test_open_new_tab():
    ove_open_new_tab(URL)

def test_get():
    type_name = ove_get()
    print(type_name)

def init():
    global URL
    URL = 'http://www.baidu.com/'

def main():
    init()
    test_open()
    test_open_new()
    test_open_new_tab()
    test_get()

if __name__ == '__main__':
    main()