/*
*
* function: 日志 dll API
*
* Date:2016-04-28
*
*    Author: Bill Wang
*/

#ifndef _LOGGER_API_H_
#define _LOGGER_API_H_

#include "logger.h"

#define WH_DLL_EXPORTS
#ifdef WH_DLL_EXPORTS
#define WH_DLL_API __declspec(dllexport) //导出
#else
#define WH_DLL_API __declspec(dllimport) //导入
#endif

extern "C"
{

	WH_DLL_API void api_InitLogger(const std::string& info_log_filename,
		const std::string& warn_log_filename,
		const std::string& error_log_filename,
		bool isAppend = true);

	WH_DLL_API std::ostream& api_WriteLogger(log_rank_t rank, const std::string reason);

	WH_DLL_API void echoTest(); //echo测试
}

#endif