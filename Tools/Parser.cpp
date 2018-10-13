#include "Parser.hpp"

#include <fstream>
#include <cctype>


Parser::Parser(const char* name)
    : hasError_(false)
    , data_(nullptr)
{
    std::ifstream ifs(name);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    auto splitted = Common::split(content, '\n');
    size_ = splitted.size();
    std::vector<std::string> data;
    for (const auto& str : splitted)
    {
        auto data = Common::split(str, ' ');
        if (data.size() != size_)
        {
            hasError_ = true;
            return;
        }
        for (const auto& d : data)
            data.push_back(d);
    }
    if (data.size() != size_ * size_)
    {
        hasError_ = true;
        return;
    }

    if ( ValidateData(data) )
    {
        data_ = new int(size_ * size_);
        for (int i = 0; i < data.size(); i++)
            data_[i] = std::stoi(data[i]);
        return;
    }
    hasError_ = true;
}

int* Parser::GetData(size_t& size)
{
    size = size_;
    return (data_);
}

bool Parser::HasErrors()
{
    return (hasError_);
}

bool Parser::ValidateData(const std::vector<std::string>& data)
{
    for (const auto& d : data)
    {
        for (const auto& c : d)
        {
            if (!isdigit(c))
            {
                hasError_ = true;
                return (false);
            }
        }
    }
    return (true);
}
