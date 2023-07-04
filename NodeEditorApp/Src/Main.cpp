#include "Stdafx.h"
#include "App/MainWindow.h"
#include "Base/Environment.h"
#include "Base/Config.h"
#include "App/Application.h"
#include "App/Logger.h"


int main(int argc, char* argv[])
{
	Application app(argc, argv);


	/* 加载应用程序环境 */
	Environment::GetInstance().Initialize();

	/* 加载应用程序配置 */
	Config::GetInstance().LoadConfigurations();

	/* QSS */
	bool loadQssSuccessfully = app.LoadStyleSheet();
	if (!loadQssSuccessfully)
	{
		MessageWritter::Warning("Fail to load qss file.");
	} 
	else
	{
		MessageWritter::Information("Load qss file successfully.");
	}

	/* 创建主窗口 */
	MainWindow mainWindow;
	mainWindow.show();
	 
	return app.exec();
}
