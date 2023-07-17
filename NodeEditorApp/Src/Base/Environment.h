#pragma once


class Environment
{
public:
	static Environment& GetInstance() {
		static Environment singleton;
		return singleton;
	}

	static void Initialize() {
		Environment& e = GetInstance();

		static const QString configFileFolder = "/Config/";

		static const QString styleSheetPath = "/Qss/Stylesheet.css";

		e.m_configFileDir = QApplication::applicationDirPath() + configFileFolder;

		e.m_styleSheetPath = QApplication::applicationDirPath() + styleSheetPath;
	}

	/* Read only property */
	const QString GetConfigFileDir() const { return m_configFileDir; }

	const QString GetStyleSheetPath() const { return m_styleSheetPath; }

private:
	Environment() = default;

	QString m_configFileDir;
	QString m_styleSheetPath;
};