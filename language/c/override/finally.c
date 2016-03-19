#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void va_overload2(int p1, int p2)
{
    printf("va_overload2 %d %d\n", p1, p2);
}

void va_overload3(int p1, int p2, int p3)
{
    printf("va_overload3 %d %d %d\n", p1, p2, p3);
}

static void va_overload(int p1, int p2, ...)
{
    if (p2 == 7)
    {
        va_list v;
        va_start(v, p2);

        int p3 = va_arg(v, int);
        va_end(v);
        va_overload3(p1, p2, p3);

        return;
    }

    va_overload2(p1, p2);
}

static void print_nt_strings(const char *s, ...)
{
    va_list v;
    va_start(v, s);

    /* Stop on NULL */
    while (s)
    {
        printf("%s", s);

        /* Grab next parameter */
        s = va_arg(v, const char *);
    }

    va_end(v);
}


#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
#define COUNT_PARMS(...)\
    COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

static void print_strings2(int count, ...)
{
    int i;

    va_list v;
    va_start(v, count);

    for (i = 0; i < count; i++)
    {
        /* Grab next parameter + print it */
        const char *s = va_arg(v, const char *);
        printf("%s", s);
    }

    va_end(v);
}

#define print_strings(...)\
    print_strings2(COUNT_PARMS(__VA_ARGS__), __VA_ARGS__)

void count_overload1(int p1)
{
    printf("One param: %d\n", p1);
}

void count_overload2(double *p1, const char *p2)
{
    printf("Two params: %p (%f) %s\n", p1, *p1, p2);
}

void count_overload3(int p1, int p2, int p3)
{
    printf("Three params: %c %d %d\n", p1, p2, p3);
}

void count_overload_aux(int count, ...)
{
    va_list v;
    va_start(v, count);

    switch(count)
    {
        case 1:
        {
            int p1 = va_arg(v, int);
            count_overload1(p1);
            break;
        }

        case 2:
        {
            double *p1 = va_arg(v, double *);
            const char *p2 = va_arg(v, const char *);
            count_overload2(p1, p2);
            break;
        }

        case 3:
        {
            int p1 = va_arg(v, int);
            int p2 = va_arg(v, int);
            int p3 = va_arg(v, int);
            count_overload3(p1, p2, p3);
            break;
        }

        default:
        {
            va_end(v);

            printf("Invalid arguments to function 'count_overload()'");
            exit(1);
        }
    }

    va_end(v);
}
#define count_overload(...)\
    count_overload_aux(COUNT_PARMS(__VA_ARGS__), __VA_ARGS__)


void cpp_overload1(int p1)
{
    printf("CPP One param: %d\n", p1);
}

void cpp_overload2(double *p1, const char *p2)
{
    printf("CPP Two params: %p (%f) %s\n", p1, *p1, p2);
}

void cpp_overload3(int p1, int p2, int p3)
{
    printf("CPP Three params: %c %d %d\n", p1, p2, p3);
}

#define CAT(A, B) CAT2(A, B)
#define CAT2(A, B) A ## B

#define cpp_overload(...)\
    CAT(cpp_overload, COUNT_PARMS(__VA_ARGS__))(__VA_ARGS__)


#define cpp_default1(A) cpp_default2(A, "default string")

void cpp_default2(int x, const char *s)
{
    printf("Got %d %s\n", x, s);
}

#define cpp_default(...)\
    CAT(cpp_default, COUNT_PARMS(__VA_ARGS__))(__VA_ARGS__)

void sizeof_overload_float(float f)
{
    printf("Got float %f\n", f);
}

void sizeof_overload_double(double d)
{
    printf("Got double %f\n", d);
}

void sizeof_overload_longdouble(long double ld)
{
    printf("Got long double %Lf\n", ld);
}

#define sizeof_overload(A)\
    ((sizeof(A) == sizeof(float))?sizeof_overload_float(A):\
    (sizeof(A) == sizeof(double))?sizeof_overload_double(A):\
    (sizeof(A) == sizeof(long double))?sizeof_overload_longdouble(A):(void)0)

struct s1
{
    int a;
    int b;

    double c;
};

struct s2
{
    long long a;
    long long b;
};

void gcc_overload_s1(struct s1 s)
{
    printf("Got a struct s1: %d %d %f\n", s.a, s.b, s.c);
}

void gcc_overload_s2(struct s2 s)
{
    printf("Got a struct s2: %lld %lld\n", s.a, s.b);
}

