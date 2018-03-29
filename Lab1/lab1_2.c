#include <stdio.h>
#include <assert.h>

int sum(int numberToSum)
{
    printf("sum(%d) called\n", numberToSum);
    if (numberToSum == 1)
    {
        printf("sum(1) returning 1\n");
        return 1;
    }
    else if (numberToSum > 1)
    {
        int numberToReturn = numberToSum + sum(numberToSum - 1);
        printf("sum(%d) returning %d\n", numberToSum, numberToReturn);
        return numberToReturn;
    }
    else
    {
        printf("sum(%d) returning 0\n", numberToSum);
        return 0;
    }
}

int main(void)
{
    assert(sum(1) == 1);
    assert(sum(2) == 3);
    assert(sum(3) == 6);
    assert(sum(4) == 10);
    assert(sum(5) == 15);
    assert(sum(20) == 210);
    assert(sum(0) == 0);
    assert(sum(-1) == 0);
}