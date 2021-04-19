#	Makefile for Airline Reservation System project.
#	Created by Chayut Surathachaiopong (Mickey) ID 63070503406
#	Adapted with permission from function by S. Goldin in file [linkedListNetwork.c].
#	Princess Connect Summer Kyaru
EXECUTABLES= userInterface$(EXECEXT)

all : $(EXECUTABLES)

minPriorityQueue.o :	minPriorityQueueMod.c minPriorityQueueMod.h
	gcc -c minPriorityQueueMod.c

network.o :		network.c network.h minPriorityQueueMod.h
	gcc -c network.c 
	
itinerary.o :		itinerary.c network.c minPriorityQueueMod.c itineraries.h network.h minPriorityQueueMod.h
	gcc -c itinerary.c network.c minPriorityQueueMod.c
	
tree.o :	tree.c network.h
	gcc -c tree.c
	
	
userInterface.o :	userInterface.c network.h itineraries.h
	gcc -c userInterface.c
	
userInterface$(EXECEXT) :	userInterface.o network.o minPriorityQueue.o tree.o itinerary.o
	gcc -o userInterface$(EXECEXT) userInterface.o network.o minPriorityQueue.o tree.o itinerary.o
	
	
clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
