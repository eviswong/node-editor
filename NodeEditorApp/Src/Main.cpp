#include "Stdafx.h"
#include "App/MainWindow.h"
#include "Base/Environment.h"
#include "Base/Config.h"
#include "App/Application.h"
#include "App/Logger.h"
#include "Utility/Assert.h"
#include "Editor/NodeFactory.h"

#include "Editor/ValueNode.h"

QString s_applicationName = "Node Editor";


int main(int argc, char* argv[])
{
	/* 注册 assertion 回调, 此处可以选用 Assertion 模块内置的默认回调 */
	Assertion::InstallAssertHandler(Assertion::DefaultAssertionHandler);

	Application app(argc, argv);

	/* 加载应用程序环境 */
	Environment::Initialize();

	/* 加载应用程序配置 */
	Config::LoadConfigurations();
	 
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

	NodeFactory::RegisterNodeInfo(DmGraphicsValueNodeItem::GetNodeMetaStatic());

	NodeFactory::RegisterNodeInfo(DmGraphicsIntegerValueNodeItem::GetNodeMetaStatic());

	/* 创建主窗口 */
	MainWindow mainWindow;
	mainWindow.show();
	 
	return app.exec();
}
