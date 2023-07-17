#include "Stdafx.h"
#include "DmGraphicsEdge.h"
#include "DmGraphicsSocketItem.h"


DmGraphicsEdgeItem::DmGraphicsEdgeItem(DmGraphicsSocketItem* startSocket, DmGraphicsSocketItem* endSocket)
	: QGraphicsPathItem(nullptr)
{
	m_startSocket = startSocket;
	m_endSocket = endSocket;
}

void DmGraphicsEdgeItem::UpdateStartPos(const QPointF& pos)
{
	UpdatePath();
}

void DmGraphicsEdgeItem::UpdateEndPos(const QPointF& pos)
{
	UpdatePath();
}

void DmGraphicsEdgeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}


// DmGraphicsBezireEdgeItem
// 
//

void DmGraphicsEdgeItem::UpdatePath()
{

}