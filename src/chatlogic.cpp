#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <tuple>
#include <vector>

#include "chatbot.h"
#include "chatlogic.h"
#include "graphedge.h"
#include "graphnode.h"

ChatLogic::ChatLogic() {
  //// STUDENT CODE
  ////

  // create instance of chatbot
  // TASK5 
// Commented out #ifdef MY_IMAGES_PATH_DEBUG
// Commented out  _chatBot = new ChatBot("./images/chatbot.png");
// Commented out #else
// Commented out  _chatBot = new ChatBot("../images/chatbot.png");
// Commented out #endif

  // add pointer to chatlogic so that chatbot answers can be passed on to the
  // GUI
  // TASK 5
  // Commented out _chatBot->SetChatLogicHandle(this);

  ////
  //// EOF STUDENT CODE
}

ChatLogic::~ChatLogic() {
  //// STUDENT CODE
  ////

  // delete chatbot instance
  // TASK 5
  // Commented out delete _chatBot;

  // delete all nodes
  // TASK 3
  // Commented out for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it) {
  // Commented out  delete *it;
  // Commented out }

  // delete all edges
  // TASK 4   
  // Owner is class GraphNode
  // Commented out for (auto it = std::begin(_edges); it != std::end(_edges); ++it) {
  // Commented out  delete *it;
  // Commented out }

  ////
  //// EOF STUDENT CODE
}

