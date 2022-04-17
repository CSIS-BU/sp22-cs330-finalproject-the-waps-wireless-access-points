//
//  server.cpp
//  MontyHall
//
//  Created by Christine Helenick on 4/13/22.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;
    
void allDoors();
void door1();
void door2();
void door3();

#define QUEUE_LENGTH 10
#define BUFFER_SIZE 2048
#define PORT "8888"

int main()
{
    /* START: setting up server */

    struct sockaddr_in sin; 
    char buf[BUFFER_SIZE]; 
    int buf_len; 
    socklen_t addr_len; 
    int s, new_s;
    int yes = 1;

    /* build address data structure */ 
    bzero((char *)&sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = INADDR_ANY; 
    sin.sin_port = htons(atoi(PORT)); 
 
    /* setup passive open */ 
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("server: socket"); 
        exit(1); 
    } 
    /* force resuse of socket and port */
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("server: setsockopt");
        return 1;
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) { 
        perror("server: bind"); 
        exit(1); 
    } 
    listen(s, QUEUE_LENGTH);

    /* END: setting up server */
    
    while(1) {
        if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) { 
            perror("server: accept");
            exit(1);
        }

        /* START: game code */
        
        int games = 0;
        int stayWins = 0;
        int switchWins = 0;
        int winningDoor;

        cout << "Welcome to the WAP show! The way the game works is pretty simple, so don't fret. 
                 You'll be presented three doors, two of which will contain goats and one will contain a
                 brand new car! Pick any door you feel that the car is behind. We will then reveal the door that has the goat.
                 You'll then be asked if you would like to choose the unreaveled door or keep the door you originally
                 picked. Once you lock in your answer, we will then reveal what's behind the two doors. You'll either get
                 a goat or a new car. Feeling lucky? Will you end up choosing the right door? Alright, let's play!";

        //start of the actual game
        while(games < 4)
        {
            //chooses random number that's either 1, 2, or 3
            srand (time(NULL));

            winningDoor = rand() % 3 + 1;
        
            allDoors();
            cout << "Select a door \n";
        
            // makes user select 1 of the 3 doors
            int selection;
            cin >> selection;

            //user input for corresponding doors
            while(selection != 1 && selection != 2 && selection != 3)
            {
                if(selection == 1)
                {
                    door1();
                }
                else if(selection == 2)
                {
                    door2();
                }
                else if(selection == 3)
                {
                    door3();
                }
                else
                {
                    cout << "Please select door 1, 2, or 3." << endl;
                }
            }

            //TODO: game logic for choosing the goat door after user selection
            cout << "You've chosen door " << selection << ". Let's see what's behind one of the other doors!" << endl;

            //door 1 selection if statements 
            if(winningDoor == 2 && selection == 1)
            {
                cout << "Well would you look at that. Door #3 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }
            else if(winningDoor == 3 && selection ==1)
            {
                cout << "Well would you look at that. Door #2 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }
        
            //door 2 selection if satements
            else if(winningDoor == 1 && selection == 2)
            {
                cout << "Well would you look at that. Door #3 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }
            else if(winningDoor == 3 && selection == 2)
            {
                cout << "Well would you look at that. Door #1 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }

            //door 3 selection if statements
            else if(winningDoor == 1 && selection == 3)
            {
                cout << "Well would you look at that. Door #2 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }
            else if(winningDoor == 2 && selection == 3)
            {
                cout << "Well would you look at that. Door #1 had a goat behind it. You're lucky you didn't 
                        pick that one, am I right?" << endl;
            }

            cout << "Now that we have revealed the door with the goat behind it, you have a tough decision to make.
                     There's a 50/50 chance you could get the door with the car behind it. But the question is...
                     would you like to keep the door you've chosen or test your luck with the unopened door?/n 
                     (Type '1' to keep your chosen door)/n
                     (Type '2' to choose the unopened door";

            games++;
        } //end of games

        cout << "\n Out of 3, the contestant won " << stayWins << " times by staying with his/her original choice and won " << switchWins << " times by switching his/her choice.\n";
        
        /* END: game code */
        
        close(new_s); 
    }
    close(s);
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
