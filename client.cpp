//
//  client.cpp
//  MontyHall
//
//  Created by Trenton Paul on 4/15/22.
//

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
using namespace std;

#define BUFFER_SIZE 2048
#define PORT "8888"

int main()
{
    FILE *fp; 
    struct hostent *hp; 
    struct sockaddr_in sin;
    char buf[BUFFER_SIZE]; 
    int s;
 
    /* translate host name into peer's IP address */ 
    hp = gethostbyname("localhost"); 
    if (!hp) { 
        fprintf(stderr, "%s: unknown host\n", host); 
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


 

    return 0;
}