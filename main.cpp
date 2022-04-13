//
//  main.cpp
//  MontyHall
//
//  Created by Christine Helenick on 4/13/22.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int games = 0;
    int stayWins = 0;
    int switchWins = 0;
    int chosenDoor;
    int remainingDoor;
    int winningDoor;
    int option;
    
    void allDoors();
    void door1();
    void door2();
    void door3();

    //chooses random number that's either 1, 2, or 3
    srand (time(NULL));
    chosenDoor = rand() % 3 + 1;
    winningDoor = rand() % 3 + 1;
    
    allDoors();
    cout << "Select a door \n";
    
    // makes user select 1 of the 3 doors
    int selection;
    cin >> selection;

    // TODO add if else statements to compare their selection and then
    // call the corresponding door method that displays the corresponding ASCII art

    // TODO a do while isn't necessary but we need the logic for 3 rounds of the game to be
    // executed with different random winning doors each round
    do
    {
        
    } while (games < 3);

    cout << "\n Out of 3, the contestant won " << stayWins << " times by staying with his/her original choice and won " << switchWins << " times by switching his/her choice.\n";
    
    return 0;
}

void allDoors(){
    
    cout << R"(
             _______________    _______________    _______________
            |\ ___________ /|  |\ ___________ /|  |\ ___________ /|
            | |  _ _ _ _  | |  | |  _ _ _ _  | |  | |  _ _ _ _  | |
            | | | | | | | | |  | | | | | | | | |  | | | | | | | | |
            | | |-+ 1 +-| | |  | | |-+ 2 +-| | |  | | |-+ 3 +-| | |
            | | |-+ | +%| | |  | | |-+ | +%| | |  | | |-+ | +%| | |
            | | |_|_|_|_| | |  | | |_|_|_|_| | |  | | |_|_|_|_| | |
            | |    ___    | |  | |    ___    | |  | |    ___    | |
            | |   [___] ()| |  | |   [___] ()| |  | |   [___] ()| |
            | |         ||| |  | |         ||| |  | |         ||| |
            | |         ()| |  | |         ()| |  | |         ()| |
            | |           | |  | |           | |  | |           | |
            | |           | |  | |           | |  | |           | |
            | |           | |  | |           | |  | |           | |
            |_|___________|_|  |_|___________|_|  |_|___________|_|

            )";
}

void door1(){
    
    cout << R"(
             _______________    _______________    _______________
            |\ ___________ /|  |\ ___________ /|  |\ ___________ /|
            | |  /|,| |   | |  | |  _ _ _ _  | |  | |  _ _ _ _  | |
            | | | 1 | |   | |  | | | | | | | | |  | | | | | | | | |
            | | |,x,' |   | |  | | |-+ 2 +-| | |  | | |-+ 3 +-| | |
            | | |,x   ,   | |  | | |-+ | +%| | |  | | |-+ | +%| | |
            | | |/    |   | |  | | |_|_|_|_| | |  | | |_|_|_|_| | |
            | |    /] ,   | |  | |    ___    | |  | |    ___    | |
            | |   [/ ()   | |  | |   [___] ()| |  | |   [___] ()| |
            | |       |   | |  | |         ||| |  | |         ||| |
            | |       |   | |  | |         ()| |  | |         ()| |
            | |       |   | |  | |           | |  | |           | |
            | |      ,'   | |  | |           | |  | |           | |
            | |   ,'      | |  | |           | |  | |           | |
            |_|,'_________|_|  |_|___________|_|  |_|___________|_|
            
            )";
}

void door2(){
    
    cout << R"(
             _______________    _______________    _______________
            |\ ___________ /|  |\ ___________ /|  |\ ___________ /|
            | |  _ _ _ _  | |  | |  /|,| |   | |  | |  _ _ _ _  | |
            | | | | | | | | |  | | | 2 | |   | |  | | | | | | | | |
            | | |-+ 1 +-| | |  | | |,x,' |   | |  | | |-+ 3 +-| | |
            | | |-+ | +%| | |  | | |,x   ,   | |  | | |-+ | +%| | |
            | | |_|_|_|_| | |  | | |/    |   | |  | | |_|_|_|_| | |
            | |    ___    | |  | |    /] ,   | |  | |    ___    | |
            | |   [___] ()| |  | |   [/ ()   | |  | |   [___] ()| |
            | |         ||| |  | |       |   | |  | |         ||| |
            | |         ()| |  | |       |   | |  | |         ()| |
            | |           | |  | |       |   | |  | |           | |
            | |           | |  | |      ,'   | |  | |           | |
            | |           | |  | |   ,'      | |  | |           | |
            |_|___________|_|  |_|,'_________|_|  |_|___________|_|
            
            )";
}

void door3(){
    
    cout << R"(
             _______________    _______________    _______________
            |\ ___________ /|  |\ ___________ /|  |\ ___________ /|
            | |  _ _ _ _  | |  | |  _ _ _ _  | |  | |  /|,| |   | |
            | | | | | | | | |  | | | | | | | | |  | | | 3 | |   | |
            | | |-+ 1 +-| | |  | | |-+ 2 +-| | |  | | |,x,' |   | |
            | | |-+ | +%| | |  | | |-+ | +%| | |  | | |,x   ,   | |
            | | |_|_|_|_| | |  | | |/    |   | |  | | |_|_|_|_| | |
            | |    ___    | |  | |    ___    | |  | |    /] ,   | |
            | |   [___] ()| |  | |   [___] ()| |  | |   [/ ()   | |
            | |         ||| |  | |         ||| |  | |       |   | |
            | |         ()| |  | |         ()| |  | |       |   | |
            | |           | |  | |           | |  | |       |   | |
            | |           | |  | |           | |  | |      ,'   | |
            | |           | |  | |           | |  | |   ,'      | |
            |_|___________|_|  |_|___________|_|  |_|,'_________|_|
            
            )";
}
