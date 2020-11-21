#include "Shop.h"


Shop::Shop()
{
    List[0] = {"1.Increase Max Health", 3};
    List[1] = {"2.Healing potion", 1};
    List[2] = {"3.Upgrade Weapon", 2};
    List[3] = {"4.Upgrade Armor", 2};
}

void Shop::DisplayShop(Player p1){
    system("cls");
    puts("************************************************");
    puts("*****   Welcome to the Universal shop :)   *****");
    puts("************************************************");
    puts("\nWhat would you like to buy?\n");

    int Weapon = p1.getWeapon()+1;
    int Armor = p1.getArmor()+1;
    int MaxHealth = p1.getHealthRank()+1;
    int Health = p1.getHealth()+1;
    int arr[4] = {MaxHealth, Health, Weapon, Armor};
    for(int i = 0 ; i < 4 ; ++i){
        if(i == 1)  cout << List[i].first << "\nPrice: " << List[i].second << "\n\n";
        else    cout << List[i].first << "\nPrice: " << List[i].second * arr[i] << "\n\n";
    }
    puts("5.Exit\n");

}

