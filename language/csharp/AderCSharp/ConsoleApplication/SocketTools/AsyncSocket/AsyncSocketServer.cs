using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

///  SOKCET 
using System.Net.Sockets;  
using System.Net;
using Newtonsoft.Json;


using SignPressServer.SignFile;
/*
 *  在同步模式中，
 *  在服务器上使用Accept方法接入连接请求，
 *  而在客户端则使用Connect方法来连接服务器。
 *  
 *  相对地，在异步模式下，
 *  服务器可以使用BeginAccept方法和EndAccept方法来完成连接到客户端的任务，
 *  在客户端则通过BeginConnect方法和EndConnect方法来实现与服务器的连接。
 *  
 *  BeginAccept在异步方式下传入的连接尝试，它允许其他动作而不必等待连接建立才继续执行后面程序。
 *  在调用BeginAccept之前，必须使用Listen方法来侦听是否有连接请求，
 *  
 *  BeginAccept的函数原型为
 *  BeginAccept(AsyncCallback AsyncCallback, Ojbect state)
 *  参数：
 *  AsyncCallBack：代表回调函数
 *  state：表示状态信息，必须保证state中包含socket的句柄
 *  
 *  使用BeginAccept的基本流程是：
 *  (1)创建本地终节点，并新建套接字与本地终节点进行绑定；
 *  (2)在端口上侦听是否有新的连接请求；
 *  (3)请求开始接入新的连接，传入Socket的实例或者StateOjbect的实例。
 *  
 *  当BeginAccept()方法调用结束后，一旦新的连接发生，将调用回调函数，
 *  而该回调函数必须包括用来结束接入连接操作的EndAccept()方法。
 *  该方法参数列表为 Socket EndAccept(IAsyncResult iar)
 *  
 *  如何获取连接的客户端的IP和端口
 *  Accpet和BeginAccept获取到来自客户端的连接
 *  然后创建并返回新的 Socket。
 *  不能使用返回的这个 Socket 接受连接队列中的任何附加连接。
 *  然而，可以调用返回的 Socket 的 RemoteEndPoint 方法来标识远程主机的网络地址和端口号
 * 
 * 
 *  最后附上同步还是异步服务器的性能对比
 *  同步:  编程简单,不易出错
 *  异步:  流量较少,性能较高
 *  项目实战中, 一般采用同步, 短连接的形式
 *  如果确实有必要, 才会选用异步, 长连接的形式
 *  
 *  老板要的是 短时间能出成果,稳定的程序, 所以项目经理定方案时, 首选同步短连接
 *  如果频繁建立连接成为性能瓶颈的话, 那就要采用长连接了.
 * 
 *  大量客户端的话用异步加多线程，小量客户端用同步加线程池 
 * 
 */



/*[问题1]
http://www.cnblogs.com/csMapx/archive/2011/09/04/2166515.html
 * 一下内容摘自http://s.yanghao.org/program/viewdetail.php?i=2945
 * 自己写的客户端马上要发布了，忽然发现了一大堆问题，
 * 主要集中在与服务器的TCP连接经常莫名断开，
 * 客户端又检测不到，不能及时重连。
 * 一个多星期的改，有一些心得，与大家分享。
 * 也希望大家多发表意见，您的意见也许最后就实现在我的软件中了！
 * 
 * 
 * 主要分为两部分：
一，如何更好的检测TCP连接是否正常
二，如何提取本机TCP连接状态

一，如何更好的检测TCP连接是否正常
这方面问题，我上网查了很久，一般来说比较成熟的有两种方法：
1是在应用层制定协议，发心跳包，这也是C#，JAVA等高级语言比较常用的方法。客户端和服务端制定一个通讯协议，每隔一定时间（一般15秒左右），由一方发起，向对方发送协议包；对方收到这个包后，按指定好的通讯协议回一个。若没收到回复，则判断网络出现问题，服务器可及时的断开连接，客户端也可以及时重连。
2通过TCP协议层发送KeepAlive包。这个方法只需设置好你使用的TCP的KeepAlive项就好，其他的操作系统会帮你完成。操作系统会按时发送KeepAlive包，一发现网络异常，马上断开。我就是使用这个方法，也是重点向大家介绍的。

使用第二种方法的好处，是我们在应用层不需自己定协议，通信的两端，只要有一端设好这个值，两边都能及时检测出TCP连接情况。而且这些都是操作系统帮你自动完成的。像我们公司的服务端代码就是早写好的，很难改动。以前也没加入心跳机制，后面要改很麻烦，boss要求检测连接的工作尽量客户端单独完成....
还有一个好处就是节省网络资源。KeepAlive包，只有很简单的一些TCP信息，无论如何也是比你自己设计的心跳包短小的。然后就是它的发送机制，在TCP空闲XXX秒后才开始发送。自己设计心跳机制的话，很难做到这一点。

这种方法也是有些缺陷的。比如某一时刻，网线松了，如果刚好被KeepAlive包检测到，它会马上断开TCP连接。但其实这时候TCP连接也算是established的，只要网线再插好，这个连接还是可以正常工作的。这种情况，大家有什么好办法处理吗？

C#中设置KeepAlive的代码
  uint dummy = 0;
  byte[] inOptionValues = new byte[Marshal.SizeOf(dummy) * 3];
  BitConverter.GetBytes((uint)1).CopyTo(inOptionValues, 0);
  BitConverter.GetBytes((uint)15000).CopyTo(inOptionValues, Marshal.SizeOf(dummy));
  BitConverter.GetBytes((uint)15000).CopyTo(inOptionValues, Marshal.SizeOf(dummy) * 2);

  IPEndPoint iep = new IPEndPoint(this._IPadd, xxxx);
  this._socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
  this._socket.IOControl(IOControlCode.KeepAliveValues, inOptionValues, null);
  this._socket.Connect(iep);
这里我设定TCP15秒钟空闲，就开始发送KeepAlive包，其实完全可是设定得长一点。


二，如何提取本机TCP连接状态
设好了KeepAlive值，又遇到麻烦了，我没找到当网络异常时，它断开连接后怎么通知我...我搜了很久都没找到，要是哪位兄弟知道的话告诉我吧。我是使用笨办法的，找到所有本地TCP连接的信息，筛选出我需要的那个TCP。
查看本机所有TCP连接信息，网上一般的方法，都是通过程序调用CMD命令里的netstat进行，然后再分析其内容。但在CMD窗口用过这个命令的都知道，悲剧的时候它显示完所有TCP信息需要15s，或者更长时间，这在我的程序中是不能忍受的。
然后我又查找了一些牛人的博客，发现有人提到用iphlpapi.dll。这是一个在win98以上操作系统目录System32都包含的库函数，功能异常强大，大家可以放心使用！但是使用起来比较麻烦，基本找不到C#现成使用的例子，就算有，也是很老版本的，完全不能用
我参考了这两位高人的博客
http://blog.csdn.net/yulinlover/archive/2009/02/08/3868824.aspx
（另一位的博客连接找不到了..悲剧啊！）
下载了里面提到的项目，仔细结合自己体会进行修改，终于能用了。每隔一段时间，我的客户端就用这个方法扫描一遍本地TCP信息，若发现连接有问题，则断开重连。
这个方法能瞬间得到本机所有TCP连接信息（如果你有兴趣可以扩充，它的功能真的是太强大了），没有CMD命令netstat那不能忍受的延迟，相当好用。代码比较长，就不贴出来了。


这些是我不太成熟的做法，下星期项目就要提交了，不能再出啥岔子，希望大家多提意见，帮我改善一下。
本版人气很旺，但貌似用socket的人不多，不知道帖子发这是否合适。要是不合适，请前辈提点下发在哪个版比较好？
 
 * 
 * 关于Keep-alive
在TCP中有一个Keep-alive的机制可以检测死连接，原理很简单，
TCP会在空闲了一定时间后发送数据给对方：
1.如果主机可达，对方就会响应ACK应答，就认为是存活的。
2.如果可达，但应用程序退出，对方就发RST应答，发送TCP撤消连接。
3.如果可达，但应用程序崩溃，对方就发FIN消息。
4.如果对方主机不响应ack, rst，继续发送直到超时，就撤消连接。这个时间就是默认
的二个小时。
 */

/*
 * [问题二]
 * C#出现严重的粘包问题
 1．在上述实验环境下，当发送方连续发送的若干包数据长度之和小于1500b时，常会出现粘包现象，接收方经预处理线程处理后能正确解开粘在一起的包。若程序中设置了“发送不延迟”：（setsockopt (socket_name，ipproto_tcp，tcp_nodelay，(char *) &on，sizeof on) ，其中on=1），则不存在粘包现象。

　　2．当发送数据为每包1kb～2kb的不定长数据时，若发送间隔时间小于10ms，偶尔会出现粘包，接收方经预处理线程处理后能正确解开粘在一起的包。

　　3．为测定处理粘包的时间，发送方依次循环发送长度为1.5kb、1.9kb、1.2kb、1.6kb、1.0kb数据，共计1000包。为制造粘包现象，接收线程每次接收前都等待10ms，接收缓冲区设为5000b，结果接收方收到526包数据，其中长度为5000b的有175包。经预处理线程处理可得到1000包正确数据，粘包处理总时间小于1ms。

　　实验结果表明，TCP粘包现象确实存在，但可通过接收方的预处理予以解决，而且处理时间非常短（实验中1000包数据总共处理时间不到1ms），几乎不影响应用程序的正常工作
 
 * 粘包出现原因：在流传输中出现，UDP不会出现粘包，因为它有消息边界(参考Windows 网络编程)
 * 1 发送端需要等缓冲区满才发送出去，造成粘包
 * 2 接收方不及时接收缓冲区的包，造成多个包接收
 */

using SignPressServer.SignDAL;
using SignPressServer.SignData;
using SignPressServer.SignTools;
using SignPressServer.SignLog;


namespace SignPressServer.SignSocket.AsyncSocket
{
    /// <summary>
    /// Socket实现的异步TCP服务器
    /// </summary>
    public class AsyncSocketServer: IDisposable
    {

        #region 字段信息Fields
        /// <summary>
        /// 服务器的监听端口
        /// </summary>
        private const int  LISENT_PORT = 6666;

        /// <summary>
        /// 服务器程序允许的最大客户端连接数
        /// </summary>
        private int m_maxClientCount;

        /// <summary>
        /// 当前的连接的客户端数
        /// </summary>
        private int m_currClientCount;

        /// <summary>
        /// 服务器使用的异步socket
        /// </summary>
        private Socket m_serverSocket;

        /// <summary>
        /// 客户端会话列表
        /// </summary>
        private List<AsyncSocketState> m_clientList;

        private bool disposed = false;

        #endregion

        #region 属性信息Properties

        /// <summary>
        /// 服务器是否正在运行
        /// </summary>
        public bool IsRunning { get; private set; }
        /// <summary>
        /// 监听的IP地址
        /// </summary>
        public IPAddress Address { get; private set; }
        /// <summary>
        /// 监听的端口
        /// </summary>
        public int Port { get; private set; }
        /// <summary>
        /// 通信使用的编码
        /// </summary>
        public Encoding Encoding { get; set; }


        #endregion



        #region 扩展信息域
        private LogerHelper m_log;          // LOG日志文件
        public LogerHelper Log
        {
            get { return this.m_log;}
        }

        //  进行文件传输的服务器
        private FileSocketServer m_fileTcpServer;        // 进行文件传输的TCP服务器
        public FileSocketServer FileTcpServer
        {
            get { return this.m_fileTcpServer; }
            set { this.m_fileTcpServer = value; }
        }
        private const int FILE_TCP_SERVRT_PORT = 6060;


        // modify by gatieme @ 2015-12-12 16:58
        //private MSWordTools m_msofficeServer;               //  生成会签单文件的线程
        //public MSWordTools MSWordServer
        //{
        //    get { return this.m_msofficeServer; }
        //    set { this.m_msofficeServer = value; }
        //}

        private MSOfficeThread m_msofficeServer;               //  生成会签单文件的线程
        public MSOfficeThread MSOfficeServer
        {
            get { return this.m_msofficeServer; }
            set { this.m_msofficeServer = value; }
        }

        //  进行生成会签单信息的线程
        
        #endregion


        #region 构造函数

        /// <summary>
        /// 异步Socket TCP服务器
        /// </summary>
        /// <param name="listenPort">监听的端口</param>
        public AsyncSocketServer(int listenPort)
            : this(IPAddress.Any, listenPort, 65536)
        {
        }

        /// <summary>
        /// 异步Socket TCP服务器
        /// </summary>
        /// <param name="localEP">监听的终结点</param>
        public AsyncSocketServer(IPEndPoint localEP)
            : this(localEP.Address, localEP.Port, 65536)
        {
        }

