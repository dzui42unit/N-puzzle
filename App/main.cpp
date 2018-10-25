#include "../Tools/Parser.hpp"
#include "../Tools/Field.hpp"
#include "../Tools/argh.h"
#include "../Tools/Common.hpp"
#include "AStarNode.hpp"
#include "Heuristic.hpp"
#include <exception>
#include <random>
#include <ctime>

void ShowHelp(char** av)
{
    std::cout << "Usage: " << av[0] << " [-fsh][--help]" << std::endl;
    std::cout << std::endl << "OPTIONS:" << std::endl;
    std::cout << "\t-f --file\t\tUse file as input" << std::endl;
    std::cout << "\t-s --size\t\tSize of generated map 3 by default, must be greater than 2. If -f is specified will be ignored" << std::endl;
    std::cout << "\t-h --heuristic\t\tWhich heuristic to use" << std::endl;
    std::cout << "\t\t\t\t[1 | Manhattan | manhattan] - Manhattan Distance heuristic function" << std::endl;
    std::cout << "\t\t\t\t[2 | LinearConflict | linearconflict] - Linear Conflict + Manhattan Distance heuristic function" << std::endl;
    std::cout << "\t\t\t\t[3 | EuclidianDistance | euclidiandistance] - Lenear Conflict + Misplaced Tiles heuristic function" << std::endl;
    std::cout << "\t--help\t\t\tShow this help" << std::endl;
    exit(0);
}

int     *GeneratePuzzle(size_t size)
{
    std::mt19937_64 rng(std::time(NULL));
    std::uniform_int_distribution<int> next_move(1, 4);
    std::uniform_int_distribution<int> iterations(100, 1000000);

    int nb;
    int iter;
    int *puzzle;

    puzzle = nullptr;
    iter = iterations(rng);
    puzzle = Field::CreateSnailGrid(nullptr, size);
    for (int i = 0; i < iter; i++)
    {
        nb = next_move(rng);
        switch (nb)
        {
        case 1:
            Field::Up(puzzle, size);
            break;
        case 2:
            Field::Down(puzzle, size);
            break;
        case 3:
            Field::Left(puzzle, size);
            break;
        case 4:
            Field::Right(puzzle, size);
            break;
        }
    }
    return (puzzle);
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

void TraverseNodes(int* field, size_t size, Common::HeuristicTypes hType)
{
    std::list<Node*> openedNodes;
    std::list<Node*> closedNodes;
    Node startingNode(field, size, &closedNodes, &openedNodes, nullptr, hType);

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
            else if (nodePtr->GetHeuristicValue() > node->GetHeuristicValue())
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
    size_t                  size = 3;
    int*                    data;
    Common::HeuristicTypes  hType = Common::Manhattan;

    data = nullptr;
    std::string filename = "";

    argh::parser cmdl;
    std::initializer_list<const char* const> flags = {"file", "f", "h", "heuristic", "s", "size"};
    cmdl.add_params(flags);
    cmdl.parse(ac, av);

    for (const auto& param : cmdl.params())
    {
        if (param.first == "f" || param.first == "file")
            filename = param.second;
        else if (param.first == "h" || param.first == "heuristic")
        {
            if (param.second == "1" || param.second == "Manhattan" || param.second == "manhattan")
                hType = Common::Manhattan;
            else if (param.second == "2" || param.second == "LinearConflict" || param.second == "linearconflict")
                hType = Common::LinearConflictManhattan;
            else if (param.second == "3" || param.second == "EuclidianDistance" || param.second == "euclidiandistance")
                hType = Common::EuclidianDistance;
            else
                ShowHelp(av);
        }
        else if (param.first == "s" || param.first == "size")
        {
            size = std::stoi(param.second);
        }
        else
        {
            ShowHelp(av);
        }
    }

    for (const auto& flag : cmdl.flags())
    {
        if (flag == "help")
            ShowHelp(av);
        for (const std::string str : flags )
        {
            if (flag == str)
                ShowHelp(av);
        }
    }

    // Try to Load file
    if (filename != "")
    {
        Parser parser(filename.c_str());
        if (parser.HasErrors())
        {
            std::cout << "Error while parsing specified file! Aborting!" << std::endl;
            ShowHelp(av);
        }
        data = parser.GetData(size);
        TraverseNodes(data, size, hType);
    }
    else
    {
        if (size < 3)
            ShowHelp(av);
        data = GeneratePuzzle(size);
        TraverseNodes(data, size, hType);
    }
    
    return (0);
}
