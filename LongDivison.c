/*
Program description: User inputs 2 numbers (dividend and quotient)[positive only][0-2147483647] and program illustrates long division in terminal with remainder 

Author: Dorian Dzigumovic
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 20

// function signatures
short options();
int countingDigits (int);
void setup (int, int, int);
void longDivision(int, int);
void divisionSteps (int, int, int, int, int, int);


int main ()
{
    short choice;
    int dividend = 0, quotient = 0, negative = 0;
    while(1)
    {
        choice = options();
        
        switch(choice)
        {
            case '1':
            {       
                // Getting input from user
                printf("\nEnter your numbers in format [DIVIDEND/QUOTIENT]\n? ");
                scanf("%d/%d", &dividend, &quotient);

                if (dividend < 0 || quotient < 0)
                {
                    printf("\nYou have entered a negative number. Try again....");
                    break;
                }
                else if (quotient == 0)
                {
                    printf("\nInvalid quotient. Try again....");
                    break;
                }
                else if (dividend == 0)
                {
                    printf("\nAnswer = 0");
                    break;
                }

                setup(dividend, quotient, negative);
                break;
            }
            case '2':
            {
                // Ending program
                printf("\nEnding program....");
                return 0;
            }
            default:
            {
                printf("\nInvalid input. Try again");
                break;
            }
        }
    }
}

short options()
{
    char input;
    printf("\n\n1. Calculate long division\n2. End program\n\n? ");
    scanf("%c", &input);
    return input;
}

int countingDigits(int num)
{
    // converting int to string and then getting its length
    char str[SIZE];
    sprintf(str,"%d", num);
    return strlen(str);
}

void setup (int dividend, int quotient, int n) 
{
    // dividend digits, quotient digits, result digits
    int dDigits = countingDigits(dividend);
    int qDigits = countingDigits(quotient);
    int rDigits = countingDigits(dividend/quotient);

    printf("\n");

    // printing white space before remainder
    for (int i = (-1 - (dDigits - rDigits)) - n; i < qDigits; i++)
    {
        printf(" ");
    }

    // printing the result and the remainder
    printf("%d r%d\n", (dividend/quotient), (dividend%quotient));

    // printing '____'
    for (int i = -1; i < qDigits; i++)
    {
        printf(" ");
    }

    for (int i = 0; i < dDigits; i++)
    {
        printf("_");
    }

    // printing out the quotient and dividend
    printf("\n%d|%d\n", quotient, dividend);

    longDivision (dividend, quotient);
}

void longDivision (int dividend, int quotient)
{
    // dividend digits
    int dDigits = countingDigits(dividend);

    // int -> string to get 'current' correct
    char tempStr[SIZE];
    sprintf(tempStr, "%d", dividend);
    int current = tempStr[0] - '0';

    int index = 0;

    // increasing 'current' digit by digit to be able to be divided by quotient
    while (current < quotient && index < dDigits - 1)
    {
        index++;
        int tempDigit = tempStr[index] - '0';
        current = current * 10 + tempDigit;
    }
    
    divisionSteps (dividend, quotient, current, index, (dDigits - index), (dDigits - 1 - index));   
}

void divisionSteps (int dividend, int quotient, int lastNum, int index, int subtrahendLines, int lastNumLines)
{
    // calculating dividend digits and quotient digits
    int dDigits = countingDigits(dividend);
    int qDigits = countingDigits(quotient);
    
    // base case, true if we go through all digits of dividend AND validating by making sure final remainder is correct
    if (index >= dDigits - 1 && lastNum == (dividend%quotient))
    {
        return;
    }
    else
    {
        char tempChar;
        int tempInt, tempRemainder;

        // converting to string to be able to easily break down integers in long division
        char minuend[(dDigits+1)];
        char *minuendPtr = minuend;
        sprintf(minuend,"%d", dividend);
        
        // doing the subtraction
        int subDivision = lastNum/quotient;               
        int subtrahend = quotient * subDivision;            
        tempRemainder = lastNum - subtrahend;   

        // true if we have more digits to drop
        if (index < dDigits - 1 )
        {
            // concatenating next digit to 'lastNum'
            tempChar = *(minuendPtr+(index + 1));   // 
            tempInt = tempChar - '0';
            lastNum = tempRemainder * 10 + tempInt;
            index++;
        }
        else
        {
            lastNum = tempRemainder;
        }

        // PRINTING WHITESPACE THEN VALUES

        // qDigits [to skip past quotient digits] + index [to be alligned correctly with current sub division] - currentDigits(subtrahend)) [to be alligned correctly no matter how many digits the subtrahend has]
        for (int i = 0; i < (qDigits + index - countingDigits(subtrahend)); i++)
        {
            printf(" ");
        }

        printf("-");  

        printf("%d", subtrahend);

        // decreasing number of '|' 
        subtrahendLines--;

        for (int i = 0; i < subtrahendLines; i++)
        {
            printf("|");
        }

        printf("\n");

        // qDigits [to skip past quotient] + index [to be aligned correctly with current sub division] + countingDigits(lastNum) [to make sure remainders are correctly alligned no matter how many digits lastNum has]
        for (int i = 0; i < (qDigits + index - (countingDigits(lastNum)) + 1); i++)
        {
            printf(" ");
        }

        // if no remainder on sub subtraction enter 0 to signify no remainder
        if (countingDigits(lastNum) == 1)
        {
            printf("0");
        }
        else
        {
            printf(" ");
        }

        printf("%d", lastNum);

        // decreasing number of '|' 
        lastNumLines--;

        for (int i = 0; i < lastNumLines; i++)
        {
            printf("|");
        }

        printf("\n");

        // to fix issue where last subtrahend would print one whitespace too early since index reached it max value
        if (index == dDigits - 1)
        {
            printf(" ");
        }

        // calling recursive function
        divisionSteps(dividend, quotient, lastNum, index, subtrahendLines, lastNumLines);
    }
}