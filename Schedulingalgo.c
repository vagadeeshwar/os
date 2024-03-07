// easycodingzone.com
#include <stdio.h>

int n, check_ar = 0, temp[10], queue[100], front = -1, rear = -1;
int p, TIME = 0;
int Cmp_time = 0, count = 0, t = 0, short_P, exist[10] = {0};
float Total_WT = 0, Total_TAT = 0, Avg_WT, Avg_TAT;

#define TQ 2

void swap();
void display();
void bubblesort();
void sjf();
void accept();
void srtf();
void rr();
void priorityp();
void prioritynp();
void insert();
int delete ();

struct process
{
    int id, PR, AT, WT, BT, TAT;
};
struct process a[10];

void insert(int n)
{
    if (front == -1)
        front = 0;
    rear = rear + 1;
    queue[rear] = n;
}

int delete ()
{
    int n;
    n = queue[front];
    front = front + 1;
    return n;
}

void swap(struct process *b, struct process *c)
{
    struct process tem = *c;
    *c = *b;
    *b = tem;
}

void display()
{
    printf("The students are\n");
    printf("ID\tAT\tXeroxT\tWT\tTAT\tPR\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", a[i].id, a[i].AT, a[i].BT, a[i].WT, a[i].TAT, a[i].PR);
    }

    printf("Avg waiting time is:- %f\n", Avg_WT);
    printf("Avg turn around time is:- %f\n", Avg_TAT);
}

void sjf()
{
    if (check_ar != 0)
    {
        bubblesort();
        a[0].WT = a[0].AT;
        a[0].TAT = a[0].BT - a[0].AT;
        Cmp_time = a[0].TAT;
        Total_WT = Total_WT + a[0].WT;
        Total_TAT = Total_TAT + a[0].TAT;
        for (int i = 1; i < n; i++)
        {
            int min = a[i].BT;
            for (int j = i + 1; j < n; j++)
            {
                if (min > a[j].BT && a[j].AT <= Cmp_time)
                {
                    min = a[j].BT;
                    swap(&a[i], &a[j]);
                }
            }
            a[i].WT = Cmp_time - a[i].AT;
            Total_WT = Total_WT + a[i].WT;

            Cmp_time = Cmp_time + a[i].BT;

            a[i].TAT = Cmp_time - a[i].AT;
            Total_TAT = Total_TAT + a[i].TAT;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int min = a[i].BT;
            for (int j = i + 1; j < n; j++)
            {
                if (min > a[j].BT && a[j].AT <= Cmp_time)
                {
                    min = a[j].BT;
                    swap(&a[i], &a[j]);
                }
            }
            a[i].WT = Cmp_time - a[i].AT;

            Cmp_time = Cmp_time + a[i].BT;

            a[i].TAT = Cmp_time - a[i].AT;
            Total_WT = Total_WT + a[i].WT;
            Total_TAT = Total_TAT + a[i].TAT;
        }
    }

    Avg_WT = Total_WT / n;
    Avg_TAT = Total_TAT / n;
}

void srtf()
{

    a[9].BT = 10000;
    for (t = 0; count != n; t++)
    {
        short_P = 9;
        for (int i = 0; i < n; i++)
        {
            if (a[i].BT < a[short_P].BT && (a[i].AT <= t && a[i].BT > 0))
            {
                short_P = i;
            }
        }

        a[short_P].BT = a[short_P].BT - 1;

        if (a[short_P].BT == 0)
        {
            count++;
            a[short_P].WT = t + 1 - a[short_P].AT - temp[short_P];
            a[short_P].TAT = t + 1 - a[short_P].AT;

            Total_WT = Total_WT + a[short_P].WT;
            Total_TAT = Total_TAT + a[short_P].TAT;
        }
    }
    Avg_WT = Total_WT / n;
    Avg_TAT = Total_TAT / n;
}

