/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : Sort.h                                                       *
*  Description: 排序函数模版                                                *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : 数据结构与算法（C++）版书上源码                            *
******************************************************************************
**/
#include <iostream>
#include <algorithm>
#include <functional>
#include "LinkList.h"
#include <cmath>
#ifndef SORT_H_INCLUDE
#define SORT_H_INCLUDE

///
#define SIZE 10
#define STEP false
#define NOMAL true
typedef bool OutWay;


//#ifdef SWAP_FUN

/// 交换函数
template <class ElemType>
void Write(const ElemType &elem);
//#endif

/******************************************************插入排序BEGIN******************************************************/
//#ifdef INSERT_SORT_FUN
//#error "You must define INSERT_SORT_FUN macro before include this file"
//#else

/// 简单插入排序
// 函数名称：void StraightInsertSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：简单插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void StraightInsertSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);

// 函数名称：void ShellSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：希尔插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void ShellSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);

//#endif
/******************************************************插入排序_END_******************************************************/



/******************************************************交换排序BEGIN******************************************************/
//#ifdef SWAP_SORT_FUN
//#error "You must define SWAP_SORT_FUN macro before include this file"
//#else
/// 冒泡排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);

// 函数名称：void BubbleUpSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法上升排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleUpSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);

// 函数名称：void BubbleDownSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法下沉排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleDownSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);

/// 快速排序算法
// 函数名称：void QuickSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：简单插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void QuickSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), OutWay outWay);


template <class ElemType>
int Partition(ElemType elem[], int low, int high);
template <class ElemType>
void Quick_Sort_Help(ElemType *elem, int low, int high);
template <class ElemType>
void Quick_Sort(ElemType *elem, int n);
//#endif
/******************************************************交换排序_END_******************************************************/


/******************************************************选择排序BEGIN******************************************************/
//#ifdef SWAP_SORT_FUN
//#error "You must define SWAP_SORT_FUN macro before include this file"
//#else
/// 简单选择排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template <class ElemType>
void SelectSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), void (*Visit)(const ElemType &), OutWay outWa = NOMAL);

/// 堆排序排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template <class ElemType>
void SiftAdjust(ElemType *elem, int low, int high, bool (*Comp)(const void *, const void *));
template<class ElemType>
void HeapSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay = NOMAL);
//#endif
//#endif
/******************************************************选择排序_END_******************************************************/


/******************************************************归并排序BEGIN******************************************************/
//#ifdef MEEGING_SORT_FUN
//#error "You must define MERGING_SORT_FUN macro before include this file"
//#else
/// 归并排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void MergeSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), OutWay outWay);
// 函数名称：MergeSort
// 函数功能：利用辅助数组空间tempElem对Elem数组low到high位置的数据进行排序
template <class ElemType>
void MergeSort(ElemType *elem, ElemType *tempElem, int low, int high, bool (*Comp)(const void *, const void *), OutWay outWay);
// 函数名称：Merge
// 函数功能：将所有有序的自序列[low, mid]和[mid+1, high]归并为新的
template <class ElemType>
void Merge(ElemType *elem, ElemType *tempElem, int low, int mid, int high, bool (*Comp)(const void *, const void *));


/******************************************************归并排序_END_******************************************************/

/******************************************************基数排序BEGIN*****************************************************/

template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[]);


template <class ElemType>
void Colect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[], OutWay outWay);

template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d, OutWay outWay);
/******************************************************基数排序_END_******************************************************/



template <class ElemType>
void Write(const ElemType &elem)
{
    std::cout <<std::setw(4)<<elem;
}




/// 简单插入排序
// 函数名称：void StraightInsertSort(ElemType , int , bool (*Comp)(  ), void (*Visit)(ElemType &), OutWay);
// 函数功能：简单插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void StraightInsertSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    // 排序部分
    int i, j;
    ElemType temp;

    for(i = 1; i < length; i++)      // 循环第1个数据以后的每个数据
    {
        temp = elem[i];         // 保存第i个数据,
        for(j = i - 1; j >= 0 && Comp(&temp, &elem[j]); j--)      // 将比保存的数据都往后移
        {
            elem[j + 1] = elem[j];
        }
        // 循环结束后就在有序的0-i的位置中找到了temp应该插入的位置(j + 1)
        elem[j + 1] = temp;         // 将保存的数据插进来


        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"第" <<i <<"趟排序：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }

}

