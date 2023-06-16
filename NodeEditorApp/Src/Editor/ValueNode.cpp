#include "Stdafx.h"
#include "ValueNode.h"
#include "DmGraphicsSocketItem.h"
#include "NodeFactory.h"

IMPL_NODE_INFO_BEGIN(DmGraphicsValueNodeItem)
	__name("Value"),
	__desc("Use to display dynamic creation of an object"),
	__icon(":/Resource/Icon/value.svg"),
	__type(NodeType_ValueNode)
IMPL_NODE_INFO_END()

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

#if 1 // 以下为测试代码，注释这段代码，观察效果

class DmGraphicsIntegerValueNodeItem : public DmGraphicsValueNodeItem
{
	using Self = DmGraphicsIntegerValueNodeItem;

	DECL_NODE_INFO(DmGraphicsIntegerValueNodeItem);

public:
	// virtual int type() const override { return NodeType_IntegerNode; }
};

IMPL_NODE_INFO_BEGIN(DmGraphicsIntegerValueNodeItem)
	__name("Integer"),
	__desc("Test DSL"),
	__icon(":/Resource/Icon/value.svg"),
	__type(NodeType_IntegerNode)
IMPL_NODE_INFO_END()

#endif