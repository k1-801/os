#ifndef __KLOG_H
#define __KLOG_H
#define MAX_LOG 2048
const char* logs[MAX_LOG];
int lnum=0;
void log(const char *str)
{
	logs[lnum++]=str;
	
}
#endif
