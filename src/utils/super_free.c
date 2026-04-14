#include <stdarg.h>
#include <stdlib.h>

void super_free(int nb, ...)
{
    va_list ap;

    va_start(ap, nb);
    while (nb != 0) {
        void *ptr = va_arg(ap, void*);
        if (ptr)
            free(ptr);
        nb--;
    }
    va_end(ap);
}
