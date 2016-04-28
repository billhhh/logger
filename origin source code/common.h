#ifndef COMMON
#define COMMON

#include <stdint.h>
#include <vector>
#include <string>
using namespace std;

#include "../util/mutex.h"

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

extern Mutex userDBLock;

template<typename T> std::string itoa(T num);

string getTimeNow();

string getHostName();


//替换指定的子串
string replaceALL(const char* src, const string& target,const string& subs); 

//指定分隔符分割字符串
vector<string> split(const string& src,const string& delimiter);

#endif