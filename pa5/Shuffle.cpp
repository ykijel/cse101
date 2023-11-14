//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA5
// Shuffle.cpp
// Contains the main function that utilizes the List ADT
//-----------------------------------------------------------------------------

#include "List.h"
#include <iostream>

// Function to perform a single shuffle on the given list
void shuffle(List &D)
{
    int mid = D.length() / 2;
    int i;
    List E;
    D.moveBack();

    // Insert the latter half of the list first
    for (i = D.length() - 1; i >= mid; i--)
    {
        E.insertAfter(D.movePrev());
    }

    // Prepare for merge
    E.moveFront();
    D.moveFront();
    if (mid <= 1)
    {
        E.moveNext();
        if (D.position() < D.length())
        {
            E.insertBefore(D.moveNext());
        }
    }
    else
    {
        for (i = 0; i < mid; i++)
        {
            E.moveNext();
            if (D.position() < D.length())
            {
                E.insertBefore(D.moveNext());
            }
        }
    }

    // Check if cursor is not at the back before assigning D to E
    if (D.position() != D.length())
    {
        // Move cursor to the back before assigning D to E
        D.moveFront();
        D = E;
    }
}

int main(int argc, char *argv[])
{
    // Check command line for correct number of arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <max_deck_size>" << std::endl;
        return EXIT_FAILURE;
    }

    int maxDeckSize = 0;

    try
    {
        maxDeckSize = std::stoi(argv[1]);
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << "Usage: " << argv[0] << " <max_deck_size>" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "deck size\tshuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // Perform shuffles for each deck size
    for (int n = 1; n <= maxDeckSize; n++)
    {
        List L;

        // Initialize the list with values 0 to n-1
        for (int i = 0; i < n; i++)
        {
            L.insertBefore(i);
        }

        int shuffleCount = 0;
        List C = L;

        // Loop until the list is back to its original order
        do
        {
            shuffle(L);
            shuffleCount++;
        } while (!(L == C));

        // Print the results for the current deck size
        std::cout << " " << n << "\t\t" << shuffleCount << std::endl;
    }

    return EXIT_SUCCESS;
}