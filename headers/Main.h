#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <memory>
#include <experimental/filesystem>
#include <shellapi.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>

#pragma comment(lib,  "winmm.lib")
#pragma comment(lib,  "ws2_32.lib")

#include    <winuser.h>
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#define WHEEL_DELTA   120
#endif

//#include <sciter-x.h>
#include <sciter-win-main.cpp>

using namespace std;
namespace fs = std::experimental::filesystem;

#include <WUtils.h>
