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

using namespace std;

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
            exit(1)
        }

        /* START: game code */
        
        //variables
        int rounds = 0;
        int stayWins = 0;
        int switchWins = 0;
        int winningDoor;
        int unopenedDoor;

        //start of the actual game
        while(rounds < 3)
        {
            //chooses random number that's either 1, 2, or 3
            srand (time(NULL));
            winningDoor = rand() % 3 + 1;

            rounds++;
        } //end of rounds

        /* END: game code */
        
        close(new_s); 
    }
    close(s);
    return 0;
}

