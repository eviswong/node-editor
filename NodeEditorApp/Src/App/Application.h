#pragma once

class Application : public QApplication
{
public:
	using Super = QApplication;

	Application(int& argc, char** argv)
		: QApplication(argc, argv)
	{

	}

	bool LoadStyleSheet();
};