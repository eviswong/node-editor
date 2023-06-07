#include "Stdafx.h"
#include "ValueNode.h"
#include "DmGraphicsSocketItem.h"

DmGraphicsValueNodeItem::DmGraphicsValueNodeItem(QGraphicsItem* parent)
	: DmGraphicsNodeItem(parent)
{
	__super::setToolTip(m_variableName);

	m_socketItem = new DmGraphicsSocketItem(this);

	m_captionFont = QFont("Consolas", 16);

	QLineEdit* lineEdit = new QLineEdit();
	lineEdit->setFont(m_captionFont);
	lineEdit->setStyleSheet("background: #FF212121; color:#FFfafafa");

	m_inputWidget = new QGraphicsProxyWidget(this);
	m_inputWidget->setWidget(lineEdit);

	CalculateNodeRect();
	AdjustSocketPosition();
}

void DmGraphicsValueNodeItem::CalculateNodeRect()
{
	QFontMetrics metric(m_captionFont);

	m_widgetWidth = 140;
	m_widgetHeight = 40;

	m_rect.setWidth(m_widgetWidth + m_roundedRectRadius * 2 + 15);
	m_rect.setHeight(m_widgetHeight + m_roundedRectRadius * 2);

	m_inputWidget->setGeometry(QRectF((float)m_roundedRectRadius, (float)m_roundedRectRadius, m_widgetWidth, m_widgetHeight));
}

void DmGraphicsValueNodeItem::AdjustSocketPosition()
{
	QPoint socketPos(m_rect.width(), m_rect.height() / 2);
	m_socketItem->setPos(socketPos);
}