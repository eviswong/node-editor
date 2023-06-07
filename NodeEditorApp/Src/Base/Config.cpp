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

	// QVariant: ɶ���ܴ�

#if 0
	windowSize = settings.value("app/windowSize", QSize(1440, 900)).toSize();
	windowPos = settings.value("app/windowPos", QPoint(50, 50)).toPoint();
#endif
	// ��ȡ��ǰ�����Ϣ���м��� data member ֮���)
	const QMetaObject* metaObject = this->metaObject();

	/* ��ȡ��ǰ property �ĸ��� */
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("app");

	for (int i = 0; i < propertyCount; i++)
	{
		// ����ȡ�� data member
		QMetaProperty property = metaObject->property(i);

		// ��ȡ����
		QString propertyName = property.name();

		// �������������ļ��������� �ҵ��󣬶�ȡ������ֵ�� data member
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

	// QVariant: ɶ���ܴ�
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
 * @brief �������ļ��ж��������������ֵ�����ص���ǰ����
 */
void Config::LoadConfigurations()
{
	QString configFileDir = Environment::GetInstance().GetConfigFileDir();
	QString configFilePath = configFileDir + g_configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// ��ȡ��ǰ�����Ϣ���м��� data member ֮���)
	const QMetaObject* metaObject = this->metaObject();

	/* ��ȡ��ǰ property �ĸ��� */
	int propertyCount = metaObject->propertyCount();

	settings.beginGroup("App");

	for (int i = 0; i < propertyCount; i++)
	{
		// ����ȡ�� data member
		QMetaProperty property = metaObject->property(i);

		// ��ȡ����
		QString propertyName = property.name();

		// �������������ļ��������� �ҵ��󣬶�ȡ������ֵ�� data member
		QVariant peopertyValue = settings.value(propertyName);
		property.write(this, peopertyValue);
	}

	settings.endGroup();
}

/*!
 * @brief �ѵ�ǰ���е�������������������ļ�
 */
void Config::SaveConfigurations()
{
	QString configFileDir = Environment::GetInstance().GetConfigFileDir();
	QString configFilePath = configFileDir + g_configFileName;

	QSettings settings(configFilePath, QSettings::IniFormat);

	// QVariant: ɶ���ܴ�
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

