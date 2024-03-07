#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int p1 = 0, p2 = 0, p3 = 0;
pthread_t t1, t2;

void *palindrome(void *arg)
{
    int n = (int)arg, reverse = 0, remainder;

    while (n != 0)
    {
        remainder = n % 10;
        reverse = reverse * 10 + remainder;
        n /= 10;
    }

    if (arg == reverse)
        p1 = 1;

    return (void *)0;
}

void *prime(void *arg)
{
    int n = (int)arg;
    if (n == 1)
    {
        p3 = 1;
        return (void *)0;
    }

    for (int i = 2; i <= n / 2; ++i)
        if (n % i == 0)
            return (void *)0;

    p2 = 1;
    return (void *)0;
}

int main()
{
    int n;
    printf("Enter the number");
    scanf("%d", &n);
    pthread_create(&t1, NULL, palindrome, (void *)n);
    pthread_create(&t2, NULL, prime, (void *)n);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    if (p1)
        printf("The number is Palindrome\n");
    else
        printf("The number is not Palindrome\n");

    if (p3)
        printf("The number is neither prime nor composite\n");
    else if (p2)
        printf("The number is prime\n");
    else
        printf("The number is not prime\n");
    return 0;
}