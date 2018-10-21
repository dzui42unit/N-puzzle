#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>


namespace Common
{

enum class HeuristicTypes
{
    Manhattan,
    LinearConflictManhattan,
    Bar,
    HeruisticError,
};

class tools
{
    tools() = delete;
    ~tools() = delete;
public:

    /*
    * @brief call's specified function
    * @params first - function ponter, all other - function arguments
    * @return function result
    */ 
    template<typename F, typename... Args>
    static auto invoke(F f, Args&&... args) -> decltype(std::ref(f)(std::forward<Args>(args)...))
    {
        return std::ref(f)(std::forward<Args>(args)...);
    }

    /*
    * @brief splits string into the substrings with char delimiter
    * @param s - the string to split
    * @param delimiter - by this char string will be splitted
    * @return std::vector<std::string> with all splitted chanks of data
    */ 
    static std::vector<std::string> split(const std::string& s, char delimiter)
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

    /*
    * @brief counts number of digits in number
    * @param n - the number to count digits
    * @return number of digits in the number n in int format
    */ 
    static int countDigit(long long n) 
    { 
        return ceil(log10(n)); 
    }

    /*
    * @brief replaces a specified repeated character in a string with one such character
    * @param str - ref to a string to replace characters
    * @param c - a char to replace
    */ 
    static void compressChars(std::string& str, char c)
    {
        auto BothAreChar = [&](char lhs, char rhs) { 
            return (lhs == rhs) && (lhs == c);
            };

        std::string::iterator new_end = std::unique(str.begin(), str.end(), BothAreChar);
        str.erase(new_end, str.end());
    }

    /// trim from start (in place)
    static inline void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))));
    }

    /// trim from end (in place)
    static inline void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    }

    /// trim from both ends (in place)
    static inline void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }
};
}
