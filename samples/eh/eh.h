
#ifdef __cplusplus
extern "C"  {
#endif

typedef int (*exc_fun)();

int exc_wrapper(exc_fun);
int exc_throw(void);

#ifdef __cplusplus
}
#endif
