#include "Stdafx.h"
#include "App/MainWindow.h"
#include "Base/Environment.h"
#include "Base/Config.h"
#include "App/LoggerWindow.h"
#include "App/Application.h"



int main(int argc, char* argv[])
{
	Application app(argc, argv);

	/* ����Ӧ�ó��򻷾� */
	Environment::GetInstance().Initialize();

	/* ����Ӧ�ó������� */
	Config::GetInstance().LoadConfigurations();

	/* QSS */
	app.LoadStyleSheet();

	/* ���������� */
	MainWindow mainWindow;
	mainWindow.show();

	/* һ����Ϻ��� logger ���� ����ʼ���ɹ���һ�������� ����Ϣ */
	/* �ҵ���־���ڣ� ����дһ����Ϣ */
	LoggerWindow* loggerWindow = mainWindow.findChild<LoggerWindow*>("LoggerWindowClass");
	if (loggerWindow)
	{
		loggerWindow->Information("Initialize application successfully. Everything is OK.");
		loggerWindow->Warning("There is a test warning message.");
		loggerWindow->Critical("There is a test critical message.");
	}

	return app.exec();
}


