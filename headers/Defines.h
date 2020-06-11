#pragma once

// C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
// A function is declared using exception specification, which Visual C++ accepts but does not implement
#pragma warning( disable : 4290 )

//C4996	'localtime': This function or variable may be unsafe. Consider using localtime_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
