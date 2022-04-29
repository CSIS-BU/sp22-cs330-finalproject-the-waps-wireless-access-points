//
//  server.cpp
//  MontyHall
//
//  Created by Christine Helenick on 4/13/22.
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
#include <vector>

using namespace std;

#define QUEUE_LENGTH 10
#define BUFFER_SIZE 2048
#define PORT "8888"

int otherDoor(int, int);

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
        
        //variables
        int rounds = 0;
        int winningDoor;
        int goatDoor;
        int guess;
        int result;

        //start of the actual game
        while(rounds < 3)
        {
            //chooses random number that's either 1, 2, or 3
            srand (time(NULL));
            winningDoor = rand() % 3 + 1;

            // get initial guess from client
            buf_len = recv(new_s, buf, sizeof(buf), 0);
            buf[buf_len] = '\0';
            guess = atoi(buf);

            goatDoor = otherDoor(winningDoor, guess);

            // send goat door to client
            memset(buf, 0, sizeof(buf));
            buf[0] = '0' + goatDoor;
            if (send(new_s, buf, BUFFER_SIZE, 0) < 0) { 
                perror("server: send"); 
            }

            // get final guess from client
            buf_len = recv(new_s, buf, sizeof(buf), 0);
            buf[buf_len] = '\0';
            guess = atoi(buf);

            result = guess == winningDoor;

            // send win or fail (1 or 2)
            memset(buf, 0, sizeof(buf));
            buf[0] = '0' + result;
            if (send(new_s, buf, BUFFER_SIZE, 0) < 0) { 
                perror("server: send"); 
            }

            rounds++;
        }
        //end of rounds

        /* END: game code */
        
        close(new_s); 
    }
    close(s);
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

