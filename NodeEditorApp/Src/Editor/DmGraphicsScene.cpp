#include "Stdafx.h"
#include "DmGraphicsScene.h"
#include "Base/Config.h"
#include "DmGraphicsNode.h"
#include "NodeFactory.h"

DmGraphicsScene::DmGraphicsScene(QObject* parent)
	: QGraphicsScene(parent)
{
	m_gridSize = 20;

	m_sceneWidth = 36000;
	m_sceneHeight = 36000;

	QRect sceneRect(- (m_sceneWidth / 2), -(m_sceneHeight / 2), m_sceneWidth, m_sceneHeight);
	Super::setSceneRect(sceneRect);

	Self::InitializeGrid();


	/* Graphics Item test */
#if 0
	QGraphicsRectItem* item = new QGraphicsRectItem(0, 0, 300, 300);
	item->setPen(QPen(Qt::yellow));
	Super::addItem(item);
#endif

#if 0
	// QGraphicsItem* item = new ValueNodeItem();
	DmGraphicsNodeItem* item = NodeFactory::GetInstance().Create(NodeType_ValueNode);
	Super::addItem(item);
#endif
	__make_sure(s_scene == nullptr, "Graphics scene is existed.");
	s_scene = this;
}

void DmGraphicsScene::InitializeGrid()
{
	/* Graphics scene background style */
	m_backgroundColor = QColor("#393939");

	m_backgroundBrush = QBrush(m_backgroundColor);

	/* Grid style */
	m_gridPenLight = QPen(Qt::SolidLine);
	m_gridPenLight.setColor("#2f2f2f");
	m_gridPenLight.setWidth(1);

	m_gridPenDark = QPen(Qt::SolidLine);
	m_gridPenDark.setColor("#151515");
	m_gridPenDark.setWidth(1);

	/* Grid data */
	int left = -m_sceneWidth / 2;
	int right = m_sceneWidth / 2;
	int bottom = m_sceneHeight / 2;
	int top = -m_sceneHeight / 2;

	int lineNum = 0;
	for (int x = left; x <= right; x += m_gridSize)
	{
		if (lineNum % 10 != 0)
		{
			m_gridLinesLight.push_back(QLine(x, top, x, bottom));
		}
		else
		{
			m_gridLinesDark.push_back(QLine(x, top, x, bottom));
		}

		lineNum++;
	}

	lineNum = 0;
	for (int y = top; y <= bottom; y += m_gridSize)
	{
		if (lineNum % 10 != 0)
		{
			m_gridLinesLight.push_back(QLine(left, y, right, y));
		}
		else
		{
			m_gridLinesDark.push_back(QLine(left, y, right, y));
		}
		lineNum++;
	}
}

void DmGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
{

	/* 绘制网格背景 */
	Super::setBackgroundBrush(m_backgroundBrush);
	Super::drawBackground(painter, rect);

	/* 绘制浅色网格 */
	painter->setPen(m_gridPenLight);
	painter->drawLines(m_gridLinesLight);

	/* 绘制深色网格 */
	painter->setPen(m_gridPenDark);
	painter->drawLines(m_gridLinesDark);

	/* 绘制坐标轴 */
#if 0
	{
		QPen axisPen(Qt::red);
		painter->setPen(axisPen);
		painter->drawLine(-m_sceneWidth / 2, 0, m_sceneWidth / 2, 0);
	}

	{
		QPen axisPen(Qt::green);
		painter->setPen(axisPen);
		painter->drawLine(0, -m_sceneHeight, 0, m_sceneHeight);
	}
#endif

#if 0
	/* 绘制文字 */
	QFont f("Consolas", 36);
	painter->setFont(f);

	QPen textPen(Qt::white);
	painter->setPen(textPen);

	/* 认识坐标系 */
	{
		painter->drawText(QPoint(0, 0), "Origin");
	}

	{
		painter->drawText(QPoint(100, 100), "Apple");
	}

	{
		painter->drawText(QPoint(-100, -100), "Banana");
	}
#endif
}

void DmGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-item"))
	{
		event->acceptProposedAction();
	}
}

void DmGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	// Super::dragMoveEvent(event);
}

void DmGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-item"))
	{
		QPointF cursorPos = event->scenePos();

		QByteArray eventData = event->mimeData()->data("application/x-item");

		QDataStream dataStream(&eventData, QIODevice::ReadOnly);

		int opCode;
		dataStream >> opCode;

		DmGraphicsNodeItem* item = NodeFactory::GetInstance().Create((NodeType)opCode);
		item->setPos(cursorPos);
		
		Super::addItem(item);
	}
}

void DmGraphicsScene::AddItem(QGraphicsItem* item)
{
	DmGraphicsScene* graphicsScene = GetScene();
	__check_pointer(graphicsScene);

	graphicsScene->addItem(item);
}