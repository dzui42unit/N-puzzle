#include "Parser.hpp"

#include <fstream>
#include <cctype>


Parser::Parser(const char* name)
    : hasError_(false)
    , isSolvable_(true)
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
        for (size_t i = 0; i < strData.size(); i++)
            data_[i] = std::stoi(strData[i]);
    }
    else
    {
        std::cout << "Error: Invalid character!" << std::endl;
        hasError_ = true;
        return ;
    }

    if (!ValidateSolution())
    {
        isSolvable_ = false;
        return ;
    }
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
    for (size_t i = 0; i < data.size(); i++)
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

bool    Parser::ValidateSolution(void)
{
    size_t blank_space_row_pos = GetBlankRowPosition();
    size_t inversions = CountInversions();

    std::cout << "Blank space row: " << blank_space_row_pos << std::endl;
    std::cout << "Number of inversions: " << inversions << std::endl;
    if (size_ % 2 == 0) 
    {
        std::cout << "The size of puzzle is " << size_ << " and it is even" << std::endl;
        if (blank_space_row_pos % 2 == 0 && inversions % 2 != 0)
        {
            std::cout << "First condition is satisfied" << std::endl;
            std::cout << "Blank is on even and inversions odd" << std::endl;
            return (true);
        }
        if (blank_space_row_pos % 2 != 0 && inversions % 2 == 0)
        {
            std::cout << "Second condition is satisfied" << std::endl;
            std::cout << "Blank is on odd and inversions even" << std::endl;
            return (true);
        }
    }
    else
    {
        std::cout << "The size of puzzle is " << size_ << " and it is odd" << std::endl;
       if (inversions % 2 == 0)
       {
            std::cout << "First condition is satisfied" << std::endl;
            return (true);
       }
    }
    return (false);
}

size_t  Parser::GetBlankRowPosition(void)
{
    size_t blank_space_row;

    blank_space_row = 0;
    for ( ; blank_space_row < size_ * size_; blank_space_row++)
    {
        if (data_[blank_space_row] == 0)
        {
            blank_space_row = size_ - (blank_space_row / size_);
            break ;
        }
    }
    return (blank_space_row);
}

size_t  Parser::CountInversions(void)
{
    size_t inversions;

    inversions = 0;
    for (size_t a_pos = 0; a_pos < (size_ * size_) - 1; a_pos++)
    {
        for (size_t b_pos = a_pos + 1; b_pos < size_ * size_; b_pos++)
        {
            if (data_[a_pos] && data_[b_pos] && data_[a_pos] > data_[b_pos])
                inversions++;
        }
    }
    return (inversions);
}

bool    Parser::IsSolvable(void)
{
    return (isSolvable_);
}