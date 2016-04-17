#链接
-------
[二叉树的遍历详解（前序中序后序层次-递归和非递归）](http://blog.csdn.net/gatieme/article/details/51163010)


#二叉树
-------

二叉树是一种非常重要的数据结构，很多其它数据结构都是基于二叉树的基础演变而来的。对于二叉树，有前序、中序以及后序三种遍历方法。因为树的定义本身就是递归定义，因此采用递归的方法去实现树的三种遍历不仅容易理解而且代码很简洁。而对于树的遍历若采用非递归的方法，就要采用栈去模拟实现。在三种遍历中，前序和中序遍历的非递归算法都很容易实现，非递归后序遍历实现起来相对来说要难一点

#前序遍历
-------
 

前序遍历按照“根结点-左孩子-右孩子”的顺序进行访问。



##递归实现

-------

```cpp
void PreOrder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }

    cout <<root->val;
    PreOrder(root->left);
    PreOrder(root->right);

}


```



#非递归实现

-------

根据前序遍历访问的顺序，优先访问根结点，然后再分别访问左孩子和右孩子。



即对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树；当访问其左子树时，再访问它的右子树。

*    从根节点开始，开始遍历，并输出（先序遍历首先输出根）

*    递归输出直至最左（先序根后面输出的是左孩子）

*    当到达最左节点的时候，访问右节点

因此其处理过程如下：

对于任一结点P：

*    访问结点P，并将结点P入栈;

*    判断结点P的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点P，循环至1);若不为空，则将P的左孩子置为当前的结点P;

*    直到P为NULL并且栈为空，则遍历结束。

```cpp

void PreOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }


    stack<TreeNode *> nstack;



    TreeNode *node = root;
    
    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty( ) != true)
    {
        //  输出当前子树的根节点，然后递归直至最左
        while(node != NULL)
        {
            cout <<node->val;
            nstack.push(node);
            node = node->left;
        }



        //  此时循环结束时，当前栈顶节点已经是最左节点
        //  此时递归开始返回，开始出栈，并输出节点的右节点
        if(nstack.empty() != true)
        {

            node = nstack.top( );
            nstack.pop( );
            node = node->right;
        }

    }

}


```

另外还有一种方法，如果我们把一颗树当成一个图，前序，中序和后序遍历都是深度优先遍历的特例。

而其中前序遍历与深度优先遍历最像，打印顺序也一致，因此前序遍历也可以用深度优先搜索来实现

```cpp

//
//  前序遍历的方法二，利用了栈的特性，但是此方法不通用
//  此过程相当于一次深度优先遍历
//
void TreeNode::PreOrderDFS(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    stack<TreeNode *> nstack;
    nstack.push(root);

    TreeNode *node = root;
    while(nstack.empty() != true)
    {
        node = nstack.top( );
        nstack.pop( );
        cout <<node->val;

        if(node->right != NULL)
        {
            nstack.push(node->right);
        }
        if(node->left != NULL)
        {
            nstack.push(node->left);
        }
    }
}

```


#中序遍历

-------

 

中序遍历按照“左孩子-根结点-右孩子”的顺序进行访问。



##递归实现

-------


```cpp

void InOrder(TreeNode *root)
{

    if(root == NULL)
    {
        return;
    }

    InOrder(root->left);
    cout <<root->val;
    InOrder(root->right);

}


```





##非递归实现

-------



根据中序遍历的顺序，对于任一结点，优先访问其左孩子，而左孩子结点又可以看做一根结点，然后继续访问其左孩子结点，直到遇到左孩子结点为空的结点才进行访问，然后按相同的规则访问其右子树。

*    从根节点开始，开始遍历

*    递归输出直至最左，然后输出（中序先输出左孩子，而中序遍历第一个输出的是其最左叶子节点）

*    当到达最左节点的时候，访问右节点


因此其处理过程如下：



对于任一结点P，

1.    若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对当前结点P再进行相同的处理；

2.    若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的P置为栈顶结点的右孩子；

3.    直到P为NULL并且栈为空则遍历结束



