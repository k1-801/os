#include "../include/Syslog.hpp"

const char* logs[MAX_LOG];
int lnum=0;
void log(const char *str)
{
	logs[lnum++]=str;
}