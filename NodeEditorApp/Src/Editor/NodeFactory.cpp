#include "Stdafx.h"
#include "NodeFactory.h"
#include "ValueNode.h"
// Operator node ...
// function node ...

DmGraphicsNodeItem* NodeFactory::Create(NodeType nodeType)
{
	auto nodeMeta = NodeFactory::GetInstance().GetNodesMeta();

	auto res = std::find_if(nodeMeta.begin(), nodeMeta.end(), 
		[nodeType](const NodeMeta* nodeMeta) 
		{
			return nodeMeta->type == nodeType;
		}
	);

	DmGraphicsNodeItem* item = nullptr;

	if (*res != nullptr) 
	{
		item = (*res)->defaultConstructor();

		auto nodeMeta = item->GetNodeMetaDynamic();
		item->setToolTip(nodeMeta->description);
	}

	return item;
}