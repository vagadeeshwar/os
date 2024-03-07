#include <stdio.h>  //15 pages 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0 fifo 12 faults 3 frames
#include <stdlib.h> //20 pages 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 lru 8 faults opt 8 faults both 4 frames

int pages[30], pageFaults, pages_number, frames[10], frames_number;

void accept();
void fifo();
void optimal();
void lru();
int findLRU(int *, int);

int main()
{
    int choice;
    do
    {
        printf("Enter your choice:\n");
        printf("1. Enter data\t2. FIFO\t3. Optimal\t4. LRU\t5. Exit : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            accept();
            break;
        case 2:
            fifo();
            break;
        case 3:
            optimal();
            break;
        case 4:
            lru();
            break;
        case 5:
            break;
        default:
            printf("Invalid Choice\n");
        }
    } while (choice != 5);
    return 0;
}

void accept()
{
    printf("Enter number of frames: ");
    scanf("%d", &frames_number);

    printf("Enter number of pages: ");
    scanf("%d", &pages_number);

    printf("Enter page reference string: ");
    for (int i = 0; i < pages_number; ++i)
    {
        scanf("%d", &pages[i]);
    }
}

void fifo()
{
    pageFaults = 0;
    int m, n, s;
    for (m = 0; m < frames_number; m++)
    {
        frames[m] = -1;
    }
    for (m = 0; m < pages_number; m++)
    {
        s = 0;
        for (n = 0; n < frames_number; n++)
        {
            if (pages[m] == frames[n])
            {
                s++;
                pageFaults--;
            }
        }
        pageFaults++;
        if ((pageFaults <= frames_number) && (s == 0))
        {
            frames[m] = pages[m];
        }
        else if (s == 0)
        {
            frames[(pageFaults - 1) % frames_number] = pages[m];
        }
        printf("\n");
        for (n = 0; n < frames_number; n++)
        {
            printf("%d\t", frames[n]);
        }
    }
    printf("\nTotal Page Faults:\t%d\n", pageFaults);
}

void optimal()
{
    pageFaults = 0;
    int temp[30], flag1, flag2, flag3, i, j, k, pos, max;
    for (i = 0; i < frames_number; ++i)
    {
        frames[i] = -1;
    }
    for (i = 0; i < pages_number; ++i)
    {
        flag1 = flag2 = 0;
        for (j = 0; j < frames_number; ++j)
        {
            if (frames[j] == pages[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }
        // definition of the flag at the starting of the string
        if (flag1 == 0)
        {
            for (j = 0; j < frames_number; ++j)
            {
                if (frames[j] == -1)
                {
                    pageFaults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }
        // definition of the flag at the mid position
        if (flag2 == 0)
        {
            flag3 = 0;
            for (j = 0; j < frames_number; ++j)
            {
                temp[j] = -1;
                for (k = i + 1; k < pages_number; ++k)
                {
                    if (frames[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            for (j = 0; j < frames_number; ++j)
            {
                if (temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            // definition of flag at the rear position
            if (flag3 == 0)
            {
                max = temp[0];
                pos = 0;
                for (j = 1; j < frames_number; ++j)
                {
                    if (temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            pageFaults++;
        }
        printf("\n");
        for (j = 0; j < frames_number; ++j)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\n\nTotal Page Faults = %d\n", pageFaults);
}

int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru()
{
    pageFaults = 0;
    int i, counter = 0, time[30], flag1, flag2, j, pos;
    for (i = 0; i < frames_number; ++i)
    {
        frames[i] = -1;
    }

    for (i = 0; i < pages_number; ++i)
    {
        flag1 = flag2 = 0;

        for (j = 0; j < frames_number; ++j)
        {
            if (frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0)
        {
            for (j = 0; j < frames_number; ++j)
            {
                if (frames[j] == -1)
                {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0)
        {
            pos = findLRU(time, frames_number);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        printf("\n");

        for (j = 0; j < frames_number; ++j)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\n\nTotal Page Faults = %d\n", pageFaults);
}