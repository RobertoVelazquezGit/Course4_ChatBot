#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

    // TASK 0
    // Reason of memory leak when leaving
    // commented out _chatBot; 

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

// TASK 4
// Commented out void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
// Commented out{
// Commented out    _childEdges.push_back(edge);
// Commented out}
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    // Ownership for GraphNode with std::move, memory will automatically be freed whith
    // the instance
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
  
    // TASK 4
    // Commented out return _childEdges[index];
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}