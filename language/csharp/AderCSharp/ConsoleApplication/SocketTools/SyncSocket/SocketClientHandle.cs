using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Net.Sockets;
using System.Net;

namespace SignPressServer.SignSocket.SyncSocket
{
    /// <summary>
    /// Socket 服务器用于处理客户端连接封装的客户端处理类
    /// </summary>
    public class SocketClientHandle : IDisposable
    {
        /// <summary>
        /// 与客户端相关联的socket
        /// </summary>
        private Socket _client;

        /// <summary>
        /// 标识是否与客户端相连接
        /// </summary>
        private bool _is_connect;
        public bool IsConnect
        {
            get { return _is_connect; }
            set { _is_connect = value; }
        }

        /// <summary>
        /// 数据接受缓冲区
        /// </summary>
        private byte[] _recvBuffer;
        private int m_recvLength;
        public SocketClientHandle(Socket client)
        {
            this._client = client;
            _is_connect = true;
            _recvBuffer = new byte[1024 * 1024 * 2];
        }

        #region Method
        /// <summary>
        /// 接受来自客户端发来的数据
        /// </summary>
        public void RecevieData(Object state)
        {
            m_recvLength = -1;
            while (_is_connect)
            {
                try
                {
                    // 在这里填写服务器处理数据的逻辑
                    //////////////////////////////////////
                    m_recvLength = _client.Receive(_recvBuffer);///
                    //////////////////////////////////////
                   // DealClientRequest();
                }
                catch (Exception)
                {
                    //TODO
                }
            }
        }

        /// <summary>
        /// 向客户端发送数据
        /// </summary>
        public void SendData(string msg)
        {
            byte[] data = Encoding.Default.GetBytes(msg);
            try
            {
                //有一种比较好的写法
                _client.Send(data);
            }
            catch (Exception)
            {
                //TODO 处理异常
            }
        }

        #endregion


        #region 事件


        //TODO 消息发送事件
        //TODO 数据收到事件
        //TODO 异常处理事件

        #endregion

        #region 释放
        /// <summary>
        /// Performs application-defined tasks associated with freeing, 
        /// releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            _is_connect = false;
            if (_client != null)
            {
                _client.Close();
                _client = null;
            }
            GC.SuppressFinalize(this);
        }

        #endregion

    }
}
