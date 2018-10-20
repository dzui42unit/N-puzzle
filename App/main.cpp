#include "../Tools/Parser.hpp"
#include "../Tools/Field.hpp"
#include "AStarNode.hpp"
#include "Heuristic.hpp"


void ShowHelp(char** av)
{
    std::cout << "Usage: " << av[0] << " {filename}" << std::endl;
    exit(0);
}

void PrintPath(Node* NodePtr)
{
    if (NodePtr == nullptr)
        return ;

    std::list<Node*> path;

    path.push_front(NodePtr);

    Node* parent = const_cast<Node*>(NodePtr->GetParent());
    while (parent)
    {
        path.push_front(parent);
        parent = const_cast<Node*>(parent->GetParent());
    }

    for (const auto& node : path)
    {
        int* field = node->GetField();
        size_t size = node->GetSize();
        std::cout << "Depth: " << node->GetDepth() << " Heuristics: " << node->GetHeuristicValue() << " Field:" << std::endl;
        Field::PrintPrintf(field, size);
        std::cout << std::endl;
    }
}

void TraverseNodes(int* field, size_t size)
{
    std::list<Node*> openedNodes;
    std::list<Node*> closedNodes;
    Node startingNode(field, size, &closedNodes, &openedNodes);

    openedNodes.push_back(&startingNode);
    while (openedNodes.size() > 0)
    {
        Node* nodePtr = nullptr;
        for (auto node : openedNodes)
        {
            if (nodePtr == nullptr)
                nodePtr = node;
            else if (node->GetHeuristicValue() == 0)
                nodePtr = node;
            else if (nodePtr->GetValue() > node->GetValue())
                nodePtr = node;
        }
        if (nodePtr->GetHeuristicValue() == 0)
        {
            PrintPath(nodePtr);
            return;
        }

        nodePtr->CreateChildNodes();
        for (auto& newNode : nodePtr->childrens_)
            openedNodes.push_back(&newNode);
        auto nodeToClose = std::find(openedNodes.begin(), openedNodes.end(), nodePtr);
        closedNodes.push_back(*nodeToClose);
        openedNodes.erase(nodeToClose);
    }

}

int main(int ac, char** av)
{
    if (ac < 2)
        ShowHelp(av);
    
    // Load file
    Parser parser(av[1]);
    if (parser.HasErrors())
    {
        std::cout << "Error while parsing specified file! Aborting!" << std::endl;
        ShowHelp(av);
    }

    // if (!parser.IsSolvable())
    // {
    //     std::cout << "Error: puzzle has no possible solutions" << std::endl;
    //     exit (0);
    // }
    // else
    // {
    //     std::cout << "SUCCESS, IT IS SOLVABLE\n\n";
    // }

    // Get field data
    size_t  size;
    int*    data = parser.GetData(size);
    TraverseNodes(data, size);

    return (0);
}