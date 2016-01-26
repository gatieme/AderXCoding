using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Microsoft.Office.Core;

using MSExcel = Microsoft.Office.Interop.Excel;
using System.IO;
using System.Reflection;






namespace SignPressServer.SignTools
{
    public class MSExcelTools  : MSOfficeTools
    {


        public static void Test()
        {
            //  创建一个excel应用 
            MSExcel._Application app = new MSExcel.Application();
            
            //  打开一个excel文档
            MSExcel.Workbooks wbks = app.Workbooks;
            MSExcel._Workbook _wbk = wbks.Add(DEFAULT_CONTEMP_PATH + "statistic.xls");
            
            //  获取到excel中的一个sheet
            MSExcel.Sheets shs = _wbk.Sheets;
            MSExcel._Worksheet _wsh = (MSExcel._Worksheet)shs.get_Item(1);

            //Object Missing = System.Reflection.Missing.Value;


            String strValue = ((MSExcel.Range)_wsh.Cells[2, 1]).Text;
            
            Console.WriteLine(strValue);

            //  屏蔽掉系统跳出的Alert
            app.AlertBeforeOverwriting = false;

            //保存到指定目录
//            _wbk.SaveAs("./1.xls", Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlNoChange, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);
            _wbk.SaveAs("./1.xls", Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlNoChange, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);
        }

        static List<String> BigNum = new List<String>{
                               "零", "一", "二", "三", "四", "五", 
                               "六", "七", "八", "九", "十",
                               "十一", "十二", "十三", "十四", "十五",
                               "十六", "十七", "十八", "十九", "二十",

                           };
        


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
                    string myS = "EXCEL.EXE" + p.ProcessName + "  ID:" + p.Id.ToString();
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
                                {
                                    Console.WriteLine("发现进程" + myS);
                                    p.Kill();
                                }
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


