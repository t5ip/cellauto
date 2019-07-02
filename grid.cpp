#include grid.h

Grid::Grid()
{
    iColumnToBeEdited = 0;
    iRowToBeEdited = 0;
}

void Grid::setWidthAndHeigth(int iWidth, int iHeight)
{
    iGrid.resize(iWidth);
    for (int i=0; i<iWidth; i++)
    {
        iGrid[i].resize(iHeight);
    }
}

void Grid::setWidthAndHeigth(int iWidth, int iHeight)
{

}

void Grid::setColumnToEdit(int iColumn)
{

}

void Grid::setRowToEdit(int iRow)
{

}

void Grid::setValueToCell(int iValue)
{

}

void Grid::setColumnToInspect(int iColumn)
{

}

void Grid::setRowToInspect(int iRow)
{

}

int  Grid::getValue()
{

}
