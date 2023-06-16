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

	auto nodesMeta = NodeFactory::GetInstance().GetNodesMeta();

	std::for_each(nodesMeta.begin(), nodesMeta.end(), 
		[this](const NodeMeta* nodeMeta) 
		{
			QListWidgetItem* item = new QListWidgetItem();

			item->setIcon(QIcon(nodeMeta->iconPath));
			item->setText(nodeMeta->name);
			item->setToolTip(nodeMeta->description);
			item->setData(Qt::UserRole + 1, nodeMeta->type);

			Super::addItem(item);
		}
	);

#if 0
	QListWidgetItem* item = new QListWidgetItem();
	item->setIcon(QIcon(":/Resource/Icon/value.svg"));
	item->setText("Value Node");
	item->setToolTip("Use to display dynamic creation of an object.");

	item->setData(Qt::UserRole + 1, NodeType_ValueNode);


	Super::addItem(item);
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
