#include "AStarNode.hpp"
#include "../Tools/Field.hpp"

#include <cassert>

Node::Node( int* field, size_t size,
            std::list<Node*>* closedNodes,
            std::list<Node*>* openedNodes,
            Node* Parent,
            Common::HeuristicTypes hType)
    : field_(new int[size * size]())
    , size_(size)
    , closedNodes_(closedNodes)
    , openedNodes_(openedNodes)
    , parent_(Parent)
    , heuristicType_(hType)
    , isHighlighted_(false)
{
    for (size_t i = 0; i < size_ * size_; i++)
        field_[i] = field[i];

    if (parent_ != nullptr)
        depth_ = parent_->depth_ + 1;
    else
        depth_ = 0;
    
    /// Get Heuristic value by invoking static function for it's calculation
    /// To determine which function to call, use heuristicType_ enum value as a switch 
    if (heuristicType_ == Common::HeuristicTypes::Manhattan)
        heuristic_ = Heuristic::Manhattan(field, size); //Common::tools::invoke(&Heuristic::Manhattan, field, size); 
    else
        assert(0 && "Not implemented yet!");
}

Node::~Node()
{

}

void Node::CreateChildNodes()
{
    int*    pNewField = field_.get();

    if (Field::Up(pNewField, size_))
    {
        if (IsFieldUnique(pNewField, size_))
            childrens_.emplace_back(pNewField, size_, closedNodes_, openedNodes_, this, heuristicType_);
        Field::Down(pNewField, size_);
    }
    
    if (Field::Down(pNewField, size_))
    {
        if (IsFieldUnique(pNewField, size_))
            childrens_.emplace_back(pNewField, size_, closedNodes_, openedNodes_, this, heuristicType_);
        Field::Up(pNewField, size_);
    }

    if (Field::Left(pNewField, size_))
    {
        if (IsFieldUnique(pNewField, size_))
            childrens_.emplace_back(pNewField, size_, closedNodes_, openedNodes_, this, heuristicType_);
        Field::Right(pNewField, size_);
    }

    if (Field::Right(pNewField, size_))
    {
        if (IsFieldUnique(pNewField, size_))
            childrens_.emplace_back(pNewField, size_, closedNodes_, openedNodes_, this, heuristicType_);
        Field::Left(pNewField, size_);
    }
}

bool Node::IsFieldUnique(int* field, size_t size)
{
    if (closedNodes_ == nullptr || openedNodes_ == nullptr)
        return (false);

    for (const auto& closedNode : *closedNodes_)
    {
        int* pField = closedNode->GetField();
        bool equalityFlag = true;

        for (size_t i = 0; i < size * size; i++)
        {
            if (pField[i] != field[i])
                equalityFlag = false;
        }
        if (equalityFlag)
            return (false);
    }

    for (const auto& openedNode : *openedNodes_)
    {
        if (openedNode == this)
            continue;
        int* pField = openedNode->GetField();
        bool equalityFlag = true;

        for (size_t i = 0; i < size * size; i++)
        {
            if (pField[i] != field[i])
                equalityFlag = false;
        }
        if (equalityFlag)
            return (false);
    }
    return (true);
}

bool Node::isHighlighted()
{
    return (isHighlighted_);
}

void Node::HighlitePath()
{
    isHighlighted_ = true;
    if (parent_ != nullptr)
        const_cast<Node*>(parent_)->HighlitePath();
}
