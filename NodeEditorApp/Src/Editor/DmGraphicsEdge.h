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

	void UpdateStartPos(const QPointF& pos);

	void UpdateEndPos(const QPointF& pos);

protected:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

private:
	void UpdatePath();

private:
	DmGraphicsSocketItem* m_startSocket;
	DmGraphicsSocketItem* m_endSocket;

	/* Styles */

};

