using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SignPressServer.SignTools
{
    public class MSOfficeTools
    {
        public static String DEFAULT_ROOT_PATH = System.AppDomain.CurrentDomain.BaseDirectory;  //"E:\\signpress\\";
        //public static String DEFAULT_ROOT_PATH = "E:\\signpress\\";
        public static string DEFAULT_CONTEMP_PATH = DEFAULT_ROOT_PATH + "contemp\\";

        public static string DEFAULT_HDJCONTRACT_PATH = DEFAULT_ROOT_PATH + "hdjcontract\\";

        public static string DEFAULT_SIGNATURE_PATH = DEFAULT_ROOT_PATH + "signature\\";

        public static string DEFAULT_REGULARLOAD_PATH = DEFAULT_ROOT_PATH + "regularload\\";

        public static string DEFAULT_STATISTIC_PATH = DEFAULT_ROOT_PATH + "statistic\\";

        public static string DEFAULT_EXCEL_FILENAME_EXTENSION = ".xls";


        //  计划任务分配表的模版
        public static string DEFAULT_REGULARLOAD_CONTEMPLATE_FILE = DEFAULT_CONTEMP_PATH + "regularload" + DEFAULT_EXCEL_FILENAME_EXTENSION;
        
        public static string DEFAULT_REGULARLOAD_TEMPLATE_FILE(int categoryId)
        {
            return DEFAULT_REGULARLOAD_PATH + categoryId.ToString() + "regularloadtemplate" + DEFAULT_EXCEL_FILENAME_EXTENSION;
        }
        
        public static string DEFAULT_REGULARLOAD_FILE(int year, int categoryId)
        {
          //  MSExcelTools.DEFAULT_REGULARLOAD_PATH + year.ToString() + categoryId.ToString() + "regularload.xls"; //获得用户保存文件的路径
            return DEFAULT_REGULARLOAD_PATH + year.ToString() + categoryId.ToString() + "regularload" + DEFAULT_EXCEL_FILENAME_EXTENSION;
        }

        public static string DEFAULT_STATISTIC_FILE(int year, int categoryId)
        {
            return DEFAULT_STATISTIC_PATH + year.ToString() + categoryId.ToString() + "statistic" + DEFAULT_EXCEL_FILENAME_EXTENSION;
        }

    }
}
