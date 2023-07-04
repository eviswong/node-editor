#include "Stdafx.h"
#include "Application.h"
#include "Base/Environment.h"

bool Application::LoadStyleSheet()
{
	const QString styleSheetPath = Environment::GetInstance().GetStyleSheetPath();

	QFile styleSheetFile(styleSheetPath);

	QString qssBuffer;

	bool tryOpenFileResult = styleSheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if (tryOpenFileResult)
	{
		QTextStream ss(&styleSheetFile);
		qssBuffer = ss.readAll();
		styleSheetFile.close();

		Super::setStyleSheet(qssBuffer);
	}

	return tryOpenFileResult;
}