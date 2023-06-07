#pragma once


class Environment
{
public:
	static Environment& GetInstance() {
		static Environment singleton;
		return singleton;
	}

	void Initialize() {
		const QString configFileFolder = "/Config/";

		m_configFileDir = QApplication::applicationDirPath() + configFileFolder;
	}

	/* Read only property */
	const QString GetConfigFileDir() const { return m_configFileDir; }

private:
	Environment() = default;

	QString m_configFileDir;
};