// 函数名称：void ShellSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：希尔插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void ShellSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    // 排序函数部分
    int incr/*Shell步长*/, i/*控制每趟步长的插入过程*/, j/*循环移动元素*/;
    ElemType temp;          // 一个单位的辅助空间
    for(incr = length / 2; incr >= 1; incr /= 2)          // 控制每个步长的排序
    {   // 第coun趟排序-=>步长为incr
        for(i = incr; i < length; i++)      // 控制每趟步长的插入过程
        {   // 每趟排序的插入过程
            temp = elem[i];
            for(j = i - incr; j >= 0 && Comp(&temp, &elem[j]); j -= incr)     // 寻找插入位置
            {   // 将不满足插入位置要求的元素依次后移
                elem[j + incr] = elem[j];
            }
            elem[j + incr] = temp;      // 将元素插入
        }
            // 输出原始序列
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"当前步长" <<incr <<"：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }
}




/// 冒泡排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    int j/*控制每趟循环*/, i/*控制相邻数据的比较循环*/;
    bool flag = true;           // 排序完成的标志
    // 排序过程
    for(i = 1; i < length; i++)        // 共计进行length-1趟循环
    {
        flag = false;           // 初始默认数据是无序的
        for(j = 0; j < (length - i) && flag == true; j++)   // 每趟循环比较length-1-j次
        {
            if(Comp(&elem[j], &elem[j+1]) == true)    // 如果当前的元素与后一个元素不满足排序规则
            {
                swap(elem[j], elem[j+1]);
                flag = true;                // 仍然需要交换说明, 仍然无序
            }
        }
        // 输出排序过程中的序列信息
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"第" <<i  <<"趟循环：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }
}

// 函数名称：void BubbleUpSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法上升排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleUpSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    int j/*控制每趟循环*/, i/*控制相邻数据的比较循环*/;
    // 排序过程
    for(i = 1; i < length; i++)        // 共计进行length-1趟循环
    {
        for(j = length - i; j > 0; j--)   // 每趟循环比较length-1-j次
        {
            if(Comp(&elem[j-1], &elem[j]) == true)    // 如果当前的元素与后一个元素不满足排序规则
            {
                swap(elem[j], elem[j-1]);
            }

        }
        // 输出排序过程中的序列信息
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"第" <<i  <<"趟循环：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }
}
// 函数名称：void BubbleDownSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法下沉排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void BubbleDownSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay)
{
        // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    int j/*控制每趟循环*/, i/*控制相邻数据的比较循环*/;
    // 排序过程
    for(i = 1; i < length; i++)        // 共计进行length-1趟循环
    {
        for(j = 0; j < (length - i); j++)   // 每趟循环比较length-1-j次
        {
            if(Comp(&elem[j], &elem[j+1]) == true)    // 如果当前的元素与后一个元素不满足排序规则
            {
                swap(elem[j], elem[j+1]);
            }

        }
        // 输出排序过程中的序列信息
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"第" <<i  <<"趟循环：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }
}
/// 快速排序算法
// 函数名称：void QuickSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：简单插入排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template <class ElemType>
void QuickSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), OutWay outWay)
{
    if(length > 1)
    {

        int pivot = 0, j;
        for(j = 1; j < length; j++)        // 循环在区间上进行交换
        {
            if(Comp(elem+j, elem + 0) == true)
            {
                swap(elem[++pivot], elem[j]);
            }
        }
        swap(elem[0], elem[pivot]);

        QuickSort(elem, pivot, Comp, outWay);          // 递归排序左部区间

        QuickSort(elem + pivot + 1, length - pivot - 1, Comp, outWay); // 递归排序右部区间

    }
}



