#/usr/bin/python
#-*- coding: utf-8 -*-


#   格式：\033[显示方式;前景色;背景色m
#   说明:
#
#   前景色            背景色            颜色
#   ---------------------------------------
#     30                40              黑色
#     31                41              红色
#     32                42              绿色
#     33                43              黃色
#     34                44              蓝色
#     35                45              紫红色
#     36                46              青蓝色
#     37                47              白色
#
#   显示方式           意义
#   -------------------------
#      0           终端默认设置
#      1             高亮显示
#      4            使用下划线
#      5              闪烁
#      7             反白显示
#      8              不可见
#
#   例子：
#   \033[1;31;40m    <!--1-高亮显示 31-前景色红色  40-背景色黑色-->
#   \033[0m          <!--采用终端默认设置，即取消颜色设置-->]]]


STYLE = {
        'fore':
        {   # 前景色
            'black'    : 30,   #  黑色
            'red'      : 31,   #  红色
            'green'    : 32,   #  绿色
            'yellow'   : 33,   #  黄色
            'blue'     : 34,   #  蓝色
            'purple'   : 35,   #  紫红色
            'cyan'     : 36,   #  青蓝色
            'white'    : 37,   #  白色
        },

        'back' :
        {   # 背景
            'black'     : 40,  #  黑色
            'red'       : 41,  #  红色
            'green'     : 42,  #  绿色
            'yellow'    : 43,  #  黄色
            'blue'      : 44,  #  蓝色
            'purple'    : 45,  #  紫红色
            'cyan'      : 46,  #  青蓝色
            'white'     : 47,  #  白色
        },

        'mode' :
        {   # 显示模式
            'mormal'    : 0,   #  终端默认设置
            'bold'      : 1,   #  高亮显示
            'underline' : 4,   #  使用下划线
            'blink'     : 5,   #  闪烁
            'invert'    : 7,   #  反白显示
            'hide'      : 8,   #  不可见
        },

        'default' :
        {
            'end' : 0,
        },
}


def UseStyle(string, mode = '', fore = '', back = ''):

    mode  = '%s' % STYLE['mode'][mode] if STYLE['mode'].has_key(mode) else ''

    fore  = '%s' % STYLE['fore'][fore] if STYLE['fore'].has_key(fore) else ''

    back  = '%s' % STYLE['back'][back] if STYLE['back'].has_key(back) else ''

    style = ';'.join([s for s in [mode, fore, back] if s])

    style = '\033[%sm' % style if style else ''

    end   = '\033[%sm' % STYLE['default']['end'] if style else ''

    return '%s%s%s' % (style, string, end)



def TestColor( ):

    print UseStyle('正常显示')
    print ''

    print "测试显示模式"
    print UseStyle('高亮',   mode = 'bold'),
    print UseStyle('下划线', mode = 'underline'),
    print UseStyle('闪烁',   mode = 'blink'),
    print UseStyle('反白',   mode = 'invert'),
    print UseStyle('不可见', mode = 'hide')
    print ''


    print "测试前景色"
    print UseStyle('黑色',   fore = 'black'),
    print UseStyle('红色',   fore = 'red'),
    print UseStyle('绿色',   fore = 'green'),
    print UseStyle('黄色',   fore = 'yellow'),
    print UseStyle('蓝色',   fore = 'blue'),
    print UseStyle('紫红色', fore = 'purple'),
    print UseStyle('青蓝色', fore = 'cyan'),
    print UseStyle('白色',   fore = 'white')
    print ''


    print "测试背景色"
    print UseStyle('黑色',   back = 'black'),
    print UseStyle('红色',   back = 'red'),
    print UseStyle('绿色',   back = 'green'),
    print UseStyle('黄色',   back = 'yellow'),
    print UseStyle('蓝色',   back = 'blue'),
    print UseStyle('紫红色', back = 'purple'),
    print UseStyle('青蓝色', back = 'cyan'),
    print UseStyle('白色',   back = 'white')
    print ''
if __name__ == '__main__':

    TestColor( )