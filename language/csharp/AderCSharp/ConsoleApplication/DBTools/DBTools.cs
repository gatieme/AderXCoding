using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using MySql.Data.MySqlClient;

 
namespace SignPressServer.SignTools
{
    public class DBTools
    {

        public static readonly string M_str_sqlcon = "server=localhost;port = 3333;user id=root;password=root;database=signature";
             
        #region  建立MySql数据库连接
        /// <summary>
        /// 建立数据库连接.
        /// </summary>
        /// <returns>返回MySqlConnection对象</returns>
        public static MySqlConnection GetMySqlConnection()
        {
            //String M_str_sqlcon = "server=localhost;user id=root;password=root;database=signature"; //根据自己的设置
            MySqlConnection myCon = new MySqlConnection(M_str_sqlcon);
            return myCon;
        }
        #endregion

        #region  执行MySqlCommand命令
        /// <summary>
        /// 执行MySqlCommand
        /// </summary>
        /// <param name="M_str_sqlstr">SQL语句</param>
        public void getmysqlcom(String M_str_sqlstr)
        {
            MySqlConnection mysqlcon = GetMySqlConnection();///  先获取一个MySql的
            try
            {
                mysqlcon.Open();
                MySqlCommand mysqlcom = new MySqlCommand(M_str_sqlstr, mysqlcon);
                mysqlcom.ExecuteNonQuery();
                mysqlcom.Dispose();
                mysqlcon.Close();
                mysqlcon.Dispose();
            }
            catch
            {
                mysqlcon.Close();
            }
        }
        #endregion

        #region  创建MySqlDataReader对象
        /// <summary>
        /// 创建一个MySqlDataReader对象
        /// </summary>
        /// <param name="M_str_sqlstr">SQL语句</param>
        /// <returns>返回MySqlDataReader对象</returns>
        public MySqlDataReader getmysqlread(String M_str_sqlstr)
        {
            MySqlConnection mysqlcon = GetMySqlConnection();
            MySqlCommand mysqlcom = new MySqlCommand(M_str_sqlstr, mysqlcon);
            try
            {
                mysqlcon.Open();
                //MySqlDataReader mysqlread = mysqlcom.ExecuteReader(CommandBehavior.CloseConnection);
                MySqlDataReader mysqlread = mysqlcom.ExecuteReader();
                return mysqlread;
        
            }
            catch
            {
                mysqlcon.Close();
                return null;
            }
   
            /*if(mysqlread.Read())   // 一次读一条记录
            {
                if(mysqlread["Name"].ToString()==textBox1.Text&&mysqlread["PassWord"].ToString()==textBox2.Text)
                {
                    frmJxkh myJxkh = new frmJxkh();
                    myJxkh.Show();
                }
            }*/
        }
        #endregion
    }
}
