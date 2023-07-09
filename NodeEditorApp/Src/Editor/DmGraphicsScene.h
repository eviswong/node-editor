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

	static void DeleteItem(QGraphicsItem* item) 
	{
		Q_ASSERT_X(s_scene != nullptr, __FUNCTION__, "s_scene is nullptr");
		s_scene->removeItem(item);
		delete item;
		item = nullptr;
	}

	static void AddItem(QGraphicsItem* item)
	{
		Q_ASSERT_X(s_scene != nullptr, __FUNCTION__, "s_scene is nullptr");
		s_scene->addItem(item);
	}

protected:
	virtual void drawBackground(QPainter* painter, const QRectF& rect) override;
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
	virtual void dropEvent(QGraphicsSceneDragDropEvent* event) override;

private:
	void InitializeGrid();

private:
	/* Graphics Scene 背景色 */
	QColor m_backgroundColor;
	QBrush m_backgroundBrush;

	/* Grid style */
	QPen m_gridPenLight;
	QPen m_gridPenDark;

	/* Grid data */
	QVector<QLine> m_gridLinesLight;
	QVector<QLine> m_gridLinesDark;


	/* 网格尺寸 */
	int m_gridSize;
	
	/* Graphics Scene 的宽度 */
	int m_sceneWidth;
	int m_sceneHeight;

	inline static QGraphicsScene* s_scene{nullptr};
};