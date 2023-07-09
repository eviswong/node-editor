#include "Stdafx.h"
#include "DmGraphicsSocketItem.h"


DmGraphicsSocketItem::DmGraphicsSocketItem(QGraphicsItem* parent)
	: QGraphicsItem(parent)
{
	m_radius = 8.0;

	/* Pen */
	m_pen = QPen(Qt::SolidLine);
	m_pen.setColor("#F0F0F0");
	m_pen.setWidthF(3.f);

	m_brush.setStyle(Qt::SolidPattern);
	m_brush.setColor("#00FF00");


	Super::setAcceptHoverEvents(true);
}

void DmGraphicsSocketItem::Initialize()
{

}

void DmGraphicsSocketItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	m_mouseOnSocket = true;
	Super::hoverEnterEvent(event);
}

void DmGraphicsSocketItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_mouseOnSocket = false;
	Super::hoverEnterEvent(event);
}



void DmGraphicsSocketItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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