```cpp

void InOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }


    stack<TreeNode *> nstack;
    TreeNode *node = root;



    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty() != true)
    {
        // 不输出当前根节点，但是递归直至当前根节点node的最左端
        while(node != NULL)
        {

            nstack.push(node);
            node = node->left;
        }



        //  此时栈顶的元素是当前最左元素
        //  它应该被输出
        if(nstack.empty( ) != true)
        {

            node = nstack.top( );
            cout <<node->val;
            nstack.pop( );
            node = node->right;
        }
    }
}



```



#后序遍历

-------

 后序遍历按照“左孩子-右孩子-根结点”的顺序进行访问。

 

##递归实现


-------

```cpp

void PostOrder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }

    PostOrder(root->left);
    PostOrder(root->right);
    cout <<root->val;

}


```



##非递归实现

-------

 

后序遍历的非递归实现是三种遍历方式中最难的一种。因为在后序遍历中，要保证左孩子和右孩子都已被访问并且左孩子在右孩子前访问才能访问根结点，这就为流程的控制带来了难题。下面介绍两种思路。

     第一种思路：对于任一结点P，将其入栈，然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，此时该结点出现在栈顶，但是此时不能将其出栈并访问，因此其右孩子还为被访问。所以接下来按照相同的规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，此时可以将其出栈并访问。这样就保证了正确的访问顺序。可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。

```cpp
void PostOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
       debug <<"The tree is NULL..." <<endl;
    }


    stack<TreeNode *> nstack;
    TreeNode *node = root;



    while(node != NULL || nstack.empty( ) != true)
    {

        //  遍历直至最左节点
        while(node != NULL)
        {

            node->isFirst = 1;       // 当前节点首次被访问
            nstack.push(node);
            node = node->left;
        }



        if(nstack.empty() != true)
        {
            node = nstack.top( );
            nstack.pop( );



            if(node->isFirst == 1)   // 第一次出现在栈顶
            {

                node->isFirst++;
                nstack.push(node);

                node = node->right;
            }
            else if(node->isFirst == 2)
            {
                cout <<node->val;
                node = NULL;
            }
        }
    }
}


```

第二种思路：要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，左孩子和右孩子都在根结点前面被访问。

```cpp

void PostOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }

    stack<TreeNode *> nstack;

    TreeNode *cur;                      //当前结点
    TreeNode *pre = NULL;                 //前一次访问的结点
    nstack.push(root);



    while(nstack.empty( ) != true)
    {
        cur = nstack.top( );

        if((cur->left == NULL && cur->right == NULL)                     //  左右还是均为NULL, 可以被输出
        || (pre != NULL && ((pre == cur->left && cur->right == NULL) || pre == cur->right)))     //  左右还是被输出了, 递归返回
        //  其实当前节点要是想被输出, 要么
        //  1--其左右孩子均为NULL
        //  2--其左孩子刚被输出，而其右孩子为NULL
        //  3--其右孩子刚被输出
        //
        //  但是这里有一个优化, 入栈时候, 先是根入栈， 然后是右孩子, 然后是左孩子,
        //  因此当跟元素位于栈顶的时候, 其左右孩子必然已经弹出，即被输出,
        //  也就是说, 当前
        {
            cout<<cur->val;  //如果当前结点没有孩子结点或者孩子节点都已被访问过
            nstack.pop( );
            pre = cur;
        }
        else
        {
            // 由于栈是先进后出，因此先如后孩子, 再左孩子可以保证递归返回时先遍历左孩子
            if(cur->right != NULL)
            {
               nstack.push(cur->right);
            }


            if(cur->left != NULL)
            {
                nstack.push(cur->left);
            }
        }
    }
}

```


其实后序遍历中当前节点要是想被输出, 要么

1.    其左右孩子均为NULL

2.    其左孩子刚被输出，而其右孩子为NULL

3.    其右孩子刚被输出



但是这里有一个优化, 入栈时候, 先是根入栈， 然后是右孩子, 然后是左孩子,

因此当跟元素位于栈顶的时候, 其左右孩子必然已经弹出，即被访问并且输出,

也就是说, 判断当前节点是否需要输出时，只需要之前被输出的节点pre是当前栈定节点cur的孩子就行

即后序遍历中当前栈顶元素要是想被输出

1.    其左右孩子均为NULL

2.    其孩子（不论左右）刚被输出即可 

>而且如果刚被输出的节点是其左孩子，那么我们可以确定其有孩子必为NULL，否则它后于父节点入栈，应该在父节点之前被弹出并且输出

