#ifndef __KLOG_H
#define __KLOG_H
#define MAX_LOG 2048
char *logs[MAX_LOG];
int lnum=0;
void log(char *str)
{
	logs[lnum++]=str;
	
}
#endif
