#include "grid.h"

Grid::Grid()
{
    iColumnToBeEdited = 0;
    iRowToBeEdited = 0;
    iColumnToBeInspected = 0;
    iRowToBeInspected = 0;
}

void Grid::setWidthAndHeight(int iWidth, int iHeight)
{
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
