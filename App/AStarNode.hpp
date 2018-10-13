#pragma once

#include <memory>
#include <list>

#include "Heuristic.hpp"
#include "../Tools/Common.hpp"


struct Node
{
public:
    explicit    Node( int*  field, size_t size,
                      Node* Parent = nullptr,
                      Common::HeuristicTypes hType = Common::HeuristicTypes::Manhattan );
    Node() = delete;
    void        CreateChildNodes();
    size_t      GetSize() { return (size_); }
    int         GetHeuristicValue() { return (heuristic_); }
    int         GetDepth() { return (depth_); }
    Node*       GetParent() { return (parent_); }
    int*        GetField() { return (field_.get()); }
    ~Node();

public:
    std::list<Node>  childrens_;


private:
    std::unique_ptr<int[]>              field_;
    Node*                               parent_;
    int                                 heuristic_;
    int                                 depth_;
    size_t                              size_;
    Common::HeuristicTypes              heuristicType_;
};
