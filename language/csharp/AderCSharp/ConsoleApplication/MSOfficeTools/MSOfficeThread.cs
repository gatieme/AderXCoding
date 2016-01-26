using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;
using System.Web;
using System.Data;
using System.Reflection;
using Microsoft.Win32;
using System.Text.RegularExpressions;



/// WPS library...
//using Office;
//using Word;

/// OFFICE library...
//using Microsoft.Office.Interop.Word;
//using Word = Microsoft.Office.Interop.Word;
using MSWord = Microsoft.Office.Interop.Word;
using System.IO;




namespace SignPressServer.SignTools
{

    public enum WORK_KIND
    {
        /// <summary>
        /// 在会签单签字完成后， 生成会签单的文件
        /// </summary>
        CREATE_CONTRACT_REQUEST,

        /// <summary>
        /// 在会签单签字完成后，生成统计信息
        /// </summary>
        CREATE_STATISTC_REQUEST,

        /// <summary>
        /// 在修改item集合后生成regularload计划任务表供用户下载
        /// </summary>
        CREATE_REGULARLOAD_REQUEST,

        /// <summary>
        /// 在用户上传计划额度表之后, 将数据进行插入到数据库中
        /// </summary>
        UPLOAD_REGULARLOAD_REQUEST,
        
    }

    public class MSOfficeThreadWork
    {

        public WORK_KIND WorkKind;

        ///  CREATE_CONTRACT_REQUEST时使用此字段
        ///  用于标识其待生成的会签单编号
        private String m_contractId;
        public String ContractId
        {
            get { return this.m_contractId; }
            set { this.m_contractId = value; }
        }


        /// CREATE_STATISTC_REQUEST时使用此字段
        /// 用于标识带统计的年份year和带统计的工程的类别category
        private int m_year;
        public int Year
        {
            get { return this.m_year; }
            set { this.m_year = value; }
        }

        private int m_categoryId;
        public int CategoryId
        {
            get { return this.m_categoryId; }
            set { this.m_categoryId = value; }
        }
        
    }
    public class MSOfficeThread
    {
        //  待生成的航道局会前的那列表
        private static Queue<MSOfficeThreadWork> m_worksQueue = null;      //  待处理的工作队列
        private static Thread m_threadWatch = null;                 //  用户工作的线程

        public void AddWork(MSOfficeThreadWork work)
        {
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }

        }

        /// <summary>
        /// 向工作队列中添加一个会签单
        /// </summary>
        /// <param name="contractId"></param>
        public void AddContractWork(string contractId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            MSOfficeThreadWork work = new MSOfficeThreadWork
            {
                WorkKind = WORK_KIND.CREATE_CONTRACT_REQUEST,
                ContractId = contractId
            };
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }
        }

        /// <summary>
        /// 向工作队列中添加一个统计信息
        /// 任务为统计当前年份year, 当前类Category别下的会签单信息
        /// </summary>
        /// <param name="year"></param>
        /// <param name="categoryId"></param>
        public void AddStatisticWork(int year, int categoryId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            MSOfficeThreadWork work = new MSOfficeThreadWork
            {
                WorkKind = WORK_KIND.CREATE_STATISTC_REQUEST,
                Year = year,
                CategoryId = categoryId,

            };
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }
        }

        /// <summary>
        /// 向工作队列中添加一个统计信息
        /// 每当完成一个单子之后其实就可以统计这个单子所属的工作量的信息
        /// 任务为统计当前年份year, 当前类Category别下的会签单信息
        /// </summary>
        /// <param name="contractId"></param>
        public void AddStatisticWork(string contractId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            int year = DALHDJContract.GetYearFromContractId(contractId);                              // 从编号中取出年份信息

            //  此处其实有性能的缺失
            string categoryShortCall = DALHDJContract.GetCatgoryShortCallFromContractId(contractId).ToString();    // 从会签单中取出简称
            ContractCategory category = DALContractIdCategory.GetCategory(categoryShortCall);
            MSOfficeThreadWork work = new MSOfficeThreadWork
            {
                WorkKind = WORK_KIND.CREATE_STATISTC_REQUEST,
                Year = year,
                CategoryId = category.Id,

            };
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }
        }


        public void AddRegularloadWork(int categoryId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            MSOfficeThreadWork work = new MSOfficeThreadWork
            {
                WorkKind = WORK_KIND.CREATE_REGULARLOAD_REQUEST,
                CategoryId = categoryId,

            };
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }
        }

        public void AddUploadRegularloadWork(int year, int categoryId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            MSOfficeThreadWork work = new MSOfficeThreadWork
            {
                WorkKind = WORK_KIND.UPLOAD_REGULARLOAD_REQUEST,
                Year = year,
                CategoryId = categoryId,

            };
            lock (m_worksQueue)
            {
                m_worksQueue.Enqueue(work);
            }
        }
        /// <summary>
        /// 创建一个office Thread的新对象
        /// 用以生成新的会签单文档word和统计文档excel
        /// </summary>
        /// <param name="p">日志文件保存路径</param>
        /// <param name="t">日志文件创建方式的枚举</param>
        public MSOfficeThread( )
        {
            if (m_worksQueue == null)
            {
                m_worksQueue = new Queue<MSOfficeThreadWork>();
            }
            if(m_threadWatch == null)
            {
                m_threadWatch = new Thread(Work);
            }
            m_threadWatch.Start();
            
        }

        public void Work()
        {
            while (true)
            {
                //判断队列中是否存在待写入的日志
                if (m_worksQueue.Count > 0)
                {
                    MSOfficeThreadWork work = null;
                    
                    //  首先从工作队列中取出一个信息
                    lock (m_worksQueue)
                    {
                        work = m_worksQueue.Dequeue();
                    }

                    if(work != null)
                    {
                        // 开始工作
                        switch(work.WorkKind)
                        {
                            ///  需要生成会签单文档WORD
                            case WORK_KIND.CREATE_CONTRACT_REQUEST : 
                                MSWordTools.CreateHDJContractWork(work.ContractId);      //  生成会签单信息
                                break;
                            /// 需要生成统计文档EXCEL
                            case WORK_KIND.CREATE_STATISTC_REQUEST:
                                MSExcelTools.StatisticHSYearCategory(work.Year, work.CategoryId);
                                //MSExcelTools.StatisticYearCategory(work.Year, work.CategoryId);
                                break;   
                            case WORK_KIND.CREATE_REGULARLOAD_REQUEST:
                                MSExcelTools.CreateRegularloadTemplateFile(work.CategoryId);
                                break;
                            case WORK_KIND.UPLOAD_REGULARLOAD_REQUEST:
                                MSExcelTools.UploadRegularLoad(work.Year, work.CategoryId);
                                break;
                        }
                    }
                }
                else
                {
                    Thread.Sleep(10000);
                }
            }
        }

        public void Stop()
        {
            m_threadWatch.Abort();
        }
    }
}
