#pragma once
#include <iostream>

#ifndef NDEBUG
	#define LOG(x) { std::cout << x << std::endl; }
	#define NDEBUG false
#else
	#define LOG(x) { }
#endif