/// 简单选择排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void SelectSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    int i, j, index;
    for(i = 0; i < length - 1; i++)     // 循环每趟排序
    {
        index = i;
        for(j = i + 1; j < length; j++)
        {
            if(Comp(elem + j, elem + index) == true)
            {
                index  = j;     // 找到当前极值元素的下标
            }
        }
        if(index != i)
        {
            swap(elem[i], elem[index]);     // 将极值保存到应该填入的位置
        }
        // 输出原始序列
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"第" <<i <<"趟排序：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
    }
}


/// 堆排序排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template <class ElemType>
void SiftAdjust(ElemType *elem, int low, int high, bool (*Comp)(const void *, const void *))
{
    for(int f = low, i = 2*low+1; i <= high; i = 2*i+1)
    {   // f为不满足条件的父结点, i初始化为其左孩子, 然后递归对其左孩子堆筛选,
        if(i < high && Comp(elem + i, elem + i + 1) == true)
        {       // i指向f左海子和右孩子中较大的那个
            i++;
        }
        if(Comp(elem + f, elem + i) == false)
        {
            break;
        }

        swap(elem[f], elem[i]);

        f = i;          // 保存当前父节点的位置
    }
}

template<class ElemType>
void HeapSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *),  void (*Visit)(const ElemType &), OutWay outWay)
{
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"原始_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    int i;
    for(i = (length-2)/2; i >= 0; i--)      // 首先建立一个堆
    {
        SiftAdjust(elem, i, length - 1, Comp);
    }
    // 输出原始序列
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        std::cout <<"建堆_序列：";
        for(int pos = 0; pos < length; pos++)
        {
            Visit(elem[pos]);             // 打印每个记录信息
        }
        std::cout <<std::endl;
    }
    for(i = length - 1; i > 0; i--)
    {
        swap(elem[0], elem[i]);     // 将堆订的元素和最后一个[i]元组交换
        // 输出原始序列
        if(outWay == STEP)     // 如果系统要求单步输出排序信息
        {
            std::cout <<"排序_序列：";
            for(int pos = 0; pos < length; pos++)
            {
                Visit(elem[pos]);             // 打印每个记录信息
            }
            std::cout <<std::endl;
        }
        SiftAdjust(elem, 0, i-1, Comp);
    }
}


/// 归并排序算法
// 函数名称：void BubbleSort(ElemType , int , bool (*Comp)(  ), OutWay);
// 函数功能：冒泡法排序排序
// elem待排序的数组, length待排序数组的长度, Comp( )数据比较函数,
template<class ElemType>
void MergeSort(ElemType *elem, int length, bool (*Comp)(const void *, const void *), OutWay outWay)
{
    ElemType *tempElem = new ElemType[length];      // 开辟临时数组空间

    MergeSort(elem, tempElem, 0, length - 1, Comp, outWay);       // 归并排序过程

    delete[] tempElem;                              // 删除临时数组空间
}


// 函数名称：MergeSort
// 函数功能：利用辅助数组空间tempElem对Elem数组low到high位置的数据进行排序
template <class ElemType>
void MergeSort(ElemType *elem, ElemType *tempElem, int low, int high, bool (*Comp)(const void *, const void *), OutWay outWay)
{
    if(low < high)
    {
        int mid = (low + high) / 2;                 // 将待排序数组分成[low, mid]和[mid + 1, high]两个待排序子序列

        MergeSort(elem, tempElem, low, mid, Comp, outWay);        // 对elem[low, mid]进行归并排序
        MergeSort(elem, tempElem, mid + 1, high, Comp, outWay);   // 对elem[mid + 1, high]进行归并排序

        Merge(elem, tempElem, low, mid, high, Comp);      // 将两部分有序子序列归并为一个部分

        if(outWay == STEP)
        {
            for(int pos = 0; pos < SIZE; pos++)
            {
                std::cout <<std::setw(4) <<elem[pos];
            }
            std::cout <<std::endl;
        }
    }
}