        #region  会签单STATISTIC统计功能
      
  
        #region 统计年份year类别categoryId的会签单的所有统计信息
        public static string StatisticYearCategory(int year, int categoryId)
        {

            //////////////////////////////////////////////////////////////
            /// excel初始化
            //////////////////////////////////////////////////////////////
            //  创建一个excel应用 
            MSExcel._Application app = new MSExcel.Application();

            //  打开一个excel文档
            MSExcel.Workbooks wbks = app.Workbooks;
            MSExcel._Workbook _wbk = wbks.Add(DEFAULT_CONTEMP_PATH + "statistic.xls");

            //  获取到excel中的一个sheet
            MSExcel.Sheets shs = _wbk.Sheets;
            MSExcel._Worksheet sheet = (MSExcel._Worksheet)shs.get_Item(categoryId);


            //////////////////////////////////////////////////////////////
            /// 数据库统计信息
            //////////////////////////////////////////////////////////////
            //  首先获取到当前的会签单的信息
            ContractCategory category = DALContractIdCategory.GetCategory(categoryId);
            Console.WriteLine("统计能申请当前Id = {0}, Category = {1}信息", category.Id, category.Category);


            string sheetName = year.ToString() + category.Category + "统计表";
            ////////////////////////// 本机路径含有非法字符，
            //string filePath = MSExcelTools.DEFAULT_STATISTIC_PATH + sheetName;
            string filePath = MSExcelTools.DEFAULT_STATISTIC_FILE(year, categoryId);
            ////////////////////////////////////////////////////////////
            if (File.Exists((String)filePath) == true)     // 首先检测文件是否存在
            {
                File.Delete((String)filePath);
            }
            Console.WriteLine("待保存的excel名 sheetName = " + sheetName);
            sheet.Cells[1, 1] = sheetName;
            //  首先获取数据库中可以申请本会签单类别的所有部门的列表
            List<Department> departments = DALContractIdCategory.QueryCategoryDepartment(categoryId);
            //Console.WriteLine(JsonConvert.SerializeObject(departments));

            //  其次查询当前Category类别的所有Project信息和item信息
            List<ContractProject> projects = DALContractProject.QueryCategoryProject(categoryId);
            //Console.WriteLine("统计出当前Category = {1}的所有Project+Item信息", category.CategoryShortCall);
            //Console.WriteLine(JsonConvert.SerializeObject(projects));

            int startRow = 4, row;
            int startCol = 5, col;
            int projectCount = 1, itemCount = 1;
            foreach (Department department in departments)     ///  循环填写每个部门的信息
            {
                //  每次填写部门的信息时

                Console.WriteLine("[{0}, {1}]]开始填写部门{2}的统计信息", startRow, startCol, department.Name);
                row = startRow;
                col = startCol;
                projectCount = 1;

                //  可以填写表头, 填写部门的名称
                sheet.Cells[2, col] = department.Name;

                //Console.WriteLine("当前部门Id = {0}, Name = {1}", department.Id, department.Name);
                foreach (ContractProject project in projects)       //  循环每个项目的信息
                {
                    // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                    sheet.Cells[row, 1] = BigNum[projectCount];
                    sheet.Cells[row, 2] = project.Project;

                    ///  统计当前部门Department当年Year项目Project的统计信息
                    //Console.WriteLine(JsonConvert.SerializeObject(project));
                    ContractWorkload projectWorkload = DALContractStatistic.StatisDepartmentYearProjectWorkLoad(department.ShortCall, year, project.Id);
                    //Console.WriteLine("当前工程Id = {0}, Project = {1}, Works = {2}, Expense = {3}", project.Id, project.Project, projectWorkload.Work, projectWorkload.Expense);

                    Console.WriteLine("====[{0}  Project]--{1}-{2}-{3} [Work = {4}, Expense = {5}]====",
                        projectCount, department.ShortCall, year, project.Project, projectWorkload.Work, projectWorkload.Expense);

                    sheet.Cells[row, col] = projectWorkload.Work;              //  存储工作量信息
                    sheet.Cells[row, col + 1] = projectWorkload.Expense;       //  存储花费的信息
                    Console.WriteLine("[{0}, {1}], [{2}, {3}]", row, col, row, col + 1);

                    row++;                          //  填写完Project总的统计信息后，增加一行，开始填写分条Item的信息
                    itemCount = 1;
                    //  获取当前项目的工作量集合
                    List<ContractItem> items = DALContractItem.QueryProjectItem(project.Id);
                    foreach (ContractItem item in items)
                    {
                        // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                        sheet.Cells[row, 1] = itemCount;
                        sheet.Cells[row, 2] = item.Item;
                        //Console.WriteLine(JsonConvert.SerializeObject(item));

                        //  统计当前部门Department当年Year工作量为item的统计信息
                        ContractWorkload itemWorkload = DALContractStatistic.StatisDepartmentYearItemWorkLoad(department.ShortCall, year, item.Id);
                        //Console.WriteLine("当前的工作量Id = {0}, Item = {1}, Works = {2}, Expenses = {3}", item.Id, item.Item, itemWorkload.Work, itemWorkload.Expense);
                        Console.WriteLine("========[{0}.{1}]--{2}-{3}-{4}-{5}  [Work = {6}, Expense = {7}]",
                            projectCount, itemCount, department.ShortCall, year, project.Project, item.Item, itemWorkload.Work, itemWorkload.Expense);
                        //string str = sheet.Rows[row][col].ToString();
                        //sheet.Cells[row, col] = str;  
                        sheet.Cells[row, col] = itemWorkload.Work;              //  存储工作量信息
                        sheet.Cells[row, col + 1] = itemWorkload.Expense;       //  存储花费的信息
                        Console.WriteLine("[{0}, {1}], [{2}, {3}]", row, col, row, col + 1);

                        row++;              //  每次一个填完一个item后，行增加一行填写下一行
                        itemCount++;
                    }

                    projectCount++;

                }

                //  填完了单个部门的所有信息后
                startRow += 0;  //  回复到开始的那一行
                startCol += 2;  //  初始化的列增加两个单元格，跳到下一个部门的列中
            }

            //string filePath = DEFAULT_STATISTIC_PATH + sheetName;

            Console.WriteLine("保存的完整路径{0}", filePath);
            _wbk.SaveAs(filePath, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlNoChange, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

            _wbk.Close(null, null, null);
            wbks.Close();
            app.Quit();

            //释放掉多余的excel进程
            System.Runtime.InteropServices.Marshal.ReleaseComObject(app);
            app = null;

            return filePath;
        }
        #endregion


        #region 统计年份year类别categoryId的会签单的所有统计信息, 其中部门区分一级部门和二级部门
        /// <summary>
        /// A  --  首先是一二级部门怎么处理的
        //  首先获取数据库中可以申请本会签单类别的所有部门的列表[包括一二级部门的信息]
        ///  注意此处使用如下两个函数都可以
        ///  QueryCategoryHSDepartment获取到了所有的部门信息，包括一二级部门，二级部门可以通过IsSubDepartment过滤
        ///  QueryCategoryHigherDepartment则返回的部门中不包括二级部门
        ///  List<HSDepartment> departments = DALContractIdCategory.QueryCategoryHSDepartment(categoryId);
        ///
        /// B  --  怎么增加统计所有部门的总统计和以及计划任务
        /// 我们的处理方法是，将这两个统计对象处理成两个部门
        /// 一个id =  0，标识要统计所有部门的实际费用综合
        /// 一个id = -1，标识要统计本年度的计划任务总和
        /// </summary>
        /// <param name="year"></param>
        /// <param name="categoryId"></param>
        /// <returns></returns>
        public static string StatisticHSYearCategory(int year, int categoryId)
        {

            //////////////////////////////////////////////////////////////
            /// excel初始化
            //////////////////////////////////////////////////////////////
            //  创建一个excel应用 
            MSExcel._Application app = new MSExcel.Application();

            //  打开一个excel文档
            MSExcel.Workbooks wbks = app.Workbooks;
            MSExcel._Workbook _wbk = wbks.Add(DEFAULT_CONTEMP_PATH + "statistic.xls");

            //  获取到excel中的一个sheet
            MSExcel.Sheets shs = _wbk.Sheets;
            MSExcel._Worksheet sheet = (MSExcel._Worksheet)shs.get_Item(1);
            

            //////////////////////////////////////////////////////////////
            /// 数据库统计信息
            //////////////////////////////////////////////////////////////
            //  首先获取到当前的会签单的信息
            ContractCategory category = DALContractIdCategory.GetCategory(categoryId);
            Console.WriteLine("统计能申请当前Id = {0}, Category = {1}信息", category.Id, category.Category);


            ////////////////////////// 本机路径含有非法字符，
            string sheetName = year.ToString() + category.Category + "费用分配表";
            
            string filePath = MSExcelTools.DEFAULT_STATISTIC_FILE(year, categoryId);
            sheet.Name = sheetName;
            ////////////////////////////////////////////////////////////
            
            if (File.Exists((String)filePath) == true)     // 首先检测文件是否存在
            {
                File.Delete((String)filePath);
            }
            Console.WriteLine("待保存的excel名 sheetName = " + sheetName);
            sheet.Cells[1, 1] = sheetName;
            
            //  首先获取数据库中可以申请本会签单类别的所有部门的列表[包括一二级部门的信息]
            ///  注意此处使用如下两个函数都可以
            ///  QueryCategoryHSDepartment获取到了所有的部门信息，包括一二级部门，二级部门可以通过IsSubDepartment过滤
            ///  QueryCategoryHigherDepartment则返回的部门中不包括二级部门
            //List<HSDepartment> departments = DALContractIdCategory.QueryCategoryHSDepartment(categoryId);
            List<HSDepartment> departments = DALContractIdCategory.QueryCategoryHigherDepartment(categoryId);
            departments.Add(HSDepartment.CreateStatisTotalHSDepartment());      ///  添加统计所有的信息
            departments.Add(HSDepartment.CreateStatisRegularHSDepartment());    ///  添加计划额度信息
            
            //  其次查询当前Category类别的所有Project信息和item信息
            List<ContractProject> projects = DALContractProject.QueryCategoryProject(categoryId);
            
            int startRow = 4, row;
            int startCol = 3, col;
            int projectCount = 1, itemCount = 1;
            
            //#region   循环统计每个部门的信息
            foreach (HSDepartment department in departments)     ///  循环填写每个部门的信息
            {
                /* 使用QueryCategoryHSDepartment请注意将下面注释打开
                 * if (department.IsSubDepartment() == true)
                {
                    continue;
                }*/
               
                //Console.WriteLine("[{0}, {1}]]开始填写部门{2}的统计信息", startRow, startCol, department.Name);
                row = startRow;
                col = startCol;
                projectCount = 1;

                //  可以填写表头, 填写部门的名称
                sheet.Cells[2, col] = department.Name;

               // Console.WriteLine("当前部门Id = {0}, Name = {1}", department.Id, department.Name);
                foreach (ContractProject project in projects)       //  循环每个项目的信息
                {
                    // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                    sheet.Cells[row, 1] = BigNum[projectCount];
                    sheet.Cells[row, 2] = project.Project;

                    ///  统计当前部门Department当年Year项目Project的统计信息
                    ContractWorkload projectWorkload = DALContractStatistic.StatisHSDepartmentYearProjectWorkLoad(department, year, project);

                 //   Console.WriteLine("====[{0}  Project]--{1}-{2}-{3} [Work = {4}, Expense = {5}]====",
                   //     projectCount, department.ShortCall, year, project.Project, projectWorkload.Work, projectWorkload.Expense);

                    sheet.Cells[row, col] = projectWorkload.Work;              //  存储工作量信息
                    sheet.Cells[row, col + 1] = projectWorkload.Expense;       //  存储花费的信息
                    //Console.WriteLine("[{0}, {1}], [{2}, {3}]", row, col, row, col + 1);

                    row++;                          //  填写完Project总的统计信息后，增加一行，开始填写分条Item的信息
                    itemCount = 1;
                    //  获取当前项目的工作量集合
                    List<ContractItem> items = DALContractItem.QueryProjectItem(project.Id);
                    foreach (ContractItem item in items)
                    {
                        // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                        sheet.Cells[row, 1] = itemCount;
                        sheet.Cells[row, 2] = item.Item;
                        
                        //  统计当前部门Department当年Year工作量为item的统计信息
                        ContractWorkload itemWorkload = DALContractStatistic.StatisHSDepartmentYearItemWorkLoad(department, year, item);
                      //  Console.WriteLine("========[{0}.{1}]--{2}-{3}-{4}-{5}  [Work = {6}, Expense = {7}]",
                        //    projectCount, itemCount, department.ShortCall, year, project.Project, item.Item, itemWorkload.Work, itemWorkload.Expense);

                        sheet.Cells[row, col] = itemWorkload.Work;              //  存储工作量信息
                        sheet.Cells[row, col + 1] = itemWorkload.Expense;       //  存储花费的信息
                        //Console.WriteLine("[{0}, {1}], [{2}, {3}]", row, col, row, col + 1);

                        row++;              //  每次一个填完一个item后，行增加一行填写下一行
                        itemCount++;
                    }

                    projectCount++;

                }

                //  填完了单个部门的所有信息后
                startRow += 0;  //  回复到开始的那一行
                startCol += 2;  //  初始化的列增加两个单元格，跳到下一个部门的列中
            }
            //#endregion
            
            //   
            Console.WriteLine("保存的完整路径{0}", filePath);
            _wbk.SaveAs(filePath, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlNoChange, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

            _wbk.Close(null, null, null);
            wbks.Close();
            app.Quit();

            //  释放掉多余的excel进程
            System.Runtime.InteropServices.Marshal.ReleaseComObject(app);
            app = null;

            return filePath;
        }
        #endregion


        #endregion


        #region 会签单计划额度的所有操作

        #region  根据contemp下的计划模版创建计划额度表模版, 供用户下载
        /// <summary>
        /// 用户提交年度计划额度的时候需要一张excel表格作为模版，
        /// 这个模版中写好了所有的project + item的细则
        /// 服务器在每次用户新增加了一个item时候，就会重新生成一个模版
        /// 然后用户在提交当年的计划额度的时候就可以下载该模版，填写完整后进行提交
        /// 
        /// 这种方法有个缺陷，就是同时提交多个计划表不太好实现
        /// 每个类别的category都有一个会签单模版（由同一份空白模版生成）
        /// 
        /// </summary>
        /// <param name="categoryId"></param>
        /// <returns></returns>
        public static String CreateRegularloadTemplateFile(int categoryId)
        {
            ////////////////////////// 本机路径含有非法字符，
            int sheetIndex = 1;
            //string tempFilePath = "E:\\regularload.xls"; //MSExcelTools.DEFAULT_REGULARLOAD_TEMPLATE_FILE;
            //string saveFilePath = "E:\\" + categoryId.ToString() + "regularloadtemplate.xls";

            string tempFilePath = MSExcelTools.DEFAULT_REGULARLOAD_CONTEMPLATE_FILE;
            string saveFilePath = MSExcelTools.DEFAULT_REGULARLOAD_TEMPLATE_FILE(categoryId);
            
            
            //////////////////////////////////////////////////////////////
            /// excel初始化
            //////////////////////////////////////////////////////////////
            //  创建一个excel应用 
            MSExcel._Application app = new MSExcel.Application();

            //  打开一个excel文档
            MSExcel.Workbooks wbks = app.Workbooks;
            MSExcel._Workbook _wbk = wbks.Add(tempFilePath);  //  用系统的模版生成现在的模版

            //  获取到excel中的一个sheet
            MSExcel.Sheets shs = _wbk.Sheets;
            MSExcel._Worksheet sheet = (MSExcel._Worksheet)shs.get_Item(sheetIndex);

            //////////////////////////////////////////////////////////////
            /// 数据库统计信息
            //////////////////////////////////////////////////////////////
            //  首先获取到当前的会签单的信息
            ContractCategory category = DALContractIdCategory.GetCategory(categoryId);
            Console.WriteLine("统计能申请当前Id = {0}, Category = {1}信息", category.Id, category.Category);


            //string filePath = "E:\\" + sheetName + DEFAULT_EXCEL_FILENAME_EXTENSION;
            ////////////////////////////////////////////////////////////
            if (File.Exists((String)saveFilePath) == true)     // 首先检测文件是否存在
            {
                File.Delete((String)saveFilePath);
            } 
            Console.WriteLine("待保存的excel名 sheetName = " + saveFilePath);
            sheet.Name = category.Category + "计划任务分配表";
            sheet.Cells[1, 1] = category.Category + "计划任务分配表";

            //  查询当前Category类别的所有Project信息和item信息
            List<ContractProject> projects = DALContractProject.QueryCategoryProject(categoryId);
            //Console.WriteLine("统计出当前Category = {1}的所有Project+Item信息", category.CategoryShortCall);
            //Console.WriteLine(JsonConvert.SerializeObject(projects));
            
            int startRow = 4, row;
            int startCol = 3, col;
            int projectCount = 1, itemCount = 1;

   
            row = startRow;
            col = startCol;
            projectCount = 1;

            // 填写表头
            foreach (ContractProject project in projects)       //  循环每个项目的信息
            {
                // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                sheet.Cells[row, 1] = BigNum[projectCount];
                sheet.Cells[row, 2] = project.Id;
                sheet.Cells[row, 3] = project.Project;

                row++;                          //  填写完Project总的统计信息后，增加一行，开始填写分条Item的信息
                itemCount = 1;
                //  获取当前项目的工作量集合
                List<ContractItem> items = DALContractItem.QueryProjectItem(project.Id);
                foreach (ContractItem item in items)
                {
                    // 填写每行的表头，此处有BUG，每次循环均重复写了，其实只需要第依次填写即可
                    sheet.Cells[row, 1] = itemCount;
                    sheet.Cells[row, 2] = item.Id;
                    sheet.Cells[row, 3] = item.Item;

                    row++;              //  每次一个填完一个item后，行增加一行填写下一行
                    itemCount++;
                }
                projectCount++;


            }
            sheet.Cells[row, 1] = "END";
            sheet.Cells[row, 2] = "END";
            sheet.Cells[row, 3] = "END";
            sheet.Cells[row, 4] = "END";
            sheet.Cells[row, 5] = "END";


            Console.WriteLine("保存的完整路径{0}", saveFilePath);
            _wbk.SaveAs(saveFilePath, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlNoChange, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

            _wbk.Close(null, null, null);

            wbks.Close();
            app.Quit();

            //释放掉多余的excel进程
            System.Runtime.InteropServices.Marshal.ReleaseComObject(app);
            app = null;

            return saveFilePath;
            
        }
        #endregion

        #region  用户提交计划额度表的后, 在数据库中进行插入操作
        /// <summary>
        /// 将用户上传的filePath中的年度计划额度信息
        /// 
        /// </summary>
        /// <param name="year"></param>
        /// <param name="categoryId"></param>
        /// <param name="filePath"></param>
        public static bool UploadRegularLoad(int year, int categoryId/*, String filePath*/)
        {
            try
            {
                string filePath = DEFAULT_REGULARLOAD_FILE(year, categoryId);
                Console.WriteLine("计划额度表文件路径{0}", filePath);
                //////////////////////////////////////////////////////////////
                /// excel初始化
                //////////////////////////////////////////////////////////////
                //  创建一个excel应用 
                MSExcel._Application app = new MSExcel.Application();

                //  打开一个excel文档
                MSExcel.Workbooks wbks = app.Workbooks;
                MSExcel._Workbook _wbk = wbks.Add(filePath);

                //  获取到excel中的一个sheet
                MSExcel.Sheets shs = _wbk.Sheets;
                MSExcel._Worksheet sheet = (MSExcel._Worksheet)shs.get_Item(1);


                int startRow = 4;        // 第4行开始才是正文数据
                //int regularidcol = 2;
                //int regularnamecol = 3;
                //int regularworkcol = 4;
                //int regularexpensecol = 5;
                Console.WriteLine("行数{0}, 列数{1}", sheet.UsedRange.Rows.Count, sheet.UsedRange.Columns.Count);

                //int maxColumns = sheet.Range["4"].End[MSExcel.XlDirection.xlToLeft].Column;
                int maxRows = sheet.Range["A65535"].End[MSExcel.XlDirection.xlUp].Row;
                
                int projectId = 1, itemId = 1;
                string projectName, itemName;
                double work, expense;
                
                //Console.WriteLine("行数{0}, 列数{1}", maxColumns, maxRows);

                /////////////////////////////////
                //
                //  首先检查数据有没有问题
                //
                /////////////////////////////////
                List<ContractProject> projects = new List<ContractProject>();
                List<ContractItem> items = new List<ContractItem>();

                List<ContractRegularload> regularloads = new List<ContractRegularload>();
                for (int row = startRow; row < maxRows; row++)
                {

                    if (sheet.Cells[row, 1].Text == "END")
                    {
                        Console.WriteLine("[{0}, {1}] = {2}遇见终止符号", row, 1, sheet.Cells[row, 1].Text);
                        break;
                    }
                    //Console.WriteLine(BigNum.Find(new Predicate<String>(sheet.Cells[row, 1].Text)));
                    //Console.WriteLine(BigNum.Where(o => o == sheet.Cells[row, 1].Text).ToList().Count);
                    
                    //  使用lam
                    if (BigNum.Where(num => num == sheet.Cells[row, 1].Text).ToList().Count > 0)
                    {
                        projectId = int.Parse(sheet.Cells[row, 2].Text);
                        projectName = sheet.Cells[row, 3].Text;
                        work = double.Parse(sheet.Cells[row, 4].Text);
                        expense = double.Parse(sheet.Cells[row, 5].Text);


                        ContractProject project = new ContractProject()
                        {
                            Id = projectId,
                            Project = projectName,
                        };
                        projects.Add(project);
                        //Console.WriteLine("工程" + project.Id + ", " + project.Project);
                    }
                    else
                    {
                        itemId = int.Parse(sheet.Cells[row, 2].Text);
                        itemName = sheet.Cells[row, 3].Text;
                        work = double.Parse(sheet.Cells[row, 4].Text);
                        expense = double.Parse(sheet.Cells[row, 5].Text);
             
                        // 获取到item
                        ContractItem item = new ContractItem()
                        {
                            Id = itemId,
                            ProjectId = projectId,
                            Item = itemName,
                        };
                    
                        items.Add(item);
                    
                        ContractRegularload regularload = new ContractRegularload
                        {
                            Id     = year.ToString() + "-" + categoryId.ToString() + "-" + itemId.ToString(),
                            Year   = year,
                            ItemId = itemId,
                            Work   = work,
                            Expense = expense,
                        };
                        regularloads.Add(regularload);
                        //Console.WriteLine("ITEM" + item.Id + ", " + item.Item);

                    }

                }

                
                ////////////////////////////////////////////////
                // 在将数据插入之前检查数据是否合法
                //////////////////////////////////////////////////
                Console.WriteLine(projects.Count);
                foreach (ContractProject project in projects)
                {
                    if (DALContractProject.CheckIntegrity(project) == false)
                    {
                        //break;
                        return false;
                    }
                }

                Console.WriteLine(items.Count);
                foreach (ContractItem item in items)
                {
                    if (DALContractItem.CheckIntegrity(item) == false)
                    {
                        //break;
                        return false;
                    }
                }

                ////////////////////////////////////////////////
                // 将数据插入到数据库中
                //////////////////////////////////////////////////
                Console.WriteLine(regularloads.Count);
                foreach (ContractRegularload regularload in regularloads)
                {
                    DALContractRegularoload.InsertRegularload(regularload);      
                }

                return true;
            }
            catch (Exception)
            {
                throw;
            }
            finally
            {

            }
        }
        #endregion

        #endregion


    }
}
