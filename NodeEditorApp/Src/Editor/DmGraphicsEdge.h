#pragma once

class DmGraphicsSocketItem;

class DmGraphicsEdgeItem : public QGraphicsPathItem
{
	using Super = QGraphicsPathItem;
public:
	enum 
	{
		ItemType_Edge
	};

	explicit DmGraphicsEdgeItem(DmGraphicsSocketItem* startSocket, DmGraphicsSocketItem* endSocket = nullptr);

	void SetStartingSocket(DmGraphicsSocketItem* socketItem)
	{
		m_startSocket = socketItem;
	}

	void SetEndingSocket(DmGraphicsSocketItem* socketItem)
	{
		m_endSocket = socketItem;
	}

	void UpdateStartPos(const QPointF& pos)
	{
		m_startPos = pos;
	}

	void UpdateEndPos(const QPointF& pos)
	{
		m_endPos = pos;
	}

private:
	DmGraphicsSocketItem* m_startSocket;
	DmGraphicsSocketItem* m_endSocket;

	QPointF               m_startPos;
	QPointF               m_endPos;
};