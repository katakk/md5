
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define u_int64_t unsigned long long
#define u_int32_t unsigned long
#define u_int16_t unsigned short
#define u_int8_t unsigned char
#define u_char unsigned char
#define explicit_bzero(_x,_z) memset((_x), 0, (_z));
#define DEF_WEAK(x)
#include "md5.h"

#include "md5_1.11.c"
//#include "md5_1.10.c"
//#include "md5_1.9.c"
//#include "md5_1.8.c"
//#include "md5_1.7.c"
//#include "md5_1.6.c"
//#include "md5_1.5.c"
//#include "md5_1.4.c"
//#include "md5_1.3.c"
//#include "md5_1.2.c"
//#include "md5_1.1.c"

