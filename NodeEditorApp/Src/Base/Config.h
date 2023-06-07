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
	 * @brief �������ļ��ж��������������ֵ�����ص���ǰ����
	 */
	void LoadConfigurations();

	/*!
	 * @brief �ѵ�ǰ���е�������������������ļ�
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


