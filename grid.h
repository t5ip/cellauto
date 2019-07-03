#ifndef __GRID_H
#define __GRID_H

#include <vector>

using namespace std;

class Grid 
{
public: 
    Grid();
    void setWidthAndHeight(int iNewWidth, int iNewHeight);
    void setColumnToEdit(int iColumn);
    void setRowToEdit(int iRow);
    void setValue(int iValue);
    void setColumnToInspect(int iColumn);
    void setRowToInspect(int iRow);
    int  getValue();
    void invertValue();
    Grid& operator=(const Grid& other);// copy assignment
private: 
    void initialize();
    vector< vector<int> > grid;
    int iColumnToBeEdited;
    int iRowToBeEdited;
    int iColumnToBeInspected;
    int iRowToBeInspected;
    int iWidth;
    int iHeight;
};

#endif
