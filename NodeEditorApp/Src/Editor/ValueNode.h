#pragma once
#include "DmGraphicsNode.h"




class DmGraphicsSocketItem;
class DmGraphicsValueNodeItem : public DmGraphicsNodeItem
{
	using Self = DmGraphicsValueNodeItem;

	__node_item()
public:
	explicit DmGraphicsValueNodeItem(QGraphicsItem* parent = Q_NULLPTR);

	virtual int type() const override { return NodeType_ValueNode; }

private:
	void CalculateNodeRect();
	void AdjustSocketPosition();

private:
	DmGraphicsSocketItem* m_socketItem;
	QGraphicsProxyWidget* m_inputWidget;
	QFont m_captionFont;

	int m_widgetWidth{ 0 };
	int m_widgetHeight{ 0 };

	int m_value{ 0 };

};


class DmGraphicsIntegerValueNodeItem : public DmGraphicsValueNodeItem
{
	using Self = DmGraphicsIntegerValueNodeItem;

	__node_item()
public:
	virtual int type() const override { return NodeType_IntegerNode; }
};
