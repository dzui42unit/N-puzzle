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
    
    if (heuristicType_ == Common::HeuristicTypes::Manhattan)
        heuristic_ = Common::tools::invoke(&Heuristic::Manhattan, field, size);
    else
        assert(0 && "Not implemented yet!");
}

Node::Node(const Node& n)
{
    this->heuristicType_ = n.heuristicType_;
    this->heuristic_ = n.heuristic_;
    this->depth_ = n.depth_;
    this->size_ = n.size_;
    this->parent_ = n.parent_;

    this->field_ = std::make_unique<int[]>(size_ * size_);
    for (int i = 0; i < size_ * size_; i++)
        this->field_[i] = n.field_[i];
}

Node::~Node()
{

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
        childrens_.push_back(Node(newField.get(), size_, this, heuristicType_));
        resetField();
    }
    
    if (Field::CanMoveDown(newField.get(), size_))
    {
        Field::Down(newField.get(), size_);
        childrens_.push_back(Node(newField.get(), size_, this, heuristicType_));
        resetField();
    }

    if (Field::CanMoveLeft(newField.get(), size_))
    {
        Field::Left(newField.get(), size_);
        childrens_.push_back(Node(newField.get(), size_, this, heuristicType_));
        resetField();
    }

    if (Field::CanMoveUp(newField.get(), size_))
    {
        Field::Right(newField.get(), size_);
        childrens_.push_back(Node(newField.get(), size_, this, heuristicType_));
        resetField();
    }
}
