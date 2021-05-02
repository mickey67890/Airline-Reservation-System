# This is the Readme file of Airline Reservation System
# Group name : Princess Connect Summer Kyaru
# Members : Chayut Surathachaipong (Mickey) ID 63070503406
#           Vananya Pruksapun (Fern) ID 63070503449
#           Apiravit Intharakanchit (Cheetah) ID 63070503457
#           Kantawat Samarntrakulchai (Map) ID 63070503460
      
The Airline Reservation System's files :
C files : 
         Implemented :
              userInterface.c, network.c, tree.c, itinerary.c, and   
         Modified Aj. Sally Goldin's module :
              minPriorityQueueMod.c
Header files :
         Implemented :
              network.h itineraries.h
         Modified Aj. Sally Goldin's module :
              minPriorityQueueMod.h
Text files :
         flights.txt
         location.txt


NetworK.c, Tree.c, Network.h :
These 3 create a networks of location by first reading the location file and create tree of all location
then read the flights file to create network with location as vertex and flights as edges

## Usage
network(); ->

createTree(); # create the tree from location file
traverseInOrder(pTree->root,&addVertex); # add vertex with information from tree
createFlights(pTree->root); # create flight from flight file


itinerary.c, itineraries.h :
Do requesting the best itinerary from the Dijkstra's Algorithm then set up the itinerary for booking
and print it.

## functions
findItinerary(char * startkey,char * endkey) search for the best flights by Dijkstra's Algorithm.
        * This function adapted with permission from function                 *
        * by S. Goldin in file [linkedListNetwork.c] and [linkedListGraph.c]. *
        
  
setPath(char * startkey,char * endkey) setup the best itinerary from Dijstra's Algorithm.
        * This function adapted with permission from function                 *
        * by S. Goldin in file [linkedListNetwork.c] and [linkedListGraph.c]. *
  
printPath(char * originVertex,char * desVertex) prints the best itinerary.
  
  #### These finding itinerary functions can not validate the same city name either the same country or different countries. ####
  
  
userInterface.c :
The main interface tha user use.

When the program runs it will read the text files to create the network
    then show the main menu with three choices :
        
        1 - Requesting Itinerary
        2 - List of flights
        3 - Exit
        
        1. Requesting Itinerary
              It will move to criteria selecting menu with three choices :
              
                      1. Shortest distance sort
	                    2. Cheapest price sort
	                    3. Least amount of segments sort
                      
                      This menu cannot go back. After choosing the sort criteria
                      then the user have to type the full origin and destination city name.
                      
                      It can not do partial name search and validate the same city name 
                      either the same country or different countries.
                      
                      Then the program calls findItineraries function to search the best itinerary
                      by Dijkstra's Algorithm.
                      
                      If there is the flight goes from the origin to destination, the program will prints
                      all the flights either the single flight or the multi flights. Then the program ask
                      the user to book or not. If the user wants to book, the program will ask the date and
                      numbers of people. Then the program will book by deduct the seats of the flights.
                      
                      But the booking session is not working , so it will returns to the main session after typing the date.
                      
                      Otherwise if the user dosen't want to book, the program will ask the user to keep the sorting criteriaw or not.
                      If the user want to keep the sorting criteria, the program will ask the user want to continue or not.If yes,
                      The program will ask the origin and destination then do search. If not, the program will return main session.
                      
                      It can not do partial name search and validate the same city name 
                      either the same country or different countries.
                      
                      If the user doesn't want to keep criteria, the user will have to choose new criteria then the program
                      will do search with old origin and destination city.
                      
                      If there is no flight found, the program will ask the user want to continue or not.If yes,
                      The program will return to the criteria selecting session. If not, the program will return main session.
       
       
       2. List of flights
       
              In this choice there is noting working yet.
              
              The plan is the user enter a city name then the program will
              prints all the flights that arrives or departs that city.
              Then ask user to type done to returns the main session.
              
              
       3. Exit
              This choice will free all the allocated memories and say "Goodbye".
           
                      
  

  

