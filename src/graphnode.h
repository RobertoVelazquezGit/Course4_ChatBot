#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>  // TASK 4
#include "chatbot.h"


// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    // TASK 4
    // Commented out std::vector<GraphEdge *> _childEdges;  // edges to subsequent nodes
    std::vector<std::unique_ptr<GraphEdge>> _childEdges;  // edges to subsequent nodes


    // data handles (not owned)
    std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes 

    //TASK 5
    // Commented out ChatBot *_chatBot;
    ChatBot _chatBot;
    

    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    std::vector<std::string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _parentEdges.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);

    // TASK 4
    // Commented out void AddEdgeToChildNode(GraphEdge *edge);
    void AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge);

    //// STUDENT CODE
    ////
    // TASK 5
    // Commented out void MoveChatbotHere(ChatBot *chatbot);
    void MoveChatbotHere(ChatBot chatbot);

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */