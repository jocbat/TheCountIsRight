#include <stdlib.h>
#include <stdio.h>
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
void handleCurrentStackWhenDescending(int currentStackIndex, int quantity[], int value[], int*);
void handleCurrentStackWhenAscending(int currentStackIndex, int quantity[], int value[], int*);
bool isCountRight(int* amount);
bool areAllPreviousStacksEmpty(int, int tab[]);
bool isLastIndex(int index);

int piecesOfMoneyConst[3] = { 1, 2, 3 };

int main(int argc, char* argv[])
{
    int valuesOfMoney[3] = { 7, 5, 3 };
    int piecesOfMoney[3] = { 0, 0, 0 };
    int amount = 21;
    handleCurrentStackWhenDescending(0, piecesOfMoney, valuesOfMoney, &amount);

    return 0;
}


bool areAllPreviousStacksEmpty(int index, int tab[])
{
    bool areAllPreviousStacksEmpty = false;
    bool isThereAnyStackNotEmptyBefore = false;
    for (int i = 0; i < index && !isThereAnyStackNotEmptyBefore; i++)
    {
        isThereAnyStackNotEmptyBefore = tab[i] > 0;
    }
    return !isThereAnyStackNotEmptyBefore;
}

void takeMaximumPieces(int index, int quantity[], int value[], int* amount)
{
    int totalNumberOfPieces = piecesOfMoneyConst[index];
    int pieceValue = value[index];
    if (totalNumberOfPieces != 0)
    {
        int maxPiecesNumberToRemove = *amount / pieceValue;
        int piecesNumberToRemove = new_min(maxPiecesNumberToRemove, totalNumberOfPieces);
        *amount = *amount - piecesNumberToRemove * value[index];
        quantity[index] = piecesNumberToRemove;
    }
}

void handleCurrentStackWhenDescending(int currentStackIndex, int quantity[], int value[], int* amount)
{
    takeMaximumPieces(currentStackIndex, quantity, value, amount);
    if (isCountRight(amount))
    {
        printf("%d", quantity[0]);
        printf("\n");
        printf("%d", quantity[1]);
        printf("\n");
        printf("%d", quantity[2]);
    }
    else
    {
        if (areAllPreviousStacksEmpty(currentStackIndex, quantity) && isLastIndex(currentStackIndex))
        {
            printf("No solution");
        }
        else if (isLastIndex(currentStackIndex))
        {
            *amount = *amount + quantity[currentStackIndex] * value[currentStackIndex];
            quantity[currentStackIndex] = 0;
            handleCurrentStackWhenAscending(currentStackIndex - 1, quantity, value, amount);
        }
        else
        {
            handleCurrentStackWhenDescending(currentStackIndex + 1, quantity, value, amount);
        }
    }
}

bool isLastIndex(int index)
{
    return index == 2;
}

bool isCountRight(int* amount)
{
    return *amount == 0;
}

void handleCurrentStackWhenAscending(int currentStackIndex, int quantity[], int value[], int* amount)
{
    if (quantity[currentStackIndex] > 0)
    {
        quantity[currentStackIndex] = quantity[currentStackIndex] - 1;
        *amount = *amount + value[currentStackIndex];
        handleCurrentStackWhenDescending(currentStackIndex + 1, quantity, value, amount);
    }
    else
    {
        handleCurrentStackWhenAscending(currentStackIndex - 1, quantity, value, amount);
    }
}