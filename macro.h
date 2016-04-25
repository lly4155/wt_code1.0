#define LINUX
#ifdef LINUX

//#define sprintf_s(buffer,size,format, ...) sprintf(buffer,format,__VA_ARGS__)
#include <stdio.h>
#include <stdarg.h>
#include<sys/stat.h>

int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format ,...);    //这个比较特殊，需要真的去实现
	
	#define memcpy_s(dest,num,src,count) memcpy(dest,src,count)
	#define fprintf_s fprintf
	#define _strdate_s(buf,num) _strdate(buf)
	#define strcat_s(dest,num,src) strcat(dest,src)
	#define fopen_s(pf,name,mode) *pf=fopen(name,mode)
	#define strncpy_s(dest,num,src,count) strncpy(dest,src,count)
	#define localtime_s(tm,time) *tm=*localtime(time)
	#define _strdup strdup
	//#else
	#define  _mkdir(pathname) mkdir(pathname,S_IRWXU|S_IRWXG | S_IROTH | S_IXOTH)

#endif
