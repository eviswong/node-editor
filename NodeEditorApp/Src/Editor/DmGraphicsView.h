#pragma once

enum ViewportOperationMode
{
	Mode_Invalid,
	Mode_Pan
};

class QGraphicsScene;
class QKeyEvent;
class QWidget;

class DmGraphicsView : public QGraphicsView
{
	Q_OBJECT
		typedef DmGraphicsView Self;
	typedef QGraphicsView Super;
public:
	DmGraphicsView(QGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
	
protected:
	virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	virtual void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;
	virtual void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;


private:
	void OnZoomViewport(QWheelEvent* event);
	void OnPanViewport(QMouseEvent* event);
	void OnDeleteItem(QKeyEvent* event);
	

	ViewportOperationMode m_viewportOperationMode{ Mode_Invalid };

	QPointF m_currentPos;
};