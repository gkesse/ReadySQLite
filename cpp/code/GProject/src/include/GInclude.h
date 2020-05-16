//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__unix)
//===============================================
#define _D_GNU_SOURCE
#define _USE_MATH_DEFINES
//===============================================
#include <iostream> 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <ctime>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
//===============================================
#define _GUSE_SQLITE_ON_
//===============================================
#if defined(_GUSE_SQLITE_ON_)
#include <sqlite3.h>
#endif
//===============================================
#endif
//===============================================
#if defined(__WIN32)
//===============================================
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <ctime>
//===============================================
using namespace std;
//===============================================
#endif
//===============================================
#include "GStruct.h"
//===============================================
#endif
//===============================================
