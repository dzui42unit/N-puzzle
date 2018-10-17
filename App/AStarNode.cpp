#include "AStarNode.hpp"
#include "../Tools/Field.hpp"

#include <cassert>

Node::Node( int* field, size_t size,
            Node* Parent,
            Common::HeuristicTypes hType)
    : field_(new int[size * size]())
    , parent_(Parent)
    , size_(size)
    , heuristicType_(hType)
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
        heuristic_ = Common::tools::invoke(&Heuristic::Manhattan, field, size); 
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
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Down(pNewField, size_);
    }
    
    if (Field::Down(pNewField, size_))
    {
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Up(pNewField, size_);
    }

    if (Field::Left(pNewField, size_))
    {
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Right(pNewField, size_);
    }

    if (Field::Right(pNewField, size_))
    {
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Left(pNewField, size_);
    }
}