        /// <summary>
        /// 异步Socket TCP服务器
        /// </summary>
        /// <param name="localIPAddress">监听的IP地址</param>
        /// <param name="listenPort">监听的端口</param>
        /// <param name="maxClientCount">最大客户端数量</param>
        public AsyncSocketServer(IPAddress localIPAddress, int listenPort, int maxClientCount)
        {

            //Console.WriteLine("IP " + localIPAddress + "， PORT " + listenPort);
            this.Address = localIPAddress;
            this.Port = listenPort;
            this.Encoding = Encoding.Default;

            this.m_maxClientCount = maxClientCount;
            this.m_clientList = new List<AsyncSocketState>();
            this.m_serverSocket = new Socket(localIPAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                /*
             * 参数
             * ioControlCode
             * 一个 IOControlCode 值，它指定要执行的操作的控制代码。
             * optionInValue
             * Byte 类型的数组，包含操作要求的输入数据。
             * optionOutValue
             * Byte 类型的数组，包含由操作返回的输出数据。
             */

            this.m_serverSocket.IOControl(IOControlCode.DataToRead, null, BitConverter.GetBytes(0));
            this.m_serverSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.NoDelay, true);



            //  心跳包http://www.cnblogs.com/csMapx/archive/2011/09/04/2166515.html 

            //uint dummy = 0;
            //byte[] inOptionValues = new byte[System.Runtime.InteropServices.Marshal.SizeOf(dummy) * 3];
            //BitConverter.GetBytes((uint)1).CopyTo(inOptionValues, 0);//是否启用Keep-Alive
            //BitConverter.GetBytes((uint)120000).CopyTo(inOptionValues, System.Runtime.InteropServices.Marshal.SizeOf(dummy));//多长时间开始第一次探测
            //BitConverter.GetBytes((uint)120000).CopyTo(inOptionValues, System.Runtime.InteropServices.Marshal.SizeOf(dummy) * 2);//探测时间间隔

            //this.m_serverSocket.IOControl(IOControlCode.KeepAliveValues, inOptionValues, null);

            //this.m_serverSocket.Bind(new IPEndPoint(this.Address, this.Port));  //  绑定服务器和端口
            //this.m_serverSocket.Listen(1024);
            //  相当于如下代码 
            //byte[] buffer = new byte[12];
            //BitConverter.GetBytes(1).CopyTo(buffer, 0);     //  是否启用Keep-Alive
            //BitConverter.GetBytes(1000).CopyTo(buffer, 4);  //  多长时间开始第一次探测
            //BitConverter.GetBytes(1000).CopyTo(buffer, 8);  //  探测时间间隔

            ///  ClientSocket.IOControl(IOControlCode.KeepAliveValues, buffer, null); 
            ///  因此心跳包的设置我们长采用如下代码
            ///  http://blog.csdn.net/educast/article/details/7597829 

            ///  http://www.cnblogs.com/csMapx/archive/2011/09/04/2166515.html 

            
            ///////////////
            // 创建日志文件[2015-6-16 21:10]
            ///////////////
            this.m_log = new LogerHelper();     // 创建一个日志对象，默认设置每天更新一个日志文件
           
            ///////////////
            // 开启文件传输的TCP服务器
            ///////////////
            this.m_fileTcpServer = new FileSocketServer();
            this.m_fileTcpServer.BeginListening(IPAddress.Any, FILE_TCP_SERVRT_PORT);

            ///////////////
            //  开始生成文件的服务
            ///////////////
            this.m_msofficeServer = new MSOfficeThread();
        }

        #endregion

        #region 方法-成员函数Method

        /// <summary>
        /// 启动服务器
        /// 服务器所允许的挂起连接序列的最大长度  默认为1024
        /// </summary>
        public void Start( )
        {
            if (!IsRunning)
            {
                Console.WriteLine("服务器已经启动");
                this.IsRunning = true;
                this.m_serverSocket.Bind(new IPEndPoint(this.Address, this.Port));  //  绑定服务器和端口
                this.m_serverSocket.Listen(1024);
            
                /**
                BeginAccept在异步方式下传入的连接尝试，它允许其他动作而不必等待连接建立才继续执行后面程序。在调用BeginAccept之前，必须使用Listen方法来侦听是否有连接请求，BeginAccept的函数原型为：

                BeginAccept(AsyncCallback AsyncCallback, Ojbect state)
                参数:
                AsyncCallBack：代表回调函数
                state：表示状态信息，必须保证state中包含socket的句柄

                使用BeginAccept的基本流程是：
                (1)创建本地终节点，并新建套接字与本地终节点进行绑定；
                (2)在端口上侦听是否有新的连接请求；
                (3)请求开始接入新的连接，传入Socket的实例或者StateOjbect的实例。
                 */
                try
                {
                    this.m_serverSocket.BeginAccept(new AsyncCallback(HandleAcceptConnected), this.m_serverSocket);

                    /*
                    当BeginAccept()方法调用结束后，一旦新的连接发生，将调用回调函数，
                    而该回调函数必须包括用来结束接入连接操作的EndAccept()方法。
                    该方法参数列表为 Socket EndAccept(IAsyncResult iar)
                    */
                }
                catch (Exception e)
                {
                    //  C- TODO 异常处理
                    Console.WriteLine(e.ToString());
                    this.Log.Write(new LogMessage(e.ToString(), LogMessageType.Exception));
                }
            }
        }

        /// <summary>
        /// 启动服务器
        /// </summary>
        /// <param name="backlog">
        /// 服务器所允许的挂起连接序列的最大长度
        /// </param>
        public void Start(int backlog)
        {
            if (!IsRunning)
            {
                IsRunning = true;
                this.m_serverSocket.Bind(new IPEndPoint(this.Address, this.Port));
                this.m_serverSocket.Listen(backlog);
                this.m_serverSocket.BeginAccept(new AsyncCallback(HandleAcceptConnected), this.m_serverSocket);
            }
        }

        /// <summary>
        /// 停止服务器
        /// </summary>
        public void Stop()
        {
            if (IsRunning)
            {
                this.IsRunning = false;
                this.m_serverSocket.Close( );

                //  TODO 关闭对所有客户端的连接
      
            }
        }

        /// <summary>
        /// 处理客户端连接
        /// BeginAccept的回调函数
        /// 当BeginAccept()方法调用结束后，一旦新的连接发生，将调用回调函数，
        /// 而该回调函数必须包括用来结束接入连接操作的EndAccept()方法。
        /// 该方法参数列表为 Socket EndAccept(IAsyncResult iar)
        /// </summary>
        /// <param name="ar"></param>
        private void HandleAcceptConnected(IAsyncResult ar)
        {
            try
            {
                if (IsRunning)
                {
                    Socket server = (Socket)ar.AsyncState;
                    Socket client = server.EndAccept(ar);   //  EndAccept后，就可以进行正常的通信了

                    //  检查是否达到最大的允许的客户端数目
                    if (this.m_currClientCount >= this.m_maxClientCount)
                    {
                        //C-TODO 触发事件
                        RaiseOtherException(null);
                    }
                    else    // 处理客户端的连接
                    {

                        //  再来，我们可以利用事件在EndCallback触发事件，我再加入一个委派AsyncEventArgs以及AsyncEventHandler
                        //  然后在EndCallback触发AsyncEventHandler，这样一来UI程序便能接收到回报事件状态了。
                        AsyncSocketState state = new AsyncSocketState(client);
                        lock (this.m_clientList)        //  将连接的客户端的信息添加到客户端列表
                        {
                            this.m_clientList.Add(state);
                            this.m_currClientCount++;
                            RaiseClientConnected(state); //  触发客户端连接事件
                            
                            //IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                            //Console.WriteLine("获取到一个来自{0} : {1}的连接, 当前连接的客户端数据{2}", ip.Address, ip.Port, this.m_currClientCount);
                            //this.Log.Write(new LogMessage("获取到一个来自" + ip.Address + " : " + ip.Port + "的连接, 当前连接的客户端数据" + this.m_currClientCount.ToString(), LogMessageType.Information));
                        }

                        ////////////////////////////////////////////////////////////
                        //  modify by gatieme 2015-07-13 21:56
                        //  修复了一处性能BUG, 
                        //  why you allocate new buffers time and time again - 
                        //  this is the only opperation here that should take any resources (CPU/memory)
                        //  at http://stackoverflow.com/questions/9915101/performance-of-receiveasync-vs-beginreceive
                        // 
                        //  设置与客户端的通信的缓冲区
                        //state.RecvDataBuffer = new byte[client.ReceiveBufferSize];
                        ////////////////////////////////////////////////////////////

                        ///  开始接受来自该客户端的数据
                        ///
                        /// 接收数据自BeginRecive开始，
                        /// 调用回调函数函数HandleDataReceived
                        /// 在回调函数中以EndReceive结束
                        client.BeginReceive(state.RecvDataBuffer, 0, state.RecvDataBuffer.Length, SocketFlags.None,
                         new AsyncCallback(HandleDataReceived), state);
                    }

                    //接受下一个请求
                    server.BeginAccept(new AsyncCallback(HandleAcceptConnected), ar.AsyncState);
                }
            }
            catch (Exception e)
            {
                //  C- TODO 异常处理
                Console.WriteLine(e.ToString());
                this.Log.Write(new LogMessage(e.ToString(), LogMessageType.Exception));
                
                ////////////////////////// BIG BUG//
                //  异常后继续监听连接接受下一个请求
                ////////////////////////////////////
                Socket server = (Socket)ar.AsyncState;
                server.BeginAccept(new AsyncCallback(HandleAcceptConnected), ar.AsyncState);
            }
        }


        /// <summary>
        /// 处理客户端数据
        /// </summary>
        /// <param name="ar"></param>
        private void HandleDataReceived(IAsyncResult ar)
        {
            if (IsRunning)
            {
                AsyncSocketState state = (AsyncSocketState)ar.AsyncState;
                Socket client = state.ClientSocket;
                try
                {
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    Console.WriteLine("正在与" + ip.Address + " : " + ip.Port + "进行数据传输...");
                    this.Log.Write(new LogMessage("正在与" + ip.Address + " : " + ip.Port + "进行数据传输...", LogMessageType.Information));

                    //  如果两次开始了异步的接收,所以当客户端退出的时候
                    //  会两次执行EndReceive

                    state.RecvLength = client.EndReceive(ar);   //  异步接收数据结束
                    if (state.RecvLength == 0)
                    {
                        //  C - TODO 触发事件 (关闭客户端)
                        Close(state);
                        RaiseNetError(state);
                        state = null;
                        return;
                    }
                    //TODO 处理已经读取的数据 ps:数据在state的RecvDataBuffer中
                    Console.WriteLine("接收了" + state.RecvLength + "个数据单元");
                    this.Log.Write(new LogMessage("接收了" + state.RecvLength + "个数据单元", LogMessageType.Information));

                    // 处理客户端的数据请求
                    DealClientRequest(state);

                    //C- TODO 触发数据接收事件
                    //RaiseDataReceived(state);
                    /// [服务器异步接收来自客户端的数据]
                    /// 
                    /// 首先是服务器通过BeginReceive开始异步接收客户端的数据
                    /// 在BeginReceive的回调函数HandleDataReceived中，当接收完毕后，服务器调用EndReceive
                    /// 至此异步接收来自服务器的数据完毕
                    if (state != null)
                    {
                        Console.WriteLine("前一个处理信息已经结束, 正在准备等待下一个接收");
                        client.BeginReceive(state.RecvDataBuffer, 0, state.RecvDataBuffer.Length, SocketFlags.None,
                            new AsyncCallback(HandleDataReceived), state);
                    }
                }
                catch (SocketException e)
                {
                    //  C- TODO 异常处理
                    Console.WriteLine(e.ToString());
                    this.Log.Write(new LogMessage(e.ToString(), LogMessageType.Exception));

                    //  modify by gatieme 2015-07-02 9：09
                    Close(state);
                    RaiseNetError(state);
                    //state = null;
                    return;
                }
                catch (IOException ex)
                {
                    //if (IOException.InnerException is System.Net.Sockets.SocketException)
                    //{
                    //    Console.WriteLine("网络中断");
                    //}
                    //else
                    {
                        Console.WriteLine(ex.Message);

                    }
                }
                finally
                {
                    ///// [服务器异步接收来自客户端的数据]
                    ///// 
                    ///// 首先是服务器通过BeginReceive开始异步接收客户端的数据
                    ///// 在BeginReceive的回调函数HandleDataReceived中，当接收完毕后，服务器调用EndReceive
                    ///// 至此异步接收来自服务器的数据完毕
                    //Console.WriteLine("前一个处理信息已经结束, 正在准备等待下一个接收");
                    //client.BeginReceive(state.RecvDataBuffer, 0, state.RecvDataBuffer.Length, SocketFlags.None,
                    // new AsyncCallback(HandleDataReceived), state);
                }
            }
        }

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="state">接收数据的客户端会话</param>
        /// <param name="data">数据报文</param>
        public void Send(AsyncSocketState state, byte[] data)
        {
            RaisePrepareSend(state);
            Send(state.ClientSocket, data);
        }

        /// <summary>
        /// 异步发送数据至指定的客户端
        /// </summary>
        /// <param name="client">客户端</param>
        /// <param name="data">报文</param>
        public void Send(Socket client, byte[] data)
        {
            if (!IsRunning)
                throw new InvalidProgramException("This TCP Scoket server has not been started.");

            if (client == null)
                throw new ArgumentNullException("client");

            if (data == null)
                throw new ArgumentNullException("data");
            client.BeginSend(data, 0, data.Length, SocketFlags.None,
             new AsyncCallback(SendDataEnd), client);
        }

        /// <summary>
        /// 发送数据完成处理函数
        /// </summary>
        /// <param name="ar">目标客户端Socket</param>
        private void SendDataEnd(IAsyncResult ar)
        {
            ((Socket)ar.AsyncState).EndSend(ar);
            RaiseCompletedSend(null);
        }
        #endregion

        #region 事件

        /// <summary>
        /// 与客户端的连接已建立事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> ClientConnected;
        /// <summary>
        /// 与客户端的连接已断开事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> ClientDisconnected;

