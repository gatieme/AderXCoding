#kgdb调试内核
-------



```cpp
setenv console "ttyS0,115200 kgdboc=ttyS0,115200 kgdbwait"
```


http://blog.chinaunix.net/uid-27159438-id-3280019.html

http://blog.csdn.net/gqb_driver/article/details/9117597

http://blog.chinaunix.net/uid-632207-id-2083377.html


http://blog.csdn.net/u013470224/article/details/51314231

http://www.kgdb.info/kgdb/kdb_kgdb_mode_change/

http://www.arm9home.net/read.php?tid-25888.html

http://www.tinylab.org/kgdb-debugging-kernel/

[Linux内核驱动开发之KGDB原理介绍及kgdboe方式配置](http://blog.csdn.net/gqb_driver/article/details/9120483)


[Linux内核驱动开发之KGDB单步调试内核(kgdboc方式)](http://blog.csdn.net/gqb_driver/article/details/9117597)


[用 kGDB 调试 Linux 内核](http://www.tinylab.org/kgdb-debugging-kernel/)


#挂载远程内核和调试系统
-------


http://blog.csdn.net/yanghonker/article/details/38562655


**标准的u-boot变量**

*	emmc

```cpp
baudrate=115200
boot_normal=fatload mmc 2:1 20007800 uimage;bootm 20007800
bootcmd=run setargs_cubie boot_normal
bootdelay=3
console=ttyS0,115200
console1=tty1
filesize=1F4676
init=/init
ipaddr=192.168.10.123
loglevel=8
mmc_root=/dev/mmcblk0p2
partitions=bootloader@mmcblk0p2:env@mmcblk0p5:boot@mmcblk0p6:system@mmcblk0p7:misc@mmcblk0p8:recovery@mmcblk0p9:cache@mmcblk0p11
setargs_cubie=setenv bootargs console=${console1} console=${console} root=${mmc_root} loglevel=${loglevel}
stderr=serial
stdin=serial
stdout=serial
```


*	sdcard


```cpp
baudrate=115200
boot_normal=fatload mmc 2:1 20007800 uimage;bootm 20007800
bootcmd=run setargs_cubie boot_normal
bootdelay=3
console=ttyS0,115200
console1=tty1
filesize=1F4676
init=/init
ipaddr=192.168.10.123
loglevel=8
mmc_root=/dev/mmcblk0p2
partitions=bootloader@mmcblk0p2:env@mmcblk0p5:boot@mmcblk0p6:system@mmcblk0p7:misc@mmcblk0p8:recovery@mmcblk0p9:cache@mmcblk0p11
setargs_cubie=setenv bootargs console=${console1} console=${console} root=${mmc_root} loglevel=${loglevel}
stderr=serial
stdin=serial
stdout=serial
```

*	挂载远程内核和文件系统

```cpp
setenv baudrate 115200
setenv stderr serial
setenv stdin  serial
setenv stdout serial
setenv bootdelay 3
setenv ethact dm9000


setenv gatewayip 192.168.10.1
setenv ipaddr 192.168.10.123
setenv netmask 255.255.255.0
setenv serverip 192.168.10.77
setenv bootargs root=/dev/nfs rw nfsroot=$serverip:/home/gatieme/Work/NfsRoot/rootfs,nolock,tcp ip=$ipaddr console=ttyS0,115200 ctp=1 kgdboc=ttyS0,115200
setenv bootcmd "tftp 20007800 uImage;bootm 20007800"
```


*	内核进行调试

```cpp
setenv kgdboc "ttyS0,115200 kgdbwait"
```
