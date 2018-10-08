#pragma once

#include <memory>
#include <list>


struct Node
{
public:
    explicit    Node( int* field, size_t size, Node* Parent = nullptr );
    void        CreateChildNodes();
    ~Node();

public:
    std::unique_ptr<int[]>  field_;
    size_t*                 size_;


private:
    std::list< std::unique_ptr<Node> >  childrens_;
    Node*                               parent_;
    int                                 heuristic_;
    int                                 depth_;
    int                                 totalComplexity_;
    
public:
    template<typename F, typename... Args>
    static auto invoke(F f, Args&&... args) -> decltype(std::ref(f)(std::forward<Args>(args)...))
    {
        return std::ref(f)(std::forward<Args>(args)...);
    }
};
