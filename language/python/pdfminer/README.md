AderXCoding
=======

| CSDN | GitHub |
|:----:|:------:|
| [Python 中使用 pdfminer 解析 pdf 文件](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |

<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 也欢迎大家提供一些其他好的调试工具以供收录, 鄙人在此谢谢啦

<br>


#1   `pdfminer` 模块简介
-------

近期在做爬虫时有时会遇到网站只提供 `pdf` 的情况, 这样就不能使用 `scrapy` 直接抓取页面内容了, 只能通过解析 `PDF` 的方式处理, 目前的解决方案大致只有 `pyPDF` 和 `PDFMiner`. 因为据说 `PDFMiner` 更适合文本的解析, 而我需要解析的正是文本, 因此最后选择使用 `PDFMiner` (这也就意味着我对 `pyPDF` 一无所知了).


首先说明的是解析 `PDF` 是非常蛋疼的事, 即使是 `PDFMiner` 对于格式不工整的 `PDF` 解析效果也不怎么样, 所以连 `PDFMiner` 的开发者都吐槽 `PDF is evil`.

不过这些并不重要.

官方文档在此


[`Python PDF parser and analyzer`](http://www.unixuser.org/~euske/python/pdfminer/index.html)


#2  `pdfminer` 模块安装
-------


##2.1   `pip` 安装 `pdfminer` 模块
-------


安装anaconda后，直接可以通过pip安装


```cpp
pip install pdfminer3k
```

##2.1   源码安装 `pdfminer` 模块
-------


#3  `pdfminer` 模块实践
-------

```cpp
#!/usr/bin/env python
# encoding: utf-8

"""
@author: wugang
@software: PyCharm
@file: prase_pdf.py
@time: 2017/3/3 0003 11:16
"""
import sys
import importlib
importlib.reload(sys)

from pdfminer.pdfparser import PDFParser,PDFDocument
from pdfminer.pdfinterp import PDFResourceManager, PDFPageInterpreter
from pdfminer.converter import PDFPageAggregator
from pdfminer.layout import LTTextBoxHorizontal,LAParams
from pdfminer.pdfinterp import PDFTextExtractionNotAllowed

'''
 解析pdf 文本，保存到txt文件中
'''
path = r'../../data/pdf/阿里巴巴Java开发规范手册.pdf'
def parse():
    fp = open(path, 'rb') # 以二进制读模式打开
    #用文件对象来创建一个pdf文档分析器
    praser = PDFParser(fp)
    # 创建一个PDF文档
    doc = PDFDocument()
    # 连接分析器 与文档对象
    praser.set_document(doc)
    doc.set_parser(praser)

    # 提供初始化密码
    # 如果没有密码 就创建一个空的字符串
    doc.initialize()

    # 检测文档是否提供txt转换，不提供就忽略
    if not doc.is_extractable:
        raise PDFTextExtractionNotAllowed
    else:
        # 创建PDf 资源管理器 来管理共享资源
        rsrcmgr = PDFResourceManager()
        # 创建一个PDF设备对象
        laparams = LAParams()
        device = PDFPageAggregator(rsrcmgr, laparams=laparams)
        # 创建一个PDF解释器对象
        interpreter = PDFPageInterpreter(rsrcmgr, device)

        # 循环遍历列表，每次处理一个page的内容
        for page in doc.get_pages(): # doc.get_pages() 获取page列表
            interpreter.process_page(page)
            # 接受该页面的LTPage对象
            layout = device.get_result()
            # 这里layout是一个LTPage对象 里面存放着 这个page解析出的各种对象 一般包括LTTextBox, LTFigure, LTImage, LTTextBoxHorizontal 等等 想要获取文本就获得对象的text属性，
            for x in layout:
                if (isinstance(x, LTTextBoxHorizontal)):
                    with open(r'../../data/pdf/1.txt', 'a') as f:
                        results = x.get_text()
                        print(results)
                        f.write(results + '\n')

if __name__ == '__main__':
    parse()
```


#4  参考资料
-------

[手把手--20行Python代码教你批量将PDF转为Word
](https://mbd.baidu.com/newspage/data/landingsuper?context=%7B%22nid%22%3A%22news_9586611632993157435%22%7D&n_type=0&p_from=1)

[Python使用PDFMiner解析PDF](https://www.cnblogs.com/jamespei/p/5339769.html)

<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的. 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.
