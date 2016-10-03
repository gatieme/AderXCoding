int add(const int a, const int b);

#ifdef __cplusplus
extern "C"
{
#endif

int call_cpp_add(const int a, const int b)
{
    return add(a, b);
}

#ifdef __cplusplus
}
#endif