        /// <summary>
        /// 触发客户端连接事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseClientConnected(AsyncSocketState state)
        {
            if (ClientConnected != null)
            {
                IPEndPoint ip = (IPEndPoint)state.ClientIp;
                Console.WriteLine("获取到一个来自{0} : {1}的连接, 当前连接的客户端数据{2}", ip.Address, ip.Port, this.m_currClientCount);
                this.Log.Write(new LogMessage("获取到一个来自" + ip.Address + " : " + ip.Port + "的连接, 当前连接的客户端数据" + this.m_currClientCount.ToString(), LogMessageType.Information));

                ClientConnected(this, new AsyncSocketEventArgs(state));
            }
        }
        /// <summary>
        /// 触发客户端连接断开事件
        /// </summary>
        /// <param name="client"></param>
        private void RaiseClientDisconnected(Socket client)
        {
            if (ClientDisconnected != null)
            {
                ClientDisconnected(this, new AsyncSocketEventArgs("连接断开"));
            }
        }

        /// <summary>
        /// 接收到数据事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> DataReceived;

        private void RaiseDataReceived(AsyncSocketState state)
        {
            if (DataReceived != null)
            {
                this.DataReceived(this, new AsyncSocketEventArgs(state));
            }
        }

        /// <summary>
        /// 发送数据前的事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> PrepareSend;

        /// <summary>
        /// 触发发送数据前的事件
        /// </summary>
        /// <param name="state"></param>
        private void RaisePrepareSend(AsyncSocketState state)
        {
            if (PrepareSend != null)
            {
                PrepareSend(this, new AsyncSocketEventArgs(state));
            }
        }

        /// <summary>
        /// 数据发送完毕事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> CompletedSend;
        
        /// <summary>
        /// 触发数据发送完毕的事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseCompletedSend(AsyncSocketState state)
        {
            if (CompletedSend != null)
            {
                CompletedSend(this, new AsyncSocketEventArgs(state));
            }
        }

        /// <summary>
        /// 网络错误事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> NetError;
        /// <summary>
        /// 触发网络错误事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseNetError(AsyncSocketState state)
        {
            if (NetError != null)
            {
                NetError(this, new AsyncSocketEventArgs(state));
            }
        }

        /// <summary>
        /// 异常事件
        /// </summary>
        public event EventHandler<AsyncSocketEventArgs> OtherException;
        /// <summary>
        /// 触发异常事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseOtherException(AsyncSocketState state, string descrip)
        {
            if (OtherException != null)
            {
                OtherException(this, new AsyncSocketEventArgs(descrip, state));
            }
        }
        private void RaiseOtherException(AsyncSocketState state)
        {
            RaiseOtherException(state, "");
        }
        #endregion

        #region Close
        /// <summary>
        /// 关闭一个与客户端之间的会话
        /// </summary>
        /// <param name="state">需要关闭的客户端会话对象</param>
        public void Close(AsyncSocketState state)
        {
            //if (state != null && state.ClientSocket.Connected == false)
            if(state != null)
            {
                state.Datagram = null;
                state.RecvDataBuffer = null;

                this.m_clientList.Remove(state);
                this.m_currClientCount--;


                IPEndPoint ip = (IPEndPoint)state.ClientIp;
                Console.WriteLine("客户端终止，关闭了客户端{0}:{1}, 当前连接的客户端数目{2}", ip.Address, ip.Port, this.m_currClientCount);
                this.Log.Write(new LogMessage("客户端终止，关闭了客户端, 当前连接的客户端数目" + this.m_currClientCount, LogMessageType.Error));
                //TODO 触发关闭事件
                state.Close();
                //state = null;
            }
        }
        /// <summary>
        /// 关闭所有的客户端会话,与所有的客户端连接会断开
        /// </summary>
        public void CloseAllClient()
        {
            foreach (AsyncSocketState client in this.m_clientList)
            {
                Close(client);
            }
            this.m_currClientCount = 0;
            this.m_clientList.Clear();
        }
        #endregion

