//#include "loggerAPI.h"
//#include "logger.h"
#include<Windows.h>
#include<iostream>
#include<string>

using namespace std;

typedef enum log_rank {
	_INFO,
	_WARNING,
	_ERROR,
	_FATAL
}log_rank_t;

typedef void (*API_INITLOGGER)(const std::string& info_log_filename,
	const std::string& warn_log_filename,
	const std::string& error_log_filename,
	bool isAppend);

typedef std::ostream& (*API_WRITELOGGER)(log_rank_t rank, const std::string reason);
typedef void (*API_ECHOTEST)();

int main(int argc, char *argv[])
{
	HMODULE hm = ::LoadLibrary(TEXT("logger.dll"));
	//如果Dll加载失败，释放它占用的资源  
	if (hm == NULL) {
		cout << "hm is null" << endl;
		::FreeLibrary(hm);
		return 0;
	}

	API_ECHOTEST main_EchoTest = (API_ECHOTEST)::GetProcAddress(hm, "echoTest");
	if (main_EchoTest == NULL) {
		cout << "main_EchoTest is null" << endl;
		::FreeLibrary(hm);
	}
	main_EchoTest();

	API_INITLOGGER main_API_InitLogger = (API_INITLOGGER)::GetProcAddress(hm, "api_InitLogger");
	main_API_InitLogger("whInfolog.txt", "whWarnlog.txt", "whErrolog.txt", false);//初始化日志文件

	API_WRITELOGGER main_API_WriteLogger = (API_WRITELOGGER)::GetProcAddress(hm, "api_WriteLogger");
	main_API_WriteLogger(_INFO, "first log");
	
	::FreeLibrary(hm);

	return 0;
}