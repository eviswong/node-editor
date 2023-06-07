#pragma once
#include "DmGraphicsNode.h"

class DmGraphicsNodeItem;

struct NodeDescriptor
{
	using RawPtr = NodeDescriptor*;
	using RefPtr = std::shared_ptr<NodeDescriptor>;

	NodeType         type;
	std::string_view name;
	std::string_view description;
	std::string_view icon;
};

class NodeFactory 
{
public:
	static NodeFactory& GetInstance() 
	{
		static NodeFactory nodeFactory;
		return nodeFactory;
	}

	DmGraphicsNodeItem* Create(NodeType nodeType);
};

// 知道现在程序可以创建什么样的节点（有什么样的类）
class NodeManager
{
public:
	static NodeManager& GetInstance()
	{
		static NodeManager nodeManager;
		return nodeManager;
	}

	void RegisterNode(NodeDescriptor::RefPtr nodeDescriptorPtr)
	{
		assert(nodeDescriptorPtr != nullptr);

		m_nodeTypes[nodeDescriptorPtr->type] = nodeDescriptorPtr;
	}

private:
	std::unordered_map<NodeType, std::shared_ptr<NodeDescriptor>> m_nodeTypes;
};