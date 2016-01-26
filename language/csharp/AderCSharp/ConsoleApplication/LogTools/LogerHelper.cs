using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;

namespace SignPressServer.SignLog
{
    /// <summary>
    /// 企业应用框架的日志类
    /// </summary>
    /// <remarks>此日志类提供高性能的日志记录实现。
    /// 当调用Write方法时不会造成线程阻塞,而是立即完成方法调用,因此调用线程不用等待日志写入文件之后才返回。</remarks>
    public class LogerHelper : IDisposable
    {
        // 默认的LOG日志目录
        private const String DEFAULT_LOG_PATH = @".\\log\";

        //日志对象的缓存队列
        private static Queue<LogMessage> LogMessages;
        //日志文件保存的路径
        private static string m_path;
        //日志写入线程的控制标记
        private static bool m_state;
        //日志记录的类型
        private static LogType m_type;
        //日志文件生命周期的时间标记
        private static DateTime TimeSign;
        //日志文件写入流对象
        private static StreamWriter m_writer;

        //设置日志文件的过期删除时间
        //private static DateTime TimeDelete;

        /// <summary>
        /// 创建日志对象的新实例，采用默认当前程序位置作为日志路径和默认的每日日志文件类型记录日志
        /// </summary>
        public LogerHelper()
            : this(DEFAULT_LOG_PATH, LogType.Daily)
        {
        }

        /// <summary>
        /// 创建日志对象的新实例，采用默认当前程序位置作为日志路径并指定日志类型
        /// </summary>
        /// <param name="t">日志文件创建方式的枚举</param>
        public LogerHelper(LogType t)
            : this(DEFAULT_LOG_PATH, t)
        {
        }

        /// <summary>
        /// 创建日志对象的新实例，根据指定的日志文件路径和指定的日志文件创建类型
        /// </summary>
        /// <param name="p">日志文件保存路径</param>
        /// <param name="t">日志文件创建方式的枚举</param>
        public LogerHelper(string p, LogType t)
        {
            if (LogMessages == null)
            {
                m_state = true;
                m_path = p;
                m_type = t;
                LogMessages = new Queue<LogMessage>();
                Thread thread = new Thread(Work);
                thread.Start();
            }
        }

        //日志文件写入线程执行的方法
        private void Work()
        {
            while (true)
            {
                //判断队列中是否存在待写入的日志
                if (LogMessages.Count > 0)
                {
                    LogMessage LogMessage = null;
                    lock (LogMessages)
                    {
                        LogMessage = LogMessages.Dequeue();
                    }
                    if (LogMessage != null)
                    {
                        FileWrite(LogMessage);
                    }
                }
                else
                {
                    //判断是否已经发出终止日志并关闭的消息
                    if (m_state)
                    {
                        Thread.Sleep(1);
                    }
                    else
                    {
                        FileClose();
                    }
                }
            }
        }

        //根据日志类型获取日志文件名，并同时创建文件到期的时间标记
        //通过判断文件的到期时间标记将决定是否创建新文件。
        private string GetFilename()
        {
            DateTime now = DateTime.Now;
            string format = "";
            switch (m_type)
            {
                case LogType.Daily:
                    TimeSign = new DateTime(now.Year, now.Month, now.Day);
                    TimeSign = TimeSign.AddDays(1);
                    format = "yyyyMMdd'.log'";
                    break;
                case LogType.Weekly:
                    TimeSign = new DateTime(now.Year, now.Month, now.Day);
                    TimeSign = TimeSign.AddDays(7);
                    format = "yyyyMMdd'.log'";
                    break;
                case LogType.Monthly:
                    TimeSign = new DateTime(now.Year, now.Month, 1);
                    TimeSign = TimeSign.AddMonths(1);
                    format = "yyyyMM'.log'";
                    break;
                case LogType.Annually:
                    TimeSign = new DateTime(now.Year, 1, 1);
                    TimeSign = TimeSign.AddYears(1);
                    format = "yyyy'.log'";
                    break;
            }
            return now.ToString(format);
        }

        //写入日志文本到文件的方法
        private void FileWrite(LogMessage LogMessage)
        {
            try
            {
                if (m_writer == null)
                {
                    FileOpen();
                }
                else
                {
                    //判断文件到期标志，如果当前文件到期则关闭当前文件创建新的日志文件
                    if (DateTime.Now >= TimeSign)
                    {
                        FileClose();
                        FileOpen();

                        //  到期时创建了新的文件，但是同时应该删除7天之前的文件
                    }
                    m_writer.Write(LogMessage.Datetime);
                    m_writer.Write('\t');
                    m_writer.Write(LogMessage.Type);
                    m_writer.Write('\t');
                    m_writer.WriteLine(LogMessage.Text);
                    m_writer.Flush();
                }
            }
            catch (Exception e)
            {
                Console.Out.Write(e);
            }
        }

        //打开文件准备写入
        private void FileOpen()
        {
            m_writer = new StreamWriter(m_path + GetFilename(), true, Encoding.UTF8);
        }

        //关闭打开的日志文件
        private void FileClose()
        {
            if (m_writer != null)
            {
                m_writer.Flush();
                m_writer.Close();
                m_writer.Dispose();
                m_writer = null;
            }
        }

        /// <summary>
        /// 写入新日志，根据指定的日志对象LogMessage
        /// </summary>
        /// <param name="LogMessage">日志内容对象</param>
        public void Write(LogMessage LogMessage)
        {
            if (LogMessage != null)
            {
                lock (LogMessages)
                {
                    LogMessages.Enqueue(LogMessage);
                }
            }
        }

        /// <summary>
        /// 写入新日志，根据指定的日志内容和信息类型，采用当前时间为日志时间写入新日志
        /// </summary>
        /// <param name="text">日志内容</param>
        /// <param name="type">信息类型</param>
        public void Write(string text, LogMessageType type)
        {
            Write(new LogMessage(text, type));
        }

        /// <summary>
        /// 写入新日志，根据指定的日志时间、日志内容和信息类型写入新日志
        /// </summary>
        /// <param name="dt">日志时间</param>
        /// <param name="text">日志内容</param>
        /// <param name="type">信息类型</param>
        public void Write(DateTime dt, string text, LogMessageType type)
        {
            Write(new LogMessage(dt, text, type));
        }

        /// <summary>
        /// 写入新日志，根据指定的异常类和信息类型写入新日志
        /// </summary>
        /// <param name="e">异常对象</param>
        /// <param name="type">信息类型</param>
        public void Write(Exception e, LogMessageType type)
        {
            Write(new LogMessage(e.Message, type));
        }

        #region IDisposable 成员

        /// <summary>
        /// 销毁日志对象
        /// </summary>
        public void Dispose()
        {
            m_state = false;
        }

        #endregion
    }
}