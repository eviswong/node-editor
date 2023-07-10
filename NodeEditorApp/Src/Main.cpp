#include "Stdafx.h"
#include "App/MainWindow.h"
#include "Base/Environment.h"
#include "Base/Config.h"
#include "App/Application.h"
#include "App/Logger.h"
#include "Utility/Assert.h"

QString s_applicationName = "Node Editor";


int main(int argc, char* argv[])
{
	/* 注册 assertion 回调, 此处可以选用 Assertion 模块内置的默认回调 */
	Assertion::InstallAssertHandler(Assertion::DefaultAssertionHandler);

#if 0 // Assertion 模块的用例
	int* ptr = nullptr;

	int ret = Assertion(__FILE__, __FUNCTION__, __LINE__).CheckPointer("nullptr", ptr);
	if (ret == 1)
	{
		_CrtDbgBreak();
		std::abort();
	}
#endif

#if 0
	int* ptr = nullptr;
	__check_pointer(ptr);
#endif

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
