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
#include <stdio.h>

using namespace std;

void showDoor(int);
int otherDoor(int, int);
void allDoors();
void door1();
void door2();
void door3();

#define BUFFER_SIZE 2048
#define PORT "8888"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    /* START: setting up server */

    FILE *fp; 
    struct hostent *hp; 
    struct sockaddr_in sin;
    char buf[BUFFER_SIZE]; 
    int buf_len; 
    int s;
    char* port = argv[1];
 
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
    sin.sin_port = htons(atoi(port)); 
 
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

    /* END: setting up server */

    /* START: game code */
    
    int doorDecision;
    int selection;
    int winningDoor;
    int unopenedDoor;
    int stayWins = 0;
    int switchWins = 0;
    int goatDoor;
    int win;

    //game show intro
    cout << "Welcome to the WAP show! The way the game works is pretty simple, so don't fret."
            << " You'll be presented three doors, two of which will contain goats and one will contain a"
            << " brand new car! Pick any door you feel that the car is behind. We will then reveal a door that has the goat."
            << " You'll then be asked if you would like to choose the unreaveled door or keep the door you originally"
            << " picked. Once you lock in your answer, we will reveal what's behind the two doors. You'll either get"
            << " a goat or a new car. Feeling lucky? Will you end up choosing the right door? Alright, let's play!"
            << endl << endl;

    cout << "Press Enter to Continue";
    cin.get();
    
    // game loop
    for (int round = 1; round < 4; round++)
    {
        allDoors();

        cout << "You're presented with three closed doors. Which one do you think has the car behind it?" << endl << endl;

        // loop to verify input
        while (1)
        {
            cout << "Enter your guess ('1', '2', or '3'): ";
            // makes user select 1 of the 3 doors
            cin >> selection;
            if (selection >= 1 && selection <= 3)
            {
                break;
            }
            else 
            {
                cout << "You said something other than '1', '2', or '3'! Let's try that again." << endl;
            }
        }

        // send the choice to the server
        memset(buf, 0, sizeof(buf));
        buf[0] = '0' + selection;
        if(send(s, buf, sizeof(buf), 0) < 0) { 
            perror("client: send"); 
        }

        // get door with goat from server
        memset(buf, 0, sizeof(buf));
        buf_len = recv(s, buf, sizeof(buf), 0);
        buf[buf_len] = '\0';
        goatDoor = atoi(buf);

        cout << "You've selected door " << selection << ". Are you ready to reveal which door a goat is behind? (Press Enter to Continue)";
        // cin.ignore();
        cin.get();
        cin.ignore();

        showDoor(goatDoor);

        cout << endl << "Now that we have revealed the door with a goat behind it, you have a tough decision to make."
                    << "There's a 50/50 chance you could get the door with the car behind it. But the question is..."
                    << "would you like to keep the door you've chosen or test your luck with the unopened door?" << endl
                    << endl << "(Type '1' to keep your chosen door)" << endl << "(Type '2' to choose the unopened door): " << endl;

        //loops for correct user input for switch/keep door
        while(1)
        {
            cin >> doorDecision; //keep or switch doors
            if (doorDecision != 1 && doorDecision != 2)
            {
                cout << "Are you really cut out to be a WAP star? You need to select 1 (stay with your chosen door) or 2 (change your decision): ";
            }
            else
            {
                break;
            }
        }

        // swap guess
        if (doorDecision == 2)
        {
            selection = otherDoor(selection, goatDoor);
        }

        // send the choice to the server
        memset(buf, 0, sizeof(buf));
        buf[0] = '0' + selection;
        if(send(s, buf, sizeof(buf), 0) < 0) { 
            perror("client: send"); 
        }

        // get win or lose
        memset(buf, 0, sizeof(buf));
        buf_len = recv(s, buf, sizeof(buf), 0);
        buf[buf_len] = '\0';
        win = atoi(buf);

        winningDoor = selection;
        if (!win) {
            winningDoor = otherDoor(goatDoor, selection);
        }

        cout << "Okay, so you selected door " << selection << ". Are you ready to reveal which door the car is behind? (Press Enter to Continue)";
        cin.get();
        cin.ignore();

        cout << endl << "The car is behind door " << winningDoor << "!" << endl;
        showDoor(winningDoor);

        if (win)
        {
            if (doorDecision == 2)
            {
                switchWins++;
            }
            else
            {
                stayWins++;
            }
            cout << "Congratulations WAPstar! The car was indeed behind door " << selection << ", and you won round " << round << "! Let's move on to our next round." << endl;
        }
        else
        {
            cout << "Oof! You didn't win round " << round << ". But there's always the next round!" << endl;
        }
        if (round < 3) {
            cout << "Press Enter when you're ready for the next round";
            cin.get();
        }
    }

 /* END: game code */

cout << endl << "Out of 3 rounds, our contestant won " << stayWins << " times by staying with their original choice and won "
                << switchWins << " times by switching their choice." << endl 
                << endl << "And that will conclude our WAP show! Do you think you could be our next WAP star? "
                << "Test your luck by calling 999-999-9999! " << "See you next time!" << endl;
 
    return 0;
}

int otherDoor(int door1, int door2)
{
    int doors[3] = {1, 2, 3};
    if (door1 == door2)
    {
        doors[2] = doors[door1-1];
        doors[door1-1] = 3;
        return doors[rand() % 2];
    }
    for (int otherDoor : doors)
    {
        if (door1 != otherDoor && door2 != otherDoor)
        {
            return otherDoor;
        }
    }
    return 1;
}

void showDoor(int door)
{
    switch (door)
    {
        case 1:
            door1();
            break;
        case 2:
            door2();
            break;
        case 3:
            door3();
            break;
    }
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