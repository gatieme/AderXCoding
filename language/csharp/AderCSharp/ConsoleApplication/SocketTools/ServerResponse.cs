using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SignPressServer.SignTools
{
    public enum ServerResponse
    {
        LOGIN_SUCCESS,          //  登录成功响应
        LOGIN_FAILED,           //  登录失败响应

        QUIT_SUCCESS,           //  退出请求
        QUIT_FAILED,           //  退出请求


        // 用户文件操作
        DOWNLOAD_HDJCONTRACT_SUCCESS,   //  下载会签单的信息
        DOWNLOAD_HDJCONTRACT_FAILED,   //  下载会签单的信息

        UPLOAD_SIGN_PIC_SUCCESS,        //  上传签字图片
        UPLOAD_SIGN_PIC_FAILED,        //  上传签字图片


        /// <summary>
        /// ==部门操作==
        /// 增加部门  INSERT_DEPARTMENT_REQUEST
        /// 删除部门  DELETE_DEPARTMENT_REQUEST
        /// 修改部门  MODIFY_DEPARTMENT_REQUEST
        /// 查询部门  QUERY_DEPARTMENT_REQUEST
        /// </summary>
        INSERT_DEPARTMENT_SUCCESS,
        INSERT_DEPARTMENT_FAILED,

        INSERT_SDEPARTMENT_SUCCESS,
        INSERT_SDEPARTMENT_FAILED,

        DELETE_DEPARTMENT_SUCCESS,
        DELETE_DEPARTMENT_FAILED,
        DELETE_DEPARTMENT_EXIST_EMPLOYEE,       // 删除一个已经有员工的部门信息

        
        MODIFY_DEPARTMENT_SUCCESS,
        MODIFY_DEPARTMENT_EXIST_NAME,           //  修改的部门名称与其他部门的名称重复
        MODIFY_DEPARTMENT_EXIST_SHORTCALL,      //  修改的部门简称与其他部门的简称重复
        MODIFY_DEPARTMENT_FAILED,

        QUERY_DEPARTMENT_SUCCESS,
        QUERY_DEPARTMENT_FAILED,

        QUERY_SDEPARTMENT_SUCCESS,
        QUERY_SDEPARTMENT_FAILED,

        /// <summary>
        /// ==员工操作==
        /// 增加员工  INSERT_EMPLOYEE_REQUEST
        /// 删除员工  DELETE_EMPLOYEE_REQUEST
        /// 修改员工  MODIFY_EMPLOYEE_REQUEST
        /// 查询员工  QUERY_ERMPLOYEE_REQUEST
        /// </summary>
        INSERT_EMPLOYEE_SUCCESS,        /// </summary>
        INSERT_EMPLOYEE_FAILED,
        INSERT_EMPLOYEE_EXIST,                 /// 插入用户时用户已经村催



        DELETE_EMPLOYEE_SUCCESS,
        DELETE_EMPLOYEE_FAILED,
        DELETE_EMPLOYEE_EXIST_CONTRACT,     //  待删除的员工存在会签单信息无法删除
        DELETE_EMPLOYEE_EXIST_CONTEMP,      //  待删除的员工在某个会签模版中，无法删除
        
        MODIFY_EMPLOYEE_SUCCESS,
        MODIFY_EMPLOYEE_FAILED,
        
        QUERY_EMPLOYEE_SUCCESS,
        QUERY_EMPLOYEE_FAILED,

        MODIFY_EMP_PWD_SUCCESS,
        MODIFY_EMP_PWD_FAILED,
        /// <summary>
        /// ==会签单模版操作==
        /// 增加会签单模版  INSERT_CONTRACT_TEMPLATE_REQUEST
        /// 删除会签单模版  DELETE_CONTRACT_TEMPLATE_REQUEST
        /// 修改会签单模版  MODIFY_CONTRACT_TEMPLATE_REQUEST
        /// 查询会签单模版  QUERY_CONTRACT_TEMPLATE_REQUEST
        /// 获取会签单模版  GET_CONTRACT_TEMPLATE_REQUEST
        /// </summary>
        INSERT_CONTRACT_TEMPLATE_SUCCESS,
        INSERT_CONTRACT_TEMPLATE_FAILED,

        DELETE_CONTRACT_TEMPLATE_SUCCESS,
        DELETE_CONTRACT_TEMPLATE_FAILED,
        DELETE_CONTRACT_TEMPLATE_EXIST_CONTRACT,        //  待删除的会签单模版已经有单子无法删除 
        
        MODIFY_CONTRACT_TEMPLATE_SUCCESS,
        MODIFY_CONTRACT_TEMPLATE_FAILED,
        
        QUERY_CONTRACT_TEMPLATE_SUCCESS,
        QUERY_CONTRACT_TEMPLATE_FAILED,

        GET_CONTRACT_TEMPLATE_SUCCESS,
        GET_CONTRACT_TEMPLATE_FAILED,


        SEARCH_AGREE_HDJCONTRACT_SUCCESS,
        SEARCH_AGREE_HDJCONTRACT_FAILED,

        QUERY_AGREE_UNDOWN_SUCCESS,                //  查询已通过的但是未下载的成功
        QUERY_AGREE_UNDOWN_FAILED,                 //  查询已通过但是未下载的失败

        /// <summary>
        /// ==航道局会签单操作==
        /// 增加会签单模版  INSERT_HDJCONTRACT_REQUEST
        /// 删除会签单模版  DELETE_HDJCONTRACT_REQUEST
        /// 修改会签单模版  MODIFY_HDJCONTRACT_REQUEST
        /// 查询会签单模版  QUERY_HDJCONTRACT_REQUEST
        /// </summary>
        INSERT_HDJCONTRACT_SUCCESS,
        INSERT_HDJCONTRACT_FAILED,
        INSERT_HDJCONTRACT_EXIST,


        DELETE_HDJCONTRACT_SUCCESS,
        DELETE_HDJCONTRACT_FAILED,
        
        MODIFY_HDJCONTRACT_SUCCESS,
        MODIFY_HDJCONTRACT_FAILED,

        QUERY_HDJCONTRACT_SUCCESS,
        QUERY_HDJCONTRACT_FAILED,


        SEARCH_SIGNED_HDJCONTRACT_SUCCESS,
        SEARCH_SIGNED_HDJCONTRACT_FAILED,



        GET_HDJCONTRACT_SUCCESS,
        GET_HDJCONTRACT_FAILED,
        GET_HDJCONTRACT_WITH_WORKLOAD_SUCCESS,
        GET_HDJCONTRACT_WITH_WORKLOAD_FAILED,
        /// <summary>
        /// 提交人查询会签单状态操作
        /// </summary>
        QUERY_SIGN_PEND_SUCCESS,
        QUERY_SIGN_PEND_FAILED,

        QUERY_SIGN_AGREE_SUCCESS,
        QUERY_SIGN_AGREE_FAILED,

        QUERY_SIGN_REFUSE_SUCCESS,
        QUERY_SIGN_REFUSE_FAILED,

        /// <summary>
        /// 签字人查询会签单状态操作
        /// </summary>
        QUERY_UNSIGN_CONTRACT_SUCCESS,
        QUERY_UNSIGN_CONTRACT_FAILED,

        QUERY_SIGNED_CONTRACT_SUCCESS,
        QUERY_SIGNED_CONTRACT_FAILED,

        INSERT_SIGN_DETAIL_SUCCESS,
        INSERT_SIGN_DETAIL_FAILED,

        QUERY_SIGN_DETAIL_SUCCESS,
        QUERY_SIGN_DETAIL_FAILED,

        QUERY_SIGN_DETAIL_CON_SUCCESS,
        QUERY_SIGN_DETAIL_CON_FAILED,


        //  手机上考虑数据流量的问题
        QUERY_SIGNED_CONTRACT_TOP_SUCCESS,
        QUERY_SIGNED_CONTRACT_TOP_FAILED,


        QUERY_SDEPARTMENT_CATEGORY_SUCCESS,
        QUERY_SDEPARTMENT_CATEGORY_FAILED,
        
        QUERY_SDEP_CON_CATEGORY_SUCCESS,
        QUERY_SDEP_CON_CATEGORY_FAILED,
        /// <summary>
        /// 2015-11-2
        /// </summary>
        MODIFY_SDEPARTMENT_SUCCESS,
        MODIFY_SDEPARTMENT_FAILED,

        /// <summary>
        /// 2015-11-6
        /// </summary>
        INSERT_ITEM_SUCCESS,        //  插入任务工作量信息
        INSERT_ITEM_FAILED,        //  插入任务工作量信息
        DELETE_ITEM_SUCCESS,        //  删除任务工作量信息
        DELETE_ITEM_FAILED,        //  删除任务工作量信息
        MODIFY_ITEM_SUCCESS,        //  修改任务工作量信息
        MODIFY_ITEM_FAILED,        //  修改任务工作量信息

        INSERT_PROJECT_SUCCESS,
        INSERT_PROJECT_FAILED,
        DELETE_PROJECT_SUCCESS,
        DELETE_PROJECT_FAILED,
        MODIFY_PROJECT_SUCCESS,
        MODIFY_PROJECT_FAILED,

        QUERY_CATEGORY_PROJECT_SUCCESS,
        QUERY_CATEGORY_PROJECT_FAILED,

        QUERY_PROJECT_ITEM_SUCCESS,             /// 查询当前项目类别下的所有工作量集合
        QUERY_PROJECT_ITEM_FAILED,              /// 查询当前项目类别下的所有工作量集合 
        QUERY_PROJECT_ITEM_BY_NAME_SUCCESS,                                  /// 
        QUERY_PROJECT_ITEM_BY_NAME_FAILED,                                  /// 
        
        
        QUERY_CONTRACT_WORKLOAD_SUCCESS,            /// 查询当前会签单的所有工作量集合  
        QUERY_CONTRACT_WORKLOAD_FAILED,            /// 查询当前会签单的所有工作量集合  


        //  统计信息
        GET_CATEGORY_YEAR_CONTRACT_COUNT_SUCCESS,       // 获取当年已经签署的CATEGORY的会签单数目
        GET_CATEGORY_YEAR_CONTRACT_COUNT_FAILED,        // 获取当年已经签署的CATEGORY的会签单数目

        GET_DEP_CATE_YEAR_CON_COUNT_SUCCESS,        // [2015/12/17]编号最后两位的数目是当年部门department本年度year分类category下的会签单数目
        GET_DEP_CATE_YEAR_CON_COUNT_FAILED,        // [2015/12/17]编号最后两位的数目是当年部门department本年度year分类category下的会签单数目

        INSERT_WORKLOAD_SUCCESS,                ///  插入工作量信息
        INSERT_WORKLOAD_FAILED,                ///  插入工作量信息
                                               ///  
        DELETE_WORKLOAD_SUCCESS,                ///  删除工作量信息
        DELETE_WORKLOAD_FAILED,                ///  删除工作量信息
                                               ///  
        MODIFY_WORKLOAD_SUCCESS,                ///  修改工作量信息
        MODIFY_WORKLOAD_FAILED,                ///  修改工作量信息
                                               ///  
        QUERY_WORKLOAD_SUCCESS,                ///  修改工作量信息
        QUERY_WORKLOAD_FAILED,                ///  修改工作量信息
                                     
        ///  用户获取当前部门department当前工程的总申请额度  
        STATISTIC_DEP_YEAR_PRO_SUCCESS,
        STATISTIC_DEP_YEAR_PRO_FAILED,
    }
}
