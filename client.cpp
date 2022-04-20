//
//  client.cpp
//  MontyHall
//
//  Created by Trenton Paul on 4/15/22.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
using namespace std;
    
void allDoors();
void door1();
void door2();
void door3();

#define BUFFER_SIZE 2048
#define PORT "8888"

int main()
{
    int winningDoor;
    int unopenedDoor;

    FILE *fp; 
    struct hostent *hp; 
    struct sockaddr_in sin;
    char buf[BUFFER_SIZE]; 
    int s;
 
    /* translate host name into peer's IP address */ 
    hp = gethostbyname("localhost"); 
    if (!hp) { 
        fprintf(stderr, "%s: unknown host\n", "localhost"); 
        exit(1); 
    } 
 
    /* build address data structure */ 
    bzero((char *)&sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length); 
    sin.sin_port = htons(atoi(PORT)); 
 
    /* active open */ 
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("client: socket"); 
        exit(1); 
    } 
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) 
    { 
        perror("client: connect"); 
        close(s); 
        exit(1); 
    }

    
    int doorDecision;

    //game show intro
    cout << "Welcome to the WAP show! The way the game works is pretty simple, so don't fret."
            << "You'll be presented three doors, two of which will contain goats and one will contain a"
            << "brand new car! Pick any door you feel that the car is behind. We will then reveal the door that has the goat."
            << "You'll then be asked if you would like to choose the unreaveled door or keep the door you originally"
            << "picked. Once you lock in your answer, we will then reveal what's behind the two doors. You'll either get"
            << "a goat or a new car. Feeling lucky? Will you end up choosing the right door? Alright, let's play!"
            << endl << endl;
    
    // game loop
    for (int i = 0; i < 3; i++)
    {
         cout << "Select a door \n";

        // makes user select 1 of the 3 doors
        int selection;
        cin >> selection;

        cout << "You've chosen door " << selection << ". Let's see what's behind one of the other doors!" << endl;


        allDoors();

        //loops user input for corresponding doors
        while(1)
        {
            if(selection == 1)
            {
                door1();
                break;
            }
            else if(selection == 2)
            {
                door2();
                break;
            }
            else if(selection == 3)
            {
                door3();
                break;
            }
            else
            {
                allDoors();
                cout << "Please select door 1, 2, or 3." << endl;
            }
        }

        // send the choice to the server

        // get door with goat from server

        cout << R"(Now that we have revealed the door with the goat behind it, you have a tough decision to make.
                     There's a 50/50 chance you could get the door with the car behind it. But the question is...
                     would you like to keep the door you've chosen or test your luck with the unopened door?)" << endl
                     << endl << "(Type '1' to keep your chosen door)" << endl << "(Type '2' to choose the unopened door): " << endl;

        //loops for correct user input for switch/keep door
        while(1)
        {
            cin >> doorDecision; //keep or switch doors
            if (doorDecision != 1 || doorDecision != 2)
            {
                cout << "Are you really cut out to be a WAP star? You need to select 1 (stay with your chosen door) or 2 (change your decision): ";
            }
            else
            {
                break;
            }
        }

        if(doorDecision == 1 && winningDoor == selection) //user keeps original door
        {
            stayWins++;
        }
        else if(doorDecision == 2 && winningDoor == selection) //user switches to unopened door
        {
            selection = unopenedDoor;

            if(selection == winningDoor)
            {
                switchWins++;
            }
        }

        //door 1 selection if statements 
        if(winningDoor == 2 && selection == 1)
        {
            cout << R"(Well would you look at that. Door 3 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
            
        }
        else if(winningDoor == 3 && selection ==1)
        {
            cout << R"(Well would you look at that. Door 2 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
        }

        //door 2 selection if satements
        else if(winningDoor == 1 && selection == 2)
        {
            cout << R"(Well would you look at that. Door 3 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
            
        }
        else if(winningDoor == 3 && selection == 2)
        {
            cout << R"(Well would you look at that. Door 1 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
        }

        //door 3 selection if statements
        else if(winningDoor == 1 && selection == 3)
        {
            cout << R"(Well would you look at that. Door 2 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
        }
        else if(winningDoor == 2 && selection == 3)
        {
            cout << R"(Well would you look at that. Door 1 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
        }
        else if(winningDoor == selection) //defaults goat door to door 2
        {
            cout << R"(Well would you look at that. Door 2 had a goat behind it. You're lucky you didn't 
                    pick that one, am I right?)" << endl;
            unopenedDoor = 3;
        }

        //LOGIC: since we've already eliminated a door, the other door has to be the winning door since it's
            //       not = to the user's selection
            if(winningDoor != selection)
            {
                unopenedDoor = winningDoor;
            }

            cout << endl << "Out of 3 rounds, our contestant won " << stayWins << " times by staying with their original choice and won "
                << switchWins << " times by switching their choice." << endl 
                << endl << "And that will conclude our WAP show! Do you think you could be our next WAP star? "
                << "Test your luck by calling 999-999-9999! " << "See you next time!";
    }

   
 

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