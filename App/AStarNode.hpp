#pragma once

#include <memory>
#include <list>

#include "Heuristic.hpp"
#include "../Tools/Common.hpp"


struct Node
{
public:

    /*
    * @brief Construct the node and set all it's values except childrens_
    */ 
    explicit    Node( int*  field, size_t size,
                      std::list<Node*>* closedNodes,
                      std::list<Node*>* openedNodes,
                      Node* Parent = nullptr,
                      Common::HeuristicTypes hType = Common::HeuristicTypes::Manhattan );
    
    /*
    * @brief Creates child nodes and places them in childrens_
    */ 
    void        CreateChildNodes();

    int         GetValue() const { return ( depthCoef_ * depth_ + heuristicCoef_ * heuristic_ ); } 
    size_t      GetSize() const { return (size_); }
    int         GetHeuristicValue() const { return (heuristic_); }
    int         GetDepth() const { return (depth_); }
    const Node* GetParent() const { return (parent_); }
    int*        GetField() const { return (field_.get()); }
    ~Node();

public:
    std::list<Node>  childrens_;
private:
    bool IsFieldUnique(int* field, size_t size);


private:
    std::unique_ptr<int[]>              field_;
    size_t                              size_;
    std::list<Node*>*                   closedNodes_;
    std::list<Node*>*                   openedNodes_;
    const Node*                         parent_;
    int                                 heuristic_;
    int                                 depth_;
    Common::HeuristicTypes              heuristicType_;
    int                                 depthCoef_ = 0;
    int                                 heuristicCoef_ = 1;
};
