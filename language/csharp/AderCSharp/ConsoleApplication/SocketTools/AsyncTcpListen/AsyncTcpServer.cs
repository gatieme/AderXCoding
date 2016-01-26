using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Net.Sockets;
using System.Net;


namespace SignPressServer.SignSocket.AsyncTcpListener
{
    /// <summary>
    /// TcpListener实现异步TCP服务器
    /// </summary>
    public class AsyncTcpServer : IDisposable
    {
        #region Fields
        /// <summary>
        /// 服务器程序允许的最大客户端连接数
        /// </summary>
        // private int _maxClient;

        /// <summary>
        /// 当前的连接的客户端数
        /// </summary>
        private int _clientCount;

        /// <summary>
        /// 服务器使用的异步TcpListener
        /// </summary>
        private TcpListener _listener;

        /// <summary>
        /// 客户端会话列表
        /// </summary>
        private List<Object> _clients;

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
        /// 异步TCP服务器
        /// </summary>
        /// <param name="listenPort">监听的端口</param>
        public AsyncTcpServer(int listenPort)
            : this(IPAddress.Any, listenPort)
        {
        }

        /// <summary>
        /// 异步TCP服务器
        /// </summary>
        /// <param name="localEP">监听的终结点</param>
        public AsyncTcpServer(IPEndPoint localEP)
            : this(localEP.Address, localEP.Port)
        {
        }

        /// <summary>
        /// 异步TCP服务器
        /// </summary>
        /// <param name="localIPAddress">监听的IP地址</param>
        /// <param name="listenPort">监听的端口</param>
        public AsyncTcpServer(IPAddress localIPAddress, int listenPort)
        {
            Address = localIPAddress;
            Port = listenPort;
            this.Encoding = Encoding.Default;

            _clients = new List<Object>();

            _listener = new TcpListener(Address, Port);
            _listener.AllowNatTraversal(true);
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
                _listener.Start();
                _listener.BeginAcceptTcpClient(
                  new AsyncCallback(HandleTcpClientAccepted), _listener);
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
                _listener.Start(backlog);
                _listener.BeginAcceptTcpClient(
                  new AsyncCallback(HandleTcpClientAccepted), _listener);
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
                _listener.Stop();
                lock (_clients)
                {
                    //关闭所有客户端连接
                    CloseAllClient();
                }
            }
        }

        /// <summary>
        /// 处理客户端连接的函数
        /// </summary>
        /// <param name="ar"></param>
        private void HandleTcpClientAccepted(IAsyncResult ar)
        {
            if (IsRunning)
            {
                //TcpListener tcpListener = (TcpListener)ar.AsyncState;

                TcpClient client = _listener.EndAcceptTcpClient(ar);
                byte[] buffer = new byte[client.ReceiveBufferSize];

                TCPClientState state = new TCPClientState(client, buffer);
                lock (_clients)
                {
                    _clients.Add(state);
                    RaiseClientConnected(state);
                }

                NetworkStream stream = state.NetworkStream;
                //开始异步读取数据
                stream.BeginRead(state.Buffer, 0, state.Buffer.Length, HandleDataReceived, state);

                _listener.BeginAcceptTcpClient(
                  new AsyncCallback(HandleTcpClientAccepted), ar.AsyncState);
            }
        }
        /// <summary>
        /// 数据接受回调函数
        /// </summary>
        /// <param name="ar"></param>
        private void HandleDataReceived(IAsyncResult ar)
        {
            if (IsRunning)
            {
                TCPClientState state = (TCPClientState)ar.AsyncState;
                NetworkStream stream = state.NetworkStream;

                int recv = 0;
                try
                {
                    recv = stream.EndRead(ar);
                }
                catch
                {
                    recv = 0;
                }

                if (recv == 0)
                {
                    // connection has been closed
                    lock (_clients)
                    {
                        _clients.Remove(state);
                        //触发客户端连接断开事件
                        RaiseClientDisconnected(state);
                        return;
                    }
                }

                // received byte and trigger event notification
                byte[] buff = new byte[recv];
                Buffer.BlockCopy(state.Buffer, 0, buff, 0, recv);
                //触发数据收到事件
                RaiseDataReceived(state);

                // continue listening for tcp datagram packets
                stream.BeginRead(state.Buffer, 0, state.Buffer.Length, HandleDataReceived, state);
            }
        }

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="state">接收数据的客户端会话</param>
        /// <param name="data">数据报文</param>
        public void Send(TCPClientState state, byte[] data)
        {
            RaisePrepareSend(state);
            Send(state.TcpClient, data);
        }

