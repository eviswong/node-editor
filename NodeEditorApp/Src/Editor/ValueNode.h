#pragma once
#include "DmGraphicsNode.h"




class DmGraphicsSocketItem;
class DmGraphicsValueNodeItem : public DmGraphicsNodeItem
{
	using Self = DmGraphicsValueNodeItem;

	DECL_NODE_INFO(DmGraphicsValueNodeItem);

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



