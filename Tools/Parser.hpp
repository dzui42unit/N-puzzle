#pragma once

#include "Common.hpp"
#include "Field.hpp"

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

    /*
    *   @brief returns the size of grid
    *   @return the size size of grid as integer
    */
    size_t  GetGridSize(void) { return size_; }

    /*
    * @brief Called to see if the pazzle on N size is solvable
    * @return true if puzzle is solvable, false otherwise 
    */
    bool IsSolvable();

private:
    /*
    * @brief Ensures that the given values can be converted to int and is positive
    * @return true if data are valid, false otherwise
    */ 
    bool ValidateData(const std::vector<std::string>& data);

    /*
    * @brief Checks if the puzzle can be solved
    * @return true if the puzzle has solution, false otherwise
    */
    bool ValidateSolution(void);

    /*
    * @brief returns the row number of the blank element on the board counting from the bottom
    * @return integer number of the row
    */
    size_t  GetBlankRowPosition(void);

    /*
    *  @brief return the number of inversions
    *  inversion is a pair of tiles (a, b) where a > b and a appears before b
    */
    size_t  CountInversions(void);

    /*
    *   @brief returns the index of element in the 'snail field'
    *   @param number - represent the value whose index needs to be found
    *   @return integer value that represents index of the given element
    */
    int     GetSnailFieldIndex(int * grid, int number_to_find);

    void RemoveComments(std::vector<std::string>& data);
    void GetSize(std::vector<std::string>& data);

private:
    bool    hasError_;
    bool    isSolvable_;
    int*    data_;
    size_t  size_;
    int*    snail_grid_;

};
