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

	static void RegisterNodeInfo(const NodeMeta* nodeInfo)
	{
		// Check exists
		NodeFactory& n = GetInstance();

		n.m_nodeMeta.push_back(nodeInfo);
	}

	const std::list<const NodeMeta*>& GetNodesMeta() const 
	{
		return m_nodeMeta;
	}

private:
	std::list<const NodeMeta*> m_nodeMeta;
};

template <typename NodeClassT>
struct NodeRegistry
{
	NodeRegistry() 
	{
		NodeMeta* nodeMeta = NodeClassT::GetNodeMeta();

		NodeFactory::GetInstance().RegisterNodeInfo(nodeMeta);
	}
};