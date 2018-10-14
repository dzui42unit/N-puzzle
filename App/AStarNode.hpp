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
                      Node* Parent = nullptr,
                      Common::HeuristicTypes hType = Common::HeuristicTypes::Manhattan );
    
    Node(const Node& n);
    Node(Node&& n);
    Node() = delete;
    Node& operator=( const Node& rhs );

    /*
    * @brief Creates child nodes and places them in childrens_
    */ 
    void        CreateChildNodes();

    size_t      GetSize() const { return (size_); }
    int         GetHeuristicValue() const { return (heuristic_); }
    int         GetDepth() const { return (depth_); }
    const Node* GetParent() const { return (parent_); }
    int*        GetField() const { return (field_.get()); }
    ~Node();

public:
    std::list<Node>  childrens_;


private:
    std::unique_ptr<int[]>              field_;
    const Node*                         parent_;
    int                                 heuristic_;
    int                                 depth_;
    size_t                              size_;
    Common::HeuristicTypes              heuristicType_;
};
