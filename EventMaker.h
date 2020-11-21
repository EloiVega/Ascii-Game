#ifndef EVENTMAKER_H
#define EVENTMAKER_H
#include "Shop.h"

class EventMaker
{
    public:
        ///Construction methods
        EventMaker();
        void MakeLevel(int ln);
        void DisplayLevel();

        ///Action methods
        bool valid(int row, int col);
        int TakeAction(int row,int col);
        int Options();
        int MakeMove();
        int Fight();
        void OpenShop();

        ///Getters
        int getRows(){return _rows;}
        int getColumns(){return _columns;}
    private:
        char level[1000][1000];
        int _rows, _columns;
        int _Pr, _Pc;   ///Player row, Player Column
        Player player;
        Shop shop;
        int NumOfDoors;
        vector< pair< pair<int,int>, int > > Doors; /// x,y in terms of position and number of enemies needs to be killed
};

#endif // EVENTMAKER_H