        #region 释放
        /// <summary>
        /// Performs application-defined tasks associated with freeing, 
        /// releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        /// <param name="disposing"><c>true</c> to release 
        /// both managed and unmanaged resources; <c>false</c> 
        /// to release only unmanaged resources.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing)
                {
                    try
                    {
                        //  关闭文件传输服务器 
                        //this.m_fileTcpServer.Stop();
                        //if (this.m_fileTcpServer != null)
                        //{
                        //    this.m_fileTcpServer = null;
                        //}

                        // 关闭word工作线程
                        this.m_msofficeServer.Stop();
                        if (this.m_msofficeServer != null)
                        {
                            this.m_msofficeServer = null;
                        }

                        //  关闭服务器
                        this.Stop();
                        if (this.m_serverSocket != null)
                        {
                            this.m_serverSocket = null;
                        }

                        
                    }
                    catch (SocketException)
                    {
                        //TODO
                        RaiseOtherException(null);
                    }
                }
                disposed = true;
            }
        }
        #endregion

        /// 前面我们提到了服务器异步接收客户端请求的过程
        /// 
        /// 首先是服务器通过BeginReceive开始异步接收客户端的数据
        /// 在BeginReceive的回调函数HandleDataReceived中，当接收完毕后，服务器调用EndReceive
        /// 至此异步接收来自服务器的数据完毕
        /// 
        /// 而我们客户端默认发送数据是先发一个信息请求头，再发请求数据
        /// 因此我们可以这样处理，在BeginReceive回调函数中，异步接收[信息请求头]完毕后，
        /// 枚举信息头，来进行下面的处理，接收进一步的请求数据
        /// 
        /// 因此每增加一项客户端和服务器的通信过程，就可以这样实现，
        /// 在DealClientRequest增加一个枚举头（信息请求头），然后开始异步接收进一步的信息数据
        /// 在其回调函数中接收我们的信息，并将信息进行处理后，将事件处理函数中反馈信息发送至客户端
        /// 
        ///
        /// 例如处理客户端的登录请求
        /// 对应客户端会先发登录请求头LOGIN_REQUEST，然后接着发登录信息User
        /// 在DealClientRequest中增加相应的信息头，然后服务器BeginReceive异步接收登录信息User，
        /// 设置的接收登录信息User的回调函数HandleLoginRequestDataReceived等待接收信息完毕后
        /// 在函数RaiseLoginRequestEvent事件处理函数中处理，进行查询数据库完毕后，将数据发送至客户端
        #region 处理客户端的所有请求
        /// <summary>
        /// 处理客户端的所有请求
        /// </summary>
        /// <param name="ar"></param>
        public void DealClientRequest(AsyncSocketState state)
        {
            //  设置数据包
            state.SocketMessage.Package = Encoding.UTF8.GetString(state.RecvDataBuffer, 0, state.RecvLength);
            Console.WriteLine("接收到的数据{0}, 大小{1}", state.SocketMessage.Package, state.SocketMessage.Package.Length);
            this.Log.Write(new LogMessage("接收到的数据 " + state.SocketMessage.Package + ", 大小" + state.SocketMessage.Package.Length.ToString(), LogMessageType.Information));

            do
            {
                if (state.SocketMessage.Split() == AsyncSocketMessageFlag.MESSAGE_UNKOWN)   // 将数据包分割
                {
                    break;
                }
                //state.SocketMessage.Split();
                //foreach (string str in state.SocketMessage.Splits)
                //{
                //    Console.WriteLine(str);
                //}
                switch (state.SocketMessage.Head)
                {
                    #region   用户基本操作操作--登录, 退出
                    /// <summary>
                    /// ==用户操作==
                    /// 用户登录  LOGIN_REQUEST
                    /// 用户退出  QUIT_REQUEST
                    /// </summary>
                    case "LOGIN_REQUEST":       //  用户登录信息
                        RaiseLoginRequest(state);
                        break;
                    case "QUIT_REQUEST":
                        RaiseQuitRequest(state);    ///  处理用户的退出请求
                        break;
                    case "UPLOAD_PICTURE_REQUEST":          // 上传签字图片
                        RaiseUploadSigaturePicture(state);
                        break;
                    case "DOWNLOAD_HDJCONTRACT":         // 下载会签单
                        RaiseDownloadHDJContract(state);
                        break;
                    #endregion


                    #region 部门操作
                    /// <summary>
                    /// ==部门操作==
                    /// 增加部门  INSERT_DEPARTMENT_REQUEST
                    /// 删除部门  DELETE_DEPARTMENT_REQUEST
                    /// 修改部门  MODIFY_DEPARTMENT_REQUEST
                    /// 查询部门  QUERY_DEPARTMENT_REQUEST
                    /// </summary>
                    case "INSERT_DEPARTMENT_REQUEST":  //  添加部门请求
                        // 开始接收期望添加进入数据的库的部门的信息
                        RaiseInsertDepartmentRequest(state);
                        break;

                    case "DELETE_DEPARTMENT_REQUEST":
                        RaiseDeleteDepartmentRequest(state);
                        break;

                    case "MODIFY_DEPARTMENT_REQUEST":
                        RaiseModifyDepartmentRequest(state);
                        break;

                    case "QUERY_DEPARTMENT_REQUEST":
                        // 注意查询部门的时候，客户端只需要发送请求信息头就可以了
                        /*state.ClientSocket.BeginReceive(state.RecvDataBuffer, 0, state.RecvDataBuffer.Length, SocketFlags.None,
                            new AsyncCallback(HandleQueryDepartmentRequestDataReceived), state);*/
                        RaiseQueryDepartmentRequest(state);
                        break;

                    // modify by gatieme at 2015-08-26
                    case "INSERT_SDEPARTMENT_REQUEST":  //  添加部门请求
                        // 开始接收期望添加进入数据的库的部门的信息
                        RaiseInsertSDepartmentRequest(state);
                        break;
                    case "QUERY_SDEPARTMENT_REQUEST":
                        RaiseQuerySDepartmentRequest(state);
                        break;

                    case "MODIFY_SDEPARTMENT_REQUEST":
                        RaiseModifySDepartmentRequest(state);
                        break;

                    #endregion  部门操作


                    #region 员工操作
                    /// <summary>
                    /// ==员工操作==
                    /// 增加员工  INSERT_EMPLOYEE_REQUEST
                    /// 删除员工  DELETE_EMPLOYEE_REQUEST
                    /// 修改员工  MODIFY_EMPLOYEE_REQUEST
                    /// 查询员工  QUERY_ERMPLOYEE_REQUEST
                    /// </summary>
                    case "INSERT_EMPLOYEE_REQUEST":
                        RaiseInsertEmployeeRequest(state);
                        break;
                    case "DELETE_EMPLOYEE_REQUEST":
                        RaiseDeleteEmployeeRequest(state);
                        break;
                    case "MODIFY_EMPLOYEE_REQUEST":
                        RaiseModifyEmployeeRequest(state);
                        break;
                    case "QUERY_EMPLOYEE_REQUEST":
                        RaiseQueryEmployeeRequest(state);
                        break;
                    case "MODIFY_EMP_PWD_REQUEST":
                        RaiseModifyEmployeePasswordRequest(state);
                        break;
                    #endregion


                    #region  会签单模版操作
                    /// <summary>
                    /// ==会签单模版操作==
                    /// 增加会签单模版  INSERT_CONTRACT_TEMPLATE_REQUEST
                    /// 删除会签单模版  DELETE_CONTRACT_TEMPLATE_REQUEST
                    /// 修改会签单模版  MODIFY_CONTRACT_TEMPLATE_REQUEST
                    /// 查询会签单模版  QUERY_CONTRACT_TEMPLATE_REQUEST
                    /// </summary>
                    case "INSERT_CONTRACT_TEMPLATE_REQUEST":
                        RaiseInsertContractTemplateRequest(state);
                        break;

                    case "DELETE_CONTRACT_TEMPLATE_REQUEST":
                        RaiseDeleteContractTemplateRequest(state);
                        break;
                    case "MODIFY_CONTRACT_TEMPLATE_REQUEST":
                        RaiseModifyContractTemplateRequest(state);
                        break;
                    case "QUERY_CONTRACT_TEMPLATE_REQUEST":
                        RaiseQueryContractTemplateRequest(state);
                        break;
                    case "GET_CONTRACT_TEMPLATE_REQUEST":
                        RaiseGetContractTemplateRequest(state);
                        break;
                    #endregion


                    #region 会签单的基本操作--插入, 删除, 修改, 查询[2015-12-17 10:49:01 在会签单操作中加入了工作量的信息]
                    /// <summary>
                    /// ==航道局会签单操作==
                    /// 增加会签单模版  INSERT_HDJCONTRACT_REQUEST
                    /// 删除会签单模版  DELETE_HDJCONTRACT_REQUEST
                    /// 修改会签单模版  MODIFY_HDJCONTRACT_REQUEST
                    /// 查询会签单模版  QUERY_HDJCONTRACT_REQUEST
                    /// </summary>
                    case "INSERT_HDJCONTRACT_REQUEST":
                        RaiseInsertHDJContractRequest(state);
                        break;
                    case "DELETE_HDJCONTRACT_REQUEST":
                        RaiseDeleteHDJContractRequest(state);
                        break;
                    case "MODIFY_HDJCONTRACT_REQUEST":
                        RaiseModifyHDJContractRequest(state);
                        break;
                    case "QUERY_HDJCONTRACT_REQUEST":
                        RaiseQueryHDJContractReuqest(state);
                        break;
                    case "GET_HDJCONTRACT_REQUEST":
                        RaiseGetHDJContractRequest(state);
                        break;
                    case "GET_HDJCONTRACT_WITH_WORKLOAD_REQUEST":
                        RaiseGetHDJContractWithWorkloadRequest(state);
                        break;
                    #endregion


                    #region 提交人的会签单状态操作
                    /// <summary>
                    /// ==提交人的会签单状态操作==
                    /// 查询正在审核会签单  QUERY_SIGN_PEND_REQUEST
                    /// 查询已经通过会签单  QUERY_SIGN_AGREE_REQUEST
                    /// 查询被拒绝的会签单  QUERY_SIGN_REFUSE_REQUEST
                    /// </summary>

                    case "QUERY_SIGN_PEND_REQUEST":
                        RaiseQuerySignatureStatusPenddingRequest(state);
                        break;
                    case "QUERY_SIGN_AGREE_REQUEST":
                        RaiseQuerySignatureStatusAgreeRequest(state);
                        break;
                    case "QUERY_SIGN_REFUSE_REQUEST":
                        RaiseQuerySignatureStatusRefuseRequest(state);
                        break;

                    case "SEARCH_AGREE_HDJCONTRACT_REQUEST":
                        RaiseSearchAgreeHDJContractRequest(state);
                        break;

                    case "QUERY_AGREE_UNDOWN_REQUEST":
                        RaiseQueryAgreeUndownloadHDJContract(state);
                        break;
                    #endregion


                    #region 签字人的会签单查询操作
                    /// <summary>
                    /// ==签字人的会签单操作==
                    /// 查询本人需要签字的会签单    QUERY_UNSIGN_CONTRACT_REQUEST
                    /// 查询本人已经签字会签单  QUERY_SIGNED_CONTRACT_REQUEST
                    /// 进行签字确认  QUERY_SIGN_REFUSE_REQUEST
                    /// </summary>
                    case "QUERY_UNSIGN_CONTRACT_REQUEST":
                        RaiseQueryUnsignContractRequest(state);
                        break;

                    case "QUERY_SIGNED_CONTRACT_REQUEST":
                        RaiseQuerySignedContractRequest(state);
                        break;

                    case "QUERY_SIGNED_CONTRACT_TOP_REQUEST":
                        RaiseQuerySignedContractTopRequest(state);
                        break;

                    case "SEARCH_SIGNED_HDJCONTRACT_REQUEST":
                        RaiseSearchSignedHDJContractRequest(state);
                        break;
                    #endregion


                    #region 签字人的会签单签字操作
                    /// <summary>
                    /// ==签字人的签字操作==
                    /// 用户对某个单子进行签字    INSERT_SIGN_DETAIL_REQUEST
                    /// 用户查询自己的签单明细  QUERY_SIGN_DETAIL_REQUEST
                    /// 签字人查询自己EMP对于会签单CON的请求  QUERY_SIGN_DETAIL_EMP_CON_REQUEST
                    /// </summary>
                    case "INSERT_SIGN_DETAIL_REQUEST":      // 用户对某个单子进行签字
                        RaiseInsertSignDetailRequest(state);
                        ////////  此处数据库里会进行判断一个签字阶段是否结束
                        ////////  同时应用程序会判断一个会签单时候可以生成
                        ////  会签单信息已经完成，直接生成会签单信息

                        break;
                    case "QUERY_SIGN_DETAIL_REQUEST":      // 用户查询自己的签单明细
                        RaiseQuerySignDetailRequest(state);
                        break;
                    case "QUERY_SIGN_DETAIL_CON_REQUEST":   // 签字人查询自己EMP对于会签单CON的请求
                        RaiseQuerySignDetailContractRequest(state);
                        break;
                    #endregion


                    #region 工作量的处理操作
                    /// <summary>
                    /// ==处理工作量信息==
                    /// </summary>
                    case "INSERT_WORKLOAD_REQUEST":
                        RaiseInsertWorkloadRequest(state);
                        break;
                    case "DELETE_WORKLOAD_REQUEST":
                        RaiseDeleteWorkloadRequest(state);
                        break;
                    case "MODIFY_WORKLOAD_REQUEST":
                        RaiseModifyWorkloadRequest(state);
                        break;
                    case "QUERY_WORKLOAD_REQUEST":
                        RaiseModifyWorkloadRequest(state);
                        break;
                    #endregion


                    #region 新增统计功能
                    /// <summary>
                    /// ==新增统计功能==
                    /// </summary>
                    ///  获取
                    case "GET_CATEGORY_YEAR_CONTRACT_COUNT_REQUEST":       // 获取当年已经签署的CATEGORY的会签单数目
                        RaiseGetCategoryYearContractCountRequest(state);
                        break;

                    case "GET_DEP_CATE_YEAR_CON_COUNT_REQUEST":      // [2015/12/17]编号最后两位的数目是当年部门department本年度year分类category下的会签单数目
                        RaiseGetDepartmentCategoryYearContractCountRequest(state);
                        break;

                    case "QUERY_SDEP_CON_CATEGORY_REQUEST":     //  用于在申请会签单时，根据部门获取对应的可申请权限
                        //  暂时使用此接口而废弃下一个接口  QUERY_SDEPARTMENT_CATEGORY_REQUEST
                        //  使用此接口需要在获取时候每次都向数据库获取当前部门的权限信息
                        //  但是接口使用起来比较方便
                        RaiseQuerySDepartmentContractCategoryRequest(state);
                        break;
                    case "STATISTIC_DEP_YEAR_PRO_REQUEST":
                        RaiseStatisticDepartmentYearProjectRequest(state);
                        break;
                    #endregion


                    #region  会签单工程的管理
                    case "INSERT_PROJECT_REQUEST":        //  插入任务工作量信息
                        RaiseInsertProjectRequest(state);
                        break;
                    case "DELETE_PROJECT_REQUEST":        //  删除任务工作量信息
                        RaiseDeleteProjectRequest(state);
                        break;
                    case "MODIFY_PROJECT_REQUEST":        //  修改任务工作量信息
                        RaiseModifyProjectRequest(state);
                        break;
                    #endregion


                    #region ITEM任务量处理
                    case "INSERT_ITEM_REQUEST":        //  插入任务工作量信息
                        RaiseInsertItemRequest(state);
                        break;
                    case "DELETE_ITEM_REQUEST":        //  删除任务工作量信息
                        RaiseDeleteItemRequest(state);
                        break;
                    case "MODIFY_ITEM_REQUEST":        //  修改任务工作量信息
                        RaiseModifyItemRequest(state);
                        break;
                    //case "QUERY_SDEPARTMENT_CATEGORY_REQUEST":        //  用于在申请会签单时获取带部门带可申请权限的全信息部门信息
                    //  此接口暂时废弃，，
                    //  使用此方法可以使用户选择时无需每次都向服务器提交REQUEST
                    //  但是可能需要在Department中增加新的数据成员
                    //RaiseQuerySDepartmentCategoryRequest(state);
                    //break;
                    case "QUERY_CATEGORY_PROJECT_REQUEST":
                        RaiseQueryCategoryProjectRequest(state);
                        break;
                    case "QUERY_PROJECT_ITEM_REQUEST":
                        RaiseQueryProjectItemRequest(state);
                        break;
                    case "QUERY_PROJECT_ITEM_BY_NAME_REQUEST":      //  add by gatieme at 2015-12--30 0:01
                        //  因为会前单中只存储了相对应的string没有存储id
                        RaiseQueryProjectItemByProjectNameRequest(state);
                        break;
                    case "QUERY_CONTRACT_WORKLOAD_REQUEST":
                        RaiseQueryContractWorkloadRequest(state);
                        break;
                    #endregion



                }
                //this.Close(state);
            }while(state.SocketMessage.Flag != AsyncSocketMessageFlag.MESSAGE_RIGHT);
        }
        #endregion

        

        #region 处理客户端的登录请求
        /// <summary>
        /// 用户登录请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseLoginRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的登录信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的登录信息" + state.SocketMessage.Message, LogMessageType.Information));
            
            //string LOGIN_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            User user = JsonConvert.DeserializeObject<User>(state.SocketMessage.Message);
            Employee employee = new Employee();
            employee = DALEmployee.LoginEmployee(user);        //  如果用户名和密码验证成功
            if(employee.Id != -1)
            {
                Console.WriteLine(user + "用户名密码均正确，可以登录");
                this.Log.Write(new LogMessage(user + "用户名密码均正确，可以登录", LogMessageType.Success));
                response = ServerResponse.LOGIN_SUCCESS;               //  用户登录成功信号   
            }
            else
            {
                Console.WriteLine(user + "用户名密码验证失败，无法正常登录");
                this.Log.Write(new LogMessage(user + "用户名密码验证失败，无法正常登录", LogMessageType.Error));

                response = ServerResponse.LOGIN_FAILED;               //  用户登录成功信号   
            }
            //  将响应信号发送至客户端
            if (response.Equals(ServerResponse.LOGIN_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, employee);
                //String json = JsonConvert.SerializeObject(employee);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
                //Console.WriteLine("发送给")
            }
            else
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                //String json = JsonConvert.SerializeObject(employee);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }


        #endregion


        #region  退出请求
        private void RaiseQuitRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的退出信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的退出信息" + state.SocketMessage.Message, LogMessageType.Information));
            
            //  用户请求退出时，无需返回信息，直接销毁用户的信息即可
            //Close(state);
            //state = null;
            
        }
        #endregion


        #region 部门信息的处理（多个处理段[插入-删除-修改-查询]）


        #region 处理客户端的插入部门请求
        /// <summary>
        /// 用户登录请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertDepartmentRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入部门信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的部门信息" + state.SocketMessage.Message, LogMessageType.Information));
       
            ServerResponse response = new ServerResponse(); 

            // json数据解包
            Department department = JsonConvert.DeserializeObject<Department>(state.SocketMessage.Message);
            bool result = DALDepartment.InsertDepartment(department);
            if (result == true)
            {
                Console.WriteLine("部门{0}插入成功", department);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入成功", LogMessageType.Success));
                
                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_DEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}插入失败", department.Name);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入失败", LogMessageType.Error));
                
                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_DEPARTMENT_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }
        #endregion


        #region 处理客户端的插入S部门请求
        /// <summary>
        /// 用户登录请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertSDepartmentRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入部门信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的部门信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            SDepartment department = JsonConvert.DeserializeObject<SDepartment>(state.SocketMessage.Message);
            bool result = DALSDepartment.InsertSDepartment(department);
            if (result == true)
            {
                Console.WriteLine("部门{0}插入成功", department);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_SDEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}插入失败", department.Name);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_SDEPARTMENT_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }

        #endregion


        #region 处理客户端的删除部门请求    
        /// <summary>
        /// 用户删除部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseDeleteDepartmentRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待删除部门编号{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待删除的部门编号" + state.SocketMessage.Message, LogMessageType.Information));
      
            ServerResponse response = new ServerResponse(); 

            // json数据解包
            int departmentId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            
            //  要删除部门时首先判断该部门的员工个数是否为0
            if (DALEmployee.QueryDepartmentEmployeeCount(departmentId) > 0)
            {
                response = ServerResponse.DELETE_DEPARTMENT_EXIST_EMPLOYEE;
            }
            else
            {
                bool result = DALDepartment.DeleteDepartment(departmentId);

                if (result == true)
                {
                    Console.WriteLine("部门{0}删除成功", departmentId);
                    this.Log.Write(new LogMessage("部门" + departmentId + "删除成功", LogMessageType.Success));

                    response = ServerResponse.DELETE_DEPARTMENT_SUCCESS;               //  用户登录成功信号   
                }
                else
                {
                    Console.WriteLine("部门{0}删除失败", departmentId);
                    this.Log.Write(new LogMessage("部门" + departmentId + "删除失败", LogMessageType.Error));

                    //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                    response = ServerResponse.DELETE_DEPARTMENT_FAILED;
                }
            }
            //  删除部门的响应信息只包含响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
        }

        #endregion


        #region 处理客户端的修改部门请求
        /// <summary>
        /// 用户修改部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyDepartmentRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待修改部门信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待修改的部门信息" + state.SocketMessage.Message, LogMessageType.Information));
  

            ServerResponse response = new ServerResponse();

            // json数据解包
            Department department = JsonConvert.DeserializeObject<Department>(state.SocketMessage.Message);

            //  首先检测



            bool result = DALDepartment.ModifyDepartment(department);

            if (result == true)
            {
                Console.WriteLine("部门{0}, {1}修改成功", department.Id, department.Name);
                this.Log.Write(new LogMessage("部门" + department.Id + ", " + department.Name + "修改成功", LogMessageType.Success));

                //MODIFY_DEPARTMENT_RESPONSE = "MODIFY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_DEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}, {1}修改失败", department.Id, department.Name);
                this.Log.Write(new LogMessage("部门" + department.Id + ", " + department.Name + "修改失败", LogMessageType.Error));

                //MODIFY_DEPARTMENT_RESPONSE = "MODIFY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_DEPARTMENT_FAILED;
            }

            // 修改部门的响应信息只包含响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package)); 
        }

        #endregion


        #region 处理客户端的查询部门Department请求
        /// <summary>
        /// 处理客户端的查询部门请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryDepartmentRequest(AsyncSocketState state)
        {
            List<Department> departments = new List<Department>();
            ServerResponse response = new ServerResponse();

            // 向数据库中查询部门的信息
            departments = DALDepartment.QueryDepartment();
            if (departments != null)
            {
                Console.WriteLine("部门信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "部门信息查询成功", LogMessageType.Success));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_DEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "部门信息查询失败", LogMessageType.Error));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_DEPARTMENT_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_DEPARTMENT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, departments);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion
        

        #region 处理客户端的插入部门请求

        /// 带权限的插入操作请使用RaiseInsertDepartmentRequest
        /// 因为在部门插入的时候，权限信息可以作为迷人信息进行插入
        private void RaiseInsertSDepartmentReuqest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入部门信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的部门信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            SDepartment department = JsonConvert.DeserializeObject<SDepartment>(state.SocketMessage.Message);
            bool result = DALSDepartment.InsertSDepartment(department);
            if (result == true)
            {
                Console.WriteLine("部门{0}插入成功", department);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_DEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}插入失败", department.Name);
                this.Log.Write(new LogMessage("部门" + department.Name + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_DEPARTMENT_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }
        #endregion


        #region 处理客户端的修改部门SDepartment请求
        /// <summary>
        /// 用户修改部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifySDepartmentRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待修改部门信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待修改的部门信息" + state.SocketMessage.Message, LogMessageType.Information));
  
            ServerResponse response = new ServerResponse();

            // json数据解包
            SDepartment department = JsonConvert.DeserializeObject<SDepartment>(state.SocketMessage.Message);

            //  首先检测
            bool result = DALSDepartment.ModifySDepartment(department);

            if (result == true)
            {
                Console.WriteLine("部门{0}, {1}修改成功", department.Id, department.Name);
                this.Log.Write(new LogMessage("部门" + department.Id + ", " + department.Name + "修改成功", LogMessageType.Success));

                //MODIFY_DEPARTMENT_RESPONSE = "MODIFY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_SDEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}, {1}修改失败", department.Id, department.Name);
                this.Log.Write(new LogMessage("部门" + department.Id + ", " + department.Name + "修改失败", LogMessageType.Error));

                //MODIFY_DEPARTMENT_RESPONSE = "MODIFY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_SDEPARTMENT_FAILED;
            }

            // 修改部门的响应信息只包含响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package)); 
        }

        #endregion


        #region 处理客户端的查询部门详细请求（包括当前部门的会签单申请权限）
        /// <summary>
        /// 处理客户端的查询部门请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySDepartmentRequest(AsyncSocketState state)
        {
            List<SDepartment> departments = new List<SDepartment>();
            ServerResponse response = new ServerResponse();

            // 向数据库中查询部门的信息
            departments = DALSDepartment.QuerySDepartment();
            if (departments != null)
            {
                Console.WriteLine("部门信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "部门信息查询成功", LogMessageType.Success));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SDEPARTMENT_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "部门信息查询失败", LogMessageType.Error));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SDEPARTMENT_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SDEPARTMENT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, departments);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #endregion // 部门信息的处理（多个处理段[插入-删除-修改-查询]）


        #region 员工信息的处理(多个处理端[插入-删除-修改-查询])


        #region 处理客户端的插入人员请求
        /// <summary>
        /// 插入员工请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertEmployeeRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到的来自{0}的待插入员工信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到的来自" + state.ClientIp + "的待插入员工信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            Employee employee = JsonConvert.DeserializeObject<Employee>(state.SocketMessage.Message);
            
            //  首先判断员工信息是否存在，主要检查用户是否存在用户表中
            //  由于用户表的主键ID是自动生成的，
            //  因此我们检查唯一的成员信息，比如username
            if (DALEmployee.IsEmployeeExist(employee) == true)          //  如果
            {
                response = ServerResponse.INSERT_EMPLOYEE_EXIST;
            }
            else
            {
                bool result = DALEmployee.InsertEmployee(employee);
                if (result == true)
                {
                    Console.WriteLine("员工{0}插入成功", employee.Name);
                    this.Log.Write(new LogMessage("员工" + employee.Name + "插入成功", LogMessageType.Success));

                    response = ServerResponse.INSERT_EMPLOYEE_SUCCESS;               //  用户登录成功信号         
                }
                else
                {
                    Console.WriteLine("员工{0}插入失败", employee.Name);
                    this.Log.Write(new LogMessage("员工" + employee.Name + "插入失败", LogMessageType.Error));

                    //INSERT_EMPLOYEE_RESPONSE = "INSERT_EMPLOYEE_FAILED";                //  用户登录失败信号
                    response = ServerResponse.INSERT_EMPLOYEE_FAILED;
                }
            }
            if (response.Equals(ServerResponse.INSERT_EMPLOYEE_SUCCESS))
            {
                //  插入员工的响应信息只包含头信息
                employee = DALEmployee.GetEmployee(employee.User.Username);
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, employee.Id);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else
            {
                //  插入员工的响应信息只包含头信息
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 处理客户端的删除员工请求
        /// <summary>
        /// 用户删除部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseDeleteEmployeeRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待删除员工信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待删除员工信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            
            //  首先判断当前员工是否存在提交的会签字单子
            if (DALHDJContract.GetEmployeeSubmitedHDJContractCount(employeeId) > 0)
            {
                response = ServerResponse.DELETE_EMPLOYEE_EXIST_CONTRACT;
            }
            else if (DALContractTemplate.GetEmployeeContractTemplateCount(employeeId) > 0)
            {   // 当前员工与某个会签单模版相关联，删除可能导致模版信息不完整， 无法删除
                response = ServerResponse.DELETE_EMPLOYEE_EXIST_CONTEMP;
            }
            else
            {
                bool result = DALEmployee.DeleteEmployee(employeeId);

                if (result == true)
                {
                    Console.WriteLine("员工{0}删除成功", employeeId);
                    this.Log.Write(new LogMessage(state.ClientIp + "员工" + employeeId + "删除成功", LogMessageType.Success));

                    //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                    response = ServerResponse.DELETE_EMPLOYEE_SUCCESS;
                }
                else
                {
                    Console.WriteLine("部门{0}删除失败", employeeId);
                    this.Log.Write(new LogMessage(state.ClientIp + "部门" + employeeId + "删除失败", LogMessageType.Error));

                    //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                    response = ServerResponse.DELETE_EMPLOYEE_FAILED;
                }
            }
            //  删除员工的响应信息只包含头信息
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 处理客户端的修改员工请求
        /// <summary>
        /// 用户修改部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyEmployeeRequest(AsyncSocketState state)
        {

            Console.WriteLine("接收到来自{0}的待修改员工信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待修改员工信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            Employee employee = JsonConvert.DeserializeObject<Employee>(state.SocketMessage.Message);
            bool result = DALEmployee.ModifyEmployee(employee);

            if (result == true)
            {
                Console.WriteLine(state.ClientIp + "员工{0}, {1}修改成功", employee.Id, employee.Name);
                this.Log.Write(new LogMessage(state.ClientIp + "员工" + employee.Id + ", " + employee.Name + "修改成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_EMPLOYEE_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "员工{0}修改失败", employee.Name);
                this.Log.Write(new LogMessage(state.ClientIp + "员工" + employee.Name + "修改失败", LogMessageType.Error));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_EMPLOYEE_FAILED;
            }

            // 修改员工额响应信息至包含响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }
        #endregion
   

        #region 查询部门员工的信息请求
        /// <summary>
        /// 处理客户端的查询员工请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryEmployeeRequest(AsyncSocketState state)
        {
            Console.WriteLine("客户端{0}待查询的部门的ID = {1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage(state.ClientIp + "待查询的员工的编号 = " + state.SocketMessage.Message, LogMessageType.Information));
            
            
            //String QUERY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            int departmentId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            Console.WriteLine(departmentId);
            List<Employee> employees = DALEmployee.QueryEmployee(departmentId);

            this.Log.Write(new LogMessage(state.ClientIp + "查询到的部门编号为" + state.SocketMessage.Message + "的所有员工", LogMessageType.Information));

            if (employees != null)
            {
                Console.WriteLine("部门{0}的员工信息查询成功", state.SocketMessage.Message);
                this.Log.Write(new LogMessage(state.ClientIp + "部门" + state.SocketMessage.Message + "的员工信息查询成功", LogMessageType.Success));
                
                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_EMPLOYEE_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}的员工信息查询失败", state.SocketMessage.Message);
                this.Log.Write(new LogMessage(state.ClientIp + "部门" + state.SocketMessage.Message + "的员工信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_EMPLOYEE_FAILED;
            }
           
            //  查询部门成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_EMPLOYEE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, employees);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion

        #region 修改员工的密码
        /// <summary>
        /// 修改员工的密码
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyEmployeePasswordRequest(AsyncSocketState state)
        {
            Console.WriteLine("客户端{0}待修改的密码的信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage(state.ClientIp + "待修改的密码的信息 = " + state.SocketMessage.Message, LogMessageType.Information));


            ServerResponse response = new ServerResponse();

            User user = JsonConvert.DeserializeObject<User>(state.SocketMessage.Message);
            Console.WriteLine(user);
            bool result = DALEmployee.ModifyEmployeePassword(user);

            this.Log.Write(new LogMessage(state.ClientIp + "待修改的密码的信息" + state.SocketMessage.Message, LogMessageType.Information));

            if (result == true)
            {
                Console.WriteLine("修改{0}的员工密码查询成功", state.SocketMessage.Message);
                this.Log.Write(new LogMessage(state.ClientIp + "修改" + state.SocketMessage.Message + "的员工密码成功", LogMessageType.Success));

                response = ServerResponse.MODIFY_EMP_PWD_SUCCESS;
            }
            else
            {
                Console.WriteLine("部门{0}的员工密码查询成功", state.SocketMessage.Message);
                this.Log.Write(new LogMessage(state.ClientIp + "修改" + state.SocketMessage.Message + "的员工密码失败", LogMessageType.Error));

                response = ServerResponse.MODIFY_EMP_PWD_FAILED;
            }

   
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            
        }

        #endregion


        #endregion // 员工信息的处理(多个处理端[插入-删除-修改-查询])


        #region 会签单模版的处理(多个处理段[插入-删除-修改-查询])
        
        
        #region 处理客户端的插入会签单模版的请求
        /// <summary>
        /// 处理客户端的插入会签单模版的请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertContractTemplateRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待插入会签单模版" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待插入会签单模版" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractTemplate conTemp = JsonConvert.DeserializeObject<ContractTemplate>(state.SocketMessage.Message);
            bool result = DALContractTemplate.InsertContractTemplate(conTemp);
            
            if (result == true)
            {
                Console.WriteLine("会签单模版{0}插入成功", conTemp.Name);
                this.Log.Write(new LogMessage("会签单模版" + conTemp.Name + "插入成功", LogMessageType.Success));
                
                //  用户登录成功信号
                response = ServerResponse.INSERT_CONTRACT_TEMPLATE_SUCCESS;
                   
            }
            else
            {
                Console.WriteLine("会签单模版{0}插入失败", conTemp.Name);
                this.Log.Write(new LogMessage("会签单模版" + conTemp.Name + "插入失败", LogMessageType.Error));

                response = ServerResponse.INSERT_CONTRACT_TEMPLATE_FAILED;                //  用户登录失败信号
            }

            //  插入会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 处理客户端的删除会签单模版的请求
        /// <summary>
        /// 用户删除部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseDeleteContractTemplateRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待删除会签单模版编号" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待插入会签单模版编号" + state.SocketMessage.Message, LogMessageType.Information));
            
            //string DELETE_DEPARTMENT_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            int conTempId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);

            //  判断与当前会签单模版相关联的会签单数目
            if (DALContractTemplate.GetContractTemplateHDJContractCount(conTempId) > 0)
            {
                response = ServerResponse.DELETE_CONTRACT_TEMPLATE_EXIST_CONTRACT;
            }
            else
            {

                bool result = DALContractTemplate.DeleteContactTemplate(conTempId);//

                if (result == true)
                {
                    Console.WriteLine("会签单模版{0}删除成功", conTempId);
                    this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + conTempId.ToString() + "删除成功", LogMessageType.Success));

                    //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                    response = ServerResponse.DELETE_CONTRACT_TEMPLATE_SUCCESS;
                }
                else
                {
                    Console.WriteLine("会签单模版{0}删除失败", conTempId);
                    this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + conTempId + "删除失败", LogMessageType.Error));

                    //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                    response = ServerResponse.DELETE_CONTRACT_TEMPLATE_FAILED;
                }
            }
            //  删除会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 处理客户端的修改会签单模版请求
        /// <summary>
        /// 用户修改部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyContractTemplateRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待修改会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待插入会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));
     
            //string MODIFY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractTemplate conTemp = JsonConvert.DeserializeObject<ContractTemplate>(state.SocketMessage.Message);
            bool result = DALContractTemplate.ModifyContractTemplate(conTemp);

            if (result == true)
            {
                Console.WriteLine(state.ClientIp + "会前的那模版{0}, {1}修改成功", conTemp.TempId.ToString(), conTemp.Name);
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + conTemp.TempId.ToString() + ", " + conTemp.Name + "修改成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_CONTRACT_TEMPLATE_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "会签单模版{0}删除失败", conTemp.TempId.ToString());
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + conTemp.Name + "修改失败", LogMessageType.Error));

                // MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_CONTRACT_TEMPLATE_FAILED;
            }
            //  修改会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 查询会签单模版的信息请求
        /// <summary>
        /// 处理客户端的查询员工请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryContractTemplateRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));
  
            ServerResponse response = new ServerResponse();

            List<ContractTemplate> conTemps = DALContractTemplate.QueryContractTemplate();
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有的会签单", LogMessageType.Information));

            if (conTemps != null)
            {
                Console.WriteLine("会签单模版信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_CONTRACT_TEMPLATE_SUCCESS;
            }
            else
            {
                Console.WriteLine("会签单模版信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_CONTRACT_TEMPLATE_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_CONTRACT_TEMPLATE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, conTemps);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region  获取会签单模版的信息
        /// <summary>
        /// 获取会签单模版的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseGetContractTemplateRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待获取会签单模版编号" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待获取会签单模版编号" + state.SocketMessage.Message, LogMessageType.Information));

            //string MODIFY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            int conTempId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            ContractTemplate conTemp = DALContractTemplate.GetContractTemplate(conTempId);

            if (conTemp != null)
            {
                Console.WriteLine(state.ClientIp + "获取会签单模版{0}成功", conTempId);
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单模版" + conTempId + "成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.GET_CONTRACT_TEMPLATE_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "获取会签单模版{0}失败", conTempId.ToString());
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单模版" + conTempId + "失败", LogMessageType.Error));

                // MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.GET_CONTRACT_TEMPLATE_FAILED;
            }
            
            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.GET_CONTRACT_TEMPLATE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, conTemp);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion
        
        #endregion  //  处理会签单模版的信息 

    
        #region 会签单的处理(多个处理段[插入-删除-修改-查询])
        

        #region 处理客户端的插入会签单的请求
        /// <summary>
        /// 处理客户端的插入会签单的请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待插入会签单信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待插入会签单信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            HDJContractWithWorkload contract = JsonConvert.DeserializeObject<HDJContractWithWorkload>(state.SocketMessage.Message);

            if (DALHDJContractWithWorkload.IsHDJContractExist(contract.Id) == true)
            {
                response = ServerResponse.INSERT_HDJCONTRACT_EXIST;
            }
            else
            {
                bool result = DALHDJContractWithWorkload.InsertHDJContractWithWorkload(contract) == true;

                if (result == true)
                {
                    Console.WriteLine("会签单{0}插入成功", contract.Id);
                    this.Log.Write(new LogMessage("会签单" + contract.Id + "插入成功", LogMessageType.Success));

                    //  用户登录成功信号
                    response = ServerResponse.INSERT_HDJCONTRACT_SUCCESS;
                }
                else
                {
                    Console.WriteLine("会签单模版{0}插入失败", contract.Id);
                    this.Log.Write(new LogMessage("会签单模版" + contract.Id + "插入失败", LogMessageType.Error));

                    response = ServerResponse.INSERT_HDJCONTRACT_FAILED;                //  用户登录失败信号
                }
            }
            //  插入会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 处理客户端的删除会签单的请求
        /// <summary>
        /// 用户删除部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseDeleteHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待删除会签单模版编号" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待插入会签单模版编号" + state.SocketMessage.Message, LogMessageType.Information));
            
            //string DELETE_DEPARTMENT_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            string contractId = JsonConvert.DeserializeObject<string>(state.SocketMessage.Message);
            bool result = DALHDJContractWithWorkload.DeleteHDJContractWithWorkload(contractId);
           
            if (result == true)
            {
                Console.WriteLine("会签单{0}删除成功", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "会签单" + contractId.ToString() + "删除成功", LogMessageType.Success));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.DELETE_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("会签单模版{0}删除失败", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + contractId + "删除失败", LogMessageType.Error));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.DELETE_HDJCONTRACT_FAILED;
            }
            //  删除会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 处理客户端的修改会签单请求
        /// <summary>
        /// 用户修改部门请求的事件的具体信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待修改会签单信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待修改会签单信息" + state.SocketMessage.Message, LogMessageType.Information));
     
            //string MODIFY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            HDJContractWithWorkload contract = JsonConvert.DeserializeObject<HDJContractWithWorkload>(state.SocketMessage.Message);
            //bool result = DALHDJContract.ModifyHDJContract(contract);
            bool result = DALHDJContractWithWorkload.ModifyHDJContractWithWorkload(contract);
            if (result == true)
            {
                Console.WriteLine(state.ClientIp + "会签单信息{0}, {1}修改成功", contract.Id.ToString(), contract.Name);
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + contract.Id.ToString() + ", " + contract.Name + "修改成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "会签单模版{0}删除失败", contract.Id.ToString());
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版" + contract.Name + "修改失败", LogMessageType.Error));

                // MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_HDJCONTRACT_FAILED;
            }
            //  修改会签单模版的响应数据只包含头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }

        #endregion


        #region 查询会签单的信息请求[接口废弃]
        /// <summary>
        /// 处理客户端的查询员工请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryHDJContractReuqest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));
  
            ServerResponse response = new ServerResponse();

            List<ContractTemplate> conTemps = DALContractTemplate.QueryContractTemplate();
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有的会签单", LogMessageType.Information));

            if (conTemps != null)
            {
                Console.WriteLine("会签单模版信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("会签单模版信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_HDJCONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_CONTRACT_TEMPLATE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, conTemps);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region  获取会签单的信息
        /// <summary>
        /// 获取会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseGetHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待获取的会签单编号" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待获取的会签单编号" + state.SocketMessage.Message, LogMessageType.Information));

            //string MODIFY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            String contractId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);
            HDJContract contract = DALHDJContract.GetHDJContract(contractId);
            //HDJContract contract = DALHDJContractWithWorkload.GetHDJContractWithWorkload(contractId);
            if (contract != null)
            {
                Console.WriteLine(state.ClientIp + "获取会签单{0}成功", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单" + contractId + "成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.GET_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "获取会签单{0}失败", contractId.ToString());
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单" + contractId + "失败", LogMessageType.Error));

                // MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.GET_HDJCONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.GET_HDJCONTRACT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contract);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }


        /// <summary>
        /// 获取会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseGetHDJContractWithWorkloadRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的待获取的会签单编号" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待获取的会签单编号" + state.SocketMessage.Message, LogMessageType.Information));

            //string MODIFY_EMPLOYEE_RESPONSE;
            ServerResponse response = new ServerResponse();

            // json数据解包
            String contractId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);
            //HDJContract contract = DALHDJContract.GetHDJContract(contractId);
            HDJContractWithWorkload contract = DALHDJContractWithWorkload.GetHDJContractWithWorkload(contractId);
            if (contract != null)
            {
                Console.WriteLine(state.ClientIp + "获取会签单{0}成功", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单" + contractId + "成功", LogMessageType.Success));

                //MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.GET_HDJCONTRACT_WITH_WORKLOAD_SUCCESS;
            }
            else
            {
                Console.WriteLine(state.ClientIp + "获取会签单{0}失败", contractId.ToString());
                this.Log.Write(new LogMessage(state.ClientIp + "获取会签单" + contractId + "失败", LogMessageType.Error));

                // MODIFY_EMPLOYEE_RESPONSE = "MODIFY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.GET_HDJCONTRACT_WITH_WORKLOAD_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.GET_HDJCONTRACT_WITH_WORKLOAD_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contract);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion
        
        
        
        #endregion  //  处理会签单模版的信息 

        
        #region 提交人查询自己正在审核，审核通过以及被拒绝的所有会签单的信息


        #region 查询正在审核的所有会签单的信息
        /// <summary>
        /// 查询正在审核的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        
        private void RaiseQuerySignatureStatusPenddingRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询正在审核中的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询正在审核中的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));
  
            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QuerySignatureStatusPendding(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有正在审核中的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("会签单模版信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGN_PEND_SUCCESS;
            }
            else
            {
                Console.WriteLine("会签单模版信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "会签单模版信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGN_PEND_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGN_PEND_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 查询审核通过绝的所有会签单的信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySignatureStatusAgreeRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询已通过审核的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询已通过审核的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QuerySignatureStatusAgree(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有已通过审核的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("已通过审核会签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "已通过审核会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGN_AGREE_SUCCESS;
            }
            else
            {
                Console.WriteLine("已通过审核会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "已通过审核会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGN_AGREE_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGN_AGREE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 查询被拒绝的所有会签单的信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySignatureStatusRefuseRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询被拒绝的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询被拒绝的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QuerySignatureStatusRefuse(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有被拒绝的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("被拒绝会签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGN_REFUSE_SUCCESS;
            }
            else
            {
                Console.WriteLine("被拒绝的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGN_REFUSE_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGN_REFUSE_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion

        #region 查询被拒绝的所有会签单的信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseSearchSignedHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询被拒绝的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询被拒绝的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.SearchSignedHDJContract(search);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有被拒绝的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("被拒绝会签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.SEARCH_SIGNED_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("被拒绝的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.SEARCH_SIGNED_HDJCONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.SEARCH_SIGNED_HDJCONTRACT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 查询被拒绝的所有会签单的信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseSearchAgreeHDJContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询被拒绝的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询被拒绝的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.SearchAgreeHDJContract(search);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有被拒绝的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("被拒绝会签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.SEARCH_AGREE_HDJCONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("被拒绝的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "被拒绝的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.SEARCH_AGREE_HDJCONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.SEARCH_AGREE_HDJCONTRACT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// <summary>
        /// 
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryAgreeUndownloadHDJContract(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询未被下载的已通过的会签单模版信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询未被下载的已通过的会签单模版信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeID = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QueryAgreeUndownloadContract(employeeID);
            this.Log.Write(new LogMessage(state.ClientIp + "查询未被下载的已通过的会签单模版信息", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("查询未被下载的已通过的会签单模版信息成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询未被下载的已通过的会签单模版信息", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_AGREE_UNDOWN_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询未被下载的已通过的会签单模版信息失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询未被下载的已通过的会签单模版信息失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_AGREE_UNDOWN_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_AGREE_UNDOWN_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion

        #endregion
    
    
        #region  签字人查询自己待签字的单子以及已经签过字的单子信息  

        #region 签字人查询所有待签字的会签单信息
        /// <summary>
        /// 签字人查询所有待签字的会签单信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryUnsignContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询待签字的会签单信息" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询待签字的会签单信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();
            int employeeId;
            //lock (state.SocketMessage.Message)
            //{
            employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            //}
            List<SHDJContract> contracts = DALSignatureStatus.QueryUnsignContract(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有查询待签字的的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("查询待签字的签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询待签字的会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_UNSIGN_CONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询待签字的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询待签字的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_UNSIGN_CONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_UNSIGN_CONTRACT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion



        #region 签字人查询自己已经签过字的单子信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySignedContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询已完成签字的会签单请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "查询已完成签字的会签单的请求" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QuerySignedContract(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "查询到的了所有查询已完成签字的会签单", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("查询已完成签字的签单信息查询成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询已完成签字的会签单信息查询成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGNED_CONTRACT_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询已完成签字的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询已完成签字的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGNED_CONTRACT_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGNED_CONTRACT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion



        
        #region 签字人查询自己已经签过字前10个单子的单子信息
        /// <summary>
        /// 查询正在审核，审核通过以及被拒绝的所有会签单的信息
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySignedContractTopRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的查询已完成签字的前10个会签单请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询已完成签字的前10个会签单请求" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SHDJContract> contracts = DALSignatureStatus.QuerySignedContractTop(employeeId);
            this.Log.Write(new LogMessage(state.ClientIp + "的查询已完成签字的前10个会签单请求", LogMessageType.Information));

            if (contracts != null)
            {
                Console.WriteLine("查询已完成签字的前10个会签单请求成功");
                this.Log.Write(new LogMessage(state.ClientIp + "的查询已完成签字的前10个会签单请求", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGNED_CONTRACT_TOP_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询已完成签字的前10个会签单请求失败");
                this.Log.Write(new LogMessage(state.ClientIp + "的查询已完成签字的前10个会签单请求", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGNED_CONTRACT_TOP_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGNED_CONTRACT_TOP_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        

        #endregion  签字人查询自己待签字的单子以及已经签过字的单子信息


        #region  签字用户进行签字的流程

        #region 用户签字确认信息
        private void RaiseInsertSignDetailRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的进行签字确认的请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的进行签字确认的请求" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            SignatureDetail detail = JsonConvert.DeserializeObject<SignatureDetail>(state.SocketMessage.Message);
            bool result = DALSignatureDetail.InsertSignatureDetail(detail);

            this.Log.Write(new LogMessage(state.ClientIp + "的进行签字确认的请求", LogMessageType.Information));

            if (result == true)
            {
                Console.WriteLine("来自{0}的签字确认成功");
                this.Log.Write(new LogMessage("来自" + state.ClientIp + "的签字确认成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_SIGN_DETAIL_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询已完成签字的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询已完成签字的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_SIGN_DETAIL_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
  
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));

            //////////////////////////////////
            ///  modify by gatieme @ 2015-12-14 17:11
            ///  如果该用户签完字以后，会签单已经走完所有签字流程
            ///  那么该会签单文档就可以被生成了
            if (detail.Result == 1)                  //  如果签字同意
            {
                if (DALSignatureDetail.IsContractAgree(detail.ConId) == true)   // 如果这张单子已经被同意了
                {
                    this.m_msofficeServer.AddContractWork(detail.ConId);
                    
                    // 同时统计的信息也可以被生成
                    int year = DALHDJContract.GetYearFromContractId(detail.ConId);
                    string categoryShortCall = DALHDJContract.GetCatgoryShortCallFromContractId(detail.ConId).ToString();
                    int categoryId = DALContractIdCategory.GetCategory(categoryShortCall).Id;
                    this.m_msofficeServer.AddStatisticWork(year, categoryId);
                }
            }
            /////////////////////////////////

        }

        #endregion

        #region  签字人查询自己所有的签字信息
        private void RaiseQuerySignDetailRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的进行查询签字的请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询签字信息的请求" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            int employeeId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            List<SignatureDetail> details = DALSignatureDetail.QuerySignatureDetail(employeeId);

            this.Log.Write(new LogMessage(state.ClientIp + "的进行签字确认的请求", LogMessageType.Information));

            if (details != null)
            {
                Console.WriteLine("来自{0}的签字确认成功");
                this.Log.Write(new LogMessage("来自" + state.ClientIp + "的签字确认成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGN_DETAIL_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询已完成签字的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询已完成签字的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGN_DETAIL_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGN_DETAIL_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, details);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion


        #region  签字人查询自己针对某个单子con的签字信息
        private void RaiseQuerySignDetailContractRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "的进行签字确认的请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的进行签字确认的请求" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            SignatureDetail detail = JsonConvert.DeserializeObject<SignatureDetail>(state.SocketMessage.Message);
            bool result = DALSignatureDetail.InsertSignatureDetail(detail);

            this.Log.Write(new LogMessage(state.ClientIp + "的进行签字确认的请求", LogMessageType.Information));

            if (result == true)
            {
                Console.WriteLine("来自{0}的签字确认成功");
                this.Log.Write(new LogMessage("来自" + state.ClientIp + "的签字确认成功", LogMessageType.Success));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SIGN_DETAIL_CON_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询已完成签字的会签单信息查询失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询已完成签字的会签单信息查询失败", LogMessageType.Error));

                //QUERY_EMPLOYEE_RESPONSE = "QUERY_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SIGN_DETAIL_CON_FAILED;
            }

            //  查询会签单成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SIGN_DETAIL_CON_SUCCESS))
            {
                //AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, contracts);
                //this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion


        #endregion  签字用户进行签字的流程


        #endregion


        #region 用户上传签字图片
        private const String HDJCONTDACT_PATH = @".\\hdjcontract\\";
        private void RaiseDownloadHDJContract(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "上床签字图片的请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的进行签字确认的请求" + state.SocketMessage.Message, LogMessageType.Information));


            String contractId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);

            //ServerResponse response = new ServerResponse();

            String fileName = HDJCONTDACT_PATH + contractId + ".doc";
            FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate, FileAccess.Read);
            byte[] fssize = new byte[fs.Length];
            BinaryReader reader = new BinaryReader(fs);
            reader.Read(fssize, 0, fssize.Length - 1);
            state.ClientSocket.Send(fssize);
            fs.Flush();
        }
        #endregion


        #region 用户上传签字图片
        private const String SIGNATURE_PICTURE_PATH = ".\\signature\\";

        private void RaiseUploadSigaturePicture(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自" + state.ClientIp + "上传签字图片的请求" + state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "上传签字图片的请求" + state.SocketMessage.Message, LogMessageType.Information));


            String employeeId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);

            //ServerResponse response = new ServerResponse();
            Console.WriteLine("开始上传签字图片");

            //因为终端每次发送文件的最大缓冲区是512字节，所以每次接收也是定义为512字节
            byte[] buffer = new byte[512];
            int size = 0;
            long len = 0;

            string fileName = SIGNATURE_PICTURE_PATH + employeeId + ".jpg";//获得用户保存文件的路径
            try
            {
                //创建文件流，然后让文件流来根据路径创建一个文件
                FileStream fs = new FileStream(fileName, FileMode.Create);

                //从终端不停的接受数据，然后写入文件里面，只到接受到的数据为0为止，则中断连接
                while ((size = state.ClientSocket.Receive(buffer, 0, buffer.Length, SocketFlags.None)) > 0)
                {
                    // Console.WriteLine(Encoding.UTF8.GetString(buffer));
                    fs.Write(buffer, 0, size);
                    len += size;
                }

                fs.Flush();
                Console.WriteLine("上传签字图片成功");

            }
            catch(Exception ex)
            {
                state.Close();
                Console.WriteLine(ex.ToString());
            }
        }
        #endregion


        #region 会签单工作量的处理，添加修改与删除

        #region 会签单工程project的增删改
        private void RaiseInsertProjectRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入工程PROJECT{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入工程PROJECT" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractProject project = JsonConvert.DeserializeObject<ContractProject>(state.SocketMessage.Message);
            bool result = DALContractProject.InsertContractProject(project);
            if (result == true)
            {
                Console.WriteLine("任务工作量{0}插入成功", project.Project);
                this.Log.Write(new LogMessage("任务工作量" + project.Project + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_PROJECT_SUCCESS;

                ///////////////////////////////////////////////////////////////
                ///
                ///  
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                //this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(item));//
           
            }
            else
            {
                Console.WriteLine("任务工作量{0}插入失败", project.Project);
                this.Log.Write(new LogMessage("任务工作量" + project.Project + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_ITEM_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
        }

        private void RaiseDeleteProjectRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待删除工程类别{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待删除的工程类别" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            int projectId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            bool result = DALContractProject.DeleteContractProject(projectId);
            if (result == true)
            {
                Console.WriteLine("工程类别{0}删除成功", projectId);
                this.Log.Write(new LogMessage("工程类别" + projectId + "删除成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.DELETE_PROJECT_SUCCESS;
                ///////////////////////////////////////////////////////////////
                ///
                ///  新增一个新的计划会签单模版生成类别
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                //this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(categoryId));//
            }
            else
            {
                Console.WriteLine("任务工作量{0}删除失败", projectId);
                this.Log.Write(new LogMessage("任务工作量" + projectId + "删除失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.DELETE_PROJECT_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
        }
        
        private void RaiseModifyProjectRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入任务工作量{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的任务工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractProject project = JsonConvert.DeserializeObject<ContractProject>(state.SocketMessage.Message);
            bool result = DALContractProject.ModifyProject(project);
            if (result == true)
            {
                Console.WriteLine("任务工作量{0}插入成功", project.Project);
                this.Log.Write(new LogMessage("任务工作量" + project.Project + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_PROJECT_SUCCESS;

                ///////////////////////////////////////////////////////////////
                ///
                ///  新增一个新的计划会签单模版生成类别
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                //this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(item));//
            }
            else
            {
                Console.WriteLine("任务工作量{0}插入失败", project.Project);
                this.Log.Write(new LogMessage("任务工作量" + project.Project + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_PROJECT_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));      
        }
        #endregion

        #region  会签单工作量的处理item的增删改

        private void RaiseInsertItemRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入任务工作量{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的任务工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractItem item = JsonConvert.DeserializeObject<ContractItem>(state.SocketMessage.Message);
            bool result = DALContractItem.InserItem(item);
            if (result == true)
            {
                Console.WriteLine("任务工作量{0}插入成功", item);
                this.Log.Write(new LogMessage("任务工作量" + item.Item + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.INSERT_ITEM_SUCCESS;

                ///////////////////////////////////////////////////////////////
                ///
                ///  新增一个新的计划会签单模版生成类别
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(item));//
           
            }
            else
            {
                Console.WriteLine("任务工作量{0}插入失败", item.Item);
                this.Log.Write(new LogMessage("任务工作量" + item.Item + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_ITEM_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }

        private void RaiseDeleteItemRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待删除任务工作量{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待删除的任务工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            int itemId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            int categoryId = DALContractItem.GetCategoryId(itemId);
            bool result = DALContractItem.DeleteItem(itemId);
            if (result == true)
            {
                Console.WriteLine("任务工作量{0}删除成功", itemId);
                this.Log.Write(new LogMessage("任务工作量" + itemId + "删除成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.DELETE_ITEM_SUCCESS;
                ///////////////////////////////////////////////////////////////
                ///
                ///  新增一个新的计划会签单模版生成类别
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(categoryId));//
            }
            else
            {
                Console.WriteLine("任务工作量{0}删除失败", itemId);
                this.Log.Write(new LogMessage("任务工作量" + itemId + "删除失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.DELETE_ITEM_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }

        private void RaiseModifyItemRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待插入任务工作量{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待插入的任务工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractItem item = JsonConvert.DeserializeObject<ContractItem>(state.SocketMessage.Message);
            bool result = DALContractItem.ModifyItem(item);
            if (result == true)
            {
                Console.WriteLine("任务工作量{0}插入成功", item);
                this.Log.Write(new LogMessage("任务工作量" + item.Item + "插入成功", LogMessageType.Success));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.MODIFY_ITEM_SUCCESS;

                ///////////////////////////////////////////////////////////////
                ///
                ///  新增一个新的计划会签单模版生成类别
                ///
                ///////////////////////////////////////////////////////////////
                ///  add by gatieme at 2015-01-01
                ///  不仅如此删除和修改item的时候都应该重新生成
                this.m_msofficeServer.AddRegularloadWork(DALContractItem.GetCategoryId(item));//
            }
            else
            {
                Console.WriteLine("任务工作量{0}插入失败", item.Item);
                this.Log.Write(new LogMessage("任务工作量" + item.Item + "插入失败", LogMessageType.Error));

                //INSERT_DEPARTMENT_RESPONSE = "INSERT_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_ITEM_FAILED;
            }

            // 插入部门的相应，只是一个响应头
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将

        }
       
    
        #region 查询工作量列表的信息[2015-11-9 20:39] modify by gatieme
        /// <summary>
        ///  查询某个会签单项目可以申请的工作量列表的信息
        ///  客户端发送的请求信息QUERY_PROJECT_ITEM_REQUEST  +  projectId[int]
        ///  服务器返回的信息   
        ///  成功 QUERY_PROJECT_ITEM_SUCCESS + List<ContractItem>
        ///  失败 QUERY_PROJECT_ITEM_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryProjectItemRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的查询工作量列表的信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询工作量列表的信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            int projectId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);

            //  首先检测
            List<ContractItem> items = DALContractItem.QueryProjectItem(projectId);

            if (items != null)
            {
                Console.WriteLine("查询工作量列表成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工作量列表成功", LogMessageType.Success));

                response = ServerResponse.QUERY_PROJECT_ITEM_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询工作量列表失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工作量列表失败", LogMessageType.Error));

                response = ServerResponse.QUERY_PROJECT_ITEM_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.QUERY_PROJECT_ITEM_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, items);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        /// <summary>
        ///  查询某个会签单项目可以申请的工作量列表的信息
        ///  客户端发送的请求信息QUERY_PROJECT_ITEM_REQUEST  +  projectId[int]
        ///  服务器返回的信息   
        ///  成功 QUERY_PROJECT_ITEM_SUCCESS + List<ContractItem>
        ///  失败 QUERY_PROJECT_ITEM_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryProjectItemByProjectNameRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的查询工作量列表的信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询工作量列表的信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);

            //  首先检测
            List<ContractItem> items = DALContractItem.QueryProjectItem(search.CategoryName, search.ProjectName);

            if (items != null)
            {
                Console.WriteLine("查询工作量列表成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工作量列表成功", LogMessageType.Success));

                response = ServerResponse.QUERY_PROJECT_ITEM_BY_NAME_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询工作量列表失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工作量列表失败", LogMessageType.Error));

                response = ServerResponse.QUERY_PROJECT_ITEM_BY_NAME_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.QUERY_PROJECT_ITEM_BY_NAME_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, items);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion


        #region 查询会签单的工作量列表[2015-11-9 20:39] modify by gatieme
        /// <summary>
        ///  查询工作量列表的信息
        ///  客户端发送的请求信息QUERY_CONTRACT_WORKLOAD_REQUEST  +  contractId[string]
        ///  服务器返回的信息
        ///  成功 QUERY_CONTRACT_WORKLOAD_SUCCESS + List<ContractWorkload>
        ///  失败 QUERY_CONTRACT_WORKLOAD_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryContractWorkloadRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的查询会签单的工作量信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询会签单的工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            string contractId = JsonConvert.DeserializeObject<string>(state.SocketMessage.Message);

            //  首先检测
            List<ContractWorkload> workloads = DALContractWorkload.QureyContractWorkLoad(contractId);

            if (workloads != null)
            {
                Console.WriteLine("查询会签单的工作量信息成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询会签单的工作量信息成功", LogMessageType.Success));

                response = ServerResponse.QUERY_CONTRACT_WORKLOAD_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询会签单的工作量信息失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询会签单的工作量信息失败", LogMessageType.Error));

                response = ServerResponse.QUERY_CONTRACT_WORKLOAD_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.QUERY_CONTRACT_WORKLOAD_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, workloads);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion

        #endregion


        #region 会签单工作量的 增加 修改 删除



        #region   提交会签单的时候添加工作 [add by gatieme @ 2015-12-12 18:05]
        /// <summary>
        /// 提交会签单的时候新增某个工作量的信息工作
        /// 客户端发送的信息INSERT_WORKLOAD_REQUEST + [ContractWorkload workload]
        /// 服务器返回的数据   INSERT_WORKLOAD_SUCCESS  /  INSERT_WORKLOAD_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseInsertWorkloadRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到的来自{0}的待插入工作量信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到的来自" + state.ClientIp + "的待工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractWorkload workload = JsonConvert.DeserializeObject<ContractWorkload>(state.SocketMessage.Message);

            //  首先判断员工信息是否存在，主要检查用户是否存在用户表中
            //  由于用户表的主键ID是自动生成的，
            //  因此我们检查唯一的成员信息，比如username
            //if (DALEmployee.IsEmployeeExist(employee) == true)          //  如果
            //{
            //    response = ServerResponse.INSERT_EMPLOYEE_EXIST;
            //}
            //else
            //{
            bool result = DALContractWorkload.InsertWorkload(workload);
            if (result == true)
            {
                Console.WriteLine("工作量{0}插入成功", workload.Item.Id);
                this.Log.Write(new LogMessage("工作量" + workload.Item.Id + "插入成功", LogMessageType.Success));

                response = ServerResponse.INSERT_WORKLOAD_SUCCESS;               //  用户登录成功信号    
     
 }   
            else
            {
                Console.WriteLine("工作量{0}插入失败", workload.Item.Id);
                this.Log.Write(new LogMessage("工作量" + workload.Item.Id + "插入失败", LogMessageType.Error));

                //INSERT_EMPLOYEE_RESPONSE = "INSERT_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.INSERT_WORKLOAD_FAILED;
            }


            //  插入员工的响应信息只包含头信息
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            


        }

        #endregion

        #region   提交会签单的时候修改工作
        /// <summary>
        /// 提交会签单的时候修改某个工作量的信息工作
        /// 客户端发送的信息MODIFY_WORKLOAD_REQUEST + [ContractWorkload workload]
        /// 服务器返回的数据   MODIFY_WORKLOAD_SUCCESS  /  MODIFY_WORKLOAD_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseModifyWorkloadRequest(AsyncSocketState state)
        {

            Console.WriteLine("接收到来自{0}的待修改工作量信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待修改工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            ContractWorkload workload = JsonConvert.DeserializeObject<ContractWorkload>(state.SocketMessage.Message);

            //  首先判断当前员工是否存在提交的会签字单子
            //if (DALHDJContract.GetEmployeeSubmitedHDJContractCount(employeeId) > 0)
            //{
            //    response = ServerResponse.DELETE_EMPLOYEE_EXIST_CONTRACT;
            //}
            //else if (DALContractTemplate.GetEmployeeContractTemplateCount(employeeId) > 0)
            //{   // 当前员工与某个会签单模版相关联，删除可能导致模版信息不完整， 无法删除
            //    response = ServerResponse.DELETE_EMPLOYEE_EXIST_CONTEMP;
            //}
            //else
            //{
            bool result = DALContractWorkload.ModifyWorkload(workload);

            if (result == true)
            {
                Console.WriteLine("工作量{0}插入成功", workload.Item.Id);
                this.Log.Write(new LogMessage("工作量" + workload.Item.Id + "插入成功", LogMessageType.Success));

                response = ServerResponse.MODIFY_WORKLOAD_SUCCESS;               //  用户登录成功信号         
            }
            else
            {
                Console.WriteLine("工作量{0}插入失败", workload.Item.Id);
                this.Log.Write(new LogMessage("工作量" + workload.Item.Id + "插入失败", LogMessageType.Error));

                //INSERT_EMPLOYEE_RESPONSE = "INSERT_EMPLOYEE_FAILED";                //  用户登录失败信号
                response = ServerResponse.MODIFY_WORKLOAD_FAILED;
            }

            //  删除员工的响应信息只包含头信息
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }
        #endregion
        
        #region   提交会签单的时候删除工作
        /// <summary>
        /// 提交会签单的时候删除某个工作量的信息工作
        /// 客户端发送的信息DELETE_WORKLOAD_REQUEST + [String workloadId]
        /// 服务器返回的数据   DELETE_WORKLOAD_SUCCESS  /  DELETE_WORKLOAD_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseDeleteWorkloadRequest(AsyncSocketState state)
        {

            Console.WriteLine("接收到来自{0}的待删除工作量信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待删除工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            String workloadId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);

            //  首先判断当前员工是否存在提交的会签字单子
            bool result = DALContractWorkload.DeleteWorkload(workloadId);

            if (result == true)
            {
                Console.WriteLine("工作量{0}删除成功", workloadId);
                this.Log.Write(new LogMessage(state.ClientIp + "工作量" + workloadId + "删除成功", LogMessageType.Success));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.DELETE_WORKLOAD_SUCCESS;
            }
            else
            {
                Console.WriteLine("工作量{0}删除失败", workloadId);
                this.Log.Write(new LogMessage(state.ClientIp + "工作量" + workloadId + "删除失败", LogMessageType.Error));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.DELETE_WORKLOAD_FAILED;
            }
            //  删除员工的响应信息只包含头信息
            AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
            this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
        }
        #endregion


        #region  查询会签单编号为contractId的工作量集合
        /// <summary>
        /// 查询会签单编号为contractId的工作量集合
        /// 客户端发送的信息QUERY_WORKLOAD_REQUEST + [String workloadId]
        /// 服务器返回的数据   QUERY_WORKLOAD_SUCCESS  /  QUERY_WORKLOAD_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQueryWorkloadRequest(AsyncSocketState state)
        {

            Console.WriteLine("接收到来自{0}的待删除工作量信息{1}", state.ClientIp, state.SocketMessage.Message);
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的待删除工作量信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            String contractId = JsonConvert.DeserializeObject<String>(state.SocketMessage.Message);

            //  首先判断当前员工是否存在提交的会签字单子
            List<ContractWorkload> workloads = DALContractWorkload.QureyContractWorkLoad(contractId);

            if (workloads != null)
            {
                Console.WriteLine("工作量{0}查询成功", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "工作量" + contractId + "查询成功", LogMessageType.Success));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_WORKLOAD_SUCCESS;
            }
            else
            {
                Console.WriteLine("工作量{0}查询失败", contractId);
                this.Log.Write(new LogMessage(state.ClientIp + "工作量" + contractId + "查询失败", LogMessageType.Error));

                //DELETE_DEPARTMENT_RESPONSE = "DELETE_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_WORKLOAD_FAILED;
            }
            if (response.Equals(ServerResponse.QUERY_WORKLOAD_SUCCESS))
            {
                //  插入员工的响应信息只包含头信息
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, workloads);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else
            {
                //  插入员工的响应信息只包含头信息
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion

        #endregion

        #endregion


        #region  查询会签单数目用于提交签字时自动生成最后几位 [2015-12-17 20:39] modify by gatieme

        #region 查询会签单数目--用于提交签字时自动生成最后几位[2015-11-22 20:39] modify by gatieme
        /// <summary>
        ///  查询会签单数目--用于提交签字时自动生成最后几位
        ///  客户端发送的请求信息GET_CATEGORY_YEAR_CONTRACT_COUNT_REQUEST  +  search[填充CategoryShortCall + Year两个字段]
        ///  服务器返回的信息
        ///  成功 GET_CATEGORY_YEAR_CONTRACT_COUNT_SUCCESS + count
        ///  失败 GET_CATEGORY_YEAR_CONTRACT_COUNT_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseGetCategoryYearContractCountRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的获取当年该类别会签单已经申请的数目信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的获取当年该类别会签单已经申请的数目信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);

            //  首先检测
            int count = DALHDJContract.GetCategoryYearHDJContractCount(search);

            if (count >= 0)
            {
                Console.WriteLine("获取当年该类别会签单已经申请的数目成功");
                this.Log.Write(new LogMessage(state.ClientIp + "获取当年该类别会签单已经申请的数目成功", LogMessageType.Success));

                response = ServerResponse.GET_CATEGORY_YEAR_CONTRACT_COUNT_SUCCESS;
            }
            else
            {
                Console.WriteLine("获取当年该类别会签单已经申请的数目失败");
                this.Log.Write(new LogMessage(state.ClientIp + "获取当年该类别会签单已经申请的数目失败", LogMessageType.Error));

                response = ServerResponse.GET_CATEGORY_YEAR_CONTRACT_COUNT_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.GET_CATEGORY_YEAR_CONTRACT_COUNT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, count);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion


        #region 查询当前部门department当年year当前会签单类别category的数目
        /// <summary>
        ///  查询当前部门department当年year当前会签单类别category的数目
        ///  客户端发送的请求信息GET_DEP_CATE_YEAR_CON_COUNT_REQUEST  +  search[填充SDepartmentShortlCall + CategoryShortCall + Year两个字段]
        ///  服务器返回的信息
        ///  成功 GET_CATEGORY_YEAR_CONTRACT_COUNT_SUCCESS + count
        ///  失败 GET_CATEGORY_YEAR_CONTRACT_COUNT_FAILED
        /// </summary>
        /// <param name="state"></param>
        private void RaiseGetDepartmentCategoryYearContractCountRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的获取当年该类别会签单已经申请的数目信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的获取当年该类别会签单已经申请的数目信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);

            //  首先检测
            int count = DALHDJContract.GetSDepartmentCategoryYearHDJContractCount(search);

            if (count >= 0)
            {
                Console.WriteLine("获取当年该类别会签单已经申请的数目成功");
                this.Log.Write(new LogMessage(state.ClientIp + "获取当年该类别会签单已经申请的数目成功", LogMessageType.Success));

                response = ServerResponse.GET_DEP_CATE_YEAR_CON_COUNT_SUCCESS;
            }
            else
            {
                Console.WriteLine("获取当年该类别会签单已经申请的数目失败");
                this.Log.Write(new LogMessage(state.ClientIp + "获取当年该类别会签单已经申请的数目失败", LogMessageType.Error));

                response = ServerResponse.GET_DEP_CATE_YEAR_CON_COUNT_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.GET_DEP_CATE_YEAR_CON_COUNT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, count);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion  /// 统计功能

        #endregion


        #region 统计功能


        #region 处理客户端的查询部门会签单申请权限
        /// <summary>
        /// 处理客户端的查询部门请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseQuerySDepartmentContractCategoryRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待查询权限部门编号{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待查询权限部门编号" + state.SocketMessage.Message, LogMessageType.Information));

            List<ContractCategory> categorys = null;
            ServerResponse response = new ServerResponse();


            // json数据解包
            int departmentId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);
            // 向数据库中查询部门的信息
            categorys = DALContractIdCategory.QuerySDepartmentContractCategory(departmentId);
            if (categorys != null)
            {
                Console.WriteLine("查询部门会签单申请权限成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询部门会签单申请权限成功", LogMessageType.Success));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.QUERY_SDEP_CON_CATEGORY_SUCCESS;
        
            }
            else
            {
                Console.WriteLine("查询部门会签单申请权限失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询部门会签单申请权限失败", LogMessageType.Error));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.QUERY_SDEP_CON_CATEGORY_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.QUERY_SDEP_CON_CATEGORY_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, categorys);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #region 查询工程列表的信息[2015-11-6 21:41] modify by gatieme 
        private void RaiseQueryCategoryProjectRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的查询工程列表的信息{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "的查询工程列表的信息" + state.SocketMessage.Message, LogMessageType.Information));

            ServerResponse response = new ServerResponse();

            // json数据解包
            int categoryId = JsonConvert.DeserializeObject<int>(state.SocketMessage.Message);

            //  首先检测
            List<ContractProject> projects = DALContractProject.QueryCategoryProject(categoryId);

            if (projects != null)
            {
                Console.WriteLine("查询工程列表成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工程列表成功", LogMessageType.Success));

                response = ServerResponse.QUERY_CATEGORY_PROJECT_SUCCESS;
            }
            else
            {
                Console.WriteLine("查询工程列表失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询工程列表失败", LogMessageType.Error));

                response = ServerResponse.QUERY_CATEGORY_PROJECT_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 信息] 
            if (response.Equals(ServerResponse.QUERY_CATEGORY_PROJECT_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, projects);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                 
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }
        #endregion


        #region 处理客户端的查询部门会签单申请权限
        /// <summary>
        /// 处理客户端的查询部门请求
        /// </summary>
        /// <param name="state"></param>
        private void RaiseStatisticDepartmentYearProjectRequest(AsyncSocketState state)
        {
            Console.WriteLine("接收到来自{0}的待查询权限部门编号{1}", state.ClientIp, state.SocketMessage.Message); // 输出真正的信息
            this.Log.Write(new LogMessage("接收到来自" + state.ClientIp + "待查询权限部门编号" + state.SocketMessage.Message, LogMessageType.Information));

            List<ContractCategory> categorys = null;
            ServerResponse response = new ServerResponse();


            // json数据解包
            Search search = JsonConvert.DeserializeObject<Search>(state.SocketMessage.Message);
            // 向数据库中查询部门的信息
            ContractWorkload workload = DALContractStatistic.StatisDepartmentYearProjectWorkLoad(search.SDepartmentShortlCall, search.Year, search.ProjectId);

            if (workload != null)
            {
                Console.WriteLine("查询部门会签单申请权限成功");
                this.Log.Write(new LogMessage(state.ClientIp + "查询部门会签单申请权限成功", LogMessageType.Success));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_SUCCESS";               //  用户登录成功信号   
                response = ServerResponse.STATISTIC_DEP_YEAR_PRO_SUCCESS;

            }
            else
            {
                Console.WriteLine("查询部门会签单申请权限失败");
                this.Log.Write(new LogMessage(state.ClientIp + "查询部门会签单申请权限失败", LogMessageType.Error));

                //QUERY_DEPARTMENT_RESPONSE = "QUERY_DEPARTMENT_FAILED";                //  用户登录失败信号
                response = ServerResponse.STATISTIC_DEP_YEAR_PRO_FAILED;
            }

            //  查询部门成功则同时发送[报头 + 部门信息] 
            if (response.Equals(ServerResponse.STATISTIC_DEP_YEAR_PRO_SUCCESS))
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response, workload);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));                    //  将
            }
            else      //  查询失败则只发报头
            {
                AsyncSocketMessage socketMessage = new AsyncSocketMessage(response);
                this.Send(state.ClientSocket, Encoding.UTF8.GetBytes(socketMessage.Package));
            }
        }

        #endregion


        #endregion




    }
}