template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens,
                                      T &element) {
  // find all occurences for current node
  auto token = tokens.begin();
  while (true) {
    token = std::find_if(
        token, tokens.end(),
        [&tokenID](const std::pair<std::string, std::string> &pair) {
          return pair.first == tokenID;
          ;
        });
    if (token != tokens.end()) {
      element.AddToken(token->second); // add new keyword to edge
      token++;                         // increment iterator to next element
    } else {
      break; // quit infinite while-loop
    }
  }
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename) {
  // load file with answer graph elements
  std::ifstream file(filename);

  // check for file availability and process it line by line
  if (file) {
    // loop over all lines in the file
    std::string lineStr;
    while (getline(file, lineStr)) {
      // extract all tokens from current line
      tokenlist tokens;
      while (lineStr.size() > 0) {
        // extract next token
        int posTokenFront = lineStr.find("<");
        int posTokenBack = lineStr.find(">");
        if (posTokenFront < 0 || posTokenBack < 0)
          break; // quit loop if no complete token has been found
        std::string tokenStr =
            lineStr.substr(posTokenFront + 1, posTokenBack - 1);

        // extract token type and info
        int posTokenInfo = tokenStr.find(":");
        if (posTokenInfo != std::string::npos) {
          std::string tokenType = tokenStr.substr(0, posTokenInfo);
          std::string tokenInfo =
              tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

          // add token to vector
          tokens.push_back(std::make_pair(tokenType, tokenInfo));
        }

        // remove token from current line
        lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
      }

      // process tokens for current line
      auto type =
          std::find_if(tokens.begin(), tokens.end(),
                       [](const std::pair<std::string, std::string> &pair) {
                         return pair.first == "TYPE";
                       });
      if (type != tokens.end()) {
        // check for id
        auto idToken =
            std::find_if(tokens.begin(), tokens.end(),
                         [](const std::pair<std::string, std::string> &pair) {
                           return pair.first == "ID";
                         });
        if (idToken != tokens.end()) {
          // extract id from token
          int id = std::stoi(idToken->second);

          // node-based processing
          if (type->second == "NODE") {
            //// STUDENT CODE
            ////

            // check if node with this ID exists already
            // TASK 3
            // Commented out auto newNode = std::find_if(
            // Commented out    _nodes.begin(), _nodes.end(),
            // Commented out    [&id](GraphNode *node) { return node->GetID() ==
            // id; });
            auto newNode =
                std::find_if(_nodes.begin(), _nodes.end(),
                             [&id](std::unique_ptr<GraphNode> &node) {
                               return node->GetID() == id;
                             });

            // create new element if ID does not yet exist
            if (newNode == _nodes.end()) {
              // TASK 3
              // Commented out _nodes.emplace_back(new GraphNode(id));
              _nodes.emplace_back(std::make_unique<GraphNode>(id));
              newNode = _nodes.end() - 1; // get iterator to last element

              // add all answers to current node
              AddAllTokensToElement("ANSWER", tokens, **newNode);
            }

            ////
            //// EOF STUDENT CODE
          }

          // edge-based processing
          if (type->second == "EDGE") {
            //// STUDENT CODE
            ////

            // find tokens for incoming (parent) and outgoing (child) node
            auto parentToken = std::find_if(
                tokens.begin(), tokens.end(),
                [](const std::pair<std::string, std::string> &pair) {
                  return pair.first == "PARENT";
                });
            auto childToken = std::find_if(
                tokens.begin(), tokens.end(),
                [](const std::pair<std::string, std::string> &pair) {
                  return pair.first == "CHILD";
                });

            if (parentToken != tokens.end() && childToken != tokens.end()) {
              // get iterator on incoming and outgoing node via ID search
              // TASK 3
              //  Commented out auto parentNode = std::find_if(
              //  Commented out   _nodes.begin(), _nodes.end(),
              //  Commented out   [&parentToken](GraphNode *node) {
              //  Commented out     return node->GetID() ==
              //  std::stoi(parentToken->second); Commented out   }); Commented
              //  outauto childNode = std::find_if( Commented out
              //  _nodes.begin(), _nodes.end(), [&childToken](GraphNode *node) {
              //  Commented out     return node->GetID() ==
              //  std::stoi(childToken->second); Commented out   });
              auto parentNode = std::find_if(
                  _nodes.begin(), _nodes.end(),
                  [&parentToken](std::unique_ptr<GraphNode> &node) {
                    return node->GetID() == std::stoi(parentToken->second);
                  });
              auto childNode = std::find_if(
                  _nodes.begin(), _nodes.end(),
                  [&childToken](std::unique_ptr<GraphNode> &node) {
                    return node->GetID() == std::stoi(childToken->second);
                  });

              // create new edge
              // TASK 4
              // Commented out GraphEdge *edge = new GraphEdge(id);
              std::unique_ptr<GraphEdge> edge = std::make_unique<GraphEdge>(id);

              // TASK 3
              // Commented out edge->SetChildNode(*childNode);
              edge->SetChildNode(
                  (*childNode).get()); // childNode is the iterator,
                                       // (*childNode) is the smart pointer
                                       // (*childNode).get() is the raw pointer to GraphEdge
              // Commented out edge->SetParentNode(*parentNode);
              edge->SetParentNode((*parentNode).get());
               
              // TASK 4 
              // Commented out _edges.push_back(edge);
              _edges.push_back(edge.get());

              // find all keywords for current node
              AddAllTokensToElement("KEYWORD", tokens, *edge);

              // store reference in child node and parent node
              // TASK 4
              // Commented out (*childNode)->AddEdgeToParentNode(edge);
              (*childNode)->AddEdgeToParentNode(edge.get());

              // TASK 4
              // Commented out (*parentNode)->AddEdgeToChildNode(edge);
              (*parentNode)->AddEdgeToChildNode(std::move(edge));  // transfer ownership
            }

            ////
            //// EOF STUDENT CODE
          }
        } else {
          std::cout << "Error: ID missing. Line is ignored!" << std::endl;
        }
      }
    } // eof loop over all lines in the file

    file.close();

  } // eof check for file availability
  else {
    std::cout << "File could not be opened!" << std::endl;
    return;
  }

  //// STUDENT CODE
  ////

  // identify root node
  GraphNode *rootNode = nullptr;
  for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it) {
    // search for nodes which have no incoming edges
    if ((*it)->GetNumberOfParents() == 0) {

      if (rootNode == nullptr) {
        // TASK 3
        // Commented out rootNode = *it; // assign current node to root
        rootNode = (*it).get();
      } else {
        std::cout << "ERROR : Multiple root nodes detected" << std::endl;
      }
    }
  }

  // add chatbot to graph root node
  // TASK 5 
  // Instead of doing in constructor
#ifdef MY_IMAGES_PATH_DEBUG
  ChatBot chatBot("./images/chatbot.png");
#else
  ChatBot chatBot("../images/chatbot.png");
#endif
  chatBot.SetChatLogicHandle(this);

  // TASK 5 
  // Commented out _chatBot->SetRootNode(rootNode);
  // Commented out rootNode->MoveChatbotHere(_chatBot);
  chatBot.SetRootNode(rootNode);
  rootNode->MoveChatbotHere(std::move(chatBot));  // transfer ownership

  ////
  //// EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog) {
  _panelDialog = panelDialog;
}

void ChatLogic::SetChatbotHandle(ChatBot *chatbot) { _chatBot = chatbot; }

void ChatLogic::SendMessageToChatbot(std::string message) {
  _chatBot->ReceiveMessageFromUser(message);
}

void ChatLogic::SendMessageToUser(std::string message) {
  _panelDialog->PrintChatbotResponse(message);
}

wxBitmap *ChatLogic::GetImageFromChatbot() {
  return _chatBot->GetImageHandle();
}
