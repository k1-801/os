#ifndef __ASSERT_H
#define __ASSERT_H
#include "panic.h"
#include "strfcn.h"
#include "klog.h"
#include "zbase.h"
int oldline;
char *oldfile;
#define assert(check) oldline=__LINE__; oldfile=__FILE__; do { if(!(check)) _assertionFailed(check); panic("Assertion failed.");} while(0)
#define _assertionFailed(check) drawAFailedWnd();
void drawAFailedWnd()
{
	window afailed(400,50,100,120,"OS365 Internal Error","");
	drawObj(afailed);
	char *asserterr;
	strcat(asserterr,"Assertion failed at line ");
	strcat(asserterr,itoa(oldline));
	strcat(asserterr,", file ");
	strcat(asserterr,__FILE__);
	strcat(asserterr,". Aborting.");
	vgaWriteStr(afailed.x+5,afailed.y+21,asserterr,MAGENTA,LIGHT_GREY);
}
#endif
