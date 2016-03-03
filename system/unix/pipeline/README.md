#进程间通信
-------

http://www.cnblogs.com/forstudy/archive/2012/03/22/2412415.html

pipe.c  简单的fork后父子进程之间通过管道进程通信

fifo_write.c    向管道中写入数据
fifo_read.c     从管道中读取数据
./fifo_read &
./fifo_write somedata
