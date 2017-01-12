﻿#ifndef __ASSERT_H__
#define __ASSERT_H__
#include "common.h"
#include "log.h"
#include <string>

BEGIN_NS
#define ASSERT(cond) ((!(cond)) ? Assert::assert(#cond, __FILE__, __LINE__) : Assert::noop())
#define LOG_ASSERT(cond) ((!(cond)) ? Assert::log_assert(#cond, __FILE__, __LINE__) : Assert::noop())
#define LOG_ASSERT_MSG(cond, msg) ((!(cond)) ? Assert::log_assert(#cond, msg, __FILE__, __LINE__) : Assert::noop())
#ifdef assert(x)
#undef assert(x)
#endif
class Assert
{
public:
	static void noop();
	static void assert(const char *assertion, const char *file, int line);
	static void log_assert(const char *assertion, const char *file, int line);
	static void log_assert(const char *assertion, const char* msg, const char *file, int line);
	static void log_assert(const char *assertion, const std::string& msg, const char *file, int line);
};

#ifdef USE_OPENGL
#define ASSERT_GL() ASSERT(glGetError() == GL_NO_ERROR)
#define CHECK_GL_LOC(i) ASSERT(i != -1) 
#else
#define ASSERT_GL()
#define CHECK_GL_LOC(i)
#endif
END_NS
#endif