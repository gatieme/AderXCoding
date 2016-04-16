>转载自来源： [[C/C++] 显示各种C/C++编译器的预定义宏（C11标准、C++11标准、VC、BCB、Intel、GCC）](http://www.cnblogs.com/zyl910/archive/2012/08/02/printmacro.html)
>
>http://dev.gameres.com/Program/Other/ErrorDebug.htm
>http://blog.csdn.net/sealyao/article/details/6169568

作者：zyl910

　　在编写跨平台的程序时，我们经常使用预定义宏来检测编译环境。虽然编译器的手册中有预处理宏的介绍，但是不够详细，而且还有很多宏没有介绍。于是，我编写了一个小程序，显示常见C/C++编译器的编译器的预定义宏。

#心得
-------
　　最直接的办法是逐个逐个的用#ifdef判断宏是否存在，然后再printf显示其内容。可是预定义宏有些是整数、有些是字符串，还有些是关键字不能直接用printf输出，用起来挺麻烦的。

　　在网上发现一种不错办法，出自《关于CPP的预定义宏：unix、linux、i386、i586，大家中过招吗？》4楼“太平绅士”——


```cpp
#include <stdio.h>
 
 
#define PT_MAKE_STR(x)                { #x, PT_MAKE_STR_ESC(x) }
#define PT_MAKE_STR_ESC(x)        #x
 
 
typedef struct
{
        const char *name;
        const char *value;
} MACRO_T;
 
 
/* Compilers */const MACRO_T g_compilers[ ] =
{
#ifdef __INTEL_COMPILER        /* Interl C++ */
        PT_MAKE_STR( __INTEL_COMPILER ),
#endif
 
#ifdef _MSC_VER                        /* Visual C++ */
        PT_MAKE_STR( _MSC_VER ),
#endif
 
#ifdef __GNUC__                        /* GCC */
        PT_MAKE_STR( __GNUC__ ),
#endif
 
#ifdef __DMC__                        /* DMC++ */
        PT_MAKE_STR( __DMC__ ),
#endif
 
#ifdef __ARMCC_VERSION        /* ARM C/C++ */
        PT_MAKE_STR( __ARMCC_VERSION ),
#endif
};
 
 
/* Operation system */const MACRO_T g_platforms[ ] =
{
#ifdef _WIN32                        /* Windows 32 or Windows 64 */
        PT_MAKE_STR( _WIN32 ),
#endif
 
#ifdef _WIN64                        /* Windows 64 */
        PT_MAKE_STR( _WIN64 ),
#endif
 
#ifdef __MINGW32__                /* Windows32 by mingw compiler */
        PT_MAKE_STR( __MINGW32__ ),
#endif
 
#ifdef __CYGWIN__                /* Cygwin */
        PT_MAKE_STR( __CYGWIN__ ),
#endif
 
#ifdef __linux__                /* linux */
        PT_MAKE_STR( __linux__ ),
#endif
 
#ifdef __FreeBSD__                /* FreeBSD */
        PT_MAKE_STR( __FreeBSD__ ),
#endif
 
#ifdef __NetBSD__                /* NetBSD */
        PT_MAKE_STR( __NetBSD__ ),
#endif
 
#ifdef __OpenBSD__                /* OpenBSD */
        PT_MAKE_STR( __OpenBSD__ ),
#endif
 
#ifdef __sun__                /* Sun OS */
        PT_MAKE_STR( __sun__ ),
#endif
 
#ifdef __MaxOSX__                /* MAC OS X */
        PT_MAKE_STR( __MaxOSX__ ),
#endif
 
#ifdef __unix__                        /* unix */
        PT_MAKE_STR( __unix__ ),
#endif        
};
 
 
/* Other useful */const MACRO_T g_others[ ] =
{
#ifdef __DATE__ 
        PT_MAKE_STR( __DATE__ ),
#endif
 
#ifdef __TIME__ 
        PT_MAKE_STR( __TIME__ ),
#endif
 
#ifdef _BSD_SOURCE
        PT_MAKE_STR( _BSD_SOURCE ),
#endif
 
#ifdef _POSIX_SOURCE
        PT_MAKE_STR( _POSIX_SOURCE ),
#endif
 
#ifdef _XOPEN_SOURCE
        PT_MAKE_STR( _XOPEN_SOURCE ),
#endif
 
#ifdef _GNU_SOURCE
        PT_MAKE_STR( _GNU_SOURCE ),
#endif
 
#ifdef __GNUC_MINOR__
        PT_MAKE_STR( __GNUC_MINOR__ ),
#endif
 
#ifdef __VERSION__
        PT_MAKE_STR( __VERSION__ ),
#endif
 
#ifdef __unix
        PT_MAKE_STR( __unix ),
#endif
};
 
 
 
int main( int argc, char **argv )
{
        int i;
 
        printf( "/* Compiler definitions. */\n" );
        for( i = 0; i < sizeof( g_compilers ) / sizeof( g_compilers[ 0 ] ); ++i )
        {
                printf( "#define %s %s\n", g_compilers[ i ].name, g_compilers[ i ].value );
        }
        printf( "\n" );
 
        printf( "/* Platform definitions. */\n" );
        for( i = 0; i < sizeof( g_platforms ) / sizeof( g_platforms[ 0 ] ); ++i )
        {
                printf( "#define %s %s\n", g_platforms[ i ].name, g_platforms[ i ].value );
        }
        printf( "\n" );
 
        printf( "/* Other definitions. */\n" );
        for( i = 0; i < sizeof( g_others ) / sizeof( g_others[ 0 ] ); ++i )
        {
                printf( "#define %s %s\n", g_others[ i ].name, g_others[ i ].value );
        }
        printf( "\n" );
 
        return 0;
}
```

　　该方法巧妙的利用“#”运算将宏转成了字符串并填写数组，然后程序只需显示数组内容就行了。

　　我在该方法的基础上做了三点改进——

1. main函数中有很多相似的代码，区别仅仅是数组的不同。可以编写一个print_MACRO_T函数来显示MACRO_T数组，然后在main函数中对每一个数组调用该函数。

2. 当某个数组的宏均不存在时，编译器会报错。可以在数组的第一行填上该类别的描述信息，保证编译通过。另一个好处是精简了main函数中显示不同类别描述信息的代码。

3. 某些编译器不支持内容为空的宏（如BCB6）。这时只有手动#if做兼容性处理了。


#全部代码
-------

　　预定义宏的数据来自——C11标准、C++11标准，及VC、BCB、Intel、GCC这些编译器。
　　最初想删除重名的宏，后来考虑到需要对照各个编译器的手册，所以还是允许重名比较好。
```cpp
#include <stdio.h>


#define PT_MAKE_STR(x)    { #x, PT_MAKE_STR_ESC(x) }
#define PT_MAKE_STR_ESC(x)    #x


typedef struct tagMACRO_T
{
    const char *name;
    const char *value;
} MACRO_T;

/* Compilers */
const MACRO_T g_compilers[] =
{
    {"[Compiler]", ""},

#ifdef _MSC_VER            /* Visual C++ */
    PT_MAKE_STR( _MSC_VER ),
#endif

#ifdef __BORLANDC__
    PT_MAKE_STR(__BORLANDC__),
#endif

#ifdef __INTEL_COMPILER    /* Interl C++ */
    PT_MAKE_STR( __INTEL_COMPILER ),
#endif

#ifdef __GNUC__            /* GCC */
    PT_MAKE_STR( __GNUC__ ),
#endif

#ifdef __DMC__            /* DMC++ */
    PT_MAKE_STR( __DMC__ ),
#endif

#ifdef __ARMCC_VERSION    /* ARM C/C++ */
    PT_MAKE_STR( __ARMCC_VERSION ),
#endif

#ifdef __APPLE_CC__            /* Apple's own GCC */
    PT_MAKE_STR( __APPLE_CC__ ),
#endif
};

/* Operation system */
const MACRO_T g_platforms[] =
{
    {"[Platform]", ""},

#ifdef __i386__
    PT_MAKE_STR(__i386__),
#endif

#ifdef __x86_64__
    PT_MAKE_STR(__x86_64__),
#endif

#ifdef __AMD64__
    PT_MAKE_STR(__AMD64__),
#endif

#ifdef __amd64__
    PT_MAKE_STR(__amd64__),
#endif

#ifdef __ia64__
    PT_MAKE_STR(__ia64__),
#endif

#ifdef __alpha__
    PT_MAKE_STR(__alpha__),
#endif

#ifdef __arm__
    PT_MAKE_STR(__arm__),
#endif

#ifdef __sparc__
    PT_MAKE_STR(__sparc__),
#endif

#ifdef __arch64__
    PT_MAKE_STR(__arch64__),
#endif

#ifdef __powerpc__
    PT_MAKE_STR(__powerpc__),
#endif

#ifdef __powerpc64__
    PT_MAKE_STR(__powerpc64__),
#endif

#ifdef __ppc__
    PT_MAKE_STR(__ppc__),
#endif

#ifdef __ppc64__
    PT_MAKE_STR(__ppc64__),
#endif

#ifdef _WIN32            /* Windows 32 or Windows 64 */
    PT_MAKE_STR( _WIN32 ),
#endif

#ifdef _WIN64            /* Windows 64 */
    PT_MAKE_STR( _WIN64 ),
#endif

#ifdef __MINGW32__        /* Windows32 by mingw compiler */
    PT_MAKE_STR( __MINGW32__ ),
#endif

#ifdef __CYGWIN__        /* Cygwin */
    PT_MAKE_STR( __CYGWIN__ ),
#endif

#ifdef __linux__        /* linux */
    PT_MAKE_STR( __linux__ ),
#endif

#ifdef __FreeBSD__        /* FreeBSD */
    PT_MAKE_STR( __FreeBSD__ ),
#endif

#ifdef __NetBSD__        /* NetBSD */
    PT_MAKE_STR( __NetBSD__ ),
#endif

#ifdef __OpenBSD__        /* OpenBSD */
    PT_MAKE_STR( __OpenBSD__ ),
#endif

#ifdef __sun__        /* Sun OS */
    PT_MAKE_STR( __sun__ ),
#endif

#ifdef __MaxOSX__        /* MAC OS X */
    PT_MAKE_STR( __MaxOSX__ ),
#endif

#ifdef __unix__            /* unix */
    PT_MAKE_STR( __unix__ ),
#endif

////////////////////////////////////////
#ifdef __APPLE__
    PT_MAKE_STR( __APPLE__ ),
#endif

#ifdef linux
    PT_MAKE_STR( linux ),
#endif

#ifdef _LINUX
    PT_MAKE_STR( _LINUX ),
#endif

#ifdef __USE_BSD
    PT_MAKE_STR( __USE_BSD ),
#endif

};

/* Standard C. C11, C++11 */
const MACRO_T g_stdc[] =
{
    /* [C11]: ISO/IEC 9899:2011 - Information technology -- Programming languages -- C. http://www.iso.org/iso/home/store/catalogue_tc/catalogue_detail.htm?csnumber=57853  */
    /* [C++11]: ISO/IEC 14882:2011 - Information technology -- Programming languages -- C++. http://www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=50372 */
    {"[Standard C]", ""},

    /* [C11] 6.10.8.1 Mandatory macros */
#ifdef __FILE__
    PT_MAKE_STR(__FILE__),
#endif

#ifdef __LINE__
    PT_MAKE_STR(__LINE__),
#endif

#ifdef __DATE__
    PT_MAKE_STR(__DATE__),
#endif

#ifdef __TIME__
    PT_MAKE_STR(__TIME__),
#endif

#ifdef __TIMESTAMP__
    PT_MAKE_STR(__TIMESTAMP__),
#endif

#ifdef __STDC__
    PT_MAKE_STR(__STDC__),
#endif

#ifdef __STDC_HOSTED__
    PT_MAKE_STR(__STDC_HOSTED__),
#endif

#ifdef __STDC_VERSION__
    PT_MAKE_STR(__STDC_VERSION__),
#endif

    /* [C11] 6.10.8.2 Environment macros */
#ifdef __STDC_ISO_10646__
    PT_MAKE_STR(__STDC_ISO_10646__),
#endif

#ifdef __STDC_MB_MIGHT_NEQ_WC__
    PT_MAKE_STR(__STDC_MB_MIGHT_NEQ_WC__),
#endif

#ifdef __STDC_UTF_16__
    PT_MAKE_STR(__STDC_UTF_16__),
#endif

#ifdef __STDC_UTF_32__
    PT_MAKE_STR(__STDC_UTF_32__),
#endif

    /* [C11] 6.10.8.3 Conditional feature macros */
#ifdef __STDC_ANALYZABLE__
    PT_MAKE_STR(__STDC_ANALYZABLE__),
#endif

#ifdef __STDC_IEC_559__
    PT_MAKE_STR(__STDC_IEC_559__),
#endif

#ifdef __STDC_IEC_559_COMPLEX__
    PT_MAKE_STR(__STDC_IEC_559_COMPLEX__),
#endif

#ifdef __STDC_LIB_EXT1__
    PT_MAKE_STR(__STDC_LIB_EXT1__),
#endif

#ifdef __STDC_NO_ATOMICS__
    PT_MAKE_STR(__STDC_NO_ATOMICS__),
#endif

#ifdef __STDC_NO_COMPLEX__
    PT_MAKE_STR(__STDC_NO_COMPLEX__),
#endif

#ifdef __STDC_NO_THREADS__
    PT_MAKE_STR(__STDC_NO_THREADS__),
#endif

#ifdef __STDC_NO_VLA__
    PT_MAKE_STR(__STDC_NO_VLA__),
#endif

    /* [C++11] 16.8 Predefined macro names */
#ifdef __cplusplus
    PT_MAKE_STR(__cplusplus),
#endif

#ifdef __STDCPP_STRICT_POINTER_SAFETY__
    PT_MAKE_STR(__STDCPP_STRICT_POINTER_SAFETY__),
#endif

#ifdef __STDCPP_THREADS__
    PT_MAKE_STR(__STDCPP_THREADS__),
#endif

////////////////////////////////////////
#ifdef __OBJC__
    PT_MAKE_STR(__OBJC__),
#endif

#ifdef __ASSEMBLER__
    PT_MAKE_STR(__ASSEMBLER__),
#endif

#ifdef NDEBUG
    PT_MAKE_STR(NDEBUG),
#endif
};

/* Microsoft Visual C++. VC++ 2012 */
const MACRO_T g_vc[] =
{
    {"[Visual C++]", ""},

#ifdef _ATL_VER
    PT_MAKE_STR(_ATL_VER),
#endif

#ifdef _CHAR_UNSIGNED
    PT_MAKE_STR(_CHAR_UNSIGNED),
#endif

#ifdef __CLR_VER
    PT_MAKE_STR(__CLR_VER),
#endif

#ifdef __cplusplus_cli
    PT_MAKE_STR(__cplusplus_cli),
#endif

#ifdef __COUNTER__
    PT_MAKE_STR(__COUNTER__),
#endif

#ifdef __cplusplus
    PT_MAKE_STR(__cplusplus),
#endif

#ifdef _CPPRTTI
    PT_MAKE_STR(_CPPRTTI),
#endif

#ifdef _CPPUNWIND
    PT_MAKE_STR(_CPPUNWIND),
#endif

#ifdef _DEBUG
    #if (defined(__BORLANDC__))
    {"_DEBUG", "#"},
    #else
    PT_MAKE_STR(_DEBUG),
    #endif
#endif

#ifdef _DLL
    PT_MAKE_STR(_DLL),
#endif

#ifdef __FUNCDNAME__
    PT_MAKE_STR(__FUNCDNAME__),
#endif

#ifdef __FUNCSIG__
    PT_MAKE_STR(__FUNCSIG__),
#endif

#ifdef __FUNCTION__
    PT_MAKE_STR(__FUNCTION__),
#endif

#ifdef _INTEGRAL_MAX_BITS
    PT_MAKE_STR(_INTEGRAL_MAX_BITS),
#endif

#ifdef _M_ALPHA
    PT_MAKE_STR(_M_ALPHA),
#endif

#ifdef _M_AMD64
    PT_MAKE_STR(_M_AMD64),
#endif

#ifdef _M_CEE
    PT_MAKE_STR(_M_CEE),
#endif

#ifdef _M_CEE_PURE
    PT_MAKE_STR(_M_CEE_PURE),
#endif

#ifdef _M_CEE_SAFE
    PT_MAKE_STR(_M_CEE_SAFE),
#endif

#ifdef _M_IX86
    PT_MAKE_STR(_M_IX86),
#endif

#ifdef _M_IA64
    PT_MAKE_STR(_M_IA64),
#endif

#ifdef _M_IX86_FP
    PT_MAKE_STR(_M_IX86_FP),
#endif

#ifdef _M_MPPC
    PT_MAKE_STR(_M_MPPC),
#endif

#ifdef _M_MRX000
    PT_MAKE_STR(_M_MRX000),
#endif

#ifdef _M_PPC
    PT_MAKE_STR(_M_PPC),
#endif

#ifdef _M_X64
    PT_MAKE_STR(_M_X64),
#endif

#ifdef _MANAGED
    PT_MAKE_STR(_MANAGED),
#endif

#ifdef _MFC_VER
    PT_MAKE_STR(_MFC_VER),
#endif

#ifdef _MSC_BUILD
    PT_MAKE_STR(_MSC_BUILD),
#endif

#ifdef _MSC_EXTENSIONS
    PT_MAKE_STR(_MSC_EXTENSIONS),
#endif

#ifdef _MSC_FULL_VER
    PT_MAKE_STR(_MSC_FULL_VER),
#endif

#ifdef _MSC_VER
    PT_MAKE_STR(_MSC_VER),
#endif

#ifdef __MSVC_RUNTIME_CHECKS
    PT_MAKE_STR(__MSVC_RUNTIME_CHECKS),
#endif

#ifdef _MT
    PT_MAKE_STR(_MT),
#endif

#ifdef _NATIVE_WCHAR_T_DEFINED
    PT_MAKE_STR(_NATIVE_WCHAR_T_DEFINED),
#endif

#ifdef _OPENMP
    PT_MAKE_STR(_OPENMP),
#endif

#ifdef _VC_NODEFAULTLIB
    PT_MAKE_STR(_VC_NODEFAULTLIB),
#endif

#ifdef _WCHAR_T_DEFINED
    #if (defined(__BORLANDC__))
    {"_WCHAR_T_DEFINED", "#"},
    #else
    PT_MAKE_STR(_WCHAR_T_DEFINED),
    #endif
#endif

#ifdef _WIN32
    PT_MAKE_STR(_WIN32),
#endif

#ifdef _WIN64
    PT_MAKE_STR(_WIN64),
#endif

#ifdef _Wp64
    PT_MAKE_STR(_Wp64),
#endif

////////////////////////////////////////
#ifdef _POSIX_
    PT_MAKE_STR(_POSIX_),
#endif

#ifdef _CONSOLE
    PT_MAKE_STR(_CONSOLE),
#endif

#ifdef _MBCS
    PT_MAKE_STR(_MBCS),
#endif

#ifdef _UNICODE
    PT_MAKE_STR(_UNICODE),
#endif

#ifdef UNICODE
    PT_MAKE_STR(UNICODE),
#endif
};

/* Borland C++. C++ Builder 6.0 */
const MACRO_T g_borland[] =
{
    {"[Borland C++]", ""},
#ifdef __BCOPT__
    PT_MAKE_STR(__BCOPT__),
#endif

#ifdef __BCPLUSPLUS__
    PT_MAKE_STR(__BCPLUSPLUS__),
#endif

#ifdef __BORLANDC__
    PT_MAKE_STR(__BORLANDC__),
#endif

#ifdef __CDECL__
    PT_MAKE_STR(__CDECL__),
#endif

#ifdef _CHAR_UNSIGNED
    PT_MAKE_STR(_CHAR_UNSIGNED),
#endif

#ifdef __CODEGUARD__
    PT_MAKE_STR(__CODEGUARD__),
#endif

#ifdef __CONSOLE__
    PT_MAKE_STR(__CONSOLE__),
#endif

#ifdef _CPPUNWIND
    PT_MAKE_STR(_CPPUNWIND),
#endif

#ifdef __DLL__
    PT_MAKE_STR(__DLL__),
#endif

#ifdef __FLAT__
    PT_MAKE_STR(__FLAT__),
#endif

#ifdef __FUNC__
    PT_MAKE_STR(__FUNC__),
#endif

#ifdef _M_IX86
    PT_MAKE_STR(_M_IX86),
#endif

#ifdef __MT__
    PT_MAKE_STR(__MT__),
#endif

#ifdef __PASCAL__
    PT_MAKE_STR(__PASCAL__),
#endif

#ifdef __TCPLUSPLUS__
    PT_MAKE_STR(__TCPLUSPLUS__),
#endif

#ifdef __TEMPLATES__
    PT_MAKE_STR(__TEMPLATES__),
#endif

#ifdef __TLS__
    PT_MAKE_STR(__TLS__),
#endif

#ifdef __TURBOC__
    PT_MAKE_STR(__TURBOC__),
#endif

#ifdef _WCHAR_T
    #if (defined(__BORLANDC__))
    {"_WCHAR_T", "#"},
    #else
    PT_MAKE_STR(_WCHAR_T),
    #endif
#endif

#ifdef _WCHAR_T_DEFINED
    #if (defined(__BORLANDC__))
    {"_WCHAR_T_DEFINED", "#"},
    #else
    PT_MAKE_STR(_WCHAR_T_DEFINED),
    #endif
#endif

#ifdef _Windows
    PT_MAKE_STR(_Windows),
#endif

#ifdef __WIN32__
    PT_MAKE_STR(__WIN32__),
#endif

////////////////////////////////////////
#ifdef BCBVER1
    PT_MAKE_STR(BCBVER1),
#endif
};

/* Intel C++: Windows. Intel C++ Compiler XE 12.1. */
const MACRO_T g_intel_win[] =
{
    {"[Intel C++: Windows]", ""},

#ifdef __cilk
    PT_MAKE_STR(__cilk),
#endif

#ifdef __COUNTER__
    PT_MAKE_STR(__COUNTER__),
#endif

#ifdef __ECL
    PT_MAKE_STR(__ECL),
#endif

#ifdef __EDG__
    PT_MAKE_STR(__EDG__),
#endif

#ifdef __EDG_VERSION__
    PT_MAKE_STR(__EDG_VERSION__),
#endif

#ifdef _export
    PT_MAKE_STR(_export),
#endif

#ifdef __ICL
    PT_MAKE_STR(__ICL),
#endif

#ifdef _INC_STDIO
    #if (defined(__BORLANDC__))
    {"_INC_STDIO", "#"},
    #else
    PT_MAKE_STR(_INC_STDIO),
    #endif
#endif

#ifdef _INTEGRAL_MAX_BITS
    PT_MAKE_STR(_INTEGRAL_MAX_BITS),
#endif

#ifdef __INTEL_COMPILER
    PT_MAKE_STR(__INTEL_COMPILER),
#endif

#ifdef __INTEL_COMPILER_BUILD_DATE
    PT_MAKE_STR(__INTEL_COMPILER_BUILD_DATE),
#endif

#ifdef __INTEL_MS_COMPAT_LEVEL
    PT_MAKE_STR(__INTEL_MS_COMPAT_LEVEL),
#endif

#ifdef __LONG_DOUBLE_SIZE__
    PT_MAKE_STR(__LONG_DOUBLE_SIZE__),
#endif

#ifdef _M_AMD64
    PT_MAKE_STR(_M_AMD64),
#endif

#ifdef _M_IX86
    PT_MAKE_STR(_M_IX86),
#endif

#ifdef _M_IA64
    PT_MAKE_STR(_M_IA64),
#endif

#ifdef _M_X64
    PT_MAKE_STR(_M_X64),
#endif

#ifdef _MSC_EXTENSIONS
    PT_MAKE_STR(_MSC_EXTENSIONS),
#endif

#ifdef _MSC_FULL_VER
    PT_MAKE_STR(_MSC_FULL_VER),
#endif

#ifdef _MSC_VER
    PT_MAKE_STR(_MSC_VER),
#endif

#ifdef _MT
    PT_MAKE_STR(_MT),
#endif

#ifdef _OPENMP
    PT_MAKE_STR(_OPENMP),
#endif

#ifdef _PGO_INSTRUMENT
    PT_MAKE_STR(_PGO_INSTRUMENT),
#endif

#ifdef __QMSPP_
    PT_MAKE_STR(__QMSPP_),
#endif

#ifdef __SIGNED_CHARS__
    PT_MAKE_STR(__SIGNED_CHARS__),
#endif

#ifdef _SIZE_T_DEFINED
    #if (defined(__BORLANDC__))
    {"_SIZE_T_DEFINED", "#"},
    #else
    PT_MAKE_STR(_SIZE_T_DEFINED),
    #endif
#endif

#ifdef __STDC_VERSION__
    PT_MAKE_STR(__STDC_VERSION__),
#endif

#ifdef __w64
    PT_MAKE_STR(__w64),
#endif

#ifdef _WCHAR_T_DEFINED
    #if (defined(__BORLANDC__))
    {"_WCHAR_T_DEFINED", "#"},
    #else
    PT_MAKE_STR(_WCHAR_T_DEFINED),
    #endif
#endif

#ifdef _WCTYPE_T_DEFINED
    #if (defined(__BORLANDC__))
    {"_WCTYPE_T_DEFINED", "#"},
    #else
    PT_MAKE_STR(_WCTYPE_T_DEFINED),
    #endif
#endif

#ifdef _WIN32
    PT_MAKE_STR(_WIN32),
#endif

#ifdef _WIN64
    PT_MAKE_STR(_WIN64),
#endif

#ifdef _VA_LIST_DEFINED
    PT_MAKE_STR(_VA_LIST_DEFINED),
#endif

};

/* Intel C++: Linux. Intel C++ Compiler XE 12.1. */
const MACRO_T g_intel_linux[] =
{
    {"[Intel C++: Linux]", ""},

#ifdef __ARRAY_OPERATORS
    PT_MAKE_STR(__ARRAY_OPERATORS),
#endif

#ifdef __BASE_FILE__
    PT_MAKE_STR(__BASE_FILE__),
#endif

#ifdef _BOOL
    PT_MAKE_STR(_BOOL),
#endif

#ifdef __cilk
    PT_MAKE_STR(__cilk),
#endif

#ifdef __cplusplus
    PT_MAKE_STR(__cplusplus),
#endif

#ifdef __DEPRECATED
    PT_MAKE_STR(__DEPRECATED),
#endif

#ifdef __EDG__
    PT_MAKE_STR(__EDG__),
#endif

#ifdef __EDG_VERSION__
    PT_MAKE_STR(__EDG_VERSION__),
#endif

#ifdef __ELF__
    PT_MAKE_STR(__ELF__),
#endif

#ifdef __extension__
    PT_MAKE_STR(__extension__),
#endif

#ifdef __EXCEPTIONS
    PT_MAKE_STR(__EXCEPTIONS),
#endif

#ifdef __GNUC__
    PT_MAKE_STR(__GNUC__),
#endif

#ifdef __GNUG__
    PT_MAKE_STR(__GNUG__),
#endif

#ifdef __gnu_linux__
    PT_MAKE_STR(__gnu_linux__),
#endif

#ifdef __GNUC_MINOR__
    PT_MAKE_STR(__GNUC_MINOR__),
#endif

#ifdef __GNUC_PATCHLEVEL__
    PT_MAKE_STR(__GNUC_PATCHLEVEL__),
#endif

#ifdef __GXX_ABI_VERSION
    PT_MAKE_STR(__GXX_ABI_VERSION),
#endif

#ifdef __HONOR_STD
    PT_MAKE_STR(__HONOR_STD),
#endif

#ifdef __i386
    PT_MAKE_STR(__i386),
#endif

#ifdef __i386__
    PT_MAKE_STR(__i386__),
#endif

#ifdef i386
    PT_MAKE_STR(i386),
#endif

#ifdef __ICC
    PT_MAKE_STR(__ICC),
#endif

#ifdef __INTEL_COMPILER
    PT_MAKE_STR(__INTEL_COMPILER),
#endif

#ifdef __INTEL_COMPILER_BUILD_DATE
    PT_MAKE_STR(__INTEL_COMPILER_BUILD_DATE),
#endif

#ifdef __INTEL_RTTI__
    PT_MAKE_STR(__INTEL_RTTI__),
#endif

#ifdef __INTEL_STRICT_ANSI__
    PT_MAKE_STR(__INTEL_STRICT_ANSI__),
#endif

#ifdef __linux
    PT_MAKE_STR(__linux),
#endif

#ifdef __linux__
    PT_MAKE_STR(__linux__),
#endif

#ifdef linux
    PT_MAKE_STR(linux),
#endif

#ifdef __LONG_DOUBLE_SIZE__
    PT_MAKE_STR(__LONG_DOUBLE_SIZE__),
#endif

#ifdef __LONG_MAX__
    PT_MAKE_STR(__LONG_MAX__),
#endif

#ifdef __LP64__
    PT_MAKE_STR(__LP64__),
#endif

#ifdef _LP64
    PT_MAKE_STR(_LP64),
#endif

#ifdef _MT
    PT_MAKE_STR(_MT),
#endif

#ifdef __MMX__
    PT_MAKE_STR(__MMX__),
#endif

#ifdef __NO_INLINE__
    PT_MAKE_STR(__NO_INLINE__),
#endif

#ifdef __NO_MATH_INLINES
    PT_MAKE_STR(__NO_MATH_INLINES),
#endif

#ifdef __NO_STRING_INLINES
    PT_MAKE_STR(__NO_STRING_INLINES),
#endif

#ifdef _OPENMP
    PT_MAKE_STR(_OPENMP),
#endif

#ifdef __OPTIMIZE__
    PT_MAKE_STR(__OPTIMIZE__),
#endif

#ifdef __pentium4
    PT_MAKE_STR(__pentium4),
#endif

#ifdef __pentium4__
    PT_MAKE_STR(__pentium4__),
#endif

#ifdef __PIC__
    PT_MAKE_STR(__PIC__),
#endif

#ifdef __pic__
    PT_MAKE_STR(__pic__),
#endif

#ifdef _PGO_INSTRUMENT
    PT_MAKE_STR(_PGO_INSTRUMENT),
#endif

#ifdef _PLACEMENT_DELETE
    PT_MAKE_STR(_PLACEMENT_DELETE),
#endif

#ifdef __PTRDIFF_TYPE__
    PT_MAKE_STR(__PTRDIFF_TYPE__),
#endif

#ifdef __REGISTER_PREFIX__
    PT_MAKE_STR(__REGISTER_PREFIX__),
#endif

#ifdef __SIGNED_CHARS__
    PT_MAKE_STR(__SIGNED_CHARS__),
#endif

#ifdef __SIZE_TYPE__
    PT_MAKE_STR(__SIZE_TYPE__),
#endif

#ifdef __SSE__
    PT_MAKE_STR(__SSE__),
#endif

#ifdef __SSE2__
    PT_MAKE_STR(__SSE2__),
#endif

#ifdef __SSE3__
    PT_MAKE_STR(__SSE3__),
#endif

#ifdef __SSSE3__
    PT_MAKE_STR(__SSSE3__),
#endif

#ifdef __unix
    PT_MAKE_STR(__unix),
#endif

#ifdef __unix__
    PT_MAKE_STR(__unix__),
#endif

#ifdef unix
    PT_MAKE_STR(unix),
#endif

#ifdef __USER_LABEL_PREFIX__
    PT_MAKE_STR(__USER_LABEL_PREFIX__),
#endif

#ifdef __VERSION__
    PT_MAKE_STR(__VERSION__),
#endif

#ifdef __WCHAR_T
    PT_MAKE_STR(__WCHAR_T),
#endif

#ifdef __WCHAR_TYPE__
    PT_MAKE_STR(__WCHAR_TYPE__),
#endif

#ifdef __WINT_TYPE__
    PT_MAKE_STR(__WINT_TYPE__),
#endif

#ifdef __x86_64
    PT_MAKE_STR(__x86_64),
#endif

};

/* GCC */
const MACRO_T g_gcc[] =
{
    {"[GCC]", ""},

#ifdef __COUNTER__
    PT_MAKE_STR(__COUNTER__),
#endif

#ifdef __GFORTRAN__
    PT_MAKE_STR(__GFORTRAN__),
#endif

#ifdef __GNUC__
    PT_MAKE_STR(__GNUC__),
#endif

#ifdef __GNUC_MINOR__
    PT_MAKE_STR(__GNUC_MINOR__),
#endif

#ifdef __GNUC_PATCHLEVEL__
    PT_MAKE_STR(__GNUC_PATCHLEVEL__),
#endif

#ifdef __GNUG__
    PT_MAKE_STR(__GNUG__),
#endif

#ifdef __STRICT_ANSI__
    PT_MAKE_STR(__STRICT_ANSI__),
#endif

#ifdef __BASE_FILE__
    PT_MAKE_STR(__BASE_FILE__),
#endif

#ifdef __INCLUDE_LEVEL__
    PT_MAKE_STR(__INCLUDE_LEVEL__),
#endif

#ifdef __ELF__
    PT_MAKE_STR(__ELF__),
#endif

#ifdef __VERSION__
    PT_MAKE_STR(__VERSION__),
#endif

#ifdef __OPTIMIZE__
    PT_MAKE_STR(__OPTIMIZE__),
#endif

#ifdef __OPTIMIZE_SIZE__
    PT_MAKE_STR(__OPTIMIZE_SIZE__),
#endif

#ifdef __NO_INLINE__
    PT_MAKE_STR(__NO_INLINE__),
#endif

#ifdef __GNUC_GNU_INLINE__
    PT_MAKE_STR(__GNUC_GNU_INLINE__),
#endif

#ifdef __GNUC_STDC_INLINE__
    PT_MAKE_STR(__GNUC_STDC_INLINE__),
#endif

#ifdef __CHAR_UNSIGNED__
    PT_MAKE_STR(__CHAR_UNSIGNED__),
#endif

#ifdef __WCHAR_UNSIGNED__
    PT_MAKE_STR(__WCHAR_UNSIGNED__),
#endif

#ifdef __REGISTER_PREFIX__
    PT_MAKE_STR(__REGISTER_PREFIX__),
#endif

#ifdef __USER_LABEL_PREFIX__
    PT_MAKE_STR(__USER_LABEL_PREFIX__),
#endif

#ifdef __SIZE_TYPE__
    PT_MAKE_STR(__SIZE_TYPE__),
#endif

#ifdef __PTRDIFF_TYPE__
    PT_MAKE_STR(__PTRDIFF_TYPE__),
#endif

#ifdef __WCHAR_TYPE__
    PT_MAKE_STR(__WCHAR_TYPE__),
#endif

#ifdef __WINT_TYPE__
    PT_MAKE_STR(__WINT_TYPE__),
#endif

#ifdef __INTMAX_TYPE__
    PT_MAKE_STR(__INTMAX_TYPE__),
#endif

#ifdef __UINTMAX_TYPE__
    PT_MAKE_STR(__UINTMAX_TYPE__),
#endif

#ifdef __SIG_ATOMIC_TYPE__
    PT_MAKE_STR(__SIG_ATOMIC_TYPE__),
#endif

#ifdef __INT8_TYPE__
    PT_MAKE_STR(__INT8_TYPE__),
#endif

#ifdef __INT16_TYPE__
    PT_MAKE_STR(__INT16_TYPE__),
#endif

#ifdef __INT32_TYPE__
    PT_MAKE_STR(__INT32_TYPE__),
#endif

#ifdef __INT64_TYPE__
    PT_MAKE_STR(__INT64_TYPE__),
#endif

#ifdef __UINT8_TYPE__
    PT_MAKE_STR(__UINT8_TYPE__),
#endif

#ifdef __UINT16_TYPE__
    PT_MAKE_STR(__UINT16_TYPE__),
#endif

#ifdef __UINT32_TYPE__
    PT_MAKE_STR(__UINT32_TYPE__),
#endif

#ifdef __UINT64_TYPE__
    PT_MAKE_STR(__UINT64_TYPE__),
#endif

#ifdef __INT_LEAST8_TYPE__
    PT_MAKE_STR(__INT_LEAST8_TYPE__),
#endif

#ifdef __INT_LEAST16_TYPE__
    PT_MAKE_STR(__INT_LEAST16_TYPE__),
#endif

#ifdef __INT_LEAST32_TYPE__
    PT_MAKE_STR(__INT_LEAST32_TYPE__),
#endif

#ifdef __INT_LEAST64_TYPE__
    PT_MAKE_STR(__INT_LEAST64_TYPE__),
#endif

#ifdef __UINT_LEAST8_TYPE__
    PT_MAKE_STR(__UINT_LEAST8_TYPE__),
#endif

#ifdef __UINT_LEAST16_TYPE__
    PT_MAKE_STR(__UINT_LEAST16_TYPE__),
#endif

#ifdef __UINT_LEAST32_TYPE__
    PT_MAKE_STR(__UINT_LEAST32_TYPE__),
#endif

#ifdef __UINT_LEAST64_TYPE__
    PT_MAKE_STR(__UINT_LEAST64_TYPE__),
#endif

#ifdef __INT_FAST8_TYPE__
    PT_MAKE_STR(__INT_FAST8_TYPE__),
#endif

#ifdef __INT_FAST16_TYPE__
    PT_MAKE_STR(__INT_FAST16_TYPE__),
#endif

#ifdef __INT_FAST32_TYPE__
    PT_MAKE_STR(__INT_FAST32_TYPE__),
#endif

#ifdef __INT_FAST64_TYPE__
    PT_MAKE_STR(__INT_FAST64_TYPE__),
#endif

#ifdef __UINT_FAST8_TYPE__
    PT_MAKE_STR(__UINT_FAST8_TYPE__),
#endif

#ifdef __UINT_FAST16_TYPE__
    PT_MAKE_STR(__UINT_FAST16_TYPE__),
#endif

#ifdef __UINT_FAST32_TYPE__
    PT_MAKE_STR(__UINT_FAST32_TYPE__),
#endif

#ifdef __UINT_FAST64_TYPE__
    PT_MAKE_STR(__UINT_FAST64_TYPE__),
#endif

#ifdef __INTPTR_TYPE__
    PT_MAKE_STR(__INTPTR_TYPE__),
#endif

#ifdef __UINTPTR_TYPE__
    PT_MAKE_STR(__UINTPTR_TYPE__),
#endif

#ifdef __CHAR_BIT__
    PT_MAKE_STR(__CHAR_BIT__),
#endif

#ifdef __SCHAR_MAX__
    PT_MAKE_STR(__SCHAR_MAX__),
#endif

#ifdef __WCHAR_MAX__
    PT_MAKE_STR(__WCHAR_MAX__),
#endif

#ifdef __SHRT_MAX__
    PT_MAKE_STR(__SHRT_MAX__),
#endif

#ifdef __INT_MAX__
    PT_MAKE_STR(__INT_MAX__),
#endif

#ifdef __LONG_MAX__
    PT_MAKE_STR(__LONG_MAX__),
#endif

#ifdef __LONG_LONG_MAX__
    PT_MAKE_STR(__LONG_LONG_MAX__),
#endif

#ifdef __WINT_MAX__
    PT_MAKE_STR(__WINT_MAX__),
#endif

#ifdef __SIZE_MAX__
    PT_MAKE_STR(__SIZE_MAX__),
#endif

#ifdef __PTRDIFF_MAX__
    PT_MAKE_STR(__PTRDIFF_MAX__),
#endif

#ifdef __INTMAX_MAX__
    PT_MAKE_STR(__INTMAX_MAX__),
#endif

#ifdef __UINTMAX_MAX__
    PT_MAKE_STR(__UINTMAX_MAX__),
#endif

#ifdef __SIG_ATOMIC_MAX__
    PT_MAKE_STR(__SIG_ATOMIC_MAX__),
#endif

#ifdef __INT8_MAX__
    PT_MAKE_STR(__INT8_MAX__),
#endif

#ifdef __INT16_MAX__
    PT_MAKE_STR(__INT16_MAX__),
#endif

#ifdef __INT32_MAX__
    PT_MAKE_STR(__INT32_MAX__),
#endif

#ifdef __INT64_MAX__
    PT_MAKE_STR(__INT64_MAX__),
#endif

#ifdef __UINT8_MAX__
    PT_MAKE_STR(__UINT8_MAX__),
#endif

#ifdef __UINT16_MAX__
    PT_MAKE_STR(__UINT16_MAX__),
#endif

#ifdef __UINT32_MAX__
    PT_MAKE_STR(__UINT32_MAX__),
#endif

#ifdef __UINT64_MAX__
    PT_MAKE_STR(__UINT64_MAX__),
#endif

#ifdef __INT_LEAST8_MAX__
    PT_MAKE_STR(__INT_LEAST8_MAX__),
#endif

#ifdef __INT_LEAST16_MAX__
    PT_MAKE_STR(__INT_LEAST16_MAX__),
#endif

#ifdef __INT_LEAST32_MAX__
    PT_MAKE_STR(__INT_LEAST32_MAX__),
#endif

#ifdef __INT_LEAST64_MAX__
    PT_MAKE_STR(__INT_LEAST64_MAX__),
#endif

#ifdef __UINT_LEAST8_MAX__
    PT_MAKE_STR(__UINT_LEAST8_MAX__),
#endif

#ifdef __UINT_LEAST16_MAX__
    PT_MAKE_STR(__UINT_LEAST16_MAX__),
#endif

#ifdef __UINT_LEAST32_MAX__
    PT_MAKE_STR(__UINT_LEAST32_MAX__),
#endif

#ifdef __UINT_LEAST64_MAX__
    PT_MAKE_STR(__UINT_LEAST64_MAX__),
#endif

#ifdef __INT_FAST8_MAX__
    PT_MAKE_STR(__INT_FAST8_MAX__),
#endif

#ifdef __INT_FAST16_MAX__
    PT_MAKE_STR(__INT_FAST16_MAX__),
#endif

#ifdef __INT_FAST32_MAX__
    PT_MAKE_STR(__INT_FAST32_MAX__),
#endif

#ifdef __INT_FAST64_MAX__
    PT_MAKE_STR(__INT_FAST64_MAX__),
#endif

#ifdef __UINT_FAST8_MAX__
    PT_MAKE_STR(__UINT_FAST8_MAX__),
#endif

#ifdef __UINT_FAST16_MAX__
    PT_MAKE_STR(__UINT_FAST16_MAX__),
#endif

#ifdef __UINT_FAST32_MAX__
    PT_MAKE_STR(__UINT_FAST32_MAX__),
#endif

#ifdef __UINT_FAST64_MAX__
    PT_MAKE_STR(__UINT_FAST64_MAX__),
#endif

#ifdef __INTPTR_MAX__
    PT_MAKE_STR(__INTPTR_MAX__),
#endif

#ifdef __UINTPTR_MAX__
    PT_MAKE_STR(__UINTPTR_MAX__),
#endif

#ifdef __WCHAR_MIN__
    PT_MAKE_STR(__WCHAR_MIN__),
#endif

#ifdef __WINT_MIN__
    PT_MAKE_STR(__WINT_MIN__),
#endif

#ifdef __SIG_ATOMIC_MIN__
    PT_MAKE_STR(__SIG_ATOMIC_MIN__),
#endif

#ifdef __INT8_C
    PT_MAKE_STR(__INT8_C),
#endif

#ifdef __INT16_C
    PT_MAKE_STR(__INT16_C),
#endif

#ifdef __INT32_C
    PT_MAKE_STR(__INT32_C),
#endif

#ifdef __INT64_C
    PT_MAKE_STR(__INT64_C),
#endif

#ifdef __UINT8_C
    PT_MAKE_STR(__UINT8_C),
#endif

#ifdef __UINT16_C
    PT_MAKE_STR(__UINT16_C),
#endif

#ifdef __UINT32_C
    PT_MAKE_STR(__UINT32_C),
#endif

#ifdef __UINT64_C
    PT_MAKE_STR(__UINT64_C),
#endif

#ifdef __INTMAX_C
    PT_MAKE_STR(__INTMAX_C),
#endif

#ifdef __UINTMAX_C
    PT_MAKE_STR(__UINTMAX_C),
#endif

#ifdef __SIZEOF_INT__
    PT_MAKE_STR(__SIZEOF_INT__),
#endif

#ifdef __SIZEOF_LONG__
    PT_MAKE_STR(__SIZEOF_LONG__),
#endif

#ifdef __SIZEOF_LONG_LONG__
    PT_MAKE_STR(__SIZEOF_LONG_LONG__),
#endif

#ifdef __SIZEOF_SHORT__
    PT_MAKE_STR(__SIZEOF_SHORT__),
#endif

#ifdef __SIZEOF_POINTER__
    PT_MAKE_STR(__SIZEOF_POINTER__),
#endif

#ifdef __SIZEOF_FLOAT__
    PT_MAKE_STR(__SIZEOF_FLOAT__),
#endif

#ifdef __SIZEOF_DOUBLE__
    PT_MAKE_STR(__SIZEOF_DOUBLE__),
#endif

#ifdef __SIZEOF_LONG_DOUBLE__
    PT_MAKE_STR(__SIZEOF_LONG_DOUBLE__),
#endif

#ifdef __SIZEOF_SIZE_T__
    PT_MAKE_STR(__SIZEOF_SIZE_T__),
#endif

#ifdef __SIZEOF_WCHAR_T__
    PT_MAKE_STR(__SIZEOF_WCHAR_T__),
#endif

#ifdef __SIZEOF_WINT_T__
    PT_MAKE_STR(__SIZEOF_WINT_T__),
#endif

#ifdef __SIZEOF_PTRDIFF_T__
    PT_MAKE_STR(__SIZEOF_PTRDIFF_T__),
#endif

#ifdef __BYTE_ORDER__
    PT_MAKE_STR(__BYTE_ORDER__),
#endif

#ifdef __ORDER_LITTLE_ENDIAN__
    PT_MAKE_STR(__ORDER_LITTLE_ENDIAN__),
#endif

#ifdef __ORDER_BIG_ENDIAN__
    PT_MAKE_STR(__ORDER_BIG_ENDIAN__),
#endif

#ifdef __ORDER_PDP_ENDIAN__
    PT_MAKE_STR(__ORDER_PDP_ENDIAN__),
#endif

#ifdef __FLOAT_WORD_ORDER__
    PT_MAKE_STR(__FLOAT_WORD_ORDER__),
#endif

#ifdef __DEPRECATED
    PT_MAKE_STR(__DEPRECATED),
#endif

#ifdef __EXCEPTIONS
    PT_MAKE_STR(__EXCEPTIONS),
#endif

#ifdef __GXX_RTTI
    PT_MAKE_STR(__GXX_RTTI),
#endif

#ifdef __USING_SJLJ_EXCEPTIONS__
    PT_MAKE_STR(__USING_SJLJ_EXCEPTIONS__),
#endif

#ifdef __GXX_EXPERIMENTAL_CXX0X__
    PT_MAKE_STR(__GXX_EXPERIMENTAL_CXX0X__),
#endif

#ifdef __GXX_WEAK__
    PT_MAKE_STR(__GXX_WEAK__),
#endif

#ifdef __NEXT_RUNTIME__
    PT_MAKE_STR(__NEXT_RUNTIME__),
#endif

#ifdef __LP64__
    PT_MAKE_STR(__LP64__),
#endif

#ifdef _LP64
    PT_MAKE_STR(_LP64),
#endif

#ifdef __SSP__
    PT_MAKE_STR(__SSP__),
#endif

#ifdef __SSP_ALL__
    PT_MAKE_STR(__SSP_ALL__),
#endif

#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
    PT_MAKE_STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1),
#endif

#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
    PT_MAKE_STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2),
#endif

#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
    PT_MAKE_STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4),
#endif

#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
    PT_MAKE_STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8),
#endif

#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_16
    PT_MAKE_STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16),
#endif

#ifdef __GCC_HAVE_DWARF2_CFI_ASM
    PT_MAKE_STR(__GCC_HAVE_DWARF2_CFI_ASM),
#endif

#ifdef __FP_FAST_FMA
    PT_MAKE_STR(__FP_FAST_FMA),
#endif

#ifdef __FP_FAST_FMAF
    PT_MAKE_STR(__FP_FAST_FMAF),
#endif

#ifdef __FP_FAST_FMAL
    PT_MAKE_STR(__FP_FAST_FMAL),
#endif

////////////////////////////////////////
#ifdef __WORDSIZE
    PT_MAKE_STR(__WORDSIZE),
#endif
};

/* Other useful */
const MACRO_T g_others[] =
{
    {"[Other]", ""},

#ifdef _BSD_SOURCE
    PT_MAKE_STR( _BSD_SOURCE ),
#endif

#ifdef _POSIX_SOURCE
    PT_MAKE_STR( _POSIX_SOURCE ),
#endif

#ifdef _XOPEN_SOURCE
    PT_MAKE_STR( _XOPEN_SOURCE ),
#endif

#ifdef _GNU_SOURCE
    PT_MAKE_STR( _GNU_SOURCE ),
#endif

#ifdef __BIG_ENDIAN__
    PT_MAKE_STR( __BIG_ENDIAN__ ),
#endif

#ifdef __LITTLE_ENDIAN__
    PT_MAKE_STR( __LITTLE_ENDIAN__ ),
#endif
};

void print_MACRO_T(const MACRO_T* pArray, int cnt)
{
    int i;
    for( i = 0; i < cnt; ++i )
    {
        printf( "%s\t%s\n", pArray[i].name, pArray[i].value );
    }
    printf( "\n" );
}

int main( int argc, char *argv[])
{
    print_MACRO_T(g_compilers, sizeof(g_compilers)/sizeof(g_compilers[0]));
    print_MACRO_T(g_platforms, sizeof(g_platforms)/sizeof(g_platforms[0]));
    print_MACRO_T(g_stdc, sizeof(g_stdc)/sizeof(g_stdc[0]));
    print_MACRO_T(g_vc, sizeof(g_vc)/sizeof(g_vc[0]));
    print_MACRO_T(g_borland, sizeof(g_borland)/sizeof(g_borland[0]));
    print_MACRO_T(g_intel_win, sizeof(g_intel_win)/sizeof(g_intel_win[0]));
    print_MACRO_T(g_intel_linux, sizeof(g_intel_linux)/sizeof(g_intel_linux[0]));
    print_MACRO_T(g_gcc, sizeof(g_gcc)/sizeof(g_gcc[0]));
    print_MACRO_T(g_others, sizeof(g_others)/sizeof(g_others[0]));

    return 0;
}

```
 

在以下编译器中成功编译——
VC6
VC2003
VC2005
VC2010（x86与x64）
BCB6
GCC 4.7.0（Fedora 17）
GCC 4.6.2（MinGW (20120426)）




 

 

#参考文献
-------

[《ISO/IEC 9899:2011 - Information technology -- Programming languages -- C》. ISO/IEC, 2011.]( http://www.iso.org/iso/home/store/catalogue_tc/catalogue_detail.htm?csnumber=57853)

[《ISO/IEC 14882:2011 - Information technology -- Programming languages -- C++》. ISO/IEC, 2011. ](http://www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=50372)

[《[VS2012] Predefined Macros》. Microsoft, 2012.]( http://msdn.microsoft.com/en-us/library/b0084kay(v=vs.110).aspx)

[《[VS2012] 预定义的宏》. Microsoft, 2012. ](http://msdn.microsoft.com/zh-cn/library/b0084kay(v=vs.110).aspx)

[《[BCB6] C++Builder Language Guide》中的《Predefined macros》. Borland, 2002.

[《Intel® C++ Compiler XE 12.1 User and Reference Guides》（Windows版）中的《Additional Predefined Macros》. Intel, 2011.](http://software.intel.com/sites/products/documentation/hpc/composerxe/en-us/2011Update/cpp/win/index.htm)

[《Intel® C++ Compiler XE 12.1 User and Reference Guides》（Linux版）中的《Additional Predefined Macros》. Intel, 2011.](http://software.intel.com/sites/products/documentation/hpc/composerxe/en-us/2011Update/cpp/lin/index.htm)

[《[GCC] The C Preprocessor》中的《3.7.2 Common Predefined Macros》. GNU, 2011. ](http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html)

[《关于CPP的预定义宏：unix、linux、i386、i586，大家中过招吗？》. 太平绅士, 2009-02-10. ](http://bbs.chinaunix.net/thread-1366571-1-1.html)

[《C\C＋＋宏大全》.]( http://www.cnblogs.com/sevencat/archive/2004/06/10/14872.htm)

[《Useful GCC Macros》. OneSadCookie, 2007-07-12. ](http://blog.onesadcookie.com/2007/07/useful-gcc-macros.html)

[《[笔记] Intel C++编译器的预定义宏（Windows版、Linux版）》.](http://www.cnblogs.com/zyl910/archive/2012/07/06/intel_predefined_macros.html)

[Standard-Predefined-Macros](http://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html#Standard-Predefined-Macros)


[Common-Predefined-Macros](http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros)

[源码下载](http://files.cnblogs.com/zyl910/printmacro.rar)



