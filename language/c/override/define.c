struct s1
{
    int a;
    int b;

    double c;
};

struct s2
{
    double a;
    double b;
};

void gcc_overload_s1(struct s1 s)
{
    printf("Got a struct s1: %d %d %f\n", s.a, s.b, s.c);
}

void gcc_overload_s2(struct s2 s)
{
    printf("Got a struct s2: %f %f\n", s.a, s.b);
}

// warning: dereferencing type-punned pointer will break strict-aliasing rules
#define gcc_overload(A)\
    __builtin_choose_expr(__builtin_types_compatible_p(typeof(A), struct s1),\
        gcc_overload_s1(*(struct s1 *)&A),\
    __builtin_choose_expr(__builtin_types_compatible_p(typeof(A), struct s2),\
        gcc_overload_s2(*(struct s2 *)&A),(void)0))


int main(void)
{

    struct s1 s11 = {1};
    gcc_overload(s11);

    struct s1 s12 = {1, 2};
    gcc_overload(s12);

    struct s1 s13 = {1, 2, 3};
    gcc_overload(s13);


    struct s2 s2= {3.14, 3.14};
    gcc_overload(s2);

}