// warning: dereferencing type-punned pointer will break strict-aliasing rules
#define gcc_overload(A)\
    __builtin_choose_expr(__builtin_types_compatible_p(typeof(A), struct s1),\
        gcc_overload_s1(*(struct s1 *)&A),\
    __builtin_choose_expr(__builtin_types_compatible_p(typeof(A), struct s2),\
        gcc_overload_s2(*(struct s2 *)&A),(void)0))


void gcc_type_overload_aux(int typeval, ...)
{
    switch(typeval)
    {
        case 1:
        {
            va_list v;
            va_start(v, typeval);

            struct s1 s = va_arg(v, struct s1);

            va_end(v);

            gcc_overload_s1(s);

            break;
        }

        case 2:
        {
            va_list v;
            va_start(v, typeval);

            struct s2 s = va_arg(v, struct s2);

            va_end(v);

            gcc_overload_s2(s);

            break;
        }

        default:
        {
            printf("Invalid type to 'gcc_type_overload()'\n");
            exit(1);
        }
    }
}

#define gcc_type_overload(A)\
    gcc_type_overload_aux(\
        __builtin_types_compatible_p(typeof(A), struct s1) * 1\
        + __builtin_types_compatible_p(typeof(A), struct s2) * 2\
        , A)


void print_type(int t, va_list *v)
{
    switch(t)
    {
        case 1:
        {
            int p = va_arg(*v, int);

            printf("int :%d\n", p);
            break;
        }

        case 2:
        {
            long long p = va_arg(*v, long long);

            printf("long long :%lld\n", p);
            break;
        }

        case 3:
        {
            double p = va_arg(*v, double);

            printf("double :%f\n", p);
            break;
        }

        case 4:
        {
            long double p = va_arg(*v, long double);

            printf("long double :%Lf\n", p);
            break;
        }

        default:
        {
            printf("Unknown type\n");
            exit(1);
        }
    }
}


void param_lister1_aux(int t1, ...)
{
    va_list v;
    va_start(v, t1);

    printf("1st param:");
    print_type(t1, &v);

    va_end(v);
}

void param_lister2_aux(int t1, ...)
{
    int t2;
    va_list v;
    va_start(v, t1);

    printf("1st param:");
    print_type(t1, &v);

    t2 = va_arg(v, int);
    printf("2nd param:");
    print_type(t2, &v);

    va_end(v);
}

void param_lister3_aux(int t1, ...)
{
    int t2, t3;
    va_list v;
    va_start(v, t1);

    printf("1st param:");
    print_type(t1, &v);

    t2 = va_arg(v, int);
    printf("2nd param:");
    print_type(t2, &v);

    t3 = va_arg(v, int);
    printf("3rd param:");
    print_type(t3, &v);

    va_end(v);
}

void param_lister4_aux(int t1, ...)
{
    int t2, t3, t4;
    va_list v;
    va_start(v, t1);

    printf("1st param:");
    print_type(t1, &v);

    t2 = va_arg(v, int);
    printf("2nd param:");
    print_type(t2, &v);

    t3 = va_arg(v, int);
    printf("3rd param:");
    print_type(t3, &v);

    t4 = va_arg(v, int);
    printf("4th param:");
    print_type(t4, &v);

    va_end(v);
}

#define TYPENUM(A)\
        __builtin_types_compatible_p(typeof(A), int) * 1\
        + __builtin_types_compatible_p(typeof(A), long long) * 2\
        + __builtin_types_compatible_p(typeof(A), double) * 3\
        + __builtin_types_compatible_p(typeof(A), long double) * 4

#define param_lister1(A)\
    param_lister1_aux(TYPENUM(A), A)

#define param_lister2(A, B)\
    param_lister2_aux(TYPENUM(A), A, TYPENUM(B), B)

#define param_lister3(A, B, C)\
    param_lister3_aux(TYPENUM(A), A, TYPENUM(B), B, TYPENUM(C), C)

#define param_lister4(A, B, C, D)\
    param_lister4_aux(TYPENUM(A), A, TYPENUM(B), B, TYPENUM(C), C, TYPENUM(D), D)


#define param_lister(...)\
    CAT(param_lister, COUNT_PARMS(__VA_ARGS__))(__VA_ARGS__)


int main()
{
    param_lister(1);
    param_lister(1, 2.0, 3, 6.0);
    return 0;
}
