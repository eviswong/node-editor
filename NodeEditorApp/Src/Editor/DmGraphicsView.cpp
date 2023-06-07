#include "Stdafx.h"
#include "DmGraphicsView.h"
#include "DmGraphicsNode.h"

DmGraphicsView::DmGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView(scene, parent)
{
	Super::setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
}

void DmGraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (event->modifiers().testFlag(Qt::ShiftModifier))
	{
		m_viewportOperationMode = Mode_Pan;
		m_currentPos = event->pos();
	}

	Super::mousePressEvent(event);
}

void DmGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_viewportOperationMode == Mode_Pan)
	{
		OnPanViewport(event);
	}

	Super::mouseMoveEvent(event);

}

void DmGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->modifiers().testFlag(Qt::ShiftModifier))
	{
		m_viewportOperationMode = Mode_Invalid;

	}

	Super::mouseReleaseEvent(event);

}

void DmGraphicsView::OnPanViewport(QMouseEvent* event)
{
	QPointF newPos = event->pos();
	QPointF deltaPos = newPos - m_currentPos;
	m_currentPos = newPos;

	//ViewportAnchor anchor = transformationAnchor();
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	QPointF newCenter(
		viewport()->rect().width() / 2 - deltaPos.x(),
		viewport()->rect().height() / 2 - deltaPos.y()
	);

	centerOn(mapToScene(newCenter.toPoint()));


	//setTransformationAnchor(anchor);
}

void DmGraphicsView::wheelEvent(QWheelEvent* event)
{
	bool ctrlDown = event->modifiers() & Qt::CTRL;
	if (ctrlDown)
	{
		OnZoomViewport(event);
	}
	else
	{
		QGraphicsView::wheelEvent(event);
	}
}

void DmGraphicsView::OnZoomViewport(QWheelEvent* event)
{
	float factor = 1.f;

	int angle = event->angleDelta().y();
	if (angle > 0)
	{
		// zoom in
		factor = 1.1f;
	}
	else if (angle < 0)
	{
		factor = 0.9f;
	}
#if 1

	// AnchorViewCenter Transform 过程中， Scene 的中心点一直在 Viewport 的中心，保持不变
	ViewportAnchor oldAnchor = Super::transformationAnchor();
	Super::setTransformationAnchor(QGraphicsView::NoAnchor);


    /* 找到缩放中心 */
	QPointF targetScenePos = Super::mapToScene(event->pos());

	QTransform transform = Super::transform();
	transform.translate(targetScenePos.x(), targetScenePos.y()).scale(factor, factor).translate(-targetScenePos.x(), -targetScenePos.y());

	Super::setTransform(transform);
	Super::setTransformationAnchor(oldAnchor);
#endif
#if 0
	Super::setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QTransform transform = Super::transform();
	transform.rotate(45.f);
	Super::setTransform(transform);
#endif
}

void DmGraphicsView::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Delete:
		{
			Self::OnDeleteItem(event);
		}
	break;
	}

	Super::keyPressEvent(event);
}

void DmGraphicsView::OnDeleteItem(QKeyEvent* event)
{
	QGraphicsScene* graphicsScene = Super::scene();
	assert(graphicsScene);

	QList<QGraphicsItem*> items = graphicsScene->selectedItems();
	if (items.size() == 0)
	{
		return;
	}

	for (QGraphicsItem* item : items)
	{
		if ((item->type() & NodeType_Node) == NodeType_Node)
		{
			qDebug() << "Node delete";
			Super::scene()->removeItem(item);
		}
	}
}
