#include "AStarNode.hpp"
#include "Tools/Field.hpp"

#include <cassert>


Node::Node( int* field, size_t size,
            Node* Parent = nullptr,
            Common::HeuristicTypes hType)
    : parent_(Parent)
    , field_(new int[size * size]())
    , size_(size)
    , totalComplexity_(-1)
    , heuristicType_(hType)
{
    for (int i = 0; i < size_ * size_; i++)
        field_[i] = field[i];

    if (parent_ != nullptr)
        depth_ = parent_->depth_ + 1;
    else
        depth_ = 0;
    
    if (heuristicType_ == Common::HeuristicTypes::Manhattan)
        heuristic_ = Common::invoker::invoke(&Heuristic::Manhattan, field, size);
    else
        assert(0 && "Not implemented yet!");
    totalComplexity_ = heuristic_ + depth_;
}

void Node::CreateChildNodes()
{
    auto newField = std::make_unique<int[]>(size_ * size_);
    
    auto resetField = [&]() {
        for (int i = 0; i < size_ * size_; i++)
            newField[i] = field_[i];
    };

    resetField();
    if (Field::CanMoveUp(newField.get(), size_))
    {
        Field::Up(newField.get(), size_);
        childrens_.push_back(std::make_unique<Node>(newField.get(), size_, this, heuristicType_));
        resetField();
    }
    
    if (Field::CanMoveDown(newField.get(), size_))
    {
        Field::Down(newField.get(), size_);
        childrens_.push_back(std::make_unique<Node>(newField.get(), size_, this, heuristicType_));
        resetField();
    }

    if (Field::CanMoveLeft(newField.get(), size_))
    {
        Field::Left(newField.get(), size_);
        childrens_.push_back(std::make_unique<Node>(newField.get(), size_, this, heuristicType_));
        resetField();
    }

    if (Field::CanMoveUp(newField.get(), size_))
    {
        Field::Right(newField.get(), size_);
        childrens_.push_back(std::make_unique<Node>(newField.get(), size_, this, heuristicType_));
        resetField();
    }
}
