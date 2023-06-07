#include "Stdafx.h"
#include "App/MainWindow.h"
#include "Base/Environment.h"
#include "Base/Config.h"
#include "App/LoggerWindow.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	/* 加载应用程序环境 */
	Environment::GetInstance().Initialize();

	/* 加载应用程序配置 */
	Config::GetInstance().LoadConfigurations();

	/* 创建主窗口 */
	MainWindow mainWindow;
	mainWindow.show();

	/* 一切完毕后，向 logger 发送 “初始化成功，一切正常” 的消息 */
	/* 找到日志窗口， 向它写一条消息 */
	LoggerWindow* loggerWindow = mainWindow.findChild<LoggerWindow*>("LoggerWindowClass");
	if (loggerWindow)
	{
		loggerWindow->Information("Initialize application successfully. Everything is OK.");
		loggerWindow->Warning("There is a test warning message.");
		loggerWindow->Critical("There is a test critical message.");
	}

	return app.exec();
}


