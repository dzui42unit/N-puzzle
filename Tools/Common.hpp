#pragma once

#include <functional>


namespace Common
{

enum class HeuristicTypes
{
    Manhattan,
    Foo,
    Bar
};

struct invoker
{
    invoker() = delete;
    ~invoker() = delete;
public:
    template<typename F, typename... Args>
    static auto invoke(F f, Args&&... args) -> decltype(std::ref(f)(std::forward<Args>(args)...))
    {
        return std::ref(f)(std::forward<Args>(args)...);
    }
};
    
}