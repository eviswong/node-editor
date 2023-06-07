#pragma once
#include <QSettings>

#define SINGLETON(className)\
public:\
	static className& GetInstance() {\
		static className config;\
		return config;\
	}\
private:


class Config :QObject
{
	SINGLETON(Config);

	Q_OBJECT
public:
	/*!
	 * @brief 从配置文件中读出所有配置项的值，加载到当前类中
	 */
	void LoadConfigurations();

	/*!
	 * @brief 把当前类中的所有配置项存入配置文件
	 */
	void SaveConfigurations();

public:
	Q_PROPERTY(QSize WindowSize MEMBER windowSize)
	QSize windowSize;

	Q_PROPERTY(QPoint WindowPos MEMBER windowPos)
	QPoint windowPos;

	Q_PROPERTY(bool ItemSnapping MEMBER itemSnapping)
	bool itemSnapping;
};


