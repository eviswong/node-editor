#include "Stdafx.h"
#include "DmGraphicsEdge.h"
#include "DmGraphicsSocketItem.h"


DmGraphicsEdgeItem::DmGraphicsEdgeItem(DmGraphicsSocketItem* startSocket, DmGraphicsSocketItem* endSocket)
	: QGraphicsPathItem(nullptr)
{

	m_startSocket = startSocket;
	m_endSocket = endSocket;

	Q_ASSERT_X(startSocket != nullptr, __FUNCTION__, "m_startPos is nullptr");
	m_startPos = startSocket->scenePos();
	m_endPos = m_startPos;
}