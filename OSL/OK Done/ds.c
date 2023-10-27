#include <stdio.h>
#include <stdlib.h>
int SSTF();
int SCAN();
int CLOOK();

int main()
{
    int ch, YN = 1, i, l, f;
    char F[10], s[25];
    for (i = 0; i < f; i++)
    {
        F[i] = -1;
    }

    int flag = 1;
    do
    {
        // system("clear");
        printf("\n\n\t***** MENU *****");
        printf("\n1) SSTF\t2) SCAN\t3) CLOOK 4) EXIT");
        printf("\nChoice :: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            SSTF();
            break;
        case 2:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            SCAN();
            break;
        case 3:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            CLOOK();
            break;
        case 4:
            flag = 0;
            exit(0);
        }
    } while (flag);
    return (0);
}
// SSTF Algorithm
int SSTF()
{
    int RQ[100], i, n, TotalHeadMoment = 0, inidal, count = 0;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head posidon\n");
    scanf("%d", &inidal);
    while (count != n)
    {
        int min = 1000, d, index;
        for (i = 0; i < n; i++)
        {
            d = abs(RQ[i] - inidal);
            if (min > d)
            {
                min = d;
                index = i;
            }
        }
        TotalHeadMoment = TotalHeadMoment + min;
        inidal = RQ[index];
        RQ[index] = 1000;
        count++;
    }
    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}
// SCAN Algorithm
int SCAN()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, inidal, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter inidal head position\n");
    scanf("%d", &inidal);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (inidal < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
        TotalHeadMoment = TotalHeadMoment + abs(size - RQ[i - 1] - 1);
        inidal = size - 1;
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
        TotalHeadMoment = TotalHeadMoment + abs(RQ[i + 1] - 0);
        inidal = 0;
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
    }
    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}
// C-LOOK Algorithm
int CLOOK()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, inidal, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head posidon\n");
    scanf("%d", &inidal);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (inidal < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
        for (i = 0; i < index; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
        for (i = n - 1; i >= index; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - inidal);
            inidal = RQ[i];
        }
    }
    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}

//         ***** MENU *****
// 1) SSTF 2) SCAN 3) CLOOK 4) EXIT
// Choice :: 1
// Enter the number of Requests
// 6
// Enter the Requests sequence
// 12 34 87 56 23 81
// Enter initial head posidon
// 53
// Total head movement is 122

// if ($?) { gcc bankers.c -o bankers } ; if ($?) { .\bankers }