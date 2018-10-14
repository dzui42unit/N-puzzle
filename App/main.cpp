#include "../Tools/Parser.hpp"
#include "../Tools/Field.hpp"
#include "AStarNode.hpp"
#include "Heuristic.hpp"


void ShowHelp(char** av)
{
    std::cout << "Usage: " << av[0] << " {filename}" << std::endl;
    exit(0);
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

    // Get field data
    size_t  size;
    int*    data = parser.GetData(size);
    Field::Print(data, size);

    // Create first node and traverse it a few times for test
    Node n(data, size);
    Node* nodePtr = &n;
    int heuristics = 1;
    while (heuristics)
    {

        nodePtr->CreateChildNodes();
        Node* newNodePtr = nullptr;
        for (auto& newNode : nodePtr->childrens_)
        {
            if (newNodePtr != nullptr)
            {
                if (newNodePtr->GetHeuristicValue() > newNode.GetHeuristicValue())
                    newNodePtr = &newNode;
            }
            else
                newNodePtr = &newNode;
        }
        nodePtr = newNodePtr;
        heuristics = nodePtr->GetHeuristicValue();
    }

    nodePtr = &n;
    heuristics = 1;
    while (heuristics)
    {
        Node* newNodePtr = nullptr;
        for (auto& newNode : nodePtr->childrens_)
        {
            if (newNodePtr != nullptr)
            {
                if (newNodePtr->GetHeuristicValue() > newNode.GetHeuristicValue())
                    newNodePtr = &newNode;
            }
            else
                newNodePtr = &newNode;
        }
        nodePtr = newNodePtr;
        std::cout << "Depth: " << nodePtr->GetDepth() << " Heuristics: " << nodePtr->GetHeuristicValue() << " Field:" << std::endl;
        Field::PrintPrintf(nodePtr->GetField(), nodePtr->GetSize());
        std::cout << std::endl;
        heuristics = nodePtr->GetHeuristicValue();
    }
    return (0);
}