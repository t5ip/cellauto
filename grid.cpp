#include "grid.h"

Grid::Grid()
{
    initialize();
}

void Grid::setWidthAndHeight(int iNewWidth, int iNewHeight)
{
    iWidth = iNewWidth;
    iHeight = iNewHeight;
    grid.resize(iWidth);
    for (int i=0; i<iWidth; i++)
    {
        grid[i].resize(iHeight);
    }
}

void Grid::setColumnToEdit(int iColumn)
{
    iColumnToBeEdited = iColumn;
}

void Grid::setRowToEdit(int iRow)
{
    iRowToBeEdited = iRow;
}

void Grid::setValue(int iValue)
{
    grid[iColumnToBeEdited][iRowToBeEdited] = iValue;
}

void Grid::setColumnToInspect(int iColumn)
{
    iColumnToBeInspected = iColumn;
}

void Grid::setRowToInspect(int iRow)
{
    iRowToBeInspected = iRow;
}

int  Grid::getValue()
{
    return grid[iColumnToBeInspected][iRowToBeInspected];
}
    
void Grid::invertValue()
{
    if (0 < grid[iColumnToBeEdited][iRowToBeEdited])
    {
        grid[iColumnToBeEdited][iRowToBeEdited] = 0;
    }    
    else
    {
        grid[iColumnToBeEdited][iRowToBeEdited] = 1;
    }    
}

Grid& Grid::operator=(const Grid& other) // copy assignment
{
    if (this != &other) 
    { // self-assignment check expected
        this->grid = other.grid;
        initialize();
    }
    return *this;
}

void Grid::initialize()
{
    iColumnToBeEdited = 0;
    iRowToBeEdited = 0;
    iColumnToBeInspected = 0;
    iRowToBeInspected = 0;
    iWidth = 0;
    iHeight = 0;
}
