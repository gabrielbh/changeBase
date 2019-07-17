// For this part of the exercise i have used an algorithm that changes the
// original number i get to base 10, and then i change the number to the
// base i'vw been asked for. This algorithm i've learned in Tirgul 1 of
// "computer architecture" course last year.
// The complexity of this algorithm is O(N) when N is the longest number we could get,
// which is 20.

#include <stdio.h>

int LONGEST_NUM = 20;
char ERROR_MESSAGE[12] = "invalid!!\n";
int oldBase, newBase, numberInOldBase;


/**
 * Function that will ask for user input and will split the input
 * to three criteria as asked in the question.
 */
void splitInput()
{
    // longest input will be for the input of (for example) 10 10 101010 . it will have 13 chars.
    char userInput[13];
    fgets(userInput, sizeof(userInput), stdin);
    sscanf(userInput, "%d %d %d", &oldBase, &newBase, &numberInOldBase);
}


/**
 * we will check every digit separately. we will use the knowledge
 * that we get int and not float after division.
 */
int checkNum()
{
    int checkNum = numberInOldBase;
    while (checkNum != 0)
    {
        int lastDigit = checkNum % 10;
        if (lastDigit >= oldBase)
        {
            fprintf(stderr, ERROR_MESSAGE);
            return 1;
        }
        checkNum /= 10;
    }
    return 0;
}


/**
 * gives the i'th power of a number.
 */
int power(int oldBase, int index)
{
    int pow = 1;
    if (index == 0)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < index; ++i)
        {
            pow *= oldBase;
        }
    }
    return pow;
}


/**
 *  Function that converts a number to a base 10 number.
 */
int changeToBaseTen()
{
    int baseTenNum = 0;
    int index = 0;
    int checkNum = numberInOldBase;
    while (checkNum != 0)
    {
        int lastDigit = checkNum % 10;
        baseTenNum += lastDigit * (power(oldBase, index));
        checkNum /= 10;
        index += 1;
    }
    return baseTenNum;
}


/**
 * Function that finds the first digit that is not 0. returns -1 if there are only 0's.
 */
int findFirstDigit(int digits[])
{
    // longest number will be for the input (for example) of 10 2 999999. it will have 20 digits.
    for (int i = (LONGEST_NUM -1); i >= 0; --i)
    {
        if (digits[i] != 0)
        {
            return i;
        }
    }
    // if all digits are 0.
    return -1;
}


/**
 * Function that coverts a base 10 number to eny other base.
 */
void converter(int baseTenNum)
{

    int digit[20];
    for (int j = 0; j < LONGEST_NUM; ++j)
    {
        digit[j] = 0;
    }
    int remainder;
    int oldNum = baseTenNum;
    int index = 0;
    while (oldNum > 0)
    {
        remainder = oldNum % newBase;
        oldNum /= newBase;
        digit[index] = remainder;
        index++;
    }
    int firstDigit = findFirstDigit(digit);
    if (firstDigit == -1)
    {
        printf("%d", 0);
    }
    // run backwards on the digits array.
    else
    {
        for (int i = firstDigit; i >= 0; --i)
        {
            printf("%d", digit[i]);
        }
    }
}


/**
 * main function of the program.
 */
int main()
{
    splitInput();
    if (checkNum() == 1)
    {
        return 1;
    }
    int baseTenNum = changeToBaseTen();
    converter(baseTenNum);
    return 0;
}
