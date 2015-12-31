#coding=utf-8
from PIL import Image

if __name__ == "__main__" :
    
    im = Image.open("test.jpg")
    print im.format, im.size, im.mode
    #  这里有三个属性，我们逐一了解。
    #  format : 识别图像的源格式，如果该文件不是从文件中读取的，则被置为 None 值。
    #  size : 返回的一个元组，有两个元素，其值为象素意义上的宽和高。
    #  mode : RGB（true color image），此外还有，L（luminance），CMTK（pre-press image）。
    im.show()
