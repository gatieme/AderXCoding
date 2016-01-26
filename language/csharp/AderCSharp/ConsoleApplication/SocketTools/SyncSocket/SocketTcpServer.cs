using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;

using System.Net.Sockets;
using System.Net;


namespace SignPressServer.SignSocket.SyncSocket
{
    /// <summary>
    /// 基于socket实现的同步TCP服务器
    /// </summary>
    public class SocketTCPServer
    {
        #region Fields
        /// <summary>
        /// 服务器程序允许的最大客户端连接数
        /// </summary>
        private int _maxClient;

        /// <summary>
        /// 当前的连接的客户端数
        /// </summary>
        private int _clientCount;

        /// <summary>
        /// 服务器使用的异步socket
        /// </summary>
        private Socket _serverSock;

        /// <summary>
        /// 客户端会话列表
        /// </summary>
        private List<SocketClientHandle> _clients;

        private bool disposed = false;

        #endregion

        #region Properties

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

        #region 构造函数
        /// <summary>
        /// 同步Socket TCP服务器
        /// </summary>
        /// <param name="listenPort">监听的端口</param>
        public SocketTCPServer(int listenPort)
            : this(IPAddress.Any, listenPort, 1024)
        {
        }

        /// <summary>
        /// 同步Socket TCP服务器
        /// </summary>
        /// <param name="localEP">监听的终结点</param>
        public SocketTCPServer(IPEndPoint localEP)
            : this(localEP.Address, localEP.Port, 1024)
        {
        }

        /// <summary>
        /// 同步Socket TCP服务器
        /// </summary>
        /// <param name="localIPAddress">监听的IP地址</param>
        /// <param name="listenPort">监听的端口</param>
        /// <param name="maxClient">最大客户端数量</param>
        public SocketTCPServer(IPAddress localIPAddress, int listenPort, int maxClient)
        {
            this.Address = localIPAddress;
            this.Port = listenPort;
            this.Encoding = Encoding.Default;

            _maxClient = maxClient;
            _clients = new List<SocketClientHandle>();
            _serverSock = new Socket(localIPAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        }

        #endregion

        #region Method
        /// <summary>
        /// 启动服务器
        /// </summary>
        public void Start()
        {
            if (!IsRunning)
            {
                IsRunning = true;
                _serverSock.Bind(new IPEndPoint(this.Address, this.Port));
                Thread thread = new Thread(StartListen);
                thread.Start();

            }
        }
        /// <summary>
        /// 开始进行监听
        /// </summary>
        private void StartListen()
        {
            _serverSock.Listen(1024);
            SocketClientHandle handle;
            while (IsRunning)
            {
                if (_clientCount >= _maxClient)
                {
                    //TODO 客户端过多异常
                    RaiseOtherException(null);
                }
                else
                {
                    
                    Socket clientSock = _serverSock.Accept();
                    _clientCount++;
                    IPEndPoint ip = (IPEndPoint)clientSock.RemoteEndPoint;
                    Console.WriteLine("获取到来自{0} : {1}的连接", ip.Address, ip.Port);
                    //TODO 创建一个处理客户端的线程并启动
                    handle = new SocketClientHandle(clientSock);
                    _clients.Add(handle);
                    
                    //使用线程池来操作
                    ThreadPool.QueueUserWorkItem(new WaitCallback(handle.RecevieData));

                    //Thread pthread;
                    //pthread = new Thread(new ThreadStart(client.RecevieData));
                    //pthread.Start();
                    //这里应该使用线程池来进行
                }
            }

        }
        /// <summary>
        /// 停止服务器
        /// </summary>
        public void Stop()
        {
            if (IsRunning)
            {
                IsRunning = false;
                _serverSock.Close();
                //TODO 关闭对所有客户端的连接

            }
        }
        /// <summary>
        /// 发送函数
        /// </summary>
        public void Send(string msg, SocketClientHandle client)
        {
            //TODO
        }

        /// <summary>
        /// 关闭一个与客户端之间的会话
        /// </summary>
        /// <param name="handle">需要关闭的客户端会话对象</param>
        public void Close(SocketClientHandle handle)
        {
            if (handle != null)
            {
                _clients.Remove(handle);
                handle.Dispose();
                _clientCount--;
                //TODO 触发关闭事件
                
            }
        }
        /// <summary>
        /// 关闭所有的客户端会话,与所有的客户端连接会断开
        /// </summary>
        public void CloseAllClient()
        {
            foreach (SocketClientHandle handle in _clients)
            {
                Close(handle);
            }
            _clientCount = 0;
            _clients.Clear();
        }

        #endregion

        #region 事件

        /// <summary>
        /// 与客户端的连接已建立事件
        /// </summary>
        public event EventHandler<SocketEventArgs> ClientConnected;
        /// <summary>
        /// 与客户端的连接已断开事件
        /// </summary>
        public event EventHandler<SocketEventArgs> ClientDisconnected;

        /// <summary>
        /// 触发客户端连接事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseClientConnected(SocketClientHandle handle)
        {
            if (ClientConnected != null)
            {
                ClientConnected(this, new SocketEventArgs(handle));
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
                ClientDisconnected(this, new SocketEventArgs("连接断开"));
            }
        }

        /// <summary>
        /// 接收到数据事件
        /// </summary>
        public event EventHandler<SocketEventArgs> DataReceived;

        private void RaiseDataReceived(SocketClientHandle handle)
        {
            if (DataReceived != null)
            {
                DataReceived(this, new SocketEventArgs(handle));
            }
        }

        /// <summary>
        /// 数据发送事件
        /// </summary>
        public event EventHandler<SocketEventArgs> CompletedSend;

        /// <summary>
        /// 触发数据发送事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseCompletedSend(SocketClientHandle handle)
        {
            if (CompletedSend != null)
            {
                CompletedSend(this, new SocketEventArgs(handle));
            }
        }


        /// <summary>
        /// 网络错误事件
        /// </summary>
        public event EventHandler<SocketEventArgs> NetError;
        /// <summary>
        /// 触发网络错误事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseNetError(SocketClientHandle handle)
        {
            if (NetError != null)
            {
                NetError(this, new SocketEventArgs(handle));
            }
        }

        /// <summary>
        /// 异常事件
        /// </summary>
        public event EventHandler<SocketEventArgs> OtherException;
        /// <summary>
        /// 触发异常事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseOtherException(SocketClientHandle handle, string descrip)
        {
            if (OtherException != null)
            {
                OtherException(this, new SocketEventArgs(descrip, handle));
            }
        }
        private void RaiseOtherException(SocketClientHandle handle)
        {
            RaiseOtherException(handle, "");
        }

        #endregion

        #region Close 未实现
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
                        Stop();
                        if (_serverSock != null)
                        {
                            _serverSock = null;
                        }
                    }
                    catch (SocketException)
                    {
                        //TODO 异常
                    }
                }
                disposed = true;
            }
        }
        #endregion
    }
}
