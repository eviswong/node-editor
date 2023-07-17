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
		MsgContainer& msgContainer = GetMessageContainer();
		ui.logOutputEdit->clear();
		msgContainer.clear();
	});

	connect(ui.logLevelCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(OnLogLevelFilterChanged(int)));
}

void LoggerWindow::Information(const QString& message) {
	WriteToBuffer(message, Verbosity_Information);
	PutMessage(Verbosity_Information, message);
}

void LoggerWindow::Warning(const QString& message) {
	WriteToBuffer(message, Verbosity_Warning);
	PutMessage(Verbosity_Warning, message);
}

void LoggerWindow::Critical(const QString& message) {
	WriteToBuffer(message, Verbosity_Critical);
	PutMessage(Verbosity_Critical, message);
}

void LoggerWindow::WriteToBuffer(const QString& message, Verbosity verbosity)
{
	MsgContainer& msgContainer = GetMessageContainer();

	msgContainer.emplace_back(verbosity, message);
}

void LoggerWindow::FlushBuffer()
{
	MsgContainer& msgContainer = GetMessageContainer();

	std::for_each(msgContainer.begin(), msgContainer.end(),
		[this](Message& msg)
		{
			PutMessage(msg.verbosity, msg.content);
		}
	);
}

void LoggerWindow::PutMessage(Verbosity verbosity, const QString& message)
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
			__make_sure(false, "unknown log verbosity");
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

	MsgContainer& msgContainer = GetMessageContainer();

	if (index != 0)
	{
		Verbosity verbosity = (Verbosity)index;

		std::for_each(msgContainer.begin(), msgContainer.end(), 
			[verbosity, this](Message& msg)
			{
				if (msg.verbosity == verbosity)
				{
					PutMessage(msg.verbosity, msg.content);
				}
			}
		);
	}
	else
	{
		FlushBuffer();
	}
}
