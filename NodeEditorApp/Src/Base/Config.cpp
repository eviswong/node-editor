#include "Stdafx.h"
#include "Config.h"
#include "Environment.h"
#include <QMetaProperty>

const static QString g_configFileName = "Config.ini";

#if 0

void Config::LoadAllProperties()
{
	const QString configFileDir = Environment::GetInstance().configDir;

	QString configFilePath = configFileDir + configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// QVariant: 啥都能存

#if 0
	windowSize = settings.value("app/windowSize", QSize(1440, 900)).toSize();
	windowPos = settings.value("app/windowPos", QPoint(50, 50)).toPoint();
#endif
	// 获取当前类的信息（有几个 data member 之类的)
	const QMetaObject* metaObject = this->metaObject();

	/* 获取当前 property 的个数 */
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("app");

	for (int i = 0; i < propertyCount; i++)
	{
		// 依次取出 data member
		QMetaProperty property = metaObject->property(i);

		// 获取名字
		QString propertyName = property.name();

		// 按名字在配置文件中搜索， 找到后，读取，并赋值给 data member
		QVariant peopertyValue = settings.value(propertyName);
		property.write(this, peopertyValue);
	}

	settings.endGroup();

	// for (DataMember : All DataMembers) 
	// { settings.value("DataMember.name", DataMember.value); }
}

void Config::SaveAllProperties()
{
	const QString configFileDir = Environment::GetInstance().configDir;

	QString configFilePath = configFileDir + configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// QVariant: 啥都能存
	const QMetaObject* metaObject = this->metaObject();
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("app");

	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty property = metaObject->property(i);
		QString propertyName = property.name();
		settings.setValue(propertyName, property.read(this));
	}

	settings.endGroup();
#if 0
	settings.setValue("app/windowSize", windowSize);
	settings.setValue("app/windowPos", windowPos);
#endif
}
#endif

/*!
 * @brief 从配置文件中读出所有配置项的值，加载到当前类中
 */
void Config::LoadConfigurations()
{
	QString configFileDir = Environment::GetInstance().GetConfigFileDir();
	QString configFilePath = configFileDir + g_configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// 获取当前类的信息（有几个 data member 之类的)
	const QMetaObject* metaObject = this->metaObject();

	/* 获取当前 property 的个数 */
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("App");

	for (int i = 0; i < propertyCount; i++)
	{
		// 依次取出 data member
		QMetaProperty property = metaObject->property(i);

		// 获取名字
		QString propertyName = property.name();

		// 按名字在配置文件中搜索， 找到后，读取，并赋值给 data member
		QVariant peopertyValue = settings.value(propertyName);
		property.write(this, peopertyValue);
	}

	settings.endGroup();
}

/*!
 * @brief 把当前类中的所有配置项存入配置文件
 */
void Config::SaveConfigurations()
{
	QString configFileDir = Environment::GetInstance().GetConfigFileDir();
	QString configFilePath = configFileDir + g_configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// QVariant: 啥都能存
	const QMetaObject* metaObject = this->metaObject();
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("App");

	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty property = metaObject->property(i);
		QString propertyName = property.name();
		settings.setValue(propertyName, property.read(this));
	}

	settings.endGroup();
}

