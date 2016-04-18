// ascii_win.h
// Written by      "Lennox" Shou Hao Ho     
// https://ca.linkedin.com/in/lennoxho
// February 2016

#pragma once

#if (_MSC_VER < 1800)
#error C++11 or higher required.
#endif

#include <Windows.h>
#include <gdiplus.h>

#include <iostream>
#include <tchar.h>
#include <fstream>
#include <string>
#include <unordered_map>

#ifdef _DEBUG
#include <vld.h>
#endif

#define E_TEMP 1
#define E_BAD_FILENAME E_TEMP
#define E_BAD_ARGS E_TEMP