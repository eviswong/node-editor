#pragma once

#include <QWidget>
#include "ui_LoggerWindow.h"

enum Verbosity {
	Verbosity_Information = 1,
	Verbosity_Warning,
	Verbosity_Critical
}; 

struct LogEntry {
	Verbosity verbosity;
	QString   message;

	LogEntry(Verbosity inVerbosity, const QString& inMessage)
	{
		verbosity = inVerbosity;
		message = inMessage;
	}
}; 

class LoggerWindow : public QWidget
{
	Q_OBJECT
	using Self = LoggerWindow;
public:
	LoggerWindow(QWidget *parent = nullptr);
	~LoggerWindow() {};

	void Information(const QString& message) {
		m_logEntry.emplace_back(Verbosity_Information, message);
		putMessage(Verbosity_Information, message);
	}

	void Warning(const QString& message) {
		m_logEntry.emplace_back(Verbosity_Warning, message);
		putMessage(Verbosity_Warning, message);
	}

	void Critical(const QString& message) {
		m_logEntry.emplace_back(Verbosity_Critical, message);
		putMessage(Verbosity_Critical, message);
	}

private:
	void putMessage(Verbosity verbosity, const QString& message);

private:
	void MakeConnections();

private slots:
	void OnLogLevelFilterChanged(int index);

private:
	Ui::LoggerWindowClass ui;

	std::list<LogEntry> m_logEntry;
};
