#pragma once


class Environment
{
public:
	static Environment& GetInstance() {
		static Environment singleton;
		return singleton;
	}

	void Initialize() {
		static const QString configFileFolder = "/Config/";

		static const QString styleSheetPath = "/Qss/Stylesheet.css";

		m_configFileDir = QApplication::applicationDirPath() + configFileFolder;

		m_styleSheetPath = QApplication::applicationDirPath() + styleSheetPath;
	}

	/* Read only property */
	const QString GetConfigFileDir() const { return m_configFileDir; }

	const QString GetStyleSheetPath() const { return m_styleSheetPath; }

private:
	Environment() = default;

	QString m_configFileDir;
	QString m_styleSheetPath;
};