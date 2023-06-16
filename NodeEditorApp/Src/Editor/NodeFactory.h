#pragma once
#include "DmGraphicsNode.h"

class DmGraphicsNodeItem;

class NodeFactory 
{
public:
	static NodeFactory& GetInstance() 
	{
		static NodeFactory nodeFactory;
		return nodeFactory;
	}

	DmGraphicsNodeItem* Create(NodeType nodeType);

	void RegisterNodeInfo(NodeMeta* nodeInfo)
	{
		// Check exists

		m_nodeMeta.push_back(nodeInfo);
	}

	const std::list<NodeMeta*>& GetNodesMeta() const 
	{
		return m_nodeMeta;
	}

private:
	std::list<NodeMeta*> m_nodeMeta;
};

template <typename NodeClassT>
struct NodeRegistry
{
	NodeRegistry() 
	{
		NodeMeta* nodeMeta = NodeClassT::GetNodeMetaStatic();

		NodeFactory::GetInstance().RegisterNodeInfo(nodeMeta);
	}
};