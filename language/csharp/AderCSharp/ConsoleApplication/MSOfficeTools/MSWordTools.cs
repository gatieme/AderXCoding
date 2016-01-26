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


using Microsoft.Office.MyWord;
//using System.Reflection;
//using Microsoft.Office.Interop.Word;

using SignPressServer.SignContract;
using SignPressServer.SignData;
using SignPressServer.SignDAL;

namespace SignPressServer.SignTools
{
    /*
     * 操作word的类库MSWordTools
     * 参考: http://www.cnblogs.com/eye-like/p/4121219.html
     * 
     * 创建Word 文档所使用的主要方法是通过微软公司提供的Microsoft Word X Object Library，
     * 其中X 为版本号。
     * Word 2010  对应  14.0, 
     * Word 2007  对应  12.0,
     * Word 2003  对应  11.0.
     */
    public class MSWordTools : MSOfficeTools
    {


        //  待生成的航道局会前的那列表
        private static Queue<String> m_contracts = null;
        private static Thread m_threadWatch = null;

        public void AddContractWhenCanCreated(string contractId)
        {
            //  会签单信息已经完成，直接生成会签单信息
            if (DALSignatureDetail.IsContractAgree(contractId) == true)
            {
                // 创建后台线程生成会签单信息
                //parameterizedthreadstart pts = new parameterizedthreadstart(createhdjcontracttrigger);
                //            thread thradrecmsg = new thread(pts);
                //            thradrecmsg.isbackground = true;
                //            thradrecmsg.start(detail.conid);

                lock (m_contracts)
                {
                    m_contracts.Enqueue(contractId);
                }

            }
        }
        /// <summary>
        /// 创建日志对象的新实例，根据指定的日志文件路径和指定的日志文件创建类型
        /// </summary>
        /// <param name="p">日志文件保存路径</param>
        /// <param name="t">日志文件创建方式的枚举</param>
        public MSWordTools( )
        {
            if (m_contracts == null)
            {
                m_contracts = new Queue<string>();
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
                if (m_contracts.Count > 0)
                {
                    string contractId = null;
                    lock (m_contracts)
                    {
                        contractId = m_contracts.Dequeue();
                    }
                    /// modify by gatieme @ 2015-12-14 16:51
                    if (contractId != null)
                    {
                        CreateHDJContractWork(contractId);      //  生成会签单信息
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

        public static void CreateHDJContractWork(string contractId)
        {
            String filePath = MSWordTools.DEFAULT_HDJCONTRACT_PATH + contractId + ".pdf";
            if (!(File.Exists((String)filePath)))     // 首先检测文件是否存在
            {
                String wordPath = MSWordTools.DEFAULT_HDJCONTRACT_PATH + contractId + ".doc";
                HDJContract contract = DALHDJContract.GetHDJContactAgree(contractId);       // 获取待生成的会签单信息
                
                //  之前接口已经不合乎要去了, 因为新增了对workload的支持
                MSWordTools.CreateHDJContractWordWithReplace(contract, wordPath);
                //MSWordTools.CreateHDJContractWordWithReplace(contract, wordPath);
                MSWordTools.WordConvertToPdf(wordPath, filePath);

                File.Delete((String)wordPath);
                MSWordTools.KillWordProcess();

            }
        }


        #region  创建一个WORD文档
        public void CreateWord(Object filePath)
        {
            MSWord._Application wordApp;             //  Word应用程序变量
            MSWord._Document wordDoc;                //  Word文档变量

            //MSWord.Application wordApp;             //  Word应用程序变量
            //MSWord.Document wordDoc;                //  Word文档变量

            wordApp = new MSWord.Application( );    //初始化
            
            if (File.Exists((String)filePath))
            {
                File.Delete((String)filePath);
            }
            
            //由于使用的是COM 库，因此有许多变量需要用Missing.Value 代替
            Object Missing = System.Reflection.Missing.Value;
            //新建一个word对象
            wordDoc = wordApp.Documents.Add(ref Missing, ref Missing, ref Missing, ref Missing);
            
            //WdSaveDocument为Word2003文档的保存格式(文档后缀.doc)\wdFormatDocumentDefault为Word2007的保存格式(文档后缀.docx)
            Object format = MSWord.WdSaveFormat.wdFormatDocument;
            
            //将wordDoc 文档对象的内容保存为DOC 文档,并保存到filePath指定的路径
            wordDoc.SaveAs(ref filePath, ref format, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);
            //关闭wordDoc文档
            
            wordDoc.Close(ref Missing, ref Missing, ref Missing);
            //关闭wordApp组件对象
            wordApp.Quit(ref Missing, ref Missing, ref Missing);
            Console.WriteLine(filePath + ": Word文档创建完毕!')...");
        }
        #endregion


        #region  在WORD中添加图片
        public void AddWordPic(Object filePath, Object picPath)
        {
            MSWord._Application wordApp;            //  Word应用程序变量
            MSWord._Document    wordDoc;            //  Word文档变量
            
            wordApp = new MSWord.Application( );    //初始化
            if(File.Exists((String)filePath))
            {
                File.Delete((String)filePath);
            }
            Object Missing = System.Reflection.Missing.Value;
            
            wordDoc = wordApp.Documents.Add(ref Missing, ref Missing, ref Missing, ref Missing);

            //定义要向文档中插入图片的位置
            Object Range = wordDoc.Paragraphs.Last.Range;
            
            //定义该图片是否为外部链接
            Object linkToFile = false;  //默认
            
            //定义插入的图片是否随word一起保存
            Object saveWithDocument = true;
            
            //向word中写入图片
            wordDoc.InlineShapes.AddPicture((String)picPath, ref Missing, ref Missing, ref Missing);

            Object unite = Microsoft.Office.Interop.Word.WdUnits.wdStory;
            wordApp.Selection.ParagraphFormat.Alignment = MSWord.WdParagraphAlignment.wdAlignParagraphCenter;//居中显示图片
            wordDoc.InlineShapes[1].Height = 130;
            wordDoc.InlineShapes[1].Width = 200;
            wordDoc.Content.InsertAfter("\n");
            wordApp.Selection.EndKey(ref unite, ref Missing);
            wordApp.Selection.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphCenter;
            wordApp.Selection.Font.Size = 10;//字体大小
            wordApp.Selection.TypeText("图1 测试图片\n");

            //WdSaveDocument为Word2003文档的保存格式(文档后缀.doc)\wdFormatDocumentDefault为Word2007的保存格式(文档后缀.docx)
            Object format = MSWord.WdSaveFormat.wdFormatDocument;
            wordDoc.SaveAs(ref filePath, ref format, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);
            wordDoc.Close(ref Missing, ref Missing, ref Missing);
            wordApp.Quit(ref Missing, ref Missing, ref Missing);
            Console.WriteLine(filePath + ": Word文档创建图片完毕!");
        }
        #endregion


        #region  在WORD中添加表格
        public void AddWordTable(Object filePath)
        {
            MSWord._Application wordApp;             //Word应用程序变量
            MSWord._Document wordDoc;                //Word文档变量
            wordApp = new MSWord.Application();     //初始化
            
            if(File.Exists((String)filePath))
            {
                File.Delete((String)filePath);
            }
            Object Missing = System.Reflection.Missing.Value;
            wordDoc = wordApp.Documents.Add(ref Missing, ref Missing, ref Missing, ref Missing);

            int tableRow = 6;
            int tableColumn = 6;
            
            //定义一个word中的表格对象
            MSWord.Table table = wordDoc.Tables.Add(wordApp.Selection.Range, tableRow, tableColumn, ref Missing, ref Missing);


            wordDoc.Tables[1].Cell(1, 1).Range.Text = "列\n行"; 
            for (int i = 1; i < tableRow; i++)
            {
                for (int j = 1; j < tableColumn; j++)
                {
                    if (i == 1)
                    {
                        table.Cell(i, j+1).Range.Text = "Column " + j;
                    }
                    if (j == 1)
                    {
                        table.Cell(i+1, j).Range.Text = "Row " + i;
                    }
                    table.Cell(i+1, j+1).Range.Text =  i + "行 " + j + "列";
                }
            }


            //添加行
            table.Rows.Add(ref Missing);
            table.Rows[tableRow + 1].Height = 45;
            //向新添加的行的单元格中添加图片
            String fileName = @"G:\[B]CodeRuntimeLibrary\[E]GitHub\SignPressServer\测试图片.jpg";   //图片所在路径
            Object LinkToFile = false;
            Object SaveWithDocument = true;
            Object Anchor = table.Cell(tableRow+1, tableColumn).Range;//选中要添加图片的单元格
            
            wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((String)fileName, ref LinkToFile, ref SaveWithDocument, ref Anchor);
            wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
            wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 45;//图片高度
            // 将图片设置为四周环绕型
            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
            s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;


            //设置table样式
            table.Rows.HeightRule = MSWord.WdRowHeightRule.wdRowHeightAtLeast;
            table.Rows.Height = wordApp.CentimetersToPoints(float.Parse("0.8"));

            table.Range.Font.Size = 10.5F;
            table.Range.Font.Bold = 0;

            table.Range.ParagraphFormat.Alignment = MSWord.WdParagraphAlignment.wdAlignParagraphCenter;
            table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalBottom;
            //设置table边框样式
            table.Borders.OutsideLineStyle = MSWord.WdLineStyle.wdLineStyleDouble;
            table.Borders.InsideLineStyle = MSWord.WdLineStyle.wdLineStyleSingle;

            table.Rows[1].Range.Font.Bold = 1;
            table.Rows[1].Range.Font.Size = 12F;
            table.Cell(1, 1).Range.Font.Size = 10.5F;
            wordApp.Selection.Cells.Height = 40;//所有单元格的高度
            for (int i = 2; i <= tableRow; i++)
            {
                table.Rows[i].Height = 20;
            }
            table.Cell(1, 1).Range.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphRight;
            table.Cell(1, 1).Range.Paragraphs[2].Format.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphLeft;
            
            table.Columns[1].Width = 50;
            for (int i = 2; i <=tableColumn; i++)
            {
                table.Columns[i].Width = 75;
            }


            //添加表头斜线,并设置表头的样式
            table.Cell(1, 1).Borders[Microsoft.Office.Interop.Word.WdBorderType.wdBorderDiagonalDown].Visible = true;
            table.Cell(1, 1).Borders[Microsoft.Office.Interop.Word.WdBorderType.wdBorderDiagonalDown].Color = Microsoft.Office.Interop.Word.WdColor.wdColorGray60;
            table.Cell(1, 1).Borders[Microsoft.Office.Interop.Word.WdBorderType.wdBorderDiagonalDown].LineWidth = Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth050pt;

            //表格边框
            /*//表格内容行边框
            table.SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderHorizontal, Microsoft.Office.Interop.Word.WdColor.wdColorGray20, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth025pt);
            //表格内容列边框
            table.SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderVertical, Microsoft.Office.Interop.Word.WdColor.wdColorGray20, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth025pt);

            SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderLeft, Microsoft.Office.Interop.Word.WdColor.wdColorGray50, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth050pt);

            SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderRight, Microsoft.Office.Interop.Word.WdColor.wdColorGray50, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth050pt);

            SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderTop, Microsoft.Office.Interop.Word.WdColor.wdColorGray50, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth050pt);

            SetTableBorderStyle(table, Microsoft.Office.Interop.Word.WdBorderType.wdBorderBottom, Microsoft.Office.Interop.Word.WdColor.wdColorGray50, Microsoft.Office.Interop.Word.WdLineWidth.wdLineWidth050pt);
            */
              //合并单元格
            table.Cell(4, 4).Merge(table.Cell(4, 5));//横向合并

            table.Cell(2, 3).Merge(table.Cell(4, 3));//纵向合并


            Object format = MSWord.WdSaveFormat.wdFormatDocument;
            wordDoc.SaveAs(ref filePath, ref format, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);
            wordDoc.Close(ref Missing, ref Missing, ref Missing);
            wordApp.Quit(ref Missing, ref Missing, ref Missing);
            Console.Write(filePath + ": Word文档创建表格完毕!");
        }

        #endregion


        #region 将WORD转换为PDF
        public static bool WordConvertToPdf(Object wordFilePath, Object saveFilePath)
        {
            bool result                 = false;

            Object readOnly             = true;
            Object isVisible            = true;
            Object confirmConverisons   = false;
            Object openAndRepair        = false;
            Object Missing              = System.Reflection.Missing.Value;

            MSWord._Application wordApp = new MSWord.Application( );
            MSWord._Document    wordDoc = null;
            
            try
            {
                wordDoc = wordApp.Documents.Open((String)wordFilePath, ref confirmConverisons, ref readOnly,
                            ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                            ref Missing, ref Missing, ref isVisible, ref openAndRepair, ref Missing, ref Missing, ref Missing);


                //  设置保存的格式   
                Object fileFarmat = Microsoft.Office.Interop.Word.WdSaveFormat.wdFormatPDF;
                //   保存为PDF   
                wordDoc.SaveAs(ref saveFilePath, ref fileFarmat, ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing,ref Missing);
                result = true;

                Console.WriteLine("将转换WORD文件" + wordFilePath + "转换为" + saveFilePath);
            }
            catch(Exception ex)
            {
                result = false;

                // 输出异常信息
                Console.WriteLine("Error:" + ex.Message);
                Console.WriteLine("Source:" + ex.Source);
                Console.WriteLine("StackTrace:" + ex.StackTrace);
            }
            finally
            {
                //  关闭文档对象 
                if (wordDoc != null)
                {
                    wordDoc.Close(ref Missing, ref Missing, ref Missing);
                    wordDoc = null;
                }
                
                //  退出组件   
                if (wordApp != null)
                {
                    wordApp.Quit(ref Missing, ref Missing, ref Missing);
                    wordApp = null;
                }
            }
            return result;
        }  
        #endregion


        #region 生成拨款会签单

        public static bool CreateHDJContractWordWithReplace(HDJContract contract)
        {

            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = DEFAULT_HDJCONTRACT_PATH + contract.Id + ".doc";                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();



                MSWord.Table table = wordDoc.Tables[1];
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来

                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;

                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                // 首先填写前5行的会签单基本信息
                //object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                int currTableRow = 1;
                for (currTableRow = 1; currTableRow <= 5; currTableRow++)
                {

                    replaceKey = "$" + contract.ConTemp.ColumnNames[currTableRow - 1] + "$";
                    replaceValue = contract.ColumnDatas[currTableRow - 1].ToString().Replace("\r\n", "^l");
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                }

                //  开始添加审核人的签名图片信息和备注信息
                Console.WriteLine("开始生成后8行签字栏目的信息");

                int signCount = 0;                          // 8个签字人的计数器
                for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
                {
                    for (int col = 1; col <= 3; col += 2, signCount++)
                    {
                        Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

                        ///////
                        // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
                        ///////
                        /// 填写第row行第一个签字人的表头
                        /// [签字人表头坐标(row, col), 签字人序号cnt]
                        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                        table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                        // 插入第row行第一个人签字人的签字图片
                        //[签字人签字位置坐标(row, col + 1)] 
                        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                        object linktofile = false;
                        object savewithdocument = true;
                        object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
                        Console.WriteLine("签字人的签名图片地址" + signFileName);
                        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 30;//图片高度

                        // 将图片设置为四周环绕型
                        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                    }
                }

                // 生成主管局长和局长的签字信息
                for (currTableRow = 9; currTableRow <= table.Rows.Count; currTableRow++, signCount++)
                {
                    Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                    //table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 局长副局长只需要签字就可以，因此合并后面的单元格
                    //table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
                    //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 插入第row行第一个人签字人的签字图片
                    //[签字人签字位置坐标(row, col + 1)] 
                    string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                    //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                    object linktofile = false;
                    object savewithdocument = true;
                    object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
                    Console.WriteLine("签字人的签名图片地址" + signFileName);
                    wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 30;//图片高度

                    // 将图片设置为四周环绕型
                    MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                    s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                }
            
                //   保存为PDF   
                wordDoc.Save();

                result = true;
            }
            catch (Exception)
            {
                result = false;

            }
            finally
            {
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
            }
            return result;
        }



        public static bool CreateHDJContractWordWithReplace(HDJContract contract, Object filePath)
        {

            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = filePath;                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();
                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;


                wordApp.Selection.Find.Text = "$编号$";
                //wordApp.Selection.Find.Replacement.ClearFormatting(); 
                wordApp.Selection.Find.Replacement.Text = contract.Id;
                wordApp.Selection.Find.Execute(ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                //  填写表格的信息
                MSWord.Table table = wordDoc.Tables[1];
                //table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter;
                //table.Range.Rows.Alignment = MSWord.WdRowAlignment.wdAlignRowCenter;
                //设置table边框样式
                //table.Borders.Outsidelinestyle = MSWord.WdLineStyle.wdLineStyleDouble;
                //table.Borders.Insidelinestyle = MSWord.WdLineStyle.wdLineStyleSingle;
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来


                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                // 首先填写前5行的会签单基本信息
                //object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                int currTableRow = 1;
                for (currTableRow = 1; currTableRow <= 5; currTableRow++)
                {

                    replaceKey = "$" + contract.ConTemp.ColumnNames[currTableRow - 1] + "$";
                    replaceValue = contract.ColumnDatas[currTableRow - 1].ToString().Replace("\r", "").Replace("\n", "^p");
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                }

                //  开始添加审核人的签名图片信息和备注信息
                Console.WriteLine("开始生成后8行签字栏目的信息");

                int signCount = 0;                          // 8个签字人的计数器
                for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
                {
                    for (int col = 1; col <= 3; col += 2, signCount++)
                    {
                        Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

                        ///////
                        // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
                        ///////
                        /// 填写第row行第一个签字人的表头
                        /// [签字人表头坐标(row, col), 签字人序号cnt]
                        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                        table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                        // 插入第row行第一个人签字人的签字图片
                        //[签字人签字位置坐标(row, col + 1)] 
                        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                        object linktofile = false;
                        object savewithdocument = true;
                        object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
                        Console.WriteLine("签字人的签名图片地址" + signFileName);
                        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度

                        // 将图片设置为四周环绕型
                        //MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        //s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                    }
                }

                // 生成主管局长和局长的签字信息
                for (currTableRow = 9; currTableRow <= table.Rows.Count; currTableRow++, signCount++)
                {
                    Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                    //table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 局长副局长只需要签字就可以，因此合并后面的单元格
                    //table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
                    //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 插入第row行第一个人签字人的签字图片
                    //[签字人签字位置坐标(row, col + 1)] 
                    string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                    //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                    object linktofile = false;
                    object savewithdocument = true;
                    object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
                    Console.WriteLine("签字人的签名图片地址" + signFileName);
                    wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度


                    // 将图片设置为四周环绕型
                    //MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                    //s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                }

                //   保存为PDF   
                wordDoc.Save();
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
                result = true;
            }
            catch (Exception)
            {
                result = false;

            }
            finally
            {


            }
            return result;
        }

        public static bool CreateHDJContractWordWithEorkloadWithReplace(HDJContract contract, Object filePath)
        {

            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = filePath;                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();
                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;


                wordApp.Selection.Find.Text = "$编号$";
                //wordApp.Selection.Find.Replacement.ClearFormatting(); 
                wordApp.Selection.Find.Replacement.Text = contract.Id;
                wordApp.Selection.Find.Execute(ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                //  填写表格的信息
                MSWord.Table table = wordDoc.Tables[1];
                //table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter;
                //table.Range.Rows.Alignment = MSWord.WdRowAlignment.wdAlignRowCenter;
                //设置table边框样式
                //table.Borders.Outsidelinestyle = MSWord.WdLineStyle.wdLineStyleDouble;
                //table.Borders.Insidelinestyle = MSWord.WdLineStyle.wdLineStyleSingle;
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来


                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                // 首先填写前5行的会签单基本信息
                //object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                int currTableRow = 1;
                for (currTableRow = 1; currTableRow <= 5; currTableRow++)
                {

                    replaceKey = "$" + contract.ConTemp.ColumnNames[currTableRow - 1] + "$";
                    
                    replaceValue = contract.ColumnDatas[currTableRow - 1].ToString().Replace("\r", "").Replace("\n", "^p");
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                }

                
                //  开始添加审核人的签名图片信息和备注信息
                Console.WriteLine("开始生成后8行签字栏目的信息");

                int signCount = 0;                          // 8个签字人的计数器
                for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
                {
                    for (int col = 1; col <= 3; col += 2, signCount++)
                    {
                        Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

                        ///////
                        // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
                        ///////
                        /// 填写第row行第一个签字人的表头
                        /// [签字人表头坐标(row, col), 签字人序号cnt]
                        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                        table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                        // 插入第row行第一个人签字人的签字图片
                        //[签字人签字位置坐标(row, col + 1)] 
                        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                        object linktofile = false;
                        object savewithdocument = true;
                        object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
                        Console.WriteLine("签字人的签名图片地址" + signFileName);
                        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度

                        // 将图片设置为四周环绕型
                        //MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        //s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                    }
                }

                // 生成主管局长和局长的签字信息
                for (currTableRow = 9; currTableRow <= table.Rows.Count; currTableRow++, signCount++)
                {
                    Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                    //table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 局长副局长只需要签字就可以，因此合并后面的单元格
                    //table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
                    //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 插入第row行第一个人签字人的签字图片
                    //[签字人签字位置坐标(row, col + 1)] 
                    string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                    //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                    object linktofile = false;
                    object savewithdocument = true;
                    object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
                    Console.WriteLine("签字人的签名图片地址" + signFileName);
                    wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度


                    // 将图片设置为四周环绕型
                    //MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                    //s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                }

                //   保存为PDF   
                wordDoc.Save();
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
                result = true;
            }
            catch (Exception)
            {
                result = false;

            }
            finally
            {


            }
            return result;
        }



        /// <summary>
        /// 使用替换的方式生成会签单，同时加上备注信息
        /// </summary>
        /// <param name="contract"></param>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static bool CreateHDJContractWordWithReplaceIntoRemarks(HDJContract contract, Object filePath)
        {

            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = filePath;                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();
                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;


                wordApp.Selection.Find.Text = "$编号$";
                //wordApp.Selection.Find.Replacement.ClearFormatting(); 
                wordApp.Selection.Find.Replacement.Text = contract.Id;
                wordApp.Selection.Find.Execute(ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                //  填写表格的信息
                MSWord.Table table = wordDoc.Tables[1];
                //table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter;
                //table.Range.Rows.Alignment = MSWord.WdRowAlignment.wdAlignRowCenter;
                //设置table边框样式
                //table.Borders.Outsidelinestyle = MSWord.WdLineStyle.wdLineStyleDouble;
                //table.Borders.Insidelinestyle = MSWord.WdLineStyle.wdLineStyleSingle;
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来


                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                // 首先填写前5行的会签单基本信息
                //object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                int currTableRow = 1;
                for (currTableRow = 1; currTableRow <= 5; currTableRow++)
                {

                    replaceKey = "$" + contract.ConTemp.ColumnNames[currTableRow - 1] + "$";
                    replaceValue = contract.ColumnDatas[currTableRow - 1].ToString();
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                }

                //  开始添加审核人的签名图片信息和备注信息
                Console.WriteLine("开始生成后8行签字栏目的信息");

                int signCount = 0;                          // 8个签字人的计数器
                for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
                {
                    for (int col = 1; col <= 3; col += 2, signCount++)
                    {
                        Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

                        ///////
                        // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
                        ///////
                        /// 填写第row行第一个签字人的表头
                        /// [签字人表头坐标(row, col), 签字人序号cnt]
                        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                        table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                        // 插入第row行第一个人签字人的签字图片
                        //[签字人签字位置坐标(row, col + 1)] 
                        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                        object linktofile = false;
                        object savewithdocument = true;
                        object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
                        Console.WriteLine("签字人的签名图片地址" + signFileName);
                        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度
                        //Console.WriteLine("签字人的备注信息" + contract.SignRemarks[signCount]);


                        // 将图片设置为四周环绕型
                        //	wdWrapInline 7 将形状嵌入到文字中。 
                        //	wdWrapNone 3 将形状放在文字前面。请参阅 wdWrapFront 。
                        //	wdWrapSquare 0 使文字环绕形状。行在形状的另一侧延续。
                        //	wdWrapThrough 2 使文字环绕形状。
                        //	wdWrapTight 1 使文字紧密地环绕形状。
                        //	wdWrapTopBottom 4 将文字放在形状的上方和下方。
                        //	wdWrapBehind 5 将形状放在文字后面。
                        //	wdWrapFront 6 将形状放在文字前面。
                        string signRemark = contract.SignRemarks[signCount].ToString();
                        replaceKey = "$备注" + signCount + "$";
                        if(signRemark == "" || signRemark == "未填")
                        {

                            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                            s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                        
                            replaceValue = "";
                        }
                        else
                        {
                            // 将图片设置为四周环绕型
                            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                            s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                        
                            replaceValue = contract.SignRemarks[signCount].ToString();
                        }
                        table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                        Console.WriteLine("替换备注{0}为{1}成功", replaceKey, replaceValue);
 
                    }
                }

                // 生成主管局长和局长的签字信息
                for (currTableRow = 9; currTableRow <= table.Rows.Count; currTableRow++, signCount++)
                {
                    Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                    //table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 局长副局长只需要签字就可以，因此合并后面的单元格
                    //table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
                    //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 插入第row行第一个人签字人的签字图片
                    //[签字人签字位置坐标(row, col + 1)] 
                    string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                    //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                    object linktofile = false;
                    object savewithdocument = true;
                    object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
                    Console.WriteLine("签字人的签名图片地址" + signFileName);
                    wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度



                    string signRemark = contract.SignRemarks[signCount].ToString();
                    replaceKey = "$备注" + signCount + "$";
                    if (signRemark == "" || signRemark == "未填")
                    {
                        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                        replaceValue = "";
                    }
                    else
                    {
                        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                        replaceValue = contract.SignRemarks[signCount].ToString();
                    }
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换备注{0}为{1}成功", replaceKey, replaceValue);
                }
                table.Range.ParagraphFormat.Alignment = MSWord.WdParagraphAlignment.wdAlignParagraphCenter;     //  水平居中
                table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter; //  垂直居中

                //   保存为PDF   
                wordDoc.Save();
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
                result = true;
            }
            catch (Exception)
            {
                result = false;

            }
            finally
            {

            }
            return result;
        }


        /// <summary>
        /// 使用替换的方式生成会签单，同时加上备注信息
        /// </summary>
        /// <param name="contract"></param>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static bool CreateHDJContractWordWithReplaceOntoRemarks(HDJContract contract, Object filePath)
        {

            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = filePath;                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();
                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;


                wordApp.Selection.Find.Text = "$编号$";
                //wordApp.Selection.Find.Replacement.ClearFormatting(); 
                wordApp.Selection.Find.Replacement.Text = contract.Id;
                wordApp.Selection.Find.Execute(ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                //  填写表格的信息
                MSWord.Table table = wordDoc.Tables[1];
                //table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter;
                //table.Range.Rows.Alignment = MSWord.WdRowAlignment.wdAlignRowCenter;
                //设置table边框样式
                //table.Borders.Outsidelinestyle = MSWord.WdLineStyle.wdLineStyleDouble;
                //table.Borders.Insidelinestyle = MSWord.WdLineStyle.wdLineStyleSingle;
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来


                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                // 首先填写前5行的会签单基本信息
                //object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                int currTableRow = 1;
                for (currTableRow = 1; currTableRow <= 5; currTableRow++)
                {

                    replaceKey = "$" + contract.ConTemp.ColumnNames[currTableRow - 1] + "$";
                    replaceValue = contract.ColumnDatas[currTableRow - 1].ToString();
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                }

                //  开始添加审核人的签名图片信息和备注信息
                Console.WriteLine("开始生成后8行签字栏目的信息");

                int signCount = 0;                          // 8个签字人的计数器
                for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
                {
                    for (int col = 1; col <= 3; col += 2, signCount++)
                    {
                        Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

                        ///////
                        // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
                        ///////
                        /// 填写第row行第一个签字人的表头
                        /// [签字人表头坐标(row, col), 签字人序号cnt]
                        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                        table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;



                        // 将图片设置为四周环绕型
                        //	wdWrapInline 7 将形状嵌入到文字中。 
                        //	wdWrapNone 3 将形状放在文字前面。请参阅 wdWrapFront 。
                        //	wdWrapSquare 0 使文字环绕形状。行在形状的另一侧延续。
                        //	wdWrapThrough 2 使文字环绕形状。
                        //	wdWrapTight 1 使文字紧密地环绕形状。
                        //	wdWrapTopBottom 4 将文字放在形状的上方和下方。
                        //	wdWrapBehind 5 将形状放在文字后面。
                        //	wdWrapFront 6 将形状放在文字前面。
                        string signRemark = contract.SignRemarks[signCount].ToString();
                        replaceKey = "$备注" + signCount + "$";
                        if (signRemark == "" || signRemark == "未填")
                        {

                            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                            s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                            replaceValue = "";
                        }
                        else
                        {
                            // 将图片设置为四周环绕型
                            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                            s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                            replaceValue = contract.SignRemarks[signCount].ToString();
                        }
                        table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                        Console.WriteLine("替换备注{0}为{1}成功", replaceKey, replaceValue);


                        // 插入第row行第一个人签字人的签字图片
                        //[签字人签字位置坐标(row, col + 1)] 
                        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                        object linktofile = false;
                        object savewithdocument = true;
                        object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
                        Console.WriteLine("签字人的签名图片地址" + signFileName);
                        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                        wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度
                        //Console.WriteLine("签字人的备注信息" + contract.SignRemarks[signCount]);
                    }
                }

                // 生成主管局长和局长的签字信息
                for (currTableRow = 9; currTableRow <= table.Rows.Count; currTableRow++, signCount++)
                {
                    Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
                    //table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    // 局长副局长只需要签字就可以，因此合并后面的单元格
                    //table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
                    //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

                    string signRemark = contract.SignRemarks[signCount].ToString();
                    replaceKey = "$备注" + signCount + "$";
                    if (signRemark == "" || signRemark == "未填")
                    {
                        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;
                        replaceValue = "";
                    }
                    else
                    {
                        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
                        s.WrapFormat.Type = MSWord.WdWrapType.wdWrapSquare;

                        replaceValue = contract.SignRemarks[signCount].ToString();
                    }
                    table.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                    Console.WriteLine("替换备注{0}为{1}成功", replaceKey, replaceValue);

                    // 插入第row行第一个人签字人的签字图片
                    //[签字人签字位置坐标(row, col + 1)] 
                    string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.Id.ToString() + ".jpg";   //图片所在路径
                    //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
                    object linktofile = false;
                    object savewithdocument = true;
                    object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
                    Console.WriteLine("签字人的签名图片地址" + signFileName);
                    wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 75;//图片宽度
                    wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 25;//图片高度



                }
                table.Range.ParagraphFormat.Alignment = MSWord.WdParagraphAlignment.wdAlignParagraphCenter;     //  水平居中
                table.Range.Cells.VerticalAlignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalCenter; //  垂直居中

                //   保存为PDF   
                wordDoc.Save();
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
                result = true;
            }
            catch (Exception)
            {
                result = false;

            }
            finally
            {

            }
            return result;
        }
        //public static bool CreateHDJContractWord(HDJContract contract, Object saveFilePath)
        //{
        //    #region 完全生成会签单信息


        //    Console.WriteLine("开始生成养护及例会项目拨款会签单");

        //    MSWord._Application wordapp;             // word应用程序变量
        //    MSWord._document wordDoc;                // word文档变量
        //    wordapp = new MSWord.Application();      //  初始化
        //    object Missing = system.reflection.Missing.value;


        //    if (file.exists((string)savefilepath))
        //    {
        //        file.delete((string)savefilepath);
        //    }
        //    wordDoc = wordapp.documents.add(ref Missing, ref Missing, ref Missing, ref Missing);

        //    //  首先添加会签单标题和编号

        //    const int tablerow = 10;          //  表格的行数
        //    const int tablecolumn = 4;        //  表格的列数
        //    int currTableRow = 1;             //  当前操作的表格行

        //    //  定义一个word中的表格对象
        //    MSWord.table table = wordDoc.tables.add(wordapp.selection.Range, tablerow, tablecolumn, ref Missing, ref Missing);

        //    // 添加表头信息，同时合并单元格的信息
        //    Console.WriteLine("开始生成前5行基本栏目的信息");
        //    for (currTableRow = 1; currTableRow <= 5/*contract.ConTemp.columncount*/; currTableRow++)              // 循环每行
        //    {
        //        table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.columnnames[currTableRow - 1];    //  添加表头信息
        //        table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
        //        table.Cell(currTableRow, 2).Range.Text = contract.ColumnDatas[currTableRow - 1];
        //    }

        //    //  开始添加审核人的签名图片信息和备注信息
        //    Console.WriteLine("开始生成后8行签字栏目的信息");
        //    int signCount = 0;                          // 8个签字人的计数器
        //    for (currTableRow = 6; currTableRow <= 8; currTableRow++)    // 填写表格的签字人表头
        //    {
        //        for (int col = 1; col <= 3; col += 2, signCount++)
        //        {
        //            Console.WriteLine("签字人信息位置{0}, {1} ==== 签字人序号{2} ==== 签字位置{3},{4}", currTableRow, col, signCount, currTableRow, col + 1);

        //            ///////
        //            // 填写第row行第一个签字人的签字信息[表头 + 签字信息 + 备注]
        //            ///////
        //            /// 填写第row行第一个签字人的表头
        //            /// [签字人表头坐标(row, col), 签字人序号cnt]
        //            Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
        //            table.Cell(currTableRow, col).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

        //            // 插入第row行第一个人签字人的签字图片
        //            //[签字人签字位置坐标(row, col + 1)] 
        //            string signFileName = default_signature_path + contract.ConTemp.SignDatas[signCount].SignEmployee.id.tostring() + ".jpg";   //图片所在路径
        //            //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
        //            object linktofile = false;
        //            object savewithdocument = true;
        //            object anchor = table.Cell(currTableRow, col + 1).Range;//选中要添加图片的单元格
        //            Console.WriteLine("签字人的签名图片地址" + signFileName);
        //            wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
        //            wordDoc.Application.ActiveDocument.InlineShapes[1].width = 75;//图片宽度
        //            wordDoc.Application.ActiveDocument.InlineShapes[1].height = 45;//图片高度

        //            // 将图片设置为四周环绕型
        //            MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].converttoShape();
        //            s.wrapformat.type = MSWord.wdwraptype.wdwrapsquare;
        //        }
        //    }

        //    // 生成主管局长和局长的签字信息
        //    for (currTableRow = 9; currTableRow <= tablerow; currTableRow++, signCount++)
        //    {
        //        Console.WriteLine("当前签字人序号{0}, 信息{1}", signCount, contract.ConTemp.SignDatas[signCount].SignInfo);
        //        table.Cell(currTableRow, 1).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

        //        // 局长副局长只需要签字就可以，因此合并后面的单元格
        //        table.Cell(currTableRow, 2).Merge(table.Cell(currTableRow, 4));                       //  横向合并
        //        //table.Cell(currTableRow, 2).Range.Text = contract.ConTemp.SignDatas[signCount].SignInfo;

        //        // 插入第row行第一个人签字人的签字图片
        //        //[签字人签字位置坐标(row, col + 1)] 
        //        string signFileName = DEFAULT_SIGNATURE_PATH + contract.ConTemp.SignDatas[signCount].SignEmployee.id.tostring() + ".jpg";   //图片所在路径
        //        //string signFileName = @"g:\[b]coderuntimelibrary\[e]github\signpressserver\测试图片.jpg";
        //        object linktofile = false;
        //        object savewithdocument = true;
        //        object anchor = table.Cell(currTableRow, 2).Range;//选中要添加图片的单元格
        //        Console.WriteLine("签字人的签名图片地址" + signFileName);
        //        wordDoc.Application.ActiveDocument.InlineShapes.AddPicture((string)signFileName, ref linktofile, ref savewithdocument, ref anchor);
        //        wordDoc.Application.ActiveDocument.InlineShapes[1].width = 75;//图片宽度
        //        wordDoc.Application.ActiveDocument.InlineShapes[1].height = 45;//图片高度

        //        // 将图片设置为四周环绕型
        //        MSWord.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].converttoShape();
        //        s.wrapformat.type = MSWord.WdWrapType.wdWrapSquare;

        //    }
        //    //设置table样式
        //    table.rows.heightrule = MSWord.WdRowHeightRule.wdRowHeightAtLeast;
        //    table.rows.height = wordapp.centimeterstopoints(float.Parse("0.8"));

        //    table.Range.font.size = 10.5f;
        //    table.Range.font.bold = 0;

        //    table.Range.paragraphformat.alignment = MSWord.WdParagraphAlignment.wdAlignParagraphCenter;
        //    table.Range.Cells.verticalalignment = MSWord.WdCellVerticalAlignment.wdCellAlignVerticalBottom;
        //    //设置table边框样式
        //    table.borders.outsidelinestyle = MSWord.WdLineStyle.wdLineStyleDouble;
        //    table.borders.insidelinestyle = MSWord.WdLineStyle.wdLineStyleSingle;

        //    table.rows[1].Range.font.bold = 1;
        //    table.rows[1].Range.font.size = 12f;
        //    table.Cell(1, 1).Range.font.size = 10.5f;
        //    wordapp.selection.Cells.height = 40;                //所有单元格的高度

        //    for (int i = 2; i <= tablerow; i++)
        //    {
        //        table.rows[i].height = 20;
        //    }

        //    //table.Cell(1, 1).Range.paragraphformat.alignment = microsoft.office.interop.word.wdparagraphalignment.wdalignparagraphright;
        //    //table.Cell(1, 1).Range.paragraphs[2].format.alignment = microsoft.office.interop.word.wdparagraphalignment.wdalignparagraphleft;

        //    //table.columns[1].width = 50;
        //    //for (int i = 2; i <= tablecolumn; i++)
        //    //{
        //    //    table.columns[i].width = 75;
        //    //}

        //    object format = MSWord.WdSaveFormat.wdFormatDocument;
        //    wordDoc.saveas(ref saveFilePath, ref format, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);
        //    wordDoc.close(ref Missing, ref Missing, ref Missing);
        //    wordapp.quit(ref Missing, ref Missing, ref Missing);
        //    Console.WriteLine(saveFilePath + ": word文档创建表格完毕!");
        //    #endregion

        //    return true;
        //}




        public static bool CreateHDJContractWordWithBookMark(HDJContract contract, Object saveFilePath)
        {
            bool result = false;

            // 首先导入会签单模版
            object Missing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word._Application wordApp;
            Microsoft.Office.Interop.Word._Document wordDoc = null;
            wordApp = new Microsoft.Office.Interop.Word.Application();
            wordApp.Visible = false;
            object ConTempFileName = DEFAULT_CONTEMP_PATH + contract.ConTemp.TempId + ".doc";        //  模版信息
            object saveFileName = DEFAULT_SIGNATURE_PATH + contract.Id + ".doc";                    //  保存成的会签单信息
            Console.WriteLine("待导入的会签单模版{0}", ConTempFileName);
            Console.WriteLine("待保存的会签单信息{0}", saveFileName);

            try
            {

                File.Copy((string)ConTempFileName, (string)saveFileName, true);
                wordDoc = wordApp.Documents.Open(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);


                //wordDoc = wordApp.Documents.Add(ref saveFileName, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing,
                //    ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);

                wordDoc.Activate();



                MSWord.Table table = wordDoc.Tables[1];
                Console.WriteLine("表格的行数{0}, 列数{1}", table.Rows.Count, table.Columns.Count);
                //wordDoc.Tables[1].Select();     //复制第一个表格,如果有多条粘贴到尾部
                //wordDoc.Selection.Copy();       //如果导入多条要把原来的模版粘贴下来

                object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;

                object replaceKey = "$编号$";
                object replaceValue = contract.Id.ToString();
                //wordDoc.Range.Find.Execute(ref replaceKey, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref  replaceValue, ref replaceArea, ref Missing, ref Missing, ref Missing, ref Missing);

                //// 首先填写前5行的会签单基本信息
                ////object replaceArea = Microsoft.Office.Interop.Word.WdReplace.wdReplaceAll;
                //for (int row = 0; row < 5; row++)
                //{

                //    #region 查找书签并替换
                //    wordApp.GotoBookMark(contract.ConTemp.ColumnNames[row]);
                //    wordApp.InsertText(contract.ColumnDatas[row]);
                //    wordApp.SetFont(nothing);

                //    Console.WriteLine("替换{0}为{1}成功", replaceKey, replaceValue);
                //}


                // 填写后面8个签字人的签字信息
                wordDoc.Save();
                result = true;
            }
            catch (Exception)
            {


            }
            finally
            {
                object o = false;
                wordDoc.Close(ref o, ref Missing, ref Missing);
                wordApp.Quit(ref o, ref Missing, ref Missing);
            }
            return result;


        }
        public static bool CreateHDJContractPdf(HDJContract contract, Object saveFilePath)
        {
            /////////////////////
            ///
            ///
            ///
            ////////////////////


            //  设置保存的格式   
            //Object fileFarmat = Microsoft.Office.Interop.Word.WdSaveFormat.wdFormatPDF;
            ////   保存为PDF   
            //wordDoc.SaveAs(ref saveFilePath, ref fileFarmat, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing, ref Missing);
            //result = true;

            //Console.WriteLine("转换为PDF成功..." + saveFilePath);

            //return result;
            return true;
        }

        #endregion



        //#region 动态生成Word文档并填充数据
        ///**/
        ///// <summary>
        ///// 动态生成Word文档并填充数据
        ///// </summary>
        ///// <returns>返回自定义信息</returns>
        //public static string CreateWordFile()
        //{
        //    string message = "";
        //    try
        //    {
        //        Object oMissing = System.Reflection.Missing.Value;
        //        string dir = System.Web.HttpConText.Current.Server.MapPath("");//首先在类库添加using System.web的引用
        //        if (!Directory.Exists(dir + "//file"))
        //        {
        //            Directory.CreateDirectory(dir + "//file");  //创建文件所在目录
        //        }
        //        string name = DateTime.Now.ToLongDateString() + ".doc";
        //        object filename = dir + "//file//" + name;  //文件保存路径
        //        //创建Word文档
        //        Microsoft.Office.Interop.Word.Application WordApp = new Microsoft.Office.Interop.Word.Application();
        //        Microsoft.Office.Interop.Word.Document wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        //        /**/
        //        ////添加页眉方法一：
        //        //WordApp.ActiveWindow.View.Type = WdViewType.wdOutlineView;
        //        //WordApp.ActiveWindow.View.SeekView = WdSeekView.wdSeekPrimaryHeader;
        //        //WordApp.ActiveWindow.ActivePane.Selection.InsertAfter( "无锡全真通科技有限公司" );//页眉内容
        //        //添加页眉方法二：
        //        if (WordApp.ActiveWindow.ActivePane.View.Type == Microsoft.Office.Interop.Word.WdViewType.wdNormalView || WordApp.ActiveWindow.ActivePane.View.Type == Microsoft.Office.Interop.Word.WdViewType.wdOutlineView)
        //        {
        //            WordApp.ActiveWindow.ActivePane.View.Type = Microsoft.Office.Interop.Word.WdViewType.wdPrintView;
        //        }
        //        WordApp.ActiveWindow.View.SeekView = Microsoft.Office.Interop.Word.WdSeekView.wdSeekCurrentPageHeader;
        //        string sHeader = "页眉内容";
        //        WordApp.Selection.HeaderFooter.LinkToPrevious = false;
        //        WordApp.Selection.HeaderFooter.Range.Text = sHeader;
        //        WordApp.ActiveWindow.View.SeekView = Microsoft.Office.Interop.Word.WdSeekView.wdSeekMainDocument;
        //        //WordApp.Selection.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphRight;//设置右对齐
        //        WordApp.Selection.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphLeft;//设置左对齐  
        //        WordApp.ActiveWindow.View.SeekView = WdSeekView.wdSeekMainDocument;//跳出页眉设置
        //        WordApp.Selection.ParagraphFormat.LineSpacing = 15f;//设置文档的行间距
        //        //移动焦点并换行
        //        object count = 14;
        //        object WdLine = Microsoft.Office.Interop.Word.WdUnits.wdLine;//换一行;
        //        WordApp.Selection.MoveDown(ref WdLine, ref count, ref oMissing);//移动焦点
        //        WordApp.Selection.TypeParagraph();//插入段落
        //        //文档中创建表格
        //        Microsoft.Office.Interop.Word.Table newTable = wordDoc.Tables.Add(WordApp.Selection.Range, 12, 3, ref oMissing, ref oMissing);
        //        //设置表格样式
        //        newTable.Borders.OutsideLineStyle = Microsoft.Office.Interop.Word.WdLineStyle.wdLineStyleThickThinLargeGap;
        //        newTable.Borders.InsideLineStyle = Microsoft.Office.Interop.Word.WdLineStyle.wdLineStyleSingle;
        //        newTable.Columns[1].Width = 100f;
        //        newTable.Columns[2].Width = 220f;
        //        newTable.Columns[3].Width = 105f;
        //        //填充表格内容
        //        newTable.Cell(1, 1).Range.Text = "产品详细信息表";
        //        newTable.Cell(1, 1).Range.Bold = 2;//设置单元格中字体为粗体
        //        //合并单元格
        //        newTable.Cell(1, 1).Merge(newTable.Cell(1, 3));
        //        WordApp.Selection.Cells.VerticalAlignment = Microsoft.Office.Interop.Word.WdCellVerticalAlignment.wdCellAlignVerticalCenter;//垂直居中
        //        WordApp.Selection.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphCenter;//水平居中
        //        //填充表格内容
        //        newTable.Cell(2, 1).Range.Text = "产品基本信息";
        //        newTable.Cell(2, 1).Range.Font.Color = Microsoft.Office.Interop.Word.WdColor.wdColorDarkBlue;//设置单元格内字体颜色
        //        //合并单元格
        //        newTable.Cell(2, 1).Merge(newTable.Cell(2, 3));
        //        WordApp.Selection.Cells.VerticalAlignment = Microsoft.Office.Interop.Word.WdCellVerticalAlignment.wdCellAlignVerticalCenter;
        //        //填充表格内容
        //        newTable.Cell(3, 1).Range.Text = "品牌名称：";
        //        newTable.Cell(3, 2).Range.Text = "BrandName";
        //        //纵向合并单元格
        //        newTable.Cell(3, 3).Select();//选中一行
        //        object moveUnit = Microsoft.Office.Interop.Word.WdUnits.wdLine;
        //        object moveCount = 5;
        //        object moveExtend = Microsoft.Office.Interop.Word.WdMovementType.wdExtend;
        //        WordApp.Selection.MoveDown(ref moveUnit, ref moveCount, ref moveExtend);
        //        WordApp.Selection.Cells.Merge();
        //        //插入图片
        //        if (File.Exists(System.Web.HttpConText.Current.Server.MapPath("images//picture.jpg")))
        //        {
        //            string FileName = System.Web.HttpConText.Current.Server.MapPath("images//picture.jpg");//图片所在路径
        //            object LinkToFile = false;
        //            object SaveWithDocument = true;
        //            object Anchor = wordDoc.Application.Selection.Range;
        //            wordDoc.Application.ActiveDocument.InlineShapes.AddPicture(FileName, ref LinkToFile, ref SaveWithDocument, ref Anchor);
        //            wordDoc.Application.ActiveDocument.InlineShapes[1].Width = 100f;//图片宽度
        //            wordDoc.Application.ActiveDocument.InlineShapes[1].Height = 100f;//图片高度
        //        }
        //        //将图片设置为四周环绕型
        //        Microsoft.Office.Interop.Word.Shape s = wordDoc.Application.ActiveDocument.InlineShapes[1].ConvertToShape();
        //        s.WrapFormat.Type = Microsoft.Office.Interop.Word.WdWrapType.wdWrapSquare;
        //        newTable.Cell(12, 1).Range.Text = "产品特殊属性";
        //        newTable.Cell(12, 1).Merge(newTable.Cell(12, 3));
        //        //在表格中增加行
        //        wordDoc.Content.Tables[1].Rows.Add(ref oMissing);
        //        wordDoc.Paragraphs.Last.Range.Text = "文档创建时间：" + DateTime.Now.ToString();//“落款”
        //        wordDoc.Paragraphs.Last.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphRight;
        //        //文件保存
        //        wordDoc.SaveAs(ref filename, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        //        wordDoc.Close(ref oMissing, ref oMissing, ref oMissing);
        //        WordApp.Quit(ref oMissing, ref oMissing, ref oMissing);
        //        message = name + "文档生成成功";
        //    }
        //    catch
        //    {
        //        message = "文件导出异常！";
        //    }
        //    return message;
        //}
        //#endregion
        #region 创建并打开一个空的word文档进行编辑
        /**/
        /// <summary>
        /// 创建并打开一个空的word文档进行编辑
        /// </summary>
        public static void OpenNewWordFileToEdit()
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        }
        #endregion
        //#region 创建word文档
        ///**/
        ///// <summary>
        ///// 创建word文档
        ///// </summary>
        ///// <returns></returns>
        //public static string createWord()
        //{
        //    Microsoft.Office.Interop.Word.Application WordApp = new Microsoft.Office.Interop.Word.Application();
        //    Microsoft.Office.Interop.Word.Document wordDoc;
        //    string strContent = "";
        //    object strFileName = System.Web.HttpConText.Current.Server.MapPath("test.doc ");
        //    if (System.IO.File.Exists((string)strFileName))
        //        System.IO.File.Delete((string)strFileName);
        //    Object oMissing = System.Reflection.Missing.Value;
        //    wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        //    #region   将数据库中读取得数据写入到word文件中
        //    strContent = "你好/n/n/r ";
        //    wordDoc.Paragraphs.Last.Range.Text = strContent;
        //    strContent = "这是测试程序 ";
        //    wordDoc.Paragraphs.Last.Range.Text = strContent;
        //    #endregion
        //    //将wordDoc文档对象的内容保存为DOC文档  
        //    wordDoc.SaveAs(ref strFileName, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref   oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        //    //关闭wordDoc文档对象  
        //    wordDoc.Close(ref oMissing, ref oMissing, ref oMissing);
        //    //关闭WordApp组件对象  
        //    WordApp.Quit(ref oMissing, ref oMissing, ref oMissing);
        //    string message = strFileName + "/r/n " + "创建成功 ";
        //    return message;
        //}
        //#endregion
        #region 把Word文档装化为Html文件
        /**/
        /// <summary>
        /// 把Word文档装化为Html文件
        /// </summary>
        /// <param name="strFileName">要转换的Word文档</param>
        public static void WordToHtml(string strFileName)
        {
            string saveFileName = strFileName + DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss") + ".html";
            WordToHtml(strFileName, saveFileName);
        }
        /**/
        /// <summary>
        /// 把Word文档装化为Html文件
        /// </summary>
        /// <param name="strFileName">要转换的Word文档</param>
        /// <param name="strSaveFileName">要生成的具体的Html页面</param>
        public static void WordToHtml(string strFileName, string strSaveFileName)
        {
            Microsoft.Office.Interop.Word._Application WordApp;
            Microsoft.Office.Interop.Word._Document wordDoc;
            Object oMissing = System.Reflection.Missing.Value;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            object fileName = strFileName;

            wordDoc = WordApp.Documents.Open(ref fileName,
               ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing,
               ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing,
               ref oMissing, ref oMissing, ref oMissing, ref oMissing, ref oMissing);
            Type wordType = WordApp.GetType();
            // 打开文件
            Type docsType = WordApp.Documents.GetType();
            // 转换格式，另存为
            Type docType = wordDoc.GetType();
            object saveFileName = strSaveFileName;
            docType.InvokeMember("SaveAs", System.Reflection.BindingFlags.InvokeMethod, null, wordDoc, new object[] { saveFileName, Microsoft.Office.Interop.Word.WdSaveFormat.wdFormatHTML });
            #region 其它格式：
            /**/
            /**/
            /**/
            ///wdFormatHTML
            ///wdFormatDocument
            ///wdFormatDOSText
            ///wdFormatDOSTextLineBreaks
            ///wdFormatEncodedText
            ///wdFormatRTF
            ///wdFormatTemplate
            ///wdFormatText
            ///wdFormatTextLineBreaks
            ///wdFormatUnicodeText
            //--------------------------------------------------------------------------            //            docType.InvokeMember( "SaveAs", System.Reflection.BindingFlags.InvokeMethod,
            //                null, wordDoc, new object[]{saveFileName, Word.WdSaveFormat.wdFormatHTML} );
            // 退出 Word
            //wordType.InvokeMember( "Quit", System.Reflection.BindingFlags.InvokeMethod,
            //    null, WordApp, null );
            #endregion
            wordDoc.Close(ref oMissing, ref oMissing, ref oMissing);
            WordApp.Quit(ref oMissing, ref oMissing, ref oMissing);
        }
        #endregion
        #region 导入模板
        /**/
        /// <summary>
        /// 导入模板
        /// </summary>
        /// <param name="filePath">模板文档路径</param>
        public static void ImportTemplate(string filePath)
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            object fileName = filePath;
            wordDoc = WordApp.Documents.Add(ref fileName, ref oMissing, ref oMissing, ref oMissing);
        }


        #endregion
        #region word中添加新表
        /**/
        /// <summary>
        /// word中添加新表
        /// </summary>
        public static void AddTable()
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
            object start = 0;
            object end = 0;
            Microsoft.Office.Interop.Word.Range tableLocation = wordDoc.Range(ref start, ref end);
            wordDoc.Tables.Add(tableLocation, 3, 4, ref oMissing, ref oMissing);//3行4列的表
        }
        #endregion
        #region 在表中插入新行
        /**/
        /// <summary>
        /// 在表中插入新的1行
        /// </summary>
        public static void AddRow()
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
            object start = 0;
            object end = 0;
            Microsoft.Office.Interop.Word.Range tableLocation = wordDoc.Range(ref start, ref end);
            wordDoc.Tables.Add(tableLocation, 3, 4, ref oMissing, ref oMissing);
            Microsoft.Office.Interop.Word.Table newTable = wordDoc.Tables[1];
            object beforeRow = newTable.Rows[1];
            newTable.Rows.Add(ref beforeRow);
        }
        #endregion
        #region 分离单元格
        /**/
        /// <summary>
        /// 合并单元格
        /// </summary>
        public static void CombinationCell()
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
            object start = 0;
            object end = 0;
            Microsoft.Office.Interop.Word.Range tableLocation = wordDoc.Range(ref start, ref end);
            wordDoc.Tables.Add(tableLocation, 3, 4, ref oMissing, ref oMissing);
            Microsoft.Office.Interop.Word.Table newTable = wordDoc.Tables[1];
            object beforeRow = newTable.Rows[1];
            newTable.Rows.Add(ref beforeRow);
            Microsoft.Office.Interop.Word.Cell Cell = newTable.Cell(2, 1);//2行1列合并2行2列为一起
            Cell.Merge(newTable.Cell(2, 2));
            //Cell.Merge( newTable.Cell( 1, 3 ) );
        }
        #endregion
        #region 分离单元格
        /**/
        /// <summary>
        /// 分离单元格
        /// </summary>
        public static void SeparateCell()
        {
            object oMissing = System.Reflection.Missing.Value;
            Microsoft.Office.Interop.Word.Application WordApp;
            Microsoft.Office.Interop.Word.Document wordDoc;
            WordApp = new Microsoft.Office.Interop.Word.Application();
            WordApp.Visible = true;
            wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
            object start = 0;
            object end = 0;
            Microsoft.Office.Interop.Word.Range tableLocation = wordDoc.Range(ref start, ref end);
            wordDoc.Tables.Add(tableLocation, 3, 4, ref oMissing, ref oMissing);
            Microsoft.Office.Interop.Word.Table newTable = wordDoc.Tables[1];
            object beforeRow = newTable.Rows[1];
            newTable.Rows.Add(ref beforeRow);
            Microsoft.Office.Interop.Word.Cell Cell = newTable.Cell(1, 1);
            Cell.Merge(newTable.Cell(1, 2));
            object Rownum = 2;
            object Columnnum = 2;
            Cell.Split(ref Rownum, ref  Columnnum);
        }
        #endregion
        //#region 通过段落控制插入Insert a paragraph at the beginning of the document.
        ///**/
        ///// <summary>
        ///// 通过段落控制插入Insert a paragraph at the beginning of the document.
        ///// </summary>
        //public static void Insert()
        //{
        //    object oMissing = System.Reflection.Missing.Value;
        //    //object oEndOfDoc = "//endofdoc"; /**//* /endofdoc is a predefined bookmark */
        //    //Start Word and create a new document.
        //    Microsoft.Office.Interop.Word.Application WordApp;
        //    Microsoft.Office.Interop.Word.Document wordDoc;
        //    WordApp = new Microsoft.Office.Interop.Word.Application();
        //    WordApp.Visible = true;
        //    wordDoc = WordApp.Documents.Add(ref oMissing, ref oMissing, ref oMissing, ref oMissing);
        //    //Insert a paragraph at the beginning of the document.
        //    Microsoft.Office.Interop.Word.Paragraph oPara1;
        //    oPara1 = wordDoc.Content.Paragraphs.Add(ref oMissing);
        //    oPara1.Range.Text = "Heading 1";
        //    oPara1.Range.Font.Bold = 1;
        //    oPara1.Format.SpaceAfter = 24;    //24 pt spacing after paragraph.
        //    oPara1.Range.InsertParagraphAfter();
        //}
        //#endregion
        //#region word文档设置及获取光标位置
        ///**/
        ///// <summary>
        ///// word文档设置及获取光标位置
        ///// </summary>
        //public static void WordSet()
        //{
        //    object oMissing = System.Reflection.Missing.Value;
        //    Microsoft.Office.Interop.Word.Application WordApp;
        //    Microsoft.Office.Interop.Word.Document wordDoc;
        //    WordApp = new Microsoft.Office.Interop.Word.Application();
        //    #region 文档格式设置
        //    WordApp.ActiveDocument.PageSetup.LineNumbering.Active = 0;//行编号
        //    WordApp.ActiveDocument.PageSetup.Orientation = Microsoft.Office.Interop.Word.WdOrientation.wdOrientPortrait;//页面方向
        //    WordApp.ActiveDocument.PageSetup.TopMargin = WordApp.CentimetersToPoints(float.Parse("2.54"));//上页边距
        //    WordApp.ActiveDocument.PageSetup.BottomMargin = WordApp.CentimetersToPoints(float.Parse("2.54"));//下页边距
        //    WordApp.ActiveDocument.PageSetup.LeftMargin = WordApp.CentimetersToPoints(float.Parse("3.17"));//左页边距
        //    WordApp.ActiveDocument.PageSetup.RightMargin = WordApp.CentimetersToPoints(float.Parse("3.17"));//右页边距
        //    WordApp.ActiveDocument.PageSetup.Gutter = WordApp.CentimetersToPoints(float.Parse("0"));//装订线位置
        //    WordApp.ActiveDocument.PageSetup.HeaderDistance = WordApp.CentimetersToPoints(float.Parse("1.5"));//页眉
        //    WordApp.ActiveDocument.PageSetup.FooterDistance = WordApp.CentimetersToPoints(float.Parse("1.75"));//页脚
        //    WordApp.ActiveDocument.PageSetup.PageWidth = WordApp.CentimetersToPoints(float.Parse("21"));//纸张宽度
        //    WordApp.ActiveDocument.PageSetup.PageHeight = WordApp.CentimetersToPoints(float.Parse("29.7"));//纸张高度
        //    WordApp.ActiveDocument.PageSetup.FirstPageTray = Microsoft.Office.Interop.Word.WdPaperTray.wdPrinterDefaultBin;//纸张来源
        //    WordApp.ActiveDocument.PageSetup.OtherPagesTray = Microsoft.Office.Interop.Word.WdPaperTray.wdPrinterDefaultBin;//纸张来源
        //    WordApp.ActiveDocument.PageSetup.SectionStart = Microsoft.Office.Interop.Word.WdSectionStart.wdSectionNewPage;//节的起始位置：新建页
        //    WordApp.ActiveDocument.PageSetup.OddAndEvenPagesHeaderFooter = 0;//页眉页脚-奇偶页不同
        //    WordApp.ActiveDocument.PageSetup.DifferentFirstPageHeaderFooter = 0;//页眉页脚-首页不同
        //    WordApp.ActiveDocument.PageSetup.VerticalAlignment = Microsoft.Office.Interop.Word.WdVerticalAlignment.wdAlignVerticalTop;//页面垂直对齐方式
        //    WordApp.ActiveDocument.PageSetup.SuppressEndnotes = 0;//不隐藏尾注
        //    WordApp.ActiveDocument.PageSetup.MirrorMargins = 0;//不设置首页的内外边距
        //    WordApp.ActiveDocument.PageSetup.TwoPagesOnOne = false;//不双面打印
        //    WordApp.ActiveDocument.PageSetup.BookFoldPrinting = false;//不设置手动双面正面打印
        //    WordApp.ActiveDocument.PageSetup.BookFoldRevPrinting = false;//不设置手动双面背面打印
        //    WordApp.ActiveDocument.PageSetup.BookFoldPrintingSheets = 1;//打印默认份数
        //    WordApp.ActiveDocument.PageSetup.GutterPos = Microsoft.Office.Interop.Word.WdGutterStyle.wdGutterPosLeft;//装订线位于左侧
        //    WordApp.ActiveDocument.PageSetup.LinesPage = 40;//默认页行数量
        //    WordApp.ActiveDocument.PageSetup.LayoutMode = Microsoft.Office.Interop.Word.WdLayoutMode.wdLayoutModeLineGrid;//版式模式为“只指定行网格”
        //    #endregion
        //    #region 段落格式设定
        //    WordApp.Selection.ParagraphFormat.LeftIndent = WordApp.CentimetersToPoints(float.Parse("0"));//左缩进
        //    WordApp.Selection.ParagraphFormat.RightIndent = WordApp.CentimetersToPoints(float.Parse("0"));//右缩进
        //    WordApp.Selection.ParagraphFormat.SpaceBefore = float.Parse("0");//段前间距
        //    WordApp.Selection.ParagraphFormat.SpaceBeforeAuto = 0;//
        //    WordApp.Selection.ParagraphFormat.SpaceAfter = float.Parse("0");//段后间距
        //    WordApp.Selection.ParagraphFormat.SpaceAfterAuto = 0;//
        //    WordApp.Selection.ParagraphFormat.LineSpacingRule = Microsoft.Office.Interop.Word.WdLineSpacing.wdLineSpaceSingle;//单倍行距
        //    WordApp.Selection.ParagraphFormat.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphJustify;//段落2端对齐
        //    WordApp.Selection.ParagraphFormat.WidowControl = 0;//孤行控制
        //    WordApp.Selection.ParagraphFormat.KeepWithNext = 0;//与下段同页
        //    WordApp.Selection.ParagraphFormat.KeepTogether = 0;//段中不分页
        //    WordApp.Selection.ParagraphFormat.PageBreakBefore = 0;//段前分页
        //    WordApp.Selection.ParagraphFormat.NoLineNumber = 0;//取消行号
        //    WordApp.Selection.ParagraphFormat.Hyphenation = 1;//取消段字
        //    WordApp.Selection.ParagraphFormat.FirstLineIndent = WordApp.CentimetersToPoints(float.Parse("0"));//首行缩进
        //    WordApp.Selection.ParagraphFormat.OutlineLevel = Microsoft.Office.Interop.Word.WdOutlineLevel.wdOutlineLevelBodyText;
        //    WordApp.Selection.ParagraphFormat.CharacterUnitLeftIndent = float.Parse("0");
        //    WordApp.Selection.ParagraphFormat.CharacterUnitRightIndent = float.Parse("0");
        //    WordApp.Selection.ParagraphFormat.CharacterUnitFirstLineIndent = float.Parse("0");
        //    WordApp.Selection.ParagraphFormat.LineUnitBefore = float.Parse("0");
        //    WordApp.Selection.ParagraphFormat.LineUnitAfter = float.Parse("0");
        //    WordApp.Selection.ParagraphFormat.AutoAdjustRightIndent = 1;
        //    WordApp.Selection.ParagraphFormat.DisableLineHeightGrid = 0;
        //    WordApp.Selection.ParagraphFormat.FarEastLineBreakControl = 1;
        //    WordApp.Selection.ParagraphFormat.WordWrap = 1;
        //    WordApp.Selection.ParagraphFormat.HangingPunctuation = 1;
        //    WordApp.Selection.ParagraphFormat.HalfWidthPunctuationOnTopOfLine = 0;
        //    WordApp.Selection.ParagraphFormat.AddSpaceBetweenFarEastAndAlpha = 1;
        //    WordApp.Selection.ParagraphFormat.AddSpaceBetweenFarEastAndDigit = 1;
        //    WordApp.Selection.ParagraphFormat.BaseLineAlignment = Microsoft.Office.Interop.Word.WdBaselineAlignment.wdBaselineAlignAuto;
        //    #endregion
        //    #region 字体格式设定
        //    WordApp.Selection.Font.NameFarEast = "华文中宋";
        //    WordApp.Selection.Font.NameAscii = "Times New Roman";
        //    WordApp.Selection.Font.NameOther = "Times New Roman";
        //    WordApp.Selection.Font.Name = "宋体";
        //    WordApp.Selection.Font.Size = float.Parse("14");
        //    WordApp.Selection.Font.Bold = 0;
        //    WordApp.Selection.Font.Italic = 0;
        //    WordApp.Selection.Font.Underline = Microsoft.Office.Interop.Word.WdUnderline.wdUnderlineNone;
        //    WordApp.Selection.Font.UnderlineColor = Microsoft.Office.Interop.Word.WdColor.wdColorAutomatic;
        //    WordApp.Selection.Font.StrikeThrough = 0;//删除线
        //    WordApp.Selection.Font.DoubleStrikeThrough = 0;//双删除线
        //    WordApp.Selection.Font.Outline = 0;//空心
        //    WordApp.Selection.Font.Emboss = 0;//阳文
        //    WordApp.Selection.Font.Shadow = 0;//阴影
        //    WordApp.Selection.Font.Hidden = 0;//隐藏文字
        //    WordApp.Selection.Font.SmallCaps = 0;//小型大写字母
        //    WordApp.Selection.Font.AllCaps = 0;//全部大写字母
        //    WordApp.Selection.Font.Color = Microsoft.Office.Interop.Word.WdColor.wdColorAutomatic;
        //    WordApp.Selection.Font.Engrave = 0;//阴文
        //    WordApp.Selection.Font.Superscript = 0;//上标
        //    WordApp.Selection.Font.Subscript = 0;//下标
        //    WordApp.Selection.Font.Spacing = float.Parse("0");//字符间距
        //    WordApp.Selection.Font.Scaling = 100;//字符缩放
        //    WordApp.Selection.Font.Position = 0;//位置
        //    WordApp.Selection.Font.Kerning = float.Parse("1");//字体间距调整
        //    WordApp.Selection.Font.Animation = Microsoft.Office.Interop.Word.WdAnimation.wdAnimationNone;//文字效果
        //    WordApp.Selection.Font.DisableCharacterSpaceGrid = false;
        //    WordApp.Selection.Font.EmphasisMark = Microsoft.Office.Interop.Word.WdEmphasisMark.wdEmphasisMarkNone;
        //    #endregion
        //    #region 获取光标位置
        //    /**/
        //    ////get_Information
        //    WordApp.Selection.get_Information(WdInformation.wdActiveEndPageNumber);
        //    //关于行号-页号-列号-位置
        //    //information 属性
        //    //返回有关指定的所选内容或区域的信息。variant 类型，只读。
        //    //expression.information(type)
        //    //expression 必需。该表达式返回一个 Range 或 selection 对象。
        //    //type long 类型，必需。需要返回的信息。可取下列 wdinformation 常量之一：
        //    //wdactiveendadjustedpagenumber 返回页码，在该页中包含指定的所选内容或区域的活动结尾。如果设置了一个起始页码，并对页码进行了手工调整，则返回调整过的页码。
        //    //wdactiveendpagenumber 返回页码，在该页中包含指定的所选内容或区域的活动结尾，页码从文档的开头开始计算而不考虑对页码的任何手工调整。
        //    //wdactiveendsectionnumber 返回节号，在该节中包含了指定的所选内容或区域的活动结尾。
        //    //wdatendofrowmarker 如果指定的所选内容或区域位于表格的行结尾标记处，则本参数返回 true。
        //    //wdcapslock 如果大写字母锁定模式有效，则本参数返回 true。
        //    //wdendofRangecolumnnumber 返回表格列号，在该表格列中包含了指定的所选内容或区域的活动结尾。
        //    //wdendofRangerownumber 返回表格行号，在该表格行包含了指定的所选内容或区域的活动结尾。
        //    //wdfirstcharactercolumnnumber 返回指定的所选内容或区域中第一个字符的位置。如果所选内容或区域是折叠的，则返回所选内容或区域右侧紧接着的字符编号。
        //    //wdfirstcharacterlinenumber 返回所选内容中第一个字符的行号。如果 pagination 属性为 false，或 draft 属性为 true，则返回 - 1。
        //    //wdframeisselected 如果所选内容或区域是一个完整的图文框文本框，则本参数返回 true。
        //    //wdheaderfootertype 返回一个值，该值表明包含了指定的所选内容或区域的页眉或页脚的类型，如下表所示。 值 页眉或页脚的类型
        //    //- 1 无
        //    //0 偶数页页眉
        //    //1 奇数页页眉
        //    //2 偶数页页脚
        //    //3 奇数页页脚
        //    //4 第一个页眉
        //    //5 第一个页脚
        //    //wdhorizontalpositionrelativetopage 返回指定的所选内容或区域的水平位置。该位置是所选内容或区域的左边与页面的左边之间的距离，以磅为单位。如果所选内容或区域不可见，则返回 - 1。
        //    //wdhorizontalpositionrelativetoTextboundary 返回指定的所选内容或区域相对于周围最近的正文边界的左边的水平位置，以磅为单位。如果所选内容或区域没有显示在当前屏幕，则本参数返回 - 1。
        //    //wdinclipboard 有关此常量的详细内容，请参阅 microsoft office 98 macintosh 版的语言参考帮助。
        //    //wdincommentpane 如果指定的所选内容或区域位于批注窗格，则返回 true。
        //    //wdinendnote 如果指定的所选内容或区域位于页面视图的尾注区内，或者位于普通视图的尾注窗格中，则本参数返回 true。
        //    //wdinfootnote 如果指定的所选内容或区域位于页面视图的脚注区内，或者位于普通视图的脚注窗格中，则本参数返回 true。
        //    //wdinfootnoteendnotepane 如果指定的所选内容或区域位于页面视图的脚注或尾注区内，或者位于普通视图的脚注或尾注窗格中，则本参数返回 true。详细内容，请参阅前面的 wdinfootnote 和 wdinendnote 的说明。
        //    //wdinheaderfooter 如果指定的所选内容或区域位于页眉或页脚窗格中，或者位于页面视图的页眉或页脚中，则本参数返回 true。
        //    //wdinmasterdocument 如果指定的所选内容或区域位于主控文档中，则本参数返回 true。
        //    //wdinwordmail 返回一个值，该值表明了所选内容或区域的的位置，如下表所示。值 位置
        //    //0 所选内容或区域不在一条电子邮件消息中。
        //    //1 所选内容或区域位于正在发送的电子邮件中。
        //    //2 所选内容或区域位于正在阅读的电子邮件中。
        //    //wdmaximumnumberofcolumns 返回所选内容或区域中任何行的最大表格列数。
        //    //wdmaximumnumberofrows 返回指定的所选内容或区域中表格的最大行数。
        //    //wdnumberofpagesindocument 返回与所选内容或区域相关联的文档的页数。
        //    //wdnumlock 如果 num lock 有效，则本参数返回 true。
        //    //wdovertype 如果改写模式有效，则本参数返回 true。可用 overtype 属性改变改写模式的状态。
        //    //wdreferenceoftype 返回一个值，该值表明所选内容相对于脚注、尾注或批注引用的位置，如下表所示。 值 描述
        //    //— 1 所选内容或区域包含、但不只限定于脚注、尾注或批注引用中。
        //    //0 所选内容或区域不在脚注、尾注或批注引用之前。
        //    //1 所选内容或区域位于脚注引用之前。
        //    //2 所选内容或区域位于尾注引用之前。
        //    //3 所选内容或区域位于批注引用之前。
        //    //wdrevisionmarking 如果修订功能处于活动状态，则本参数返回 true。
        //    //wdselectionmode 返回一个值，该值表明当前的选定模式，如下表所示。 值 选定模式
        //    //0 常规选定
        //    //1 扩展选定
        //    //2 列选定
        //    //wdstartofRangecolumnnumber 返回所选内容或区域的起点所在的表格的列号。
        //    //wdstartofRangerownumber 返回所选内容或区域的起点所在的表格的行号。
        //    //wdverticalpositionrelativetopage 返回所选内容或区域的垂直位置，即所选内容的上边与页面的上边之间的距离，以磅为单位。如果所选内容或区域没有显示在屏幕上，则本参数返回 - 1。
        //    //wdverticalpositionrelativetoTextboundary 返回所选内容或区域相对于周围最近的正文边界的上边的垂直位置，以磅为单位。如果所选内容或区域没有显示在屏幕上，则本参数返回 - 1。
        //    //wdwithintable 如果所选内容位于一个表格中，则本参数返回 true。
        //    //wdzoompercentage 返回由 percentage 属性设置的当前的放大百分比。
        //    #endregion
        //    #region 光标移动
        //    //移动光标
        //    //光标下移3行 上移3行
        //    object unit = Microsoft.Office.Interop.Word.WdUnits.wdLine;
        //    object count = 3;
        //    WordApp.Selection.MoveEnd(ref unit, ref count);
        //    WordApp.Selection.MoveUp(ref unit, ref count, ref oMissing);
        //    //Microsoft.Office.Interop.Word.WdUnits说明
        //    //wdCell                  A Cell.
        //    //wdCharacter             A character.
        //    //wdCharacterFormatting   Character formatting.
        //    //wdColumn                A column.
        //    //wdItem                  The selected item.
        //    //wdLine                  A line. //行
        //    //wdParagraph             A paragraph.
        //    //wdParagraphFormatting   Paragraph formatting.
        //    //wdRow                   A row.
        //    //wdScreen                The screen dimensions.
        //    //wdSection               A section.
        //    //wdSentence              A sentence.
        //    //wdStory                 A story.
        //    //wdTable                 A table.
        //    //wdWindow                A window.
        //    //wdWord                  A word.
        //    //录制的vb宏
        //    //     ,移动光标至当前行首
        //    //    Selection.HomeKey unit:=wdLine
        //    //    '移动光标至当前行尾
        //    //    Selection.EndKey unit:=wdLine
        //    //    '选择从光标至当前行首的内容
        //    //    Selection.HomeKey unit:=wdLine, Extend:=wdExtend
        //    //    '选择从光标至当前行尾的内容
        //    //    Selection.EndKey unit:=wdLine, Extend:=wdExtend
        //    //    '选择当前行
        //    //    Selection.HomeKey unit:=wdLine
        //    //    Selection.EndKey unit:=wdLine, Extend:=wdExtend
        //    //    '移动光标至文档开始
        //    //    Selection.HomeKey unit:=wdStory
        //    //    '移动光标至文档结尾
        //    //    Selection.EndKey unit:=wdStory
        //    //    '选择从光标至文档开始的内容
        //    //    Selection.HomeKey unit:=wdStory, Extend:=wdExtend
        //    //    '选择从光标至文档结尾的内容
        //    //    Selection.EndKey unit:=wdStory, Extend:=wdExtend
        //    //    '选择文档全部内容（从WholeStory可猜出Story应是当前文档的意思）
        //    //    Selection.WholeStory
        //    //    '移动光标至当前段落的开始
        //    //    Selection.MoveUp unit:=wdParagraph
        //    //    '移动光标至当前段落的结尾
        //    //    Selection.MoveDown unit:=wdParagraph
        //    //    '选择从光标至当前段落开始的内容
        //    //    Selection.MoveUp unit:=wdParagraph, Extend:=wdExtend
        //    //    '选择从光标至当前段落结尾的内容
        //    //    Selection.MoveDown unit:=wdParagraph, Extend:=wdExtend
        //    //    '选择光标所在段落的内容
        //    //    Selection.MoveUp unit:=wdParagraph
        //    //    Selection.MoveDown unit:=wdParagraph, Extend:=wdExtend
        //    //    '显示选择区的开始与结束的位置，注意：文档第1个字符的位置是0
        //    //    MsgBox ("第" & Selection.Start & "个字符至第" & Selection.End & "个字符")
        //    //    '删除当前行
        //    //    Selection.HomeKey unit:=wdLine
        //    //    Selection.EndKey unit:=wdLine, Extend:=wdExtend
        //    //    Selection.Delete
        //    //    '删除当前段落
        //    //    Selection.MoveUp unit:=wdParagraph
        //    //    Selection.MoveDown unit:=wdParagraph, Extend:=wdExtend
        //    //    Selection.Delete
        //    //表格的光标移动
        //    //光标到当前光标所在表格的地单元格
        //    WordApp.Selection.Tables[1].Cell(1, 1).Select();
        //    //unit对象定义
        //    object unith = Microsoft.Office.Interop.Word.WdUnits.wdRow;//表格行方式
        //    object extend = Microsoft.Office.Interop.Word.WdMovementType.wdExtend;/**//**//**////extend对光标移动区域进行扩展选择
        //    object unitu = Microsoft.Office.Interop.Word.WdUnits.wdLine;//文档行方式,可以看成表格一行.不过和wdRow有区别
        //    object unitp = Microsoft.Office.Interop.Word.WdUnits.wdParagraph;//段落方式,对于表格可以选择到表格行后的换车符,对于跨行合并的行选择,我能找到的最简单方式
        //    //object count = 1;//光标移动量
        //    #endregion
        //}
        //#endregion
        //#region 读取Word表格中某个单元格的数据。其中的参数分别为文件名（包括路径），行号，列号。
        ///**/
        ///// <summary>
        ///// 读取Word表格中某个单元格的数据。其中的参数分别为文件名（包括路径），行号，列号。
        ///// </summary>
        ///// <param name="fileName">word文档</param>
        ///// <param name="rowIndex">行</param>
        ///// <param name="colIndex">列</param>
        ///// <returns>返回数据</returns>
        //public static string ReadWord_tableContentByCell(string fileName, int rowIndex, int colIndex)
        //{
        //    Microsoft.Office.Interop.Word.Application cls = null;
        //    Microsoft.Office.Interop.Word.Documents doc = null;
        //    Microsoft.Office.Interop.Word.Tables table = null;
        //    object Missing = Missing.Value;
        //    object path = fileName;
        //    cls = new Microsoft.Office.Interop.Word.Application();
        //    try
        //    {
        //        doc = cls.Documents.Open
        //          (ref path, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing);
        //        table = doc.Tables[1];
        //        string Text = table.Cell(rowIndex, colIndex).Range.Text.ToString();
        //        Text = Text.Substring(0, Text.Length - 2);　　//去除尾部的mark
        //        return Text;
        //    }
        //    catch (Exception ex)
        //    {
        //        return ex.Message;
        //    }
        //    finally
        //    {
        //        if (doc != null)
        //            doc.Close(ref Missing, ref Missing, ref Missing);
        //        cls.Quit(ref Missing, ref Missing, ref Missing);
        //    }
        //}
        //#endregion

        //#region 修改word表格中指定单元格的数据
        ///**/
        ///// <summary>
        ///// 修改word表格中指定单元格的数据
        ///// </summary>
        ///// <param name="fileName">word文档包括路径</param>
        ///// <param name="rowIndex">行</param>
        ///// <param name="colIndex">列</param>
        ///// <param name="content"></param>
        ///// <returns></returns>
        //public static bool UpdateWordTableByCell(string fileName, int rowIndex, int colIndex, string content)
        //{
        //    Application cls = null;
        //    Document doc = null;
        //    Table table = null;
        //    object Missing = Missing.Value;
        //    object path = fileName;
        //    cls = new Application();
        //    try
        //    {
        //        doc = cls.Documents.Open
        //            (ref path, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing,
        //          ref Missing, ref Missing, ref Missing, ref Missing);
        //        table = doc.Tables[1];
        //        //doc.Range( ref 0, ref 0 ).InsertParagraphAfter();//插入回车
        //        table.Cell(rowIndex, colIndex).Range.InsertParagraphAfter();//.Text = content;
        //        return true;
        //    }
        //    catch
        //    {
        //        return false;
        //    }
        //    finally
        //    {
        //        if (doc != null)
        //        {
        //            doc.Close(ref Missing, ref Missing, ref Missing);
        //            cls.Quit(ref Missing, ref Missing, ref Missing);
        //        }
        //    }
        //}
        //#endregion

        #region 清除word进程
        /**/
        /// <summary>
        /// 清除word进程
        /// </summary>
        public static void KillWordProcess()
        {
            System.Diagnostics.Process[] myPs;
            myPs = System.Diagnostics.Process.GetProcesses();
            foreach (System.Diagnostics.Process p in myPs)
            {
                if (p.Id != 0)
                {
                    string myS = "WINWORD.EXE" + p.ProcessName + "  ID:" + p.Id.ToString();
                    try
                    {
                        if (p.Modules != null)
                            if (p.Modules.Count > 0)
                            {
                                System.Diagnostics.ProcessModule pm = p.Modules[0];
                                myS += "/n Modules[0].FileName:" + pm.FileName;
                                myS += "/n Modules[0].ModuleName:" + pm.ModuleName;
                                myS += "/n Modules[0].FileVersionInfo:/n" + pm.FileVersionInfo.ToString();
                                if (pm.ModuleName.ToLower() == "winword.exe")
                                    p.Kill();
                            }
                    }
                    catch
                    { }
                    finally
                    {

                    }
                }
            }
        }
        #endregion

        #region 清除excel进程
        /**/
        /// <summary>
        /// 清除excel进程
        /// </summary>
        public static void KillExcelProcess()
        {
            System.Diagnostics.Process[] myPs;
            myPs = System.Diagnostics.Process.GetProcesses();
            foreach (System.Diagnostics.Process p in myPs)
            {
                if (p.Id != 0)
                {
                    string myS = "Excel.EXE" + p.ProcessName + "  ID:" + p.Id.ToString();
                    try
                    {
                        if (p.Modules != null)
                            if (p.Modules.Count > 0)
                            {
                                System.Diagnostics.ProcessModule pm = p.Modules[0];
                                myS += "/n Modules[0].FileName:" + pm.FileName;
                                myS += "/n Modules[0].ModuleName:" + pm.ModuleName;
                                myS += "/n Modules[0].FileVersionInfo:/n" + pm.FileVersionInfo.ToString();
                                if (pm.ModuleName.ToLower() == "excel.exe")
                                    p.Kill();
                            }
                    }
                    catch
                    { }
                    finally
                    {

                    }
                }
            }
        }
        #endregion

        //#region 网页内容或导入word或excel
        ///**/
        ///// <summary>
        ///// 网页内容保存或导出为word或excel
        ///// </summary>
        ///// <param name="url">网页地址</param>
        ///// <param name="num">0为导出word,1为导出excel</param>
        //public static void SaveOrOutData(string url, int num)//导出数据的函数0为word,1为Excel
        //{
        //    WebRequest req = WebRequest.Create(url);
        //    WebResponse resp = req.GetResponse();
        //    StreamReader sr = new StreamReader(resp.GetResponseStream(), System.Text.Encoding.UTF8);
        //    string x = sr.ReadToEnd();
        //    System.Web.HttpConText.Current.Response.Clear();
        //    System.Web.HttpConText.Current.Response.ContentEncoding = System.Text.Encoding.GetEncoding("gb2312");
        //    string fName = DateTime.Now.ToString("yyyy-MM-dd-ss");
        //    if (num == 0)
        //    {
        //        fName = HttpUtility.UrlEncode(fName, System.Text.Encoding.GetEncoding("gb2312")) + ".doc";
        //        System.Web.HttpConText.Current.Response.ContentType = "Application/ms-word";
        //    }
        //    else
        //    {
        //        fName = HttpUtility.UrlEncode(fName, System.Text.Encoding.GetEncoding("gb2312")) + ".xls";
        //        System.Web.HttpConText.Current.Response.ContentType = "Application nd.xls";
        //    }
        //    System.Web.HttpConText.Current.Response.AddHeader("content-disposition", "attachment;filename=" + fName);
        //    System.Web.HttpConText.Current.Response.Write(getBodyContent(x));//获取table标签
        //    System.Web.HttpConText.Current.Response.Flush();
        //    System.Web.HttpConText.Current.Response.End();
        //}
        ///**/
        ///// <summary>
        ///// 获取网页table标签的内容
        ///// </summary>
        ///// <param name="input">html代码</param>
        ///// <returns></returns>
        //private static string getBodyContent(string input)
        //{
        //    string pattern = @"<table.*?</table>";
        //    Regex reg = new Regex(pattern, RegexOptions.Singleline | RegexOptions.Compiled | RegexOptions.IgnoreCase);
        //    Match mc = reg.Match(input);
        //    string bodyContent = "";
        //    if (mc.Success)
        //    {
        //        bodyContent = mc.Value;
        //    }
        //    return bodyContent;
        //}
        //#endregion

        #region 判断系统是否装excel
        /**/
        /// <summary>
        /// 判断系统是否装excel
        /// </summary>
        /// <returns></returns>
        public static bool IsInstallExcel()
        {
            RegistryKey machineKey = Registry.LocalMachine;
            if (IsInstallExcelByVersion("12.0", machineKey))
            {
                return true;
            }
            if (IsInstallExcelByVersion("11.0", machineKey))
            {
                return true;
            }
            return false;
        }
        /**/
        /// <summary>
        /// 判断系统是否装某版本的excel
        /// </summary>
        /// <param name="strVersion">版本号</param>
        /// <param name="machineKey"></param>
        /// <returns></returns>
        private static bool IsInstallExcelByVersion(string strVersion, RegistryKey machineKey)
        {
            try
            {
                RegistryKey installKey = machineKey.OpenSubKey("Software").OpenSubKey("Microsoft").OpenSubKey("Office").OpenSubKey(strVersion).OpenSubKey("Excel").OpenSubKey("InstallRoot");
                if (installKey == null)
                {
                    return false;
                }
                return true;
            }
            catch
            {
                return false;
            }
        }
        #endregion

        #region 判断系统是否装word
        /**/
        /// <summary>
        /// 判断系统是否装word
        /// </summary>
        /// <returns></returns>
        public static bool IsInstallWord()
        {
            RegistryKey machineKey = Registry.LocalMachine;
            if (IsInstallExcelByVersion("12.0", machineKey))
            {
                return true;
            }
            if (IsInstallExcelByVersion("11.0", machineKey))
            {
                return true;
            }
            return false;
        }
        /**/
        /// <summary>
        /// 判断系统是否装某版本的word
        /// </summary>
        /// <param name="strVersion">版本号</param>
        /// <param name="machineKey"></param>
        /// <returns></returns>
        private static bool IsInstallWordByVersion(string strVersion, RegistryKey machineKey)
        {
            try
            {
                RegistryKey installKey = machineKey.OpenSubKey("Software").OpenSubKey("Microsoft").OpenSubKey("Office").OpenSubKey(strVersion).OpenSubKey("Word").OpenSubKey("InstallRoot");
                if (installKey == null)
                {
                    return false;
                }
                return true;
            }
            catch
            {
                return false;
            }
        }
        #endregion      
    }       // end of MSWordTools Class

}   // end of NameSpace

