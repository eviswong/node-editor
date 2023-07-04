#pragma once
#include <QObject>
#include <QGraphicsItem>


class DmGraphicsNodeItem;

enum NodeType {
	NodeType_Node = 0x1000, // 4096 ¸ö
	NodeType_ValueNode,     // 0x1000  + 1 
	NodeType_IntegerNode,   // 0x1000 + 2
};

struct NodeMeta
{
	typedef DmGraphicsNodeItem* (*NodeDefaultConstructor)();

	const char* className;
	NodeDefaultConstructor defaultConstructor;

	const char* name;
	const char* description;
	const char* iconPath; 
	NodeType    type;
};

class NodePainter
{
public:
	NodePainter(DmGraphicsNodeItem* nodeItem);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	DmGraphicsNodeItem* m_nodeItem{nullptr};

	QPen m_penDefault;
	QPen m_penSelected;
	QPen m_penHovered;

	QBrush brushTitle;
	QBrush brushBackground;
};

class DmGraphicsNodeItem : public QGraphicsItem
{
	using Super = QGraphicsItem;
	using Self = DmGraphicsNodeItem;

	friend class NodePainter;

public:
	static NodeMeta* GetNodeMetaStatic() { return nullptr; }
	virtual NodeMeta* GetNodeMetaDynamic() { return nullptr; }

public:
	explicit DmGraphicsNodeItem(QGraphicsItem* parent = Q_NULLPTR);

	virtual QRectF boundingRect() const override 
	{ return m_rect; }

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;
	virtual int type() const override { return NodeType_Node; }
protected:
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
	bool OnSelected();
	bool OnUnSelected();

protected:
	QRectF m_rect {0, 0, 300, 300};
	qreal m_roundedRectRadius{ 5.0 };

	bool m_isHovering{ false };

	QScopedPointer<NodePainter> m_nodePainter;
};

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)


#define REGISTER_NODE_INFO(className)\
namespace{\
    NodeRegistry<className> CONCAT(register, __COUNTER__);\
}

#define __decl_node_info(nodeClassName)\
public:\
    static NodeMeta* GetNodeMetaStatic();          \
    virtual NodeMeta* GetNodeMetaDynamic() override\
    { return GetNodeMetaStatic();}\
	static DmGraphicsNodeItem* DefaultConstructor();\
private:

#define __impl_node_info_begin(nodeClassName)\
REGISTER_NODE_INFO(nodeClassName)\
DmGraphicsNodeItem* nodeClassName::DefaultConstructor() \
{\
    return new nodeClassName(); \
}\
NodeMeta* nodeClassName::GetNodeMetaStatic()\
{\
	static NodeMeta nodeMeta =\
	{\
		#nodeClassName,\
		DefaultConstructor,

#define __name(name) name
#define __desc(desc) desc
#define __icon(path) path
#define __type(t) t

#define __impl_node_info_end()\
	};\
	return &nodeMeta;\
}
