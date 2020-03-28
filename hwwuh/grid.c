#include <stdio.h>

/* function divide and conquer */
int f_dc(int x, int y)
{
    /* check validity */
    if (x < 0 || y < 0)
        return 0;

    /* over, the start point */
    if (x == 0 && y == 0)
        return 1;

    return f_dc(x - 1, y) + f_dc(x, y - 1);
}

int main()
{
    int x = 3;
    int y = 2;
 
    printf("f_dc(%d, %d) = %d\n", x, y, f_dc(x, y));
 
    return 0;
}
