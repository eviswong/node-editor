#pragma once
#include <QObject>
#include <QGraphicsItem>

enum NodeType {
	NodeType_Node = 0x1000, // 4096 ¸ö
	NodeType_ValueNode,     // 0x1000  + 1 
};

class DmGraphicsNodeItem;

class NodePainter
{
public:
	NodePainter(DmGraphicsNodeItem* nodeItem);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	DmGraphicsNodeItem* m_nodeItem{nullptr};

	QPen m_penDefault;
	QPen m_penSelected;
	QPen m_penHovered;

	QBrush brushTitle;
	QBrush brushBackground;
};


class DmGraphicsNodeItem : public QGraphicsItem
{
	using Super = QGraphicsItem;
	using Self = DmGraphicsNodeItem;

	friend class NodePainter;
public:
	explicit DmGraphicsNodeItem(QGraphicsItem* parent = Q_NULLPTR);

	virtual QRectF boundingRect() const override 
	{ return m_rect; }

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;
	virtual int type() const override { return NodeType_Node; }
protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	bool OnSelected();
	bool OnUnSelected();

protected:
	QRectF m_rect {0, 0, 300, 300};
	qreal m_roundedRectRadius{ 5.0 };

	bool m_isHovering{ false };

	QScopedPointer<NodePainter> m_nodePainter;
};

