#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
// #include <time.h>
#include <unistd.h>

int main()
{
    int sd, sd2, nsd, clilen, sport, len, flag = 0;
    int port;
    time_t ticks;
    char sendmsg[100], rcvmsg[100];
    // char dict[4][2][25] = {{"apple", "fruit"}, {"boy", "male"}, {"brain", "organ"}, {"violin", "instrument"}};
    struct sockaddr_in servaddr, cliaddr;
    printf("Enter the server port:");
    scanf("%d", &sport);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    // ticks = time(NULL);
    // strcpy(sendmsg, ctime(&ticks));
    if (sd < 0)
    {
        printf("Can't create \n");
        exit(-1);
    }
    else
        printf("Socket is created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);
    sd2 = bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (sd2 < 0)
        printf("Can't bind\n");
    else
        printf(" Binded \n");
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    nsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (nsd < 0)
        printf("Can't accept\n");
    else
        printf("Accepted\n");

    recv(nsd, rcvmsg, 100, 0);
    int num1 = atoi(rcvmsg);

    recv(nsd, rcvmsg, 100, 0);
    int op = atoi(rcvmsg);

    recv(nsd, rcvmsg, 100, 0);
    int num2 = atoi(rcvmsg);

    printf("%d %d character:%d", num1, num2, op);

    switch (op)
    {
    case 2:
        sprintf(sendmsg, "Product of %d and %d is %d", num1, num2, num1 * num2);
        break;
    case 4:
        sprintf(sendmsg, "The Quotient of %d and %d is %d", num1, num2, num1 / num2);
        break;
    case 5:
        sprintf(sendmsg, "The Remainder of %d and %d is %d", num1, num2, num1 % num2);
        break;
    case 1:
        sprintf(sendmsg, "The Sum of %d and %d is %d", num1, num2, num1 + num2);
        break;
    case 3:
        sprintf(sendmsg, "The Difference of %d and %d is %d", num1, num2, num1 - num2);
    }
    send(nsd, sendmsg, 100, 0);

    // char temp[25], temp2[25];
    // for (int i = 0; i < strlen(rcvmsg); i++)
    // {
    //     if ((rcvmsg[i] != '*' || rcvmsg[i] != '-' || rcvmsg[i] != '+' || rcvmsg[i] != '/' || rcvmsg[i] != '%') && flag != -1)
    //     {
    //         strcat(temp, &rcvmsg[i]);
    //     }
    //     else
    //     {
    //         op = rcvmsg[i];
    //         flag = -1;
    //     }
    //     if (flag == -1)
    //     {
    //         strcat(temp2, &rcvmsg[i]);
    //     }
    // }

    // recv(nsd, rcvmsg, 25, 0);
    // for (int i = 0; i < 4; i++)
    // {
    //     if (!strcmp(rcvmsg, dict[i][0]))
    //     {
    //         strcpy(sendmsg, dict[i][1]);
    //         break;
    //     }
    // }
    // send(nsd, sendmsg, 100, 0);

    return 0;
}
