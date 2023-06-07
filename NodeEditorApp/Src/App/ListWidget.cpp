#include "Stdafx.h"
#include "ListWidget.h"
#include "Editor/NodeFactory.h"
#include <QMimeData>
#include <QDrag>

ListWidget::ListWidget(QWidget* parent)
	: QListWidget(parent)
{
	Super::setIconSize(QSize(32, 32));
	Super::setSelectionMode(QAbstractItemView::SingleSelection);
	Super::setDragEnabled(true);

	QListWidgetItem* item = new QListWidgetItem();
	item->setIcon(QIcon(":/Resource/Icon/value.svg"));
	item->setText("Value Node");
	item->setToolTip("Use to display dynamic creation of an object.");

	item->setData(Qt::UserRole + 1, NodeType_ValueNode);

	Super::addItem(item);
	
#if 0
	Super::addItem(new QListWidgetItem("Add"));
	Super::addItem(new QListWidgetItem("Sub"));
	Super::addItem(new QListWidgetItem("Mul"));
	Super::addItem(new QListWidgetItem("Div"));
#endif
}

void ListWidget::startDrag(Qt::DropActions supportedActions)
{
	Super::startDrag(supportedActions);


	QListWidgetItem* selectedItem = Super::currentItem();

	int opCode = selectedItem->data(Qt::UserRole + 1).toInt();

	/* Mime data */
	QByteArray byteArray;

	QDataStream ds(&byteArray, QIODevice::WriteOnly);
	ds << opCode;

	QMimeData* md = new QMimeData();
	md->setData("application/x-item", byteArray);

	/* Execute drag */
	QDrag* drag = new QDrag(this);
	drag->setMimeData(md);
	drag->exec(Qt::MoveAction);
}
