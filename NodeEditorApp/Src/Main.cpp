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
	/* ע�� assertion �ص�, �˴�����ѡ�� Assertion ģ�����õ�Ĭ�ϻص� */
	Assertion::InstallAssertHandler(Assertion::DefaultAssertionHandler);

#if 0 // Assertion ģ�������
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

	/* ����Ӧ�ó��򻷾� */
	Environment::GetInstance().Initialize();

	/* ����Ӧ�ó������� */
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

	/* ���������� */
	MainWindow mainWindow;
	mainWindow.show();
	 
	return app.exec();
}
