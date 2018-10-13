#pragma once

#include "Common.hpp"

class Parser
{
public:
    Parser(const char* name);
    Parser() = delete;
    ~Parser();

    int* GetData(size_t& size);
    bool HasErrors();

private:
    bool ValidateData(const std::vector<std::string>& data);

private:
    bool    hasError_;
    int*    data_;
    size_t  size_;

};
