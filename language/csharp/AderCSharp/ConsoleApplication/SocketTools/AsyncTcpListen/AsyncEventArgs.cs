using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Net.Sockets;
using System.Net;

/*
 *  1、SocketAsyncEventArgs介绍
 *  SocketAsyncEventArgs是微软提供的高性能异步Socket实现类，
 *  主要为高性能网络服务器应用程序而设计，
 *  主要是为了避免在在异步套接字 I/O 量非常大时发生重复的对象分配和同步。
 *  使用此类执行异步套接字操作的模式包含以下步骤：
 * 
 *  1.分配一个新的 SocketAsyncEventArgs 上下文对象，或者从应用程序池中获取一个空闲的此类对象。
 *  2.将该上下文对象的属性设置为要执行的操作（例如，完成回调方法、数据缓冲区、缓冲区偏移量以及要传输的最大数据量）。
 *  3.调用适当的套接字方法 (xxxAsync) 以启动异步操作。
 *  4.如果异步套接字方法 (xxxAsync) 返回 true，则在回调中查询上下文属性来获取完成状态。
 *  5.如果异步套接字方法 (xxxAsync) 返回 false，则说明操作是同步完成的。 可以查询上下文属性来获取操作结果。
 *  6.将该上下文重用于另一个操作，将它放回到应用程序池中，或者将它丢弃。*
 * 
 * */
namespace SignPressServer.SignSocket.AsyncTcpListener
{

    /// <summary>
    /// 异步TcpListener TCP服务器事件参数类 
    /// </summary>
    public class AsyncEventArgs : EventArgs
    {
         /// <summary>
        /// 提示信息
        /// </summary>
        public string _msg;

        /// <summary>
        /// 客户端状态封装类
        /// </summary>
        public TCPClientState _state;

        /// <summary>
        /// 是否已经处理过了
        /// </summary>
        public bool IsHandled { get; set; }

        public AsyncEventArgs(string msg)
        {
            this._msg = msg;
            IsHandled = false;
        }
        public AsyncEventArgs(TCPClientState state)
        {
            this._state = state;
            IsHandled = false;
        }
        public AsyncEventArgs(string msg, TCPClientState state)
        {
            this._msg = msg;
            this._state = state;
            IsHandled = false;
        }
    }
}
