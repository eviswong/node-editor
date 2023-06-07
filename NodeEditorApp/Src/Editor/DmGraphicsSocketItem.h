#pragma once
#include <QGraphicsItem>
#include <thread>
#include <WIndows.h>

class DmGraphicsSocketItem : public QGraphicsItem
{ 
public:
	DmGraphicsSocketItem(QGraphicsItem* parent = nullptr)
		: QGraphicsItem(parent)
	{
		m_radius = 8.0;

		/* Pen */
		m_pen = QPen(Qt::SolidLine);
		m_pen.setColor("#F0F0F0");
		m_pen.setWidthF(3.f);

		m_brush.setStyle(Qt::SolidPattern);
		m_brush.setColor("#00FF00");
	}

	void Initialize()
	{

	}

	virtual QRectF boundingRect() const override
	{
		return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
	}

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override
	{
		{
			QPainterPath titlePath;
			titlePath.addEllipse(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);

			painter->setPen(m_pen);
			painter->drawPath(titlePath.simplified());
		}

		{
			painter->setPen(Qt::NoPen);
			painter->setBrush(m_brush);
			painter->drawEllipse(-5, -5, 2 * 5, 2 * 5);
		}
	}

private:
	qreal             m_radius;
	QPen              m_pen;
	QBrush            m_brush;
};