// 函数名称：Merge
// 函数功能：将所有有序的自序列[low, mid]和[mid+1, high]归并为新的
template <class ElemType>
void Merge(ElemType *elem, ElemType *tempElem, int low, int mid, int high, bool (*Comp)(const void *, const void *))
{
    int i, j, k;

    for(i = low,j = mid + 1, k = low;   // 合并[i, k] -=>[low, mid]    AND    合并[j, high] -=> [mid + 1, high]
        i <= mid && j <= high;
        k++)
    {
       if(Comp(elem + i, elem +j))          // elem[i]较小的话，先合并
        //if(elem[i] <= elem[j])
        {
            tempElem[k] = elem[i];
            i++;
        }
        else                            // 否则elem[j]较小
        {
            tempElem[k] = elem[j];
            j++;
        }
    }

    for( ; i <= mid; i++, k++)           // 归并elem[low, mid]中剩余元素
    {
        tempElem[k] = elem[i];
    }
    for( ; j <= high; j++, k++)           // 归并elem[mid+1, high]中剩余元素
    {
        tempElem[k] = elem[j];
    }
    for( i = low; i <= high; i++)      // 将存在临时数组中已经合并的信息重新存到原数组之中
    {
        elem[i] = tempElem[i];
    }
}



template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
{
	for (int power = (int)pow((double)r, i - 1), j = 0; j < n; j++)
	{	// 进行第i起分配
		int index = (elem[j] / power) % r;
		list[index].Insert(list[index].Length() + 1, elem[j]);
	}
}

template <class ElemType>
void Colect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[], OutWay outWay)
{
	for (int k = 0, j = 0; j < r; j++)
	{	// 进行第i起分配
		ElemType tmpElem;
		while (!list[j].Empty())
		{	// 收集list[j]
			list[j].Delete(1, tmpElem);
			elem[k++] = tmpElem;
		}
        if(outWay == STEP)
        {
            for(i = 0; i < n; i++)
            {
                std::cout <<std::setw(4)<<elem[i];
            }
            std::cout <<std::endl;
        }
	}
}

template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d, OutWay outWay)
{
	LinkList<ElemType> *list;	// 用于存储被分配的线性表数组
	list = new LinkList<ElemType>[r];
	for (int i = 1; i <= d; i++)
	{	// 第i趟分配与收集
		Distribute(elem, n, r, d, i, list);	// 分配
		Colect(elem, n, r, d, i, list, outWay);		// 收集
	}
	delete []list;
}




template <class ElemType>
int Partition(ElemType elem[], int low, int high)
// 操作结果:交换elem[low .. high]中的元素,使枢轴移动到适当置,要求在枢轴之前的元素
//	不大于枢轴,在枢轴之后的元素不小于枢轴的,并返回枢轴的位置

{
	while (low < high)
	{
		while (low < high && elem[high] >= elem[low])
		{	// elem[low]为枢轴,使high右边的元素不小于elem[low]
			high--;
		}
		swap(elem[low], elem[high]);

		while (low < high && elem[low] <= elem[high])
		{	// elem[high]为枢轴,使low左边的元素不大于elem[high]
			low++;
		}
		swap(elem[low], elem[high]);
	}
	return low;	// 返回枢轴位置
}

// 函数名称：Quick_Sort_Help(ElemType *elem, int low, int high)
// 函数结果:对数组elem[low .. high]中的记录进行快速排序
template <class ElemType>
void Quick_Sort_Help(ElemType *elem, int low, int high, OutWay outWay)
{
	if (low < high)
	{
		int pivotLoc = Partition(elem, low, high);	// 进行一趟划分
		Quick_Sort_Help(elem, low, pivotLoc - 1, outWay);		// 对子表elem[low, pivotLoc - 1]递归排序
		Quick_Sort_Help(elem, pivotLoc + 1, high, outWay);	// 对子表elem[pivotLoc + 1, high]递归排序
	}
    if(outWay == STEP)     // 如果系统要求单步输出排序信息
    {
        for(int i = 0; i < SIZE; i++)
        {
            std::cout <<std::setw(4)<<elem[i];
        }
        std::cout <<std::endl;
    }
}

// 函数名称：Quick_Sort_Help(ElemType *elem, int low, int high)
// 函数结果:对数组elem进行快速排序
template <class ElemType>
void Quick_Sort(ElemType *elem, int n, OutWay outWay)
{
	Quick_Sort_Help(elem, 0, n - 1, outWay);
}


#endif // SORT_H_INCLUDE
