#pragma once
#include <QGraphicsItem>


class DmGraphicsSocketItem : public QGraphicsItem
{ 
	using Super = QGraphicsItem;

public:
	enum
	{
		ItemType_Socket = 0x02
	};

	DmGraphicsSocketItem(QGraphicsItem* parent = nullptr);

	void Initialize();

	virtual QRectF boundingRect() const override
	{
		return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
	}

	virtual int type() const override { return ItemType_Socket; }

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

protected:
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	qreal             m_radius;
	QPen              m_pen;
	QBrush            m_brush;

	bool m_mouseOnSocket {false};
};