#include "EventMaker.h"
default_random_engine Rgen(time(0));

EventMaker::EventMaker(){

    int ln, pn;     ///level number and players' number
    printf("************************************************\nWhich level would you like to play? ");
    scanf("%d", &ln);

    puts("************************************************");

    MakeLevel(ln);
    DisplayLevel();
}

int EventMaker::Fight(){

    uniform_int_distribution roll(1,1000), Ehealth(35,100);
    roll(Rgen); Ehealth(Rgen);

    bool flag = 1;
    int chance, nextmove;

    int PHP = player.getHealth(), PDMG = player.getDamage() + (10*player.getWeapon());

    int EHP = Ehealth(Rgen);
    int EDMG = EHP/2;

    while(PHP > 0 && EHP > 0){

        if(flag){
            start:;
            system("cls");
            printf("Choose your action!\tYour Health: %d\n********************\tEnemy's Health: %d\n1.Attack\t\tPotions: %d\n2.Flee\n3.Heal\n********************\n", PHP, EHP, player.getPotions());
            nextmove = getch();
            switch(nextmove){
            case '1':
                chance = roll(Rgen);
                if(chance >= 950){
                    puts("\n********************\nYou swing your sword but the enemy manages to dodges hopping back from your attack\n********************");
                }
                else if(chance >= 50){
                    puts("\n********************\nYou dashed towards the enemy fiercely slashing it quickly before\nHopping back to your initial position\n********************");
                    EHP -= PDMG;
                }
                else{
                    puts("\n********************\nYou charged quickly grinding your great sword against the ground before jumping extremely high up\nBefore smashing the ground as you fall right on top of the enemy tearing them up into several bits.\n********************");
                    EHP = 0;
                }
                getch();
                break;
            case '2':
                chance = roll(Rgen);
                if(chance > 500){
                    puts("\n********************\nYou picked up a stone from the ground and threw it at the enemy hitting it in the eye\nBy the time the enemy regained its vision, you were no where to be seen\n********************");
                    getch();
                    player.setHealth(PHP);

                    return 2;
                }
                else
                    puts("\n********************\nYou tried to run away from the scene but the enemy chased you down.You were forced to get back into combat\n");
                getch();
                break;
            case '3':
                if(!player.getPotions()){puts("\n********************\nYou don't have any potions left to consume\n********************"); getch(); goto start;}
                player.UpdatePotions(-1);
                PHP += min(100, 200 + (50* player.getHealthRank()));
                break;
            default:
                puts("Invalid option, please choose an item from the previous list...\nPress any key to go back...\n");
                getch();
                goto start;
            }
        }
        else{
            chance = roll(Rgen);
            puts("********************\nThe Enemy aimed its shining bow at you locking the target as you try to dodge");
            if(chance >= 850){
                puts("The arrow barely scratches your shoulder dealing no damaged");
            }
            else if(chance >= 10){
                puts("The arrow Hits your upper back dealing some decent damage");
                PHP -= nextmove == '2'? 5:EDMG;
            }
            else{
                puts("Before it shoots, you find the arrow glowing very bright as it leaves the bow\nLeaving a luminous trail behind as it spin its way through your heart dropping your health greatly!\n");
                PHP -= nextmove == '2'? 50:100;
            }
            puts("\n********************\n");
            getch();
            if(PHP <= 0){
                system("cls");
                puts("\n********************\nYou fell on your back before your blood start running all over the ground like a raging river.\nYou last words left a mark through the hearts of everyone who read your own heroic story\n********************\n");
                return 0;
            }
        }

        flag = !flag;
    }

    player.setHealth(PHP + 30);
    player.IncNOEK();
    return 1;
}

int EventMaker::Options(){
    system("cls");
    puts("\t\tOptions\n\t*************************\n\t1.Select another level\n\t2.Exit game\n\t*************************\n");
    return getch();
}

void EventMaker::OpenShop(){
        int num ;
        int money = player.getMoney();

        while(1){
            shop.DisplayShop(player);
            printf("Your Money: %d\n", money);

            start:;
            num = getch() - '0';
            if(num == 176){
                getch();
                goto start;
            }

            if(num == 5){break;}
            if(num > 0 && num < 5){
                switch(num){
                case 1:
                    if(money >= shop.getValue(num) + (2*player.getHealthRank())){
                        money -= shop.getValue(num) + (2*player.getHealthRank());
                        puts("Max Health Increased\n");
                        player.UpHealth();
                    }
                    else
                        puts("Sorry, You don't have enough money to buy this item.");
                    break;
                case 2:
                    money -= shop.getValue(num);
                    puts("Red potion? why not\n");
                    player.UpdatePotions(1);
                    break;
                case 3:
                    if(money >= shop.getValue(num) + (2*player.getWeapon())){
                        money -= shop.getValue(num) + (2*player.getWeapon());
                        puts("Weapons Sharpened\n");
                        player.UpWeapon();
                    }
                    else
                        puts("Sorry, You don't have enough money to buy this item.");
                    break;
                case 4:
                    if(money >= shop.getValue(num) + (2*player.getArmor())){
                        money -= shop.getValue(num) + (2*player.getArmor());
                        puts("Armor polished :D.\n");
                        player.UpArmor();
                    }
                    else
                        puts("Sorry, You don't have enough money to buy this item.");
                    break;
                }
            } else
                puts("Invalid input press a number from 1 to 4 :) ");
        }
            player.setMoney(money);
}

void EventMaker::MakeLevel(int ln){

    if(ln > 4 || ln < 1){
        puts("The level you requested doesn't exist (Valid levels 1~4)\nPress and key to continue...");
        getch();
        return;
    }

    ifstream input;
    string fileName = "level", levelNum = " ";
    levelNum[0] = ln + '0';
    fileName = fileName + levelNum + ".txt";
    input.open(fileName);

    ///input.open("level1.txt");
    input >> _rows >> _columns;
    input >> _Pr >> _Pc;

    input >> NumOfDoors;
    for(int i = 0 ; i < NumOfDoors ; ++i){
        int x,y,v;
        input >> x >> y >> v;
        Doors.push_back({{x,y}, v});
    }

    for(int i = 0 ; i < _rows ; ++i){
        input >> level[i];
    }
}

void EventMaker::DisplayLevel(){
    system("cls");
    puts("\n");
    printf("\tHealth: %d\tPotions: %d\tMoney: %d\tEnemies Killed: %d\n", player.getHealth(), player.getPotions(), player.getMoney(), player.getNOEK());

    for(int i = 0 ; i < _rows ; ++i){
        for(int j = 0 ; j < _columns; ++j){
            if(abs(i - _Pr) <= 2 && abs(j - _Pc) <= 3)    printf("%c", level[i][j]);
            else printf(" ");
        }
        puts("");
    }

    printf("\nControls:\nUp Arrow -> Go Up\tDown Arrow -> Go Down\nLeft Arrow -> Go Left\tRight Arrow -> Go Right\nH -> Use Potion\n\n\n");
}

bool EventMaker::valid(int row, int col){
    return row < _rows && col < _columns && row >= 0 && col >= 0 && level[row][col] != '#';
}

int EventMaker::TakeAction(int row,int col){

    if(level[row][col] == 'S' || level[row][col] == 's'){
        int action = Fight();
        if(!action) return 0;
        else if(action == 2){
            DisplayLevel();
            return 1;
        }
    }
    else if(level[row][col] == '$'){
        OpenShop();
        goto label;
    }
    else if(level[row][col] == '0'){
        player.UpMoney();
    }
    else if(level[row][col] == 'D'){

        int val;
        for(int i = 0 ; i < NumOfDoors ; ++i){
            if((Doors[i].first).first == row && (Doors[i].first).second == col)
                val = Doors[i].second;
                cout << (Doors[i].first).first << " " << row << "\n" << (Doors[i].first).second << " " << col << "\n" << Doors[i].second << "\n";
        }
        if(player.getNOEK() >= val){
            system("cls");
            puts("\n********************\nACCESS GRANTED\nPress enter to open the door\n********************\n");
            getch();

            if(level[row][col+1] == 'D')    level[row][col+1] = '.';
            if(level[row][col-1] == 'D')    level[row][col-1] = '.';
            if(level[row+1][col] == 'D')    level[row+1][col] = '.';
            if(level[row-1][col] == 'D')    level[row-1][col] = '.';
        }
        else{
            system("cls");
            printf("\n********************\nYou need to kill %d enemies to pass through here.\nPress enter to go back\n********************\n", val);
            getch();
            DisplayLevel();
            return 1;
        }
    }
    else if(level[row][col] == 'W'){
        system("cls");
        puts("\n\t********************\n\t   -{!YOU WIN!}-   \n\t********************\n");
        getch();
        return 2;
    }

    level[_Pr][_Pc] = '.';
    level[row][col] = '^';
    _Pr = row; _Pc = col;
    label:;
    DisplayLevel();
    return 1;
}

int EventMaker::MakeMove(){

    int row, col;
    int Move = getch();
    if(Move == 224){
        switch(getch()){
        case 72:
            row = _Pr-1;
            col = _Pc;
            break;
        case 75:
            row = _Pr;
            col = _Pc-1;
            break;
        case 80:
            row = _Pr+1;
            col = _Pc;
            break;
        case 77:
            row = _Pr;
            col = _Pc+1;
            break;
        }
    } else if(Move == 'H' || Move == 'h'){
        if(player.getPotions()){
            if(player.getHealth() < 200 + (50* player.getHealthRank())){
                player.UpdateHealth(100);
                player.UpdatePotions(-1);
                system("cls");
                DisplayLevel();
            }
            else{
                system("cls");
                puts("\n********************\nYour Health is already full\n********************\n");
                getch();
            }
        }
        else{
            system("cls");
            puts("\n********************\nYou don't have any potions\n********************\n");
            getch();
        }
        return 1;
    } else if(Move == 27){
        start:;
        int choice = Options();
        if(choice == '1')  return 2;
        else if(choice == '2') return 0;
        else if (choice == 27) return 1;
        else{
            puts("Invalid input.");
            goto start;
        }
    }

    if(valid(row, col)){
        int num = TakeAction(row, col);
        if(!num)
            return 0;
        else if(num == 2)
            return 2;
    }
    return 1;
}
