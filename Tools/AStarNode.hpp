#pragma once

#include <memory>
#include <list>

#include "Heuristic.hpp"
#include "Common.hpp"


struct Node
{
public:
    explicit    Node( int*  field, size_t size,
                      Node* Parent = nullptr,
                      Common::HeuristicTypes hType = Common::HeuristicTypes::Manhattan );
    void        CreateChildNodes();
    ~Node();

public:
    std::unique_ptr<int[]>  field_;
    size_t                  size_;
    int                     totalComplexity_;
    std::list< std::unique_ptr<Node> >  childrens_;


private:
    Node*                               parent_;
    int                                 heuristic_;
    int                                 depth_;
    Common::HeuristicTypes              heuristicType_;
};
