#include "../logger/logger.h"

int main(int argc, char *argv[])
{
	initLogger("whInfolog.txt", "whWarnlog.txt", "whErrolog.txt", false);//初始化日志文件
	
	LOG2(_INFO,"first log");
	
	return 0;
}