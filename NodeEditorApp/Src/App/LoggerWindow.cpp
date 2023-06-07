#include "stdafx.h"
#include "LoggerWindow.h"
#include "Utility/Assert.h"

LoggerWindow::LoggerWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.logLevelCombo->addItem("All");
	ui.logLevelCombo->addItem("Information");
	ui.logLevelCombo->addItem("Warning");
	ui.logLevelCombo->addItem("Critical");

	Self::MakeConnections();
}

void LoggerWindow::MakeConnections()
{
	connect(ui.clearBtn, &QPushButton::clicked, [this]() {
		ui.logOutputEdit->clear();
		m_logEntry.clear();
	});

	connect(ui.logLevelCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(OnLogLevelFilterChanged(int)));
}

void LoggerWindow::putMessage(Verbosity verbosity, const QString& message)
{
	Qt::GlobalColor textColor = Qt::black;
	QString verbosityStr;

	switch (verbosity)
	{
		case Verbosity_Critical:
		{
			textColor = Qt::red;
			verbosityStr = "Critical";
		}
		break;
		
		case Verbosity_Warning:
		{
			textColor = Qt::yellow;
			verbosityStr = "Warning";
		}
		break;

		case Verbosity_Information:
		{
			textColor = Qt::green;
			verbosityStr = "Info";
		}
		break;

		default:
		{
			ASSERT(false && "Unknown log verbosity");

		}
		break;
	}

	QDateTime currentTime = QDateTime::currentDateTime();
	QString currentTimeStr = currentTime.toString("hh:mm:ss");


	ui.logOutputEdit->setTextColor(textColor);

	QString outputMessage = QString("[%0][%1]: %2").arg(currentTimeStr).arg(verbosityStr).arg(message);

	ui.logOutputEdit->append(outputMessage);

}

void LoggerWindow::OnLogLevelFilterChanged(int index)
{
	ui.logOutputEdit->clear();

	if (index != 0)
	{
		Verbosity verbosity = (Verbosity)index;

		for (auto iter = m_logEntry.begin(); iter != m_logEntry.end(); iter++) {
			if (iter->verbosity == verbosity)
			{
				putMessage(iter->verbosity, iter->message);
			}
		}
	}
	else
	{
		for (auto iter = m_logEntry.begin(); iter != m_logEntry.end(); iter++)
		{
			putMessage(iter->verbosity, iter->message);
		}
	}
}
