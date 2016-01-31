
#coding: utf-8
import time

'''
/*****************************************************************
  Function     : GetCurrFmtTime
  Description  : 获取当前时间
******************************************************************/
'''
def GetCurrFmtTime( ) :
    t = time.localtime()
    strtime = "%02d/%02d %02d:%02d:%02d" % (t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
    return strtime


'''
/*****************************************************************
  日志类 PLog
******************************************************************/
'''
class PLog :
    def __init__(self, logFile='log.txt') :
        self.DEBUG = True
        self.logFile = logFile

    def __log__(self, *params) :
        msgs = GetCurrFmtTime()
        for msg in params:
            if msgs != "" : msgs += " "
            msgs += str(msg)
        print msgs
        self.__write__(msgs)

    def __write__(self, msgs=None) :
        if len(self.logFile) > 0 :
            f = open(self.logFile, 'at+')
            if msgs != None : f.write(msgs)
            f.write("\n")
            f.close()

    #####################################################################
    def setDebug(self, dbgFlag ) :
        self.DEBUG = dbgFlag

    def setLogFile(self, logName ) :
        self.logFile = logName

    ###########################################
    def debug(self, *params) :
        if self.DEBUG == True :
            self.__log__('DBGUG : ', *params)

    def info(self, *params) :
        self.__log__('INFORMATION : ', *params)

    def error(self, *params) :
        self.__log__('ERROR : ', *params)

    ###########################################
    def blankLine(self) :
        print
        self.__write__()

    def oneLine(self, char='=') :
        line = char
        for i in range(1, 50) :
            line += char
        print line
        self.__write__(line)

    def titleLog(self, title) :
        char = '*'
        line = char
        for i in range(1, 50) :
            line += char

        msgs = '\n'
        msgs += line + '\n\n'
        msgs += '\t' + title + '\n\n'
        msgs += line + '\n\n'
        print msgs
        self.__write__(msgs)

#################################################################
def test() :
    log = PLog()
    log.titleLog('测试CLog类')
    
    log.oneLine('#')

    log.setDebug(False)
    log.debug(2,3,4)
    log.info('Hello', 'World', 100)
    log.blankLine()
    PLog().error('This is a test.')
    
    log.setDebug(True)
    log.debug(20,30,40)
    
    log.blankLine()
    log.oneLine()

    
######################
if __name__ == '__main__':
    test()