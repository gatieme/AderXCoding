using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Net.Sockets;
using System.Net;

namespace SignPressServer.SignSocket.SyncSocket
{
    /// <summary>
    /// 同步Socket TCP服务器事件类
    /// </summary>
    public class SocketEventArgs : EventArgs
    {
        /// <summary>
        /// 提示信息
        /// </summary>
        public string _msg;

        /// <summary>
        /// 客户端状态封装类
        /// </summary>
        public SocketClientHandle _handle;

        /// <summary>
        /// 是否已经处理过了
        /// </summary>
        public bool IsHandled { get; set; }

        public SocketEventArgs(string msg)
        {
            this._msg = msg;
            IsHandled = false;
        }
        public SocketEventArgs(SocketClientHandle handle)
        {
            this._handle = handle;
            IsHandled = false;
        }
        public SocketEventArgs(string msg, SocketClientHandle handle)
        {
            this._msg = msg;
            this._handle = handle;
            IsHandled = false;
        }
    }
}
