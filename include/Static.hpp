#pragma once

#ifndef STATIC_HPP_INCLUDED
#define STATIC_HPP_INCLUDED

#include "HCL/Std.hpp"

extern const char *roundLT;
extern const char *roundRT;
extern const char *roundLB;
extern const char *roundRB;

extern const char *roundLT_1;
extern const char *roundRT_1;
extern const char *roundLB_1;
extern const char *roundRB_1;

extern const char* scancode;

extern uint8_t PAL16[48];

// Horizontal
extern uint8_t tbl_hor_txt40 [12];
extern uint8_t tbl_hor_txt80 [12];
extern uint8_t tbl_hor_txt90 [12];

extern uint8_t tbl_hor_gra640[12];
extern uint8_t tbl_hor_gra720[12];
extern uint8_t tbl_hor_gra320[12];
extern uint8_t tbl_hor_gra360[12];

// Vertical
extern uint8_t tbl_ver_txt20_12[9];
extern uint8_t tbl_ver_txt25_8 [9];
extern uint8_t tbl_ver_txt25_14[9];
extern uint8_t tbl_ver_txt25_16[9];
extern uint8_t tbl_ver_txt30_8 [9];
extern uint8_t tbl_ver_txt30_16[9];
extern uint8_t tbl_ver_txt40_12[9];
extern uint8_t tbl_ver_txt50_8 [9];
extern uint8_t tbl_ver_txt60_8 [9];

extern uint8_t tbl_ver_gra200  [9];
extern uint8_t tbl_ver_gra240  [9];
extern uint8_t tbl_ver_gra350  [9];
extern uint8_t tbl_ver_gra400  [9];
extern uint8_t tbl_ver_gra480  [9];

extern uint8_t tbl_mod_txt8p  [3];
extern uint8_t tbl_mod_txt9p  [3];
extern uint8_t tbl_mod_gra16c [3];
extern uint8_t tbl_mod_gra256c[3];

#endif // STATIC_HPP_INCLUDED