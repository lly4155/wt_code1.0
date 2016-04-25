//#ifdef _DO_NOT_HAVE_S
#include "macro.h"
#ifdef LINUX

int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format ,...)
{
    va_list ap;
    va_start(ap, format);
    int res = vsprintf(buffer, format, ap);
    va_end(ap);
    return res;
}
#endif
