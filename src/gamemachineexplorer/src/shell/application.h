﻿#ifndef __SHELL_GMEAPPLICATION_H__
#define __SHELL_GMEAPPLICATION_H__
#include <gmecommon.h>
#include <QApplication>

namespace shell
{
	class Application : public QApplication
	{
		Q_OBJECT

	public:
		using QApplication::QApplication;
	};
}

#endif