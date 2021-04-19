/*
 *	This is the header file of the requesting itinerary functions,
 *	Created by Chayut Surathacahipong (Mickey) ID 630705003406
 *	Princess Connect Summer Kyaru.
 */


#include "network.h"


/*	Calculate the differents of time1 and time2
 *	Arguments - pTime1 - pointers of time1
 *	          - pTime2 - pointers of time2
 *	returns the differents in minute
 */
 
int diffTime(TIME_T * pTime1,TIME_T * pTime2);

/*	This fumction compares the arrive time of the previous flight
 *	and the departure time of the next flight.
 *		Arguments - edge1 - pointers of previous EDGE_T flight
 *                         - edge2 - pointers of next EDGE_T flight
 *	Returns 1 if the time differences is more than 30 minutes.
 *	Otherwise returns 0.
 */
 
int flightTimeCompare(EDGE_T * edge1,EDGE_T * edge2);

/** Comparison function to send to the minPriorityQueue
 * Compares dValue values
 * @param  pV1  First vertex (will be cast to VERTEX_T *)
 * @param  pV2  Second vertex (will be cast to VERTEX_T *)
 * @return -1 if V1 < V2, 0 if dValues are the same, 1 if V1 > V2.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c].
 */
int compareVertices(void * pV1, void * pV2,int sort);

/* This function prints the shortest initeraries from the 
 * origin to the destination location.
 *	Arguments - startkey - the string of origin location
 *	          - endKey   - the string of destination locaion
 *
 *	Returns the parh's array.
 * Adapted with permission from function by S. Goldin's Lab 9-1
 * solution in file [linkedListGraph.c].
 */
 
int setPath(char* startKey, char* endKey,int vertexCount);
/** Finds the lowest weight path from one vertex to 
 * another through the network using Dijkstra's
 * algorithm. 
 * 	Arguments -  startKey - Key of start vertex
 * 	          -  endKey - Key of ending vertex
 * Returns total counts of the vertex along the path.
 * Returns -1 if either key is invalid.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c] and [linkedListGraph.c].
 */
 
int findItineraries(char* startKey, char* endKey,int vertexCount,int sort);
*	This function prints the flight data
 *		Arguments - pFlight - pointers to flight.
 *		          - count - orders of flight.
 */
 
void printFlightData(FLIGHT_T * pFlight,int count);
/*	This function prints the best itinerary from the Dijkstra's algorithm.
 *		Arguments - originVertex - the origin location
 *		          - desVertex - the destination location
 *	Returns 1 for printing successfully.
 *	Returns 0 for the location does not exist.
 */
int printPath(char * originVertex,char * desVertex);
