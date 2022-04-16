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

        //chooses random number that's either 1, 2, or 3
        srand (time(NULL));
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
