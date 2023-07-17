#include "Stdafx.h"
#include "DmGraphicsView.h"
#include "DmGraphicsNode.h"
#include "DmGraphicsSocketItem.h"
#include "DmGraphicsEdge.h"
#include "DmGraphicsScene.h"
#include "App/Logger.h"
#include "Utility/Assert.h"

DmGraphicsView::DmGraphicsView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView(scene, parent)
{
	Super::setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
}

void DmGraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (m_viewportOperationMode == Mode_Invalid && event->modifiers().testFlag(Qt::ShiftModifier))
	{
		m_viewportOperationMode = Mode_Pan;
		m_currentPos = event->pos();

		Super::mousePressEvent(event);
		return;
	}

	if (m_viewportOperationMode == Mode_Invalid && event->modifiers().testFlag(Qt::NoModifier))
	{
		// 鼠标在 scene 中的位置
		QPoint mousePos = event->pos();
		QGraphicsItem* socketItemUnderCursor = GetSocketItemUnderCursor(mousePos);
		if (socketItemUnderCursor != nullptr)
		{
			MessageWritter::Information("Start Dragging");
			m_viewportOperationMode = Mode_Drag;

			m_tempEdge = new DmGraphicsEdgeItem(static_cast<DmGraphicsSocketItem*>(socketItemUnderCursor));
			DmGraphicsScene::AddItem(m_tempEdge);
		}

		Super::mousePressEvent(event);
		return;
	}

	Super::mousePressEvent(event);
}

void DmGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_viewportOperationMode == Mode_Pan)
	{
		OnPanViewport(event);

		Super::mouseMoveEvent(event);
		return;
	}

	if (m_viewportOperationMode == Mode_Drag)
	{
		MessageWritter::Information("On Dragging");

		Q_ASSERT_X(m_tempEdge != nullptr, __FUNCTION__, "m_tempEdge is nullptr");

		QPoint scenePos = event->pos();
		m_tempEdge->UpdateEndPos(scenePos);

		Super::mouseMoveEvent(event);
		return;
	}

	Super::mouseMoveEvent(event);
}

void DmGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_viewportOperationMode == Mode_Pan && event->modifiers().testFlag(Qt::ShiftModifier))
	{
		m_viewportOperationMode = Mode_Invalid;
		Super::mouseReleaseEvent(event);
		return;
	}

	if (m_viewportOperationMode == Mode_Drag && event->modifiers().testFlag(Qt::NoModifier))
	{
		QPoint mouseScenePos = event->pos();
		DmGraphicsSocketItem* socketUnderCursor = GetSocketItemUnderCursor(mouseScenePos);
		if (socketUnderCursor == nullptr)
		{
			MessageWritter::Warning( "Stop dragging : No ending.");

			// 删除正在创建的连线
			__check_pointer(m_tempEdge);
			
			m_tempEdge = DmGraphicsScene::DeleteItem<DmGraphicsEdgeItem>(m_tempEdge);
			
			// 结束连线过程
			m_viewportOperationMode = Mode_Invalid;

			Super::mouseReleaseEvent(event);
			return;
		}

		// 建立连接关系
		MessageWritter::Information("Stop draggin : Create ending.");

		m_tempEdge->SetEndingSocket(socketUnderCursor);

		m_viewportOperationMode = Mode_Invalid;
		Super::mouseReleaseEvent(event);
		return;
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
	if (ctrlDown && m_viewportOperationMode == Mode_Invalid)
	{
		OnZoomViewport(event);
		QGraphicsView::wheelEvent(event);
		return;
	}
	else
	{
		QGraphicsView::wheelEvent(event);
		return;
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
	DmGraphicsScene* graphicsScene = DmGraphicsScene::GetScene();
	__check_pointer(graphicsScene);

	QList<QGraphicsItem*> items = graphicsScene->selectedItems();

	std::for_each(items.begin(), items.end(), 
		[](QGraphicsItem* item) 
		{
			if ((item->type() & NodeType_Node) == NodeType_Node)
			{
				item = DmGraphicsScene::DeleteItem<QGraphicsItem>(item);
			}
		}
	);
}


DmGraphicsSocketItem* DmGraphicsView::GetSocketItemUnderCursor(const QPoint& scenePos)
{
	DmGraphicsSocketItem* socketItem = nullptr;

	QGraphicsItem* itemUnderMouse = Super::itemAt(scenePos);
	if (itemUnderMouse == nullptr)
	{
		return socketItem;
	}

	if (itemUnderMouse->type() == DmGraphicsSocketItem::ItemType_Socket)
	{
		socketItem = static_cast<DmGraphicsSocketItem*>(itemUnderMouse);
	}

	return socketItem;
}