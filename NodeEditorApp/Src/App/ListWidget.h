#pragma once
#include <qlistview.h>
class ListWidget : public QListWidget
{
    Q_OBJECT

    using Super = QListWidget;
    using Self = ListWidget;
public:
    explicit ListWidget(QWidget* parent = Q_NULLPTR);

protected:
    virtual void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

};