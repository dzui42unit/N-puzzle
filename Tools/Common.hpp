#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


namespace Common
{

enum class HeuristicTypes
{
    Manhattan,
    Foo,
    Bar
};

class invoker
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

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
    
}