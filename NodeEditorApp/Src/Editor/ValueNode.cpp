#include "Stdafx.h"
#include "ValueNode.h"
#include "DmGraphicsSocketItem.h"
#include "NodeFactory.h"

#if 0
__impl_node_info_begin(DmGraphicsValueNodeItem)
__name("Value"),
__desc("Use to display dynamic creation of an object"),
__icon(":/Resource/Icon/value.svg"),
__type(NodeType_ValueNode)
__impl_node_info_end()
#endif


NodeMeta DmGraphicsValueNodeItem::s_nodeMeta = 
{
	"DmGraphicsValueNodeItem",
	"Value",
	"Use to display dynamic creation of an object",
	":/Resource/Icon/value.svg",
	NodeType_ValueNode,
	[]() -> DmGraphicsNodeItem* {return new DmGraphicsValueNodeItem(); }
};

DmGraphicsValueNodeItem::DmGraphicsValueNodeItem(QGraphicsItem* parent)
	: DmGraphicsNodeItem(parent)
{
	m_widgetWidth = 140;
	m_widgetHeight = 40;

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

	m_rect.setWidth(m_widgetWidth + m_roundedRectRadius * 2 + 15);
	m_rect.setHeight(m_widgetHeight + m_roundedRectRadius * 2);

	m_inputWidget->setGeometry(QRectF((float)m_roundedRectRadius, (float)m_roundedRectRadius, m_widgetWidth, m_widgetHeight));
}

void DmGraphicsValueNodeItem::AdjustSocketPosition()
{
	QPoint socketPos(m_rect.width(), m_rect.height() / 2);
	m_socketItem->setPos(socketPos);
}

#if 1




NodeMeta DmGraphicsIntegerValueNodeItem::s_nodeMeta =
{
	"DmGraphicsIntegerValueNodeItem",
	"Integer",
	"Use to test node registry.",
	":/Resource/Icon/value.svg",
	NodeType_IntegerNode,
	[]() -> DmGraphicsNodeItem* {return new DmGraphicsIntegerValueNodeItem(); }
};

#endif