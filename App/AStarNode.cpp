#include "AStarNode.hpp"
#include "../Tools/Field.hpp"

#include <cassert>


Node::Node( int* field, size_t size,
            Node* Parent,
            Common::HeuristicTypes hType)
    : parent_(Parent)
    , field_(new int[size * size]())
    , size_(size)
    , heuristicType_(hType)
{
    for (int i = 0; i < size_ * size_; i++)
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
    int     newField[size_ * size_];
    int*    pNewField = newField;
    
    for (int i = 0; i < size_ * size_; i++)
        pNewField[i] = field_[i];

    if (Field::CanMoveUp(newField, size_))
    {
        Field::Up(newField, size_);
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Down(newField, size_);
    }
    
    if (Field::CanMoveDown(newField, size_))
    {
        Field::Down(newField, size_);
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Up(newField, size_);
    }

    if (Field::CanMoveLeft(newField, size_))
    {
        Field::Left(newField, size_);
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Right(newField, size_);
    }

    if (Field::CanMoveRight(newField, size_))
    {
        Field::Right(newField, size_);
        childrens_.emplace_back(pNewField, size_, this, heuristicType_);
        Field::Left(newField, size_);
    }
}
