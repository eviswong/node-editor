#include "Stdafx.h"
#include "DmGraphicsNode.h"
#include "Base/Config.h"
#include "DmGraphicsScene.h"
#include "App/MainWindow.h"
#include "DmGraphicsSocketItem.h"


NodePainter::NodePainter(DmGraphicsNodeItem* nodeItem)
{
	Q_ASSERT_X(nodeItem != nullptr, __FUNCTION__, "Pointer to nodeItem is null");
	m_nodeItem = nodeItem;


	m_penDefault = QPen();
	m_penDefault.setColor(QColor("#7ff0f0f0"));
	m_penDefault.setWidth(2);

	m_penSelected = QPen();
	m_penSelected.setColor(QColor("#FFFFA637"));
	m_penSelected.setWidth(2);

	m_penHovered = QPen();
	m_penHovered.setColor(QColor("#FFC4FCEF"));
	m_penHovered.setWidth(2);

	// Title background
	brushBackground = QBrush(QColor("#FF212121"));
	brushTitle = QBrush(QColor("#a3252525"));
}

void NodePainter::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// Clear brush and pen
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);

	// 绘制节点背景

	{
		QPainterPath titlePath;
		titlePath.setFillRule(Qt::WindingFill);
		titlePath.addRoundedRect(m_nodeItem->m_rect, m_nodeItem->m_roundedRectRadius, m_nodeItem->m_roundedRectRadius);
		painter->setBrush(brushTitle);
		painter->drawPath(titlePath.simplified());
	}

	// outline
	QPainterPath outlinePath;
	outlinePath.addRoundedRect(m_nodeItem->m_rect, m_nodeItem->m_roundedRectRadius, m_nodeItem->m_roundedRectRadius);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(Qt::NoPen);

	if (m_nodeItem->isSelected())
	{
		painter->setPen(m_penSelected);
	}
	else if (m_nodeItem->m_isHovering)
	{
		painter->setPen(m_penHovered);
	}
#if 0
	else
	{
		painter->setPen(m_penDefault);
	}
#endif

	painter->drawPath(outlinePath.simplified());
}

DmGraphicsNodeItem::DmGraphicsNodeItem(QGraphicsItem* parent)
	: QGraphicsItem(parent)
{
	// m_rect = QRect(0, 0, 300, 300);


	Super::setFlag(QGraphicsItem::ItemIsMovable);
	Super::setFlag(QGraphicsItem::ItemIsSelectable);
	Super::setFlag(QGraphicsItem::ItemSendsGeometryChanges);

	Super::setAcceptHoverEvents(true);

	Super::setToolTip("This is a test graphics item");

	m_nodePainter.reset(new NodePainter(this));
}

void DmGraphicsNodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	m_nodePainter->paint(painter, option, widget);
}

void DmGraphicsNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	m_isHovering = true;
	Super::hoverEnterEvent(event);
}

void DmGraphicsNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_isHovering = false;
	Super::hoverLeaveEvent(event);
}

QVariant DmGraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
	bool toggleSnapping = Config::GetInstance().itemSnapping;

	if (toggleSnapping && change == QGraphicsItem::ItemPositionChange)
	{
		QPointF newPos = value.toPointF();

		DmGraphicsScene* graphicsScene = static_cast<DmGraphicsScene*>(Super::scene());
		/* 四舍五入 */

		int gridSize = graphicsScene->GetGridSize();

		qreal xV = std::round(newPos.x() / gridSize) * gridSize;
		qreal yV = std::round(newPos.y() / gridSize) * gridSize;

		return QPointF(xV, yV);
	}
#if 1
	else if (change == QGraphicsItem::ItemSelectedHasChanged)
	{
		bool selected = value.toBool();

		if (selected)
		{
			OnSelected();
		}
		else
		{
			OnUnSelected();
		}

		return selected;

	}
#endif
	else
	{
		return Super::itemChange(change, value);
	}
}

bool DmGraphicsNodeItem::OnSelected()
{
	qDebug() << "On selected";
	return true;
}

bool DmGraphicsNodeItem::OnUnSelected()
{
	qDebug() << "On unselected";
	return true;
}

