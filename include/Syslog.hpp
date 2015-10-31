#pragma once

#ifndef SYSLOG_HPP
#define SYSLOG_HPP

#include "HCL/Std.hpp"

// TODO: Rewrite

#define MAX_LOG 2048
extern const char* logs[MAX_LOG];
extern int lnum;
void log(const char *str);

#endif // SYSLOG_HPP