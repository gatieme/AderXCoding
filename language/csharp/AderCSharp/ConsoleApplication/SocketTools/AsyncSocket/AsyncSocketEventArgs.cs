using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using SignPressServer.SignSocket;

namespace SignPressServer.SignSocket.AsyncSocket
{
    /// <summary>
    /// 异步Socket TCP事件参数类
    /// </summary>
    public class AsyncSocketEventArgs : EventArgs
    {
        /// <summary>
        /// 提示信息
        /// </summary>
        public string m_message;

        /// <summary>
        /// 客户端状态封装类
        /// </summary>
        public AsyncSocketState m_state;

        /// <summary>
        /// 是否已经处理过了
        /// </summary>
        public bool IsHandled { get; set; }

        //  事件信息
        public AsyncSocketEventArgs(string message)
        {
            this.m_message = message;
            IsHandled = false;
        }

        // 套接字信息事件
        public AsyncSocketEventArgs(AsyncSocketState state)
        {
            this.m_state = state;
            IsHandled = false;

            //System.Net.IPEndPoint ip = (System.Net.IPEndPoint)state.ClientSocket.RemoteEndPoint;
            //Console.WriteLine("获取到一个来自" + ip.Address + " : " + ip.Port + "的连接...");

        }

        //  套接字 + 信息
        public AsyncSocketEventArgs(string message, AsyncSocketState state)
        {
            this.m_message = message;
            this.m_state = state;
            IsHandled = false;
        }
        

    }
}
