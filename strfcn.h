#ifndef __STRFCN_H
#define __STRFCN_H
#include "graphics.h"
#include <stdarg.h>
int atoi(char* string)
{
 int self = 0;
 int mult = 10;
 bool negative = false;
 int values[strlen(string)];
 int count = 0;
 for( int id = 0; id < strlen(string); id++ )
 {
  if( string[id] == '-' ) negative = true;
  for( char ch = '0'; ch <= '9'; ch++ )
   if( string[id] == ch )
    values[count++] = (int)( (int)ch - (int)'0' );
 };
 self = values[count - 1];
 for( int id = 0; id < count - 1; id++ ) mult = mult * 10;
 for( int id = 0; id < count - 1; id++ )
 { 
  mult = mult / 10;
  self = self + ( values[id] * mult );
 };
 if( negative == true ) 
  return -self;
 else
  return self;
};
 char* reverse(char* s)
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
     return s;
 }
char* itoa(int n)
 {
     char* s;
     int i, sign;
 
     if ((sign = n) < 0)  /* çàïèñûâàåì çíàê */
         n = -n;          /* äåëàåì n ïîëîæèòåëüíûì ÷èñëîì */
     i = 0;
     do {       /* ãåíåðèðóåì öèôðû â îáðàòíîì ïîðÿäêå */
         s[i++] = n % 10 + '0';   /* áåðåì ñëåäóþùóþ öèôðó */
     } while ((n /= 10) > 0);     /* óäàëÿåì */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     char * ret = reverse(s);
     //ret[0]=' ';
     return ret;
 }
int sprintf(char *str,const char *fmt, ...)
{
	va_list arg;
	va_start(arg,fmt);
	int i=0,j=0;
	int num=0;
	for(num=0; num<strlen(fmt); num++)
	{
		switch(fmt[num+1])
		{
			case '%': switch(num){
				case 's': { char *s = va_arg(arg,char*); for(; i < strlen(s); i++,num++) str[num+i]=s[i]; break; }
				case 'd': {char *iVal=itoa(va_arg(arg,int)); for(; i < strlen(iVal); j++,num++) str[num+j]=iVal[j]; break;}}break;
			default: str[num]=fmt[num];
		}
	}
	va_end(arg);
	return num;
}
char *strcpy(char *s,char *t)
{
	while(*s++ = *t++)
	;
	return s;
}
char *strcat(char *s, char *t)
{
	return strcpy(s+strlen(s),t);
}
#endif
