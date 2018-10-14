#include "Parser.hpp"

#include <fstream>
#include <cctype>


Parser::Parser(const char* name)
    : hasError_(false)
    , data_(nullptr)
{
    // Load file content
    std::ifstream ifs(name);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    // Remove spaces
    Common::tools::compressChars(content, ' ');
    Common::tools::trim(content);

    // Split by \n to get all rows, use it's count a edge size of the gamefield
    auto splitted = Common::tools::split(content, '\n');
    size_ = splitted.size();
    std::vector<std::string> data; // vector to store data in string format
    for (const auto& str : splitted)
    {
        auto splittedData = Common::tools::split(str, ' ');
        if (splittedData.size() != size_)
        {
            std::cout << "Error: size: " << splittedData.size() << " not match size_: " << size_ << std::endl;
            hasError_ = true;
            return;
        }
        for (const auto& d : splittedData)
            data.push_back(d);
    }
    if (data.size() != size_ * size_)
    {
        std::cout << "Error: size is not correct! Expected: " << size_ * size_ << " Got: " << data.size() << std::endl;
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
    std::cout << "Error: Invalid character!" << std::endl;
    hasError_ = true;
}

Parser::~Parser()
{
    delete[] data_;
}

int* Parser::GetData(size_t& size)
{
    if (HasErrors())
    {
        size = 0;
        return (nullptr);
    }
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
