/*
 * This program is the user interface of the Airline reservation system project
 * Created by Kantawat Samarntrakulchai (Map) 63070503460
 * PrincessConnectSummerKyaru	
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "itineraries.h" 

#define DONE -9999
#define YES -1111
#define SHORTEST 0
#define CHEAPEST 1
#define SEGMENTS 2
#define NONE 444

int chooseSearch();
int chooseSort();
int decision(int mode);

int main()
{
    int choice = 0;
    int subChoice = NONE;
    int subChoice2 = NONE;
    int bOk = 0;
    int vertexCount;
    int sort = NONE;
    char date[16];
    char inputline[64], origin[64], destination[64], location[64]; 
    TREE_T* pTree = NULL;
    
    printf("Creating flight network..\n");
    network(); 
    vertexCount = vertexCount;
    pTree = pTree;

    while (choice != DONE)
    {
        printf("\nWelcome to Airline reservation system\n");
        printf("\t1. Request itinerary\n");
        printf("\t2. List of flight\n");
        printf("\t3. Exit\n");
        printf("Enter Input: ");
        fgets(inputline,sizeof(inputline),stdin);
        sscanf(inputline,"%d",&choice);
        subChoice = NONE;
        subChoice2 = NONE;

        switch (choice)
        {
            case 1:
                printf("Requesting itinerary..\n");
                bOk = NONE;

                while (bOk != DONE)
                {
                    if (subChoice2 != DONE)
                        sort = chooseSort();
                    subChoice2 = NONE;
                    memset(origin, '0', 5);
                    memset(destination, '0', 5);
                    printf("Enter origin: ");
                    fgets(inputline, sizeof(inputline), stdin);
                    sscanf(inputline, "%s", origin);
                    printf("Enter destination: ");
                    fgets(inputline, sizeof(inputline), stdin);
                    sscanf(inputline, "%s", destination);

                    if (origin[0] == '0' || destination[0] == '0')
                    {
                        printf("\tError: you must enter origin and destination.\n");
                        bOk = decision(1); //continue?
                    }
                    else
                        bOk = findItineraries(origin, destination, vertexCount, sort);

                    if (bOk == -1) //NO ORIGIN OR DESTINATION
                    {
                        //printf("\tError: Origin or destination do not exist.\n");
                        bOk = decision(1); //continue?
                        //bOk = findItineraries(origin, destination, vertexCount, sort);
                    }
                    else if (!bOk) //NO FLIGHT PATH
                    {
                        //printf("\tError: There's no flight from %s to %s.\n",origin ,destination);
                        bOk = decision(1); //continue?
                        //bOk = findItineraries(origin, destination, vertexCount, sort);
                    }
                    while (bOk >= 1 && subChoice2 != DONE) //FOUND FLIGHTS
                    {
                        printPath(origin, destination); //display flight
                        subChoice = decision(2); //book or not?
                        if (subChoice == YES)
                        {
                            subChoice2 = DONE;
                            printf("\nBooking itinerary..\n");
                            //bookItinerary();
                            printf("Enter date to book (1 - 30): ");
                            fgets(inputline, sizeof(inputline), stdin);
                            sscanf(inputline, "%s",date);
                            printf("**WORK IN PROGRESS**\n");
                            bOk = DONE;
                        }
                        else if (subChoice == DONE)
                        {
                            printf("Back to sorting type..\n");
                            subChoice2 = decision(3); //changing sort?
                            if (subChoice2 == YES)
                            {
                                sort = chooseSort();
                                bOk = findItineraries(origin, destination, vertexCount, sort);
                            }      
                            else if (subChoice2 == DONE)
                            {
                                printf("Back to request itinerary..\n");   
                                bOk = decision(1); //continue?                         
                            }      
                        }                
                    }
                }
                break;
            case 2:
                printf("Listing flights..\n");
                printf("**WORK IN PROGRESS**\n");
                while (subChoice != DONE)
                {
                    subChoice = chooseSearch();      
                    printf("Enter the location: ");
                    fgets(inputline, sizeof(inputline), stdin);
                    sscanf(inputline, "%s", location);

                    /*JUST FOR TESTING*/
                    printf("Enter bOk (1 = Found / 2 = Location not exist): ");
                    fgets(inputline, sizeof(inputline), stdin);
                    sscanf(inputline, "%d", &bOk);
                    //bOk = listFlight();

                    if (bOk == 1)
                    {
                        printf("\tHere's list of flight.\n");
                        subChoice = DONE;
                    }
                    else if (bOk == 2)
                    {
                        printf("\tError: The searched location do not exist.\n");
                        subChoice = decision(1);
                    }
                }
                break;
            case 3:
                choice = DONE;
                break;  
            default :
                printf("\tError: You must enter a number between 1 - 3.\n");
        }

    }
    printf("Good bye!\n");
    
    freeTree(pTree);

}

/* Choose how do you want to search flights.
 * Return 1 if search by origin, return 2 if search by destination
 */ 
int chooseSearch()
{
    char inputline[64];
    int choice = NONE;

    while (choice == NONE)
    {   
        printf("Search list of flight by (1 = Origin / 2 = Destination): ");
        fgets(inputline, sizeof(inputline), stdin);
        sscanf(inputline, "%d", &choice);
        switch (choice)
        {
            case 1:
                printf("\tSearching by origin location.\n");
                break;
            case 2:
                printf("\tSearching by destination location.\n");
                break;
            default:
                printf("\tError: You must enter a number between 1 - 2.\n");
                choice = NONE;
        }
    } 
    return choice;  
}

/* Choose how do you want to sort list of itinerary.
 * Return type of sort for request itinerary
 */
int chooseSort()
{
    char inputline[8];
    int choice;
    int sort;
    while (1)
    {
        printf("Choose sorting type\n");
        printf("\t1. Shortest distance sort\n");
        printf("\t2. Cheapest price sort\n");
        printf("\t3. Least amount of segments sort\n");
        printf("Enter input: ");
        fgets(inputline, sizeof(inputline), stdin);
        sscanf(inputline, "%d", &choice);
        switch (choice)
        {
            case 1:
                sort = SHORTEST;
                break;
            case 2:
                sort = CHEAPEST;
                break;
            case 3:
                sort = SEGMENTS;
                break;
            default:
                printf("Error: You must enter a number between 1 - 3\n");
                sort = NONE;
        }
        if (sort != NONE)
            break;
    }
    return sort;
}

/* This function will ask user if user want to do certain things or not.
 * Arguments - mode choose 1 - 3, each mode will ask the user differently
 *             mode 1: continue , 
 *             mode 2: book or not , 
 *             mode 3: changing sort
 * return YES if continue else return DONE if not continue
 */
int decision(int mode)
{
    int choice;
    char decision[16];
    char inputline[16];
    while (choice != DONE)
    {
        if (mode == 1)
            printf("\tContinue? (Y/N): ");
        else if (mode == 2)
            printf("\tBook itinerary? (Y/N): ");
        else if (mode == 3)
            printf("\tChange flight sorting? (Y/N): ");

        fgets(inputline, sizeof(inputline), stdin);
        sscanf(inputline, "%s", decision);
        if (strcasecmp(decision, "y") == 0 || 
            strcasecmp(decision, "yes") == 0)
        {
            choice = YES;
            break;
        }
        else if (strcasecmp(decision, "n") == 0 || 
            strcasecmp(decision, "no") == 0)
            choice = DONE;
        else
            printf("\tError: You must enter between 'Yes' or 'No'.\n");
    }
    return choice;
}