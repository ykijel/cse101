#include "List.h"  // Include the definition of your List class

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <max_deck_size>" << std::endl;
        return 1;
    }

    int maxDeckSize = std::stoi(argv[1]);

    std::cout << "deck size\tshuffle count" << std::endl;
    std::cout << "----------------------------" << std::endl;

    // Perform shuffles for each value of n from 1 to maxDeckSize
    for (int n = 1; n <= maxDeckSize; ++n) {
        List deck;

        // Initialize the deck with values 0 to n-1
        for (int i = 0; i < n; ++i) {
            deck.insertAfter(i);
        }

        List originalOrder = deck;  // Store the original order

        // Perform shuffles until the original order is reached
        int shuffleCount = 0;
        do {
            // Implement the shuffle operation as described in the prompt
            List shuffledDeck;

            // Split the deck into two halves
            int middle = n / 2;

            List leftHalf;
            List rightHalf;

            for (int i = 0; i < middle; ++i) {
                leftHalf.insertAfter(deck.front());
                deck.eraseAfter();
            }

            while (deck.length() != 0) {
                rightHalf.insertAfter(deck.front());
                deck.eraseAfter();
            }

            // Merge the two halves
            while (leftHalf.length() != 0 || rightHalf.length() != 0) {
                if (leftHalf.length() != 0) {
                    shuffledDeck.insertBefore(leftHalf.front());
                    leftHalf.eraseAfter();
                }

                if (rightHalf.length() != 0) {
                    shuffledDeck.insertBefore(rightHalf.front());
                    rightHalf.eraseAfter();
                }
            }

            deck = shuffledDeck;  // Update the deck with the shuffled order
            shuffleCount++;

        } while (!deck.equals(originalOrder));  // Check if the deck is back to its original order

        // Print the result for the current n
        std::cout << " " << n << "\t\t" << shuffleCount << std::endl;
    }

    return 0;
}