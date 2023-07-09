#pragma once

enum Verbosity {
	Verbosity_Information = 1,
	Verbosity_Warning,
	Verbosity_Critical
};

struct Message {
	Verbosity verbosity;
	QString   content;

	Message(Verbosity inVerbosity, const QString& content)
	{
		verbosity = inVerbosity;
		this->content = content;
	}
};


class LoggerWindow;

class MessageWritter
{
public:
	/*!
	 * @brief 注册消息显示控件 
	 * @param loggerWindow 
 	 */
	static void InstallMessageWriter(LoggerWindow* loggerWindow);

	static void Information(const QString& message);

	static void Warning(const QString& message);

	static void Critical(const QString& message);

private:
	static LoggerWindow* s_loggerWindow;
};