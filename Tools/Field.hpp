#pragma once

#include <iostream>

class Field
{
public:
    Field() = delete;
    ~Field() = delete;
    
    /*
    * @brief swap current cell with upper cell 
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    * @return true if swap was done, false if error takes place
    */ 
    static bool     Up(int* field, size_t size);

    /*
    * @brief swap current cell with cell below
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    * @return true if swap was done, false if error takes place
    */ 
    static bool     Down(int* field, size_t size);

    /*
    * @brief swap current cell with left cell
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    * @return true if swap was done, false if error takes place
    */ 
    static bool     Left(int* field, size_t size);

    /*
    * @brief swap current cell with right cell
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    * @return true if swap was done, false if error takes place
    */ 
    static bool     Right(int* field, size_t size);

    /*
    * @brief print's field nicely
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    */ 
    static void     Print(int* field, size_t size);

    /*
    * @brief Same, but faster
    */ 
    static void     PrintPrintf(int* field, size_t size);

    /*
    * @brief finds position  of empty cell on the field
    * @param field - the field itself like flat 2d array
    * @param size - the size of the 'edge' of the array
    * @return empty cell position in array, if it can't be found - '-1'
    */ 
    static int      FindZeroPos(int* field, size_t size);

    /*
    * @brief creates a field with 'snail solution'
    * @param size - size of the field
    * @return pointer to the new generated 'snail field' 
    */
    static int      *CreateSnailGrid(int *field = nullptr, size_t size = 0);
};