#ifndef SHOP_H
#define SHOP_H
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <conio.h>
#include <string>
#include <utility>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>
#include "Player.h"

using namespace std;

class Shop
{
    public:
        Shop();
        void DisplayShop(Player p1);

        int getValue(int pos){return List[pos-1].second;}
    private:
        pair<string, int> List[4];
};

#endif // SHOP_H
