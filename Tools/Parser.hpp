#pragma once

#include "Common.hpp"

class Parser
{
public:

    /*
    * @brief Loads and validates specified file as a n-puzzle field
    * @param name - the filename to load
    */ 
    Parser(const char* name);
    Parser() = delete;
    ~Parser();

    /*
    * @brief returns current gamefield properties
    * @param size - will be set by the value of gamefield edge size 
    * @return nullptr if(HasErrors()), pointer to loaded gamefield otherwise
    */ 
    int* GetData(size_t& size);

    /*
    * @brief Called to see if there were errors during game field initialization
    * @return true if there were errors, false otherwise 
    */ 
    bool HasErrors();

private:
    /*
    * @brief Ensures that the given values can be converted to int and is positive
    * @return true if data are valid, false otherwise
    */ 
    bool ValidateData(const std::vector<std::string>& data);

private:
    bool    hasError_;
    int*    data_;
    size_t  size_;

};
