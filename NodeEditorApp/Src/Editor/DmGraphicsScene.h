#pragma once

class QGraphicsSceneDragDropEvent;
class DmGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

	using Super = QGraphicsScene;
	using Self = DmGraphicsScene;

public:
	DmGraphicsScene(QObject* parent = Q_NULLPTR);

	int GetGridSize() const { return m_gridSize; }


protected:
	virtual void drawBackground(QPainter* painter, const QRectF& rect) override;
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
	virtual void dropEvent(QGraphicsSceneDragDropEvent* event) override;

private:
	void InitializeGrid();

private:
	/* Graphics Scene ����ɫ */
	QColor m_backgroundColor;
	QBrush m_backgroundBrush;

	/* Grid style */
	QPen m_gridPenLight;
	QPen m_gridPenDark;

	/* Grid data */
	QVector<QLine> m_gridLinesLight;
	QVector<QLine> m_gridLinesDark;


	/* ����ߴ� */
	int m_gridSize;
	
	/* Graphics Scene �Ŀ�� */
	int m_sceneWidth;
	int m_sceneHeight;
};