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

    // Split by \n to get all rows, use it's count a edge size of the gamefield
    auto splitted = Common::tools::split(content, '\n');
    // remove comments
    RemoveComments(splitted);
    // get size and remove size field
    GetSize(splitted);
    if (hasError_)
    {
        std::cout << "Error: Can't get size!" << std::endl;
        return;
    }

    std::vector<std::string> strData; // vector to store data in string format
    // get all data in str format
    for (auto& str : splitted)
    {
        Common::tools::trim(str);
        auto splittedData = Common::tools::split(str, ' ');
        if (splittedData.size() != size_)
        {
            std::cout << "Error: size: " << splittedData.size() << " not match size_: " << size_ << std::endl;
            hasError_ = true;
            return;
        }
        for (const auto& d : splittedData)
            strData.push_back(d);
    }
    if (strData.size() != size_ * size_)
    {
        std::cout << "Error: size is not correct! Expected: " << size_ * size_ << " Got: " << strData.size() << std::endl;
        hasError_ = true;
        return;
    }

    // If str data is valid convert it to int
    if ( ValidateData(strData) )
    {
        data_ = new int[size_ * size_];
        for (int i = 0; i < strData.size(); i++)
            data_[i] = std::stoi(strData[i]);
        return ;
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

void Parser::RemoveComments(std::vector<std::string>& data)
{
    // traverse vector and delete all char parts starting from # 
    for (int i = 0; i < data.size(); i++)
        data[i] = data[i].substr(0, data[i].find('#'));
    // remove empty strings from vector
    auto new_end = std::remove(data.begin(), data.end(), "");
    data.erase(new_end, data.end());
}

void Parser::GetSize(std::vector<std::string>& data)
{
    // check that 'size field' exists and is valid
    for (char c : data[0])
    {
        if (!isdigit(c))
        {
            hasError_ = true;
            return ;
        }  
    }
    // get size in int format
    size_ = std::stoi(data[0]);
    // delete now useless size field from vector
    data.erase(data.begin());
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
