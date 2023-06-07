#include "Stdafx.h"
#include "NodeFactory.h"
#include "ValueNode.h"
// Operator node ...
// function node ...

DmGraphicsNodeItem* NodeFactory::Create(NodeType nodeType)
{
	DmGraphicsNodeItem* nodeItem = nullptr;

	switch (nodeType)
	{
		case (NodeType::NodeType_ValueNode):
		{
			nodeItem = new DmGraphicsValueNodeItem();
		}
		break;

		default:
		{
			Q_ASSERT_X(false, __FUNCTION__, "Unknown node type");
		}
	}

	return nodeItem;
}