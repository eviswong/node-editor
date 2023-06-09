#include "Stdafx.h"
#include "Logger.h"
#include "LoggerWindow.h"
#include "Utility/Assert.h"

LoggerWindow* MessageWritter::s_loggerWindow{ nullptr };

void MessageWritter::InstallMessageWriter(LoggerWindow* loggerWindow)
{
	s_loggerWindow = loggerWindow;
}

void MessageWritter::Information(const QString& message)
{
	// 判断当前是否存在 logger window。 如果存在，直接输出到窗口，否则装入消息容器。
	if (s_loggerWindow != nullptr)
	{
		s_loggerWindow->Information(message);
	} 
	else
	{
		s_loggerWindow->WriteToBuffer(message, Verbosity_Information);
	}
}

void MessageWritter::Warning(const QString& message)
{
	if (s_loggerWindow != nullptr)
	{
		s_loggerWindow->Warning(message);
	}
	else
	{
		s_loggerWindow->WriteToBuffer(message, Verbosity_Warning);
	}
}

void MessageWritter::Critical(const QString& message)
{
	if (s_loggerWindow != nullptr)
	{
		s_loggerWindow->Critical(message);
	}
	else
	{
		s_loggerWindow->WriteToBuffer(message, Verbosity_Critical);
	}
}