#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int csd, cport, len;
    char sendmsg[100], revmsg[100];
    struct sockaddr_in servaddr;
    printf("Enter the port \n");
    scanf("%d", &cport);
    csd = socket(AF_INET, SOCK_STREAM, 0); // client socket descriptor
    if (csd < 0)
    {
        printf("Can't create\n");
        exit(-1);
    }
    else
        printf("Socket is created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        printf("Can't  connect\n");
    else
    {
        printf("Connected sucessfully\n");

        printf("Enter the first number: ");
        scanf("%s", sendmsg);
        send(csd, sendmsg, 100, 0);

        printf("Enter the operator out of +:1, *:2, -:3, /:4 modulo:5 : "); // Tried sending operator as character but didn't work
        scanf("%s", sendmsg);
        send(csd, sendmsg, 100, 0); // that is sending + or - to server instead of 1 or 3

        printf("Enter the second number: ");
        scanf("%s", sendmsg);
        send(csd, sendmsg, 100, 0);

        recv(csd, revmsg, 100, 0);
        printf("%s\n", revmsg);

        // printf("Enter a word to search:\n");
        // scanf("%s", sendmsg);
        // send(csd, sendmsg, 25, 0);
        // recv(csd, revmsg, 100, 0);
        // printf("%s\n", revmsg);
    }
    return 0;
}
