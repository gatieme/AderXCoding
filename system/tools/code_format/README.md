Linux下的代码格式工具详解
=======

| CSDN | GitHub |
|:----:|:------:|
| [Linux下的代码格式工具详解](http://blog.csdn.net/gatieme/article/details/73692049) | [`AderXCoding/system/tools/code_format`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/code_format) |



<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处
<br>

#1	代码格式化工具
-------

#2	indent
-------


`indent` 可辨识 `C` 的原始代码文件, 并加以格式化, 以方便程序设计师阅读.



`Linux kernel` 有一个脚本 `Lindent`， 参见[`scripts/Lindent`](http://elixir.free-electrons.com/linux/latest/source/scripts/Lindent), 用来格式化 `kernel` 代码. 这个脚本就是通过 `indent` 工具来完成代码格式化的


`Ubuntu` 下 `indent` 可以通过如下方式安装

```cpp
sudo apt-get install indent
```


>功能说明：调整C原始代码文件的格式。
>
>语　　法：indent [参数][源文件] 或 indent [参数][源文件][-o 目标文件]




| 参数 | 说明 |
|:----:|:---:|
| -bad或--blank-lines-after-declarations | 在声明区段或加上空白行 |
| -bap或--blank-lines-after-procedures | 在程序或加上空白行 |
| -bbb或--blank-lines-after-block-comments | 在注释区段后加上空白行 |
| -bc或--blank-lines-after-commas | 在声明区段中，若出现逗号即换行 |
| -bl或--braces-after-if-line | if(或是else,for等等)与后面执行区段的"{"不同行，且"}"自成一行 |
| -bli<缩排格数>或--brace-indent<缩排格数> | 设置{ }缩排的格数 |
| -br或--braces-on-if-line | if(或是else,for等等)与后面执行跛段的"{"不同行，且"}"自成一行 |
| -bs或--blank-before-sizeof | 在sizeof之后空一格。
| -c<栏数>或--comment-indentation<栏数> | 将注释置于程序码右侧指定的栏位 |
| -cd<栏数>或--declaration-comment-column<栏数> | 将注释置于声明右侧指定的栏位 |
| -cdb或--comment-delimiters-on-blank-lines | 注释符号自成一行 |
| -ce或--cuddle-else | 将else置于"}"(if执行区段的结尾)之后 |
| -ci<缩排格数>或--continuation-indentation<缩排格数> | 叙述过长而换行时，指定换行后缩排的格数 |
| -cli<缩排格数>或--case-indentation-<缩排格数> | 使用case时，switch缩排的格数 |
| -cp<栏数>或-else-endif-column<栏数> | 将注释置于else与elseif叙述右侧定的栏位 |
| -cs或--space-after-cast | 在cast之后空一格 |
| -d<缩排格数>或-line-comments-indentation<缩排格数> | 针对不是放在程序码右侧的注释，设置其缩排格数 |
| -di<栏数>或--declaration-indentation<栏数> | 将声明区段的变量置于指定的栏位 |
| -fc1或--format-first-column-comments | 针对放在每行最前端的注释，设置其格式 |
| -fca或--format-all-comments | 设置所有注释的格式 |
| -gnu或--gnu-style. | 指定使用GNU的格式，此为预设值 |
| -i<格数>或--indent-level<格数> | 设置缩排的格数 |
| -ip<格数>或--parameter-indentation<格数> | 设置参数的缩排格数 |
| -kr或--k-and-r-style. | 指定使用Kernighan&Ritchie的格式 |
| -lp或--continue-at-parentheses | 叙述过长而换行，且叙述中包含了括弧时，将括弧中的每行起始栏位内容垂直对其排列 |
| -nbad或--no-blank-lines-after-declarations | 在声明区段后不要加上空白行 |
| -nbap或--no-blank-lines-after-procedures | 在程序后不要加上空白行 |
| -nbbb或--no-blank-lines-after-block-comments | 在注释区段后不要加上空白行 |
| -nbc或--no-blank-lines-after-commas | 在声明区段中，即使出现逗号，仍旧不要换行 |
| -ncdb或--no-comment-delimiters-on-blank-lines | 注释符号不要自成一行。
| -nce或--dont-cuddle-else | 不要将else置于"}"之后。
| -ncs或--no-space-after-casts | 不要在cast之后空一格。
| -nfc1或--dont-format-first-column-comments | 不要格式化放在每行最前端的注释 |
| -nfca或--dont-format-comments | 不要格式化任何的注释。
| -nip或--no-parameter-indentation | 参数不要缩排 |
| -nlp或--dont-line-up-parentheses | 叙述过长而换行，且叙述中包含了括弧时，不用将括弧中的每行起始栏位垂直对其排列 |
| -npcs或--no-space-after-function-call-names | 在调用的函数名称之后，不要加上空格 |
| -npro或--ignore-profile | 不要读取indent的配置文件.indent.pro |
| -nprs或者--space-after-parentheses | 	在"（"后"）"前不插入空格 |
| -npsl或--dont-break-procedure-type | 程序类型与程序名称放在同一行 |
| -nsc或--dont-star-comments | 不在生成的块注释中加*， 注解左侧不要加上星号(*) |
| -nsob或--leave-optional-semicolon | 不用处理多余的空白行 |
| -nss或--dont-space-special-semicolon | 若for或while区段仅有一行时，在分号前不加上空格。
| -nv或--no-verbosity | 不显示详细的信息 |
| -orig或--original | 使用Berkeley的格式 |
| -pcs或--space-after-procedure-calls | 在调用的函数名称与"{"之间加上空格 |
| -psl或--procnames-start-lines | 程序类型置于程序名称的前一行。
| -sc或--start-left-side-of-comments | 在每行注释左侧加上星号(*) |
| -sob或--swallow-optional-blank-lines | 删除多余的空白行 |
| -ss或--space-special-semicolon | 若for或swile区段今有一行时，在分号前加上空格 |
| -st或--standard-output | 将结果显示在标准输出设备 |
| -saf或者--space-after-for | for后面有空格 |
| -sai或者--space-after-if | if后面有空格 |
| -saw或者--space-after-while | while后面有空格 |
| -T | 数据类型名称缩排 |
| -ts<格数>或--tab-size<格数> | 设置tab的长度 |
| pcs或者--space-after-procedure-calls | 函数和"("之间插入一个空格 |
| psl或者--procnames-start-lines | 将函数名和返回类型放在两行定义 |
| -ut或者--use-tabs | 使用tab来缩进 |
| -v或--verbose | 执行时显示详细的信息 |
| -version | 显示版本信息 |

>其他帮助信息, 可参考
>
>[indent(linux下C代码格式化工具) 中文说明](http://blog.chinaunix.net/uid-28295089-id-4477107.html)
>
>[Linux 代码格式化工具 indent](http://blog.csdn.net/httphttpcn/article/details/5940848)
>
>[vim格式化C代码](http://blog.chinaunix.net/uid-24774106-id-3396220.html)
>
>[如何使用 indent 美化你的代码](http://www.cnblogs.com/haippy/archive/2012/08/29/2662772.html)


#3	clang-format
-------

`clang` 编译器中集成的代码格式化工具,

官方文档参见

http://clang.llvm.org/docs/ClangFormat.html

http://clang.llvm.org/docs/ClangFormatStyleOptions.html


#4 AStyle
-------


`Astyle` 的全称是 `Artistic Style`, 某种程度是目前最好用的代码整理工具, 很多所谓的代码整理工具其实都是拿这个东东改进, 开发的.

其网址在 http://astyle.sourceforge.net
最新版本是 `3.0`, 基本已经稳定
官方文档 http://astyle.sourceforge.net/astyle.html


[astyle 使用说明](http://www.cnblogs.com/jiangxinnju/p/4908575.html)

[AStyle代码格式工具在source insight中的使用](http://blog.csdn.net/gw_cs/article/details/7927735)

[astyle使用基础教程](http://www.cppblog.com/jokes000/articles/158838.html)

<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作, 

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的, 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.