因此我们的输出判断可以改为

```cpp



        if((cur->left == NULL && cur->right == NULL)                     //  左右还是均为NULL, 可以被输出
        || (pre != NULL && ((pre == cur->left /*&& cur->right == NULL*/) || pre == cur->right)))     //  其孩子刚被被输出了, 递归返回

        //  其实当前节点要是想被输出, 要么


```


#层次遍历

-------



##递归实现

-------

利用递归的方法，按层进行打印，我们把根节点当做第0层，之后层次依次增加

首先我们用递归的方式来打印某一层的信息

如果我们要打印第n层，那么就需要从根节点开始递归的遍历，当到达我们制定的层次时，就输出。

打印第n层的递归函数如下

```cpp
/*
    打印当前树的第n层

    root  树的根
    n     希望打印的层次
    level 当前递归层次
*/
int PrintLevel(TreeNode *root, int n, int level)
{
    if(root == NULL || level < 0)
    {
        return 0;
    }
    else if(level == n)
    {
        cout <<root->val;
        return 1;
    }
    else
    {
        return PrintLevel(root->left, n, level + 1) + PrintLevel(root->right, n, level + 1);
    }
}
```

如果我们想要打印第2层，就直接调用如下的即可

```cpp
    PrintLevel(root, 2, 0);
```

当然我们也可以采用层次递减的方式，level = n为希望递归的层次，而层次每深入一次，level递减，当level=0时，则说明递归至第n层
```cpp
int PrintLevel(TreeNode *root, int level)
{
    if(root == NULL || level < 0)
    {
        return 0;
    }
    else if(level == 0)
    {
        cout <<root->val;
        return 1;
    }
    else
    {
        return PrintLevel(root->left, level - 1) + PrintLevel(root->right, level - 1);
    }
}
```


能够打印第n层的节点，那么我们实现层次遍历就简单了，循环调用递归每一层的节点即可

```cpp
void LevelOrder(TreeNode *root)
{
    for(int level = 0; ; level++)
    {
        if(PrintLevel(root, level) == 0)
        {
            break;
        }
        cout <<endl;
    }
}
```

以上的方法可以很清楚的看出，存在重复访问的情况，就是第0层访问的次数最多，第1层次之。所以这个递归的方法不是很有效的方法，但是却不需要消耗额外的空间




##非递归实现

-------



###双队列法
-------
第一个尝试，利用了两个队列，一个储存本层的节点，另一个储存下层的节点。遍历本层的节点，把其子代节点排入下层队列。本层遍历完毕后，就可换行，并交换两个队列。


我们可以设置两个队列，想象一下队列的特点，就是先进先出，首先把第0层保存在一个队列中，然后按节点访问，并把已经访问节点的左右孩子节点放在第二个队列中，当第一个队列中的所有节点都访问完成之后，交换两个节点。这样重复下去，知道所有层的节点都被访问，这样做的代价就是空间复杂度有点高。

```cpp
void LevelOrderDev(TreeNode *root)
{
    deque<TreeNode *> qFirst, qSecond;
    qFirst.push_back(root);

    while(qFirst.empty( ) != true)
    {
        while (qFirst.empty( ) != true)
        {
            TreeNode *temp = qFirst.front( );
            qFirst.pop_front( );

            cout << temp->val;

            if (temp->left != NULL)
            {
                qSecond.push_back(temp->left);
            }
            if (temp->right != NULL)
            {
                qSecond.push_back(temp->right);
            }
        }
        cout << endl;
        qFirst.swap(qSecond);

    }
}
```

本实现使用deque而不是queue，因为deque才支持swap()操作。注意，swap()是O(1)的操作，实际上只是交换指针。

这实现要用两个循环(书上的实现也是)，并且用了两个队列。能够只用一个循环、一个队列么?



其实我们只需要使用标识能够标识出每层的结束即可，因此可以归纳为如下的方法
*    双指针法，标识每层的开始结点和结束节点

*    size方法，同双指针法，标识每层的节点数目

*    END标识，在每层结束后，插入一个标识（如NULL或者特殊节点）来表示结束

###双指针法
-------
第三种方法就是设置双指针，一个curr指向访问当层开始的节点，一个end指向访问当层结束节点的下一个位置
```cpp
void TreeNode::LevelOrderUsePoint(TreeNode *root)
{
    vector<TreeNode*> vec;
    vec.push_back(root);

    int cur = 0;
    int end = 1;

    while (cur < vec.size())
    {
        end = vec.size();       ///  新的一行访问开始，重新定位last于当前行最后一个节点的下一个位置

        while (cur < end)
        {
            cout << vec[cur]->val;  ///  访问节点

            if (vec[cur]->left != NULL) ///  压入左节点
            {
                vec.push_back(vec[cur]->left);

            }
            if (vec[cur]->right != NULL)    ///  压入右节点
            {
                vec.push_back(vec[cur]->right);
            }
            cur++;
        }
        cout << endl;
    }
}
```

同样类似的方式，这种方式就是用了两个指针，分别表示每层的开始和结束。


##用size记录每层节点的个数
-------

相同的，我们也可以使用两个size来表示当前队列中父节点的个数和子节点的个数

```cpp
void TreeNode::LevelOrderUseSize(TreeNode *root)
{
    int parentSize = 1, childSize = 0;
    TreeNode *temp = NULL;

    queue<TreeNode *> q;
    q.push(root);
    while(q.empty( ) != true)
    {
        temp = q.front( );
        cout <<temp->val;

        q.pop( );

        if (temp->left != NULL)
        {
            q.push(temp->left);

            childSize++;
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
            childSize++;
        }

        parentSize--;
        if (parentSize == 0)
        {
            parentSize = childSize;
            childSize = 0;
            cout << endl;
        }

    }
}
```

##在每层节点后面插入END结点标识
-------
```cpp
void TreeNode::LevelOrderUseEnd(TreeNode *root)
{
    queue<TreeNode *> q;

    q.push(root);
    q.push(NULL);

    while(q.empty( ) != true)
    {
        TreeNode* node = q.front();
        q.pop();

        if (node)
        {
            cout << node->val;

            if (node->left != NULL)
            {
                q.push(node->left);
            }
            if (node->right != NULL)
            {
                q.push(node->right);
            }
        }
        else if (q.empty( ) != true)
        {
            q.push(NULL);
            cout << endl;
        }
    }
}
```


#完整代码
-------
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
using namespace std;

//  调试开关
#ifdef DEBUG

#define debug cout

#else

#define debug 0 && cout

#endif // __tmain




//#define __ISFIRST_FOR_POSTPRDER



class TreeNode
{
public :
    int val;
    TreeNode *left;
    TreeNode *right;
#ifdef __ISFIRST_FOR_POSTPRDER
    int    isFirst;          //  非递归中序遍历中保存其是否首次被访问


#endif // __ISFIRST_FOR_POSTPRDER

    TreeNode(int x)
    : val(x), left(NULL), right(NULL)
    {
    }

    static void PreOrder(TreeNode *root);
    static void PreOrderDev(TreeNode *root);

    static void InOrder(TreeNode *root);
    static void InOrderDev(TreeNode *root);

    static void PostOrder(TreeNode *root);
    static void PostOrderDev(TreeNode *root);

    static int  PrintLevel(TreeNode *root, int level = 0);
    static void LevelOrder(TreeNode *root);
    static void LevelOrderDev(TreeNode *root);
    static void LevelOrderUsePoint(TreeNode *root);
    static void LevelOrderUseSize(TreeNode *root);
    static void LevelOrderUseEnd(TreeNode *root);


};

//
void TreeNode::PreOrder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    cout <<root->val;
    PreOrder(root->left);
    PreOrder(root->right);
}

void TreeNode::InOrder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    InOrder(root->left);
    cout <<root->val;
    InOrder(root->right);
}

void TreeNode::PostOrder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    PostOrder(root->left);
    PostOrder(root->right);
    cout <<root->val;
}

//    非递归实现
//
//    根据前序遍历访问的顺序，优先访问根结点，然后再分别访问左孩子和右孩子。
//
//    即对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树；
//    当访问其左子树时，再访问它的右子树。因此其处理过程如下：
//
//     对于任一结点P：
//
//     1)访问结点P，并将结点P入栈;
//
//     2)判断结点P的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点P，循环至1);若不为空，则将P的左孩子置为当前的结点P;
//
//     3)直到P为NULL并且栈为空，则遍历结束。
void TreeNode::PreOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }

    stack<TreeNode *> nstack;


    TreeNode *node = root;
    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty( ) != true)
    {
        //  输出当前子树的根节点，然后递归直至最左
        while(node != NULL)
        {
            cout <<node->val;
            nstack.push(node);
            node = node->left;
        }

        //  此时循环结束时，当前栈顶节点已经是最左节点
        //  此时递归开始返回，开始出栈，并输出节点的右节点
        if(nstack.empty() != true)
        {
            node = nstack.top( );
            nstack.pop( );
            node = node->right;
        }
    }
}

void TreeNode::InOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }

    stack<TreeNode *> nstack;
    TreeNode *node = root;

    //  开始遍历整个二叉树
    while(node != NULL || nstack.empty() != true)
    {
        // 不输出当前根节点，但是递归直至当前根节点node的最左端
        while(node != NULL)
        {
            nstack.push(node);
            node = node->left;
        }

        //  此时栈顶的元素是当前最左元素
        //  它应该被输出
        if(nstack.empty( ) != true)
        {
            node = nstack.top( );
            cout <<node->val;
            nstack.pop( );
            node = node->right;
        }
    }
}


#ifdef __ISFIRST_FOR_POSTPRDER
//  对于任一结点P，将其入栈，
//  然后沿其左子树一直往下搜索，直到搜索到没有左孩子的结点，
//  此时该结点出现在栈顶，但是此时不能将其出栈并访问，因此其右孩子还为被访问。
//
//  所以接下来按照相同的规则对其右子树进行相同的处理，当访问完其右孩子时，该结点又出现在栈顶，
//  此时可以将其出栈并访问。这样就保证了正确的访问顺序。
//  可以看出，在这个过程中，每个结点都两次出现在栈顶，只有在第二次出现在栈顶时，才能访问它。因此需要多设置一个变量标识该结点是否是第一次出现在栈顶。
void TreeNode::PostOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }

    stack<TreeNode *> nstack;
    TreeNode *node = root;

    while(node != NULL || nstack.empty( ) != true)
    {
        //  遍历直至最左节点
        while(node != NULL)
        {
            node->isFirst = 1;       // 当前节点首次被访问
            nstack.push(node);
            node = node->left;

        }

        if(nstack.empty() != true)
        {
            node = nstack.top( );
            nstack.pop( );

            if(node->isFirst == 1)   // 第一次出现在栈顶
            {
                node->isFirst++;
                nstack.push(node);

                node = node->right;
            }
            else if(node->isFirst == 2)
            {
                cout <<node->val;
                node = NULL;
            }
        }
    }
}
#else           //
void TreeNode::PostOrderDev(TreeNode *root)
{
    if(root == NULL)
    {
        debug <<"The tree is NULL..." <<endl;
    }
    stack<TreeNode *> nstack;

    TreeNode *cur;                      //当前结点
    TreeNode *pre = NULL;                 //前一次访问的结点
    nstack.push(root);

    while(nstack.empty( ) != true)
    {
        cur = nstack.top( );

        if((cur->left == NULL && cur->right == NULL)                     //  左右还是均为NULL, 可以被输出
        || (pre != NULL && ((pre == cur->left /*&& cur->right == NULL*/) || pre == cur->right)))     //  左右还是被输出了, 递归返回
        //  其实当前节点要是想被输出, 要么
        //  1--其左右孩子均为NULL
        //  2--其左孩子刚被输出，而其右孩子为NULL
        //  3--其右孩子刚被输出
        //
        //  但是这里有一个优化, 入栈时候, 先是根入栈， 然后是右孩子, 然后是左孩子,
        //  因此当跟元素位于栈顶的时候, 其左右孩子必然已经弹出，即被输出,
        //  也就是说, 当前
        {
            cout<<cur->val;  //如果当前结点没有孩子结点或者孩子节点都已被访问过
            nstack.pop( );
            pre = cur;
        }
        else
        {
            // 由于栈是先进后出，因此先如后孩子, 再左孩子可以保证递归返回时先遍历左孩子
            if(cur->right != NULL)
            {
                nstack.push(cur->right);
            }

            if(cur->left != NULL)
            {
                nstack.push(cur->left);
            }
        }
    }
}
#endif // __ISFIRST_FOR_POSTPRDER




int TreeNode::PrintLevel(TreeNode *root, int level)
{
    if(root == NULL || level < 0)
    {
        return 0;
    }
    else if(level == 0)
    {
        cout <<root->val;
        return 1;
    }
    else
    {
        return PrintLevel(root->left, level - 1) + PrintLevel(root->right, level - 1);
    }
}

void TreeNode::LevelOrder(TreeNode *root)
{
    for(int level = 0; ; level++)
    {
        if(PrintLevel(root, level) == 0)
        {
            break;
        }
        cout <<endl;
    }
}

void TreeNode::LevelOrderDev(TreeNode *root)
{
    /// deque双端队列，
    /// 支持迭代器，有push_back()方法，
    /// 跟vector差不多，比vector多了个pop_front,push_front方法

    deque<TreeNode *> qFirst, qSecond;
    qFirst.push_back(root);

    while(qFirst.empty( ) != true)
    {
        while (qFirst.empty( ) != true)
        {
            TreeNode *temp = qFirst.front( );
            qFirst.pop_front( );

            cout << temp->val;

            if (temp->left != NULL)
            {
                qSecond.push_back(temp->left);
            }
            if (temp->right != NULL)
            {
                qSecond.push_back(temp->right);
            }
        }
        cout << endl;
        qFirst.swap(qSecond);

    }
}


void TreeNode::LevelOrderUsePoint(TreeNode *root)
{
    vector<TreeNode*> vec;
    vec.push_back(root);

    int cur = 0;
    int end = 1;

    while (cur < vec.size())
    {
        end = vec.size();       ///  新的一行访问开始，重新定位last于当前行最后一个节点的下一个位置

        while (cur < end)
        {
            cout << vec[cur]->val;  ///  访问节点

            if (vec[cur]->left != NULL) ///  压入左节点
            {
                vec.push_back(vec[cur]->left);

            }
            if (vec[cur]->right != NULL)    ///  压入右节点
            {
                vec.push_back(vec[cur]->right);
            }
            cur++;
        }
        cout << endl;
    }
}

void TreeNode::LevelOrderUseSize(TreeNode *root)
{
    int parentSize = 1, childSize = 0;
    TreeNode *temp = NULL;

    queue<TreeNode *> q;
    q.push(root);
    while(q.empty( ) != true)
    {
        temp = q.front( );
        cout <<temp->val;

        q.pop( );

        if (temp->left != NULL)
        {
            q.push(temp->left);

            childSize++;
        }
        if (temp->right != NULL)
        {
            q.push(temp->right);
            childSize++;
        }

        parentSize--;
        if (parentSize == 0)
        {
            parentSize = childSize;
            childSize = 0;
            cout << endl;
        }

    }
}

void TreeNode::LevelOrderUseEnd(TreeNode *root)
{
    queue<TreeNode *> q;

    q.push(root);
    q.push(NULL);

    while(q.empty( ) != true)
    {
        TreeNode* node = q.front();
        q.pop();

        if (node)
        {
            cout << node->val;

            if (node->left != NULL)
            {
                q.push(node->left);
            }
            if (node->right != NULL)
            {
                q.push(node->right);
            }
        }
        else if (q.empty( ) != true)
        {
            q.push(NULL);
            cout << endl;
        }
    }
}


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in)
    {
        //  前序遍历的长度跟中序遍历的长度应该相同
        if(pre.size( ) != in.size( ))
        {
            debug <<"the length of PRE and IN should be smae" <<endl;
            return NULL;
        }

        // 长度不能为0
        int size = pre.size( );
        if(size == 0)
        {
            debug <<"it's a NULL tree(length = 0)" <<endl;
            return NULL;
        }

        int length = pre.size( );
        debug <<"the length of your tree = " <<length <<endl;
        int value = pre[0];      //  前序遍历的第一个结点是根节点
        TreeNode *root = new TreeNode(value);

        debug <<"the root is" <<root->val <<endl;
        //  在中序遍历中查找到根的位置
        int rootIndex = 0;
        for(rootIndex = 0; rootIndex < length; rootIndex++)
        {
            if(in[rootIndex] == value)
            {
                debug <<"find the root at " <<rootIndex <<" in IN" <<endl;
                break;
            }
        }
        if(rootIndex >= length)
        {
            debug <<"can't find root (value = " <<value <<") in IN" <<endl;
            return NULL;
        }

        ///  区分左子树和右子树
        ///  中序遍历中, 根左边的就是左子数, 右边的就是右子树
        ///  前序遍历中, 根后面是先遍历左子树, 然后是右子树

        ///  首先确定左右子树的长度, 从中序遍历in中确定
        int leftLength = rootIndex;
        int rightLength = length - 1 - rootIndex;
        debug <<"left length = " <<leftLength <<", rightLength = " <<rightLength <<endl;
        vector<int> preLeft(leftLength), inLeft(leftLength);
        vector<int> preRight(rightLength), inRight(rightLength);
        for(int i = 0; i < length; i++)
        {
            if(i < rootIndex)
            {
                //  前序遍历的第一个是根节点, 根后面的(leftLegnth = rootIndex) - 1个节点是左子树, 因此是i+1
                preLeft[i] = pre[i + 1];
                //  中序遍历前(leftLength = rootIndex) - 1个节点是左子树, 第rootIndex个节点是根
                inLeft[i] = in[i];
                debug <<preLeft[i] <<inLeft[i] <<" ";

            }
            else if(i > rootIndex)
            {
                //  前序遍历的第一个是根节点, 根后面的(leftLegnth = rootIndex) - 1个节点是左子树, 后面是右子树
                preRight[i - rootIndex - 1] = pre[i];
                //  中序遍历前(leftLength = rootIndex) - 1个节点是左子树, 第rootIndex个节点是根, 然后是右子树
                inRight[i - rootIndex - 1] = in[i];
                debug <<preRight[i - rootIndex - 1] <<inRight[i - rootIndex - 1] <<" ";

            }
        }
        debug <<endl <<"the left tree" <<endl;
        for(int i = 0; i < leftLength; i++)
        {
            debug <<preLeft[i] <<inLeft[i] <<" ";
        }
        debug <<endl;
        debug <<"the right tree" <<endl;
        for(int i = 0; i < rightLength; i++)
        {
            debug <<preRight[i] <<inRight[i] <<" ";
        }
        debug <<endl;


        root->left = reConstructBinaryTree(preLeft, inLeft);
        root->right = reConstructBinaryTree(preRight, inRight);

        return root;
    }

};


int main( )
{
    int pre[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int in[] = { 4, 7, 2, 1, 5, 3, 8, 6 };

    vector<int> preOrder(pre, pre + 8);
    vector<int>  inOrder( in,  in + 8);

    Solution solu;
    TreeNode *root = solu.reConstructBinaryTree(preOrder, inOrder);

    cout <<"PreOrder" <<endl;   //  12345678
    TreeNode::PreOrder(root);
    cout <<endl;
    TreeNode::PreOrderDev(root);
    cout <<endl;

    cout <<"InOrder " <<endl;   //  47215386
    TreeNode::InOrder(root);
    cout <<endl;
    TreeNode::InOrderDev(root);
    cout <<endl;


    cout <<"PostOrder " <<endl; //
    TreeNode::PostOrder(root);
    cout <<endl;
    TreeNode::PostOrderDev(root);
    cout <<endl;


    cout <<"LevelOrder " <<endl;
    TreeNode::LevelOrder(root);
    cout <<endl;
    TreeNode::LevelOrderDev(root);
    cout <<endl;
    TreeNode::LevelOrderUsePoint(root);
    cout <<endl;
    TreeNode::LevelOrderUseSize(root);
    cout <<endl;
    TreeNode::LevelOrderUseEnd(root);
    cout <<endl;
    return 0;
}

```

#参考
-------
[二叉树的非递归遍历](http://www.cnblogs.com/dolphin0520/archive/2011/08/25/2153720.html)

[层次遍历二叉树-三种不同的方法](http://blog.csdn.net/zzran/article/details/8778021)

[[编程之美]二叉树的层次遍历](http://blog.csdn.net/lalor/article/details/7626854)

[编程之美：分层遍历二叉树--的另外两个实现](http://www.cnblogs.com/miloyip/archive/2010/05/12/binary_tree_traversal.html)

[剑指Offer--006-重构二叉树-通过前序遍历和中序遍历构建二叉树](http://blog.csdn.net/gatieme/article/details/51108612)