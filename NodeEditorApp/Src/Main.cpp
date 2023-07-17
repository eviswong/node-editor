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
	/* ע�� assertion �ص�, �˴�����ѡ�� Assertion ģ�����õ�Ĭ�ϻص� */
	Assertion::InstallAssertHandler(Assertion::DefaultAssertionHandler);

	Application app(argc, argv);

	/* ����Ӧ�ó��򻷾� */
	Environment::Initialize();

	/* ����Ӧ�ó������� */
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

	/* ���������� */
	MainWindow mainWindow;
	mainWindow.show();
	 
	return app.exec();
}