void rr()
{
    insert(0);
    exist[0] = 1;
    while (front <= rear)
    {
        p = delete ();
        if (a[p].BT >= TQ)
        {
            a[p].BT = a[p].BT - TQ;
            TIME = TIME + TQ;
        }
        else
        {
            TIME = TIME + a[p].BT;
            a[p].BT = 0;
        }

        for (int i = 0; i < n; i++)
        {
            if (exist[i] == 0 && a[i].AT <= TIME)
            {
                insert(i);
                exist[i] = 1;
            }
        }
        if (a[p].BT == 0)
        {
            a[p].TAT = TIME - a[p].AT;
            a[p].WT = a[p].TAT - temp[p];
            Total_TAT = Total_TAT + a[p].TAT;
            Total_WT = Total_WT + a[p].WT;
        }
        else
        {
            insert(p);
        }
    }

    Avg_TAT = Total_TAT / n;
    Avg_WT = Total_WT / n;
}

void priorityp()
{
    printf("Enter Priority for processes\n");
    printf("M Tech - 1\tPhd - 2\tMS - 3\tB Tech - 4\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i].PR);
    a[9].PR = 10000;

    for (t = 0; count != n; t++)
    {
        short_P = 9;
        for (int i = 0; i < n; i++)
        {
            if (a[short_P].PR > a[i].PR && a[i].AT <= t && a[i].BT > 0)
            {
                short_P = i;
            }
        }

        a[short_P].BT = a[short_P].BT - 1;

        if (a[short_P].BT == 0)
        {
            count++;
            a[short_P].WT = t + 1 - a[short_P].AT - temp[short_P];
            a[short_P].TAT = t + 1 - a[short_P].AT;

            Total_WT = Total_WT + a[short_P].WT;
            Total_TAT = Total_TAT + a[short_P].TAT;
        }
    }

    Avg_WT = Total_WT / n;
    Avg_TAT = Total_TAT / n;
}

void prioritynp()
{
    printf("Enter Priority for processes\n");
    printf("M Tech - 1\tPhd - 2\tMS - 3\tB Tech - 4\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i].PR);
    if (check_ar != 0)
    {
        bubblesort();
        a[0].WT = a[0].AT;
        a[0].TAT = a[0].BT - a[0].AT;
        Cmp_time = a[0].TAT;
        Total_WT = Total_WT + a[0].WT;
        Total_TAT = Total_TAT + a[0].TAT;
        for (int i = 1; i < n; i++)
        {
            int min = a[i].PR;
            for (int j = i + 1; j < n; j++)
            {
                if (min > a[j].PR && a[j].AT <= Cmp_time)
                {
                    min = a[j].PR;
                    swap(&a[i], &a[j]);
                }
            }
            a[i].WT = Cmp_time - a[i].AT;
            Total_WT = Total_WT + a[i].WT;
            Cmp_time = Cmp_time + a[i].BT;

            a[i].TAT = Cmp_time - a[i].AT;
            Total_TAT = Total_TAT + a[i].TAT;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int min = a[i].PR;
            for (int j = i + 1; j < n; j++)
            {
                if (min > a[j].PR && a[j].AT <= Cmp_time)
                {
                    min = a[j].PR;
                    swap(&a[i], &a[j]);
                }
            }
            a[i].WT = Cmp_time - a[i].AT;

            Cmp_time = Cmp_time + a[i].BT;

            a[i].TAT = Cmp_time - a[i].AT;
            Total_WT = Total_WT + a[i].WT;
            Total_TAT = Total_TAT + a[i].TAT;
        }
    }

    Avg_WT = Total_WT / n;
    Avg_TAT = Total_TAT / n;
}

void bubblesort()
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n - 1; j++)
            if (a[i].AT > a[j].AT)
                swap(&a[i], &a[j]);
}

void accept()
{
    printf("Enter the number of students \n");
    scanf("%d", &n);
    printf("Enter the Arrival time and number of the copies of the students\n");
    printf("AT BT\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].AT, &a[i].BT);
        a[i].id = i + 1;
        temp[i] = a[i].BT;
        if (i == 0)
            check_ar = a[i].AT;

        if (check_ar != a[i].AT)
            check_ar = 1;
    }
}

int main()
{
    accept();
    //sjf();
    //srtf();
    //rr();
    prioritynp();
    //priorityp();
    display();
    return 0;
}
