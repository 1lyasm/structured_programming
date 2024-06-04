#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char flightCode[5];
    char *sourceCity;
    char *destinationCity;
    char *arrivingTime;
    int isInternalFlight;
    int runwayNumber;
} Flight;

typedef struct ListNode {
    Flight flight;
    struct ListNode *next;
} ListNode;

static void printList(ListNode *head) {
    ListNode *current;

    current = head;

    while (current) {
        printf("%s %s %s %s %d %d\n",
               current->flight.flightCode,
               current->flight.sourceCity,
               current->flight.destinationCity,
               current->flight.arrivingTime,
               current->flight.isInternalFlight,
               current->flight.runwayNumber);
        current = current->next;
    }
    printf("\n");
}

static void freeList(ListNode *head) {
    ListNode *current, *next;

    current = head;
    while (current) {
        next = current->next;
        free(current->flight.arrivingTime);
        free(current->flight.sourceCity);
        free(current->flight.destinationCity);
        free(current);
        current = next;
    }
}

int main() {
    FILE *inputFile;
    int inputStringSize;
    char *inputString;
    ListNode *head;
    ListNode *currentNode;
    ListNode *secondCurrentNode;
    int stringIndex;
    int i;
    FILE **outputFiles;

    inputStringSize = 1000;
    inputString = calloc((size_t)inputStringSize, sizeof(int));

    inputFile = fopen("ucusBilgi.txt", "r");

    if (!inputFile) {
        fprintf(stderr, "\nCould not open input file\n");
        exit(EXIT_FAILURE);
    }

    fread(inputString, sizeof(char),
          (size_t)(inputStringSize - 1), inputFile);
    inputString[strlen(inputString) - 1] = 0;

    stringIndex = 0;
    head = calloc(1, sizeof(ListNode));
    currentNode = head;
    while ((size_t)stringIndex < strlen(inputString)) {
        // Parse a line and add it to list as a flight

        for (i = 0; i < 4; ++i) {
            currentNode->flight.flightCode[i] =
                inputString[stringIndex];
            ++stringIndex;
        }
        currentNode->flight.flightCode[4] = 0;

        ++stringIndex;
        currentNode->flight.sourceCity =
            calloc((size_t)64, sizeof(char));
        for (i = 0; inputString[stringIndex] != ' '; ++i) {
            currentNode->flight.sourceCity[i] =
                inputString[stringIndex];
            ++stringIndex;
        }

        ++stringIndex;
        currentNode->flight.destinationCity =
            calloc((size_t)64, sizeof(char));
        for (i = 0; inputString[stringIndex] != ' '; ++i) {
            currentNode->flight.destinationCity[i] =
                inputString[stringIndex];
            ++stringIndex;
        }

        ++stringIndex;
        currentNode->flight.arrivingTime =
            calloc((size_t)6, sizeof(char));
        for (i = 0; inputString[stringIndex] != ' '; ++i) {
            currentNode->flight.arrivingTime[i] =
                inputString[stringIndex];
            ++stringIndex;
        }

        ++stringIndex;
        currentNode->flight.isInternalFlight =
            inputString[stringIndex] - '0';

        stringIndex += 2;
        currentNode->flight.runwayNumber =
            inputString[stringIndex] - '0';

        stringIndex += 2;

        if ((size_t)stringIndex < strlen(inputString)) {
            currentNode->next = calloc(1, sizeof(ListNode));
        }
        currentNode = currentNode->next;
    }

    printList(head);

    currentNode = head;
    while (currentNode->next) {
        char minimumFlightCode[] = "9999";
        ListNode *minimumNode = currentNode;
        Flight temporaryFlight;

        secondCurrentNode = currentNode;
        while (secondCurrentNode) {
            if (strcmp(secondCurrentNode->flight.flightCode,
                       minimumFlightCode) < 0) {
                strcpy(minimumFlightCode,
                       secondCurrentNode->flight.flightCode);
                minimumNode = secondCurrentNode;
            }
            secondCurrentNode = secondCurrentNode->next;
        }

        temporaryFlight = currentNode->flight;
        currentNode->flight = minimumNode->flight;
        minimumNode->flight = temporaryFlight;

        currentNode = currentNode->next;
    }

    printList(head);

    freeList(head);

    free(inputString);

    return 0;
}

