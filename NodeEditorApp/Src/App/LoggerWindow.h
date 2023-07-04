#pragma once

#include <QWidget>
#include "ui_LoggerWindow.h"
#include "App/Logger.h"

class LoggerWindow : public QWidget
{
	Q_OBJECT
	using Self = LoggerWindow;
public:
	LoggerWindow(QWidget *parent = nullptr);
	~LoggerWindow() {};

	void Information(const QString& message);
	void Warning(const QString& message);
	void Critical(const QString& message);
	void WriteToBuffer(const QString& message, Verbosity verbosity);
	void FlushBuffer();

private:
	static std::list<Message>& GetMessageContainer() 
	{
		static std::list<Message> s_messageContainer;
		return s_messageContainer;
	}

	void PutMessage(Verbosity verbosity, const QString& message);
	void MakeConnections();

private slots:
	void OnLogLevelFilterChanged(int index);

private:
	Ui::LoggerWindowClass ui;
};
