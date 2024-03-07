#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int partitions[5] = {100, 500, 200, 300, 600};

struct process
{
    int size, allocation;
};

void assign_default(struct process *, int);

void first_fit(struct process *ptr, int n)
{
    assign_default(ptr, n);

    int k[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((partitions[j] > ptr[i].size) && (k[j] == 0))
            {
                k[j] = 1;
                ptr[i].allocation = partitions[j];
                break;
            }
        }
    }
}

void best_fit(struct process *ptr, int n)
{
    assign_default(ptr, n);

    int k[5] = {0, 0, 0, 0, 0}, min, temp;
    for (int i = 0; i < n; i++)
    {
        min = INT16_MAX;
        temp = -1;
        for (int j = 0; j < 5; j++)
        {
            if ((partitions[j] > ptr[i].size) && !k[j])
            {
                if (partitions[j] < min)
                {
                    min = partitions[j];
                    temp = j;
                }
            }
        }
        if (temp != -1)
        {
            k[temp] = 1;
            ptr[i].allocation = partitions[temp];
        }
    }
}

void worst_fit(struct process *ptr, int n)
{
    assign_default(ptr, n);

    int k[5] = {0, 0, 0, 0, 0}, max, temp;
    for (int i = 0; i < n; i++)
    {
        max = INT16_MIN;
        temp = -1;
        for (int j = 0; j < 5; j++)
        {
            if ((partitions[j] > ptr[i].size) && !k[j])
            {
                if (partitions[j] > max)
                {
                    max = partitions[j];
                    temp = j;
                }
            }
        }
        if (temp != -1)
        {
            k[temp] = 1;
            ptr[i].allocation = partitions[temp];
        }
    }
}

void display(struct process *ptr, int n)
{
    printf("pid\tsize\tallocation\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", i, ptr[i].size, ptr[i].allocation);
    }
}

void assign_default(struct process *ptr, int n)
{
    for (int i = 0; i < n; i++)
    {
        ptr[i].allocation = -1;
    }
}

int main()
{
    struct process *ptr = (struct process *)malloc(4 * sizeof(struct process));
    ptr->size = 212;
    ptr[1].size = 417;
    ptr[2].size = 112;
    ptr[3].size = 426;
    int i, n = 4;
    assign_default(ptr, n);
    do
    {
        printf("Enter your choice:\n");
        printf("1. First fit\t2. Best fit\t3. Worst fit\t4. Display\t5. Exit : ");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            first_fit(ptr, n);
            break;
        case 2:
            best_fit(ptr, n);
            break;
        case 3:
            worst_fit(ptr, n);
            break;
        case 4:
            display(ptr, n);
            break;
        default:
            printf("Invalid Choice\n");
        }
    } while (i != 5);
    free(ptr);
    return 0;
}