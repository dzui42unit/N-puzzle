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

    // if (!ValidateSolution())
    // {
    //     isSolvable_ = false;
    //     return ;
    // }
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
    // size_t blank_space_row_pos = GetBlankRowPosition();
    // size_t inversions = CountInversions();

    // std::cout << "Blank space row: " << blank_space_row_pos << std::endl;
    // std::cout << "Number of inversions: " << inversions << std::endl;

    // int parity = 0;
    // int gridWidth = (int) Math.sqrt(puzzle.length);
    // int row = 0; // the current row we are on
    // int blankRow = 0; // the row with the blank tile

    // for (int i = 0; i < puzzle.length; i++)
    // {
    //     if (i % gridWidth == 0) { // advance to next row
    //         row++;
    //     }
    //     if (puzzle[i] == 0) { // the blank tile
    //         blankRow = row; // save the row on which encountered
    //         continue;
    //     }
    //     for (int j = i + 1; j < puzzle.length; j++)
    //     {
    //         if (puzzle[i] > puzzle[j] && puzzle[j] != 0)
    //         {
    //             parity++;
    //         }
    //     }
    // }

    // if (gridWidth % 2 == 0) { // even grid
    //     if (blankRow % 2 == 0) { // blank on odd row; counting from bottom
    //         return parity % 2 == 0;
    //     } else { // blank on even row; counting from bottom
    //         return parity % 2 != 0;
    //     }
    // } else { // odd grid
    //     return parity % 2 == 0;
    // }


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
    for (size_t i = 0; i < (size_ * size_); i++)
    {
        int cur_invers = 0;
        for (size_t j = i + 1; j < size_ * size_; j++)
        {
            if (data_[j] && data_[i] > data_[j])
            {
                cur_invers++;
                inversions++;
            }
        }
        std::cout << data_[i] << " gives: " << cur_invers << std::endl;
    }
    return (inversions);
}

bool    Parser::IsSolvable(void)
{
    return (isSolvable_);
}