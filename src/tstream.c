#include "../include/tstream.h"

int16_t ts_getc(tstream* ts)
{
    if(ts && ts->getc)
        return ts->getc(ts);
    return -1;
}

int16_t ts_putc(tstream* ts, char c)
{
    if(ts && ts->putc)
        return ts->putc(ts, c);
    return -1;
}

int64_t ts_gets(tstream* ts,       char* str, uint64_t len)
{
    if(ts)
        if(ts->gets)
            return ts->gets(ts, str, len);
        else
            if(ts->getc)
            {
                ts->gets = &ts_gets_default;
                return ts->gets(ts, str, len);
            }
    return -1;
}

int64_t ts_puts(tstream* ts, const char* str, uint64_t len)
{
    if(ts)
        if(ts->puts)
            return ts->puts(ts, str, len);
        else
            if(ts->putc)
            {
                ts->puts = &ts_puts_default;
                return ts->puts(ts, str, len);
            }
    return -1;
}

int64_t ts_size(tstream* ts)
{
    if(ts && ts->size)
        return ts->size(ts);
    return -1;
}

int64_t ts_pos(tstream* ts)
{
    if(ts && ts->pos)
        return ts->pos(ts);
    return -1;
}

int64_t ts_seek(tstream* ts, int64_t off, uint8_t mode)
{
    if(ts)
        if(ts->seek)
            return ts->seek(ts, off, mode);
    return -1;
}

int8_t ts_close(tstream* ts)
{
    if(ts && ts->close)
        return ts->close(ts);
    return 0;
}

int64_t ts_gets_default(tstream* ts, char* str, uint64_t len)
{
    if(!ts || !ts->getc)
        return -1;
    uint64_t i;
    int16_t t;
    for(i = 0; i < len - 1; ++i)
    {
        t = ts->getc(ts);
        if(t == -1 || t == '\n' || t == '\0')
            break;
        *(str + i) = (char)(t);
    }
    *(str + i) = '\0';
    return i + 1;
}

int64_t ts_puts_default(tstream* ts, const char* str, uint64_t len)
{
    if(!ts || !ts->getc)
        return -1;
    uint64_t i;
    for(i = 0; i < len; ++i)
        if(ts->putc(ts, *(str + i)) == -1)
            break;
    return i;
}