        /// <summary>
        /// 异步发送数据至指定的客户端
        /// </summary>
        /// <param name="client">客户端</param>
        /// <param name="data">报文</param>
        public void Send(TcpClient client, byte[] data)
        {
            if (!IsRunning)
                throw new InvalidProgramException("This TCP Scoket server has not been started.");

            if (client == null)
                throw new ArgumentNullException("client");

            if (data == null)
                throw new ArgumentNullException("data");
            client.GetStream().BeginWrite(data, 0, data.Length, SendDataEnd, client);
        }

        /// <summary>
        /// 发送数据完成处理函数
        /// </summary>
        /// <param name="ar">目标客户端Socket</param>
        private void SendDataEnd(IAsyncResult ar)
        {
            ((TcpClient)ar.AsyncState).GetStream().EndWrite(ar);
            RaiseCompletedSend(null);
        }
        #endregion

        #region 事件

        /// <summary>
        /// 与客户端的连接已建立事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> ClientConnected;
        /// <summary>
        /// 与客户端的连接已断开事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> ClientDisconnected;


        /// <summary>
        /// 触发客户端连接事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseClientConnected(TCPClientState state)
        {
            if (ClientConnected != null)
            {
                ClientConnected(this, new AsyncEventArgs(state));
            }
        }
        /// <summary>
        /// 触发客户端连接断开事件
        /// </summary>
        /// <param name="client"></param>
        private void RaiseClientDisconnected(TCPClientState state)
        {
            if (ClientDisconnected != null)
            {
                ClientDisconnected(this, new AsyncEventArgs("连接断开"));
            }
        }

        /// <summary>
        /// 接收到数据事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> DataReceived;

        private void RaiseDataReceived(TCPClientState state)
        {
            if (DataReceived != null)
            {
                DataReceived(this, new AsyncEventArgs(state));
            }
        }

        /// <summary>
        /// 发送数据前的事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> PrepareSend;

        /// <summary>
        /// 触发发送数据前的事件
        /// </summary>
        /// <param name="state"></param>
        private void RaisePrepareSend(TCPClientState state)
        {
            if (PrepareSend != null)
            {
                PrepareSend(this, new AsyncEventArgs(state));
            }
        }

        /// <summary>
        /// 数据发送完毕事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> CompletedSend;

        /// <summary>
        /// 触发数据发送完毕的事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseCompletedSend(TCPClientState state)
        {
            if (CompletedSend != null)
            {
                CompletedSend(this, new AsyncEventArgs(state));
            }
        }

        /// <summary>
        /// 网络错误事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> NetError;
        /// <summary>
        /// 触发网络错误事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseNetError(TCPClientState state)
        {
            if (NetError != null)
            {
                NetError(this, new AsyncEventArgs(state));
            }
        }

        /// <summary>
        /// 异常事件
        /// </summary>
        public event EventHandler<AsyncEventArgs> OtherException;
        /// <summary>
        /// 触发异常事件
        /// </summary>
        /// <param name="state"></param>
        private void RaiseOtherException(TCPClientState state, string descrip)
        {
            if (OtherException != null)
            {
                OtherException(this, new AsyncEventArgs(descrip, state));
            }
        }
        private void RaiseOtherException(TCPClientState state)
        {
            RaiseOtherException(state, "");
        }

        #endregion

        #region Close
        /// <summary>
        /// 关闭一个与客户端之间的会话
        /// </summary>
        /// <param name="state">需要关闭的客户端会话对象</param>
        public void Close(TCPClientState state)
        {
            if (state != null)
            {
                state.Close();
                _clients.Remove(state);
                _clientCount--;
                //TODO 触发关闭事件
            }
        }
        /// <summary>
        /// 关闭所有的客户端会话,与所有的客户端连接会断开
        /// </summary>
        public void CloseAllClient()
        {
            foreach (TCPClientState client in _clients)
            {
                Close(client);
            }
            _clientCount = 0;
            _clients.Clear();
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
                        Stop();
                        if (_listener != null)
                        {
                            _listener = null;
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
    }
}
