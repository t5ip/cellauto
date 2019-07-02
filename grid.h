#ifndef __GRID_H
#define __GRID_H

class Grid 
{
public: 
    Grid();
    void setWidthAndHeigth(int iWidth, int iHeight);
    void setColumnToEdit(int iColumn);
    void setRowToEdit(int iRow);
    void setValueToCell(int iValue);
    void setColumnToInspect(int iColumn);
    void setRowToInspect(int iRow);
    int  getValue();
private: 
    vector< vector<int> > iGrid;
    int iColumnToBeEdited;
    int iRowToBeEdited;
}

#endif
