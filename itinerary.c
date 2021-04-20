/*
 *	This is the file that works about finding the best itineraries from the 
 *	sorting criteria.
 *	Created by Chayut Surathachaipong (Mickey) ID 63070503406
 *	Princess Connect Summer Kyaru.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itineraries.h"
#include "network.h"
#include "minPriorityQueueMod.h"

#define WHITE 0
#define GRAY  1
#define BLACK 2


/*	Calculate the differents of time1 and time2
 *	Arguments - pTime1 - pointers of time1
 *	          - pTime2 - pointers of time2
 *	returns the differents in minute
 */
int diffTime(TIME_T * pTime1,TIME_T * pTime2)
{
	int diffMin = 0;
	int diffHour = 0;
	TIME_T time1 = *pTime1;
	TIME_T time2 = *pTime2;
	pTime2 -> addDay = pTime1 -> addDay;
	if(time1.min > time2.min)
	{
		time2.min += 60;
		time2.hour --;
	}
	if(time1.hour > time2.hour)
	{
		pTime2 -> addDay ++;
		time2.hour += 24;
	}

	diffMin = time2.min - time1.min;
	diffHour = time2.hour - time1.hour;
	
	return (diffHour * 60) + diffMin;
	
}

/*	This fumction compares the arrive time of the previous flight
 *	and the departure time of the next flight.
 *		Arguments - edge1 - pointers of previous EDGE_T flight
 *                         - edge2 - pointers of next EDGE_T flight
 *	Returns 1 if the time differences is more than 30 minutes.
 *	Otherwise returns 0.
 */
int flightTimeCompare(EDGE_T * edge1,EDGE_T * edge2)
{
	TIME_T * arrive = edge1 -> flights -> arrive;
	TIME_T * departure = edge2  -> flights -> departure;
	int result = 0;
	if(diffTime(arrive,departure) > 30)
	{
		result = 1;
	}
	return result;
}
/** Comparison function to send to the minPriorityQueue
 * Compares dValue values
 * @param  pV1  First vertex (will be cast to VERTEX_T *)
 * @param  pV2  Second vertex (will be cast to VERTEX_T *)
 * @return -1 if V1 < V2, 0 if dValues are the same, 1 if V1 > V2.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c].
 */
int compareVertices(void * pV1, void * pV2,int sort)
{
   VERTEX_T * pVertex1 = (VERTEX_T*) pV1;
   VERTEX_T * pVertex2 = (VERTEX_T*) pV2;
   if (pVertex1->dValue[sort] < pVertex2->dValue[sort])
      return -1;
   else if (pVertex1->dValue[sort] > pVertex2->dValue[sort])
      return 1;
   else 
     return 0;
}
/* This function prints the shortest initeraries from the 
 * origin to the destination location.
 *	Arguments - startkey - the string of origin location
 *	          - endKey   - the string of destination locaion
 *
 *	Returns the parh's array.
 * Adapted with permission from function by S. Goldin's Lab 9-1
 * solution in file [linkedListGraph.c].
 */
int setPath(char* startKey, char* endKey,int vertexCount)
{
	VERTEX_T * pVer1 = NULL;
	VERTEX_T * pVer2 = NULL;
	VERTEX_T * pDummy = NULL;
	VERTEX_T * pCurrent = NULL;
	
	EDGE_T * edge = NULL;

	int pathCount = 0;
	int loop;
	
	pVer1 = (VERTEX_T *)findVertexByKey(startKey,&pDummy);
	pVer2 = (VERTEX_T *)findVertexByKey(endKey,&pDummy);
	VERTEX_T ** path = calloc(vertexCount,sizeof(VERTEX_T*));
	pCurrent = pVer2;
	while(pCurrent != NULL)
	{
		path[pathCount] = pCurrent;
		edge = pCurrent -> parentEdge;
		pCurrent = pCurrent -> parent;
		if(pCurrent != NULL)
		{
			pCurrent -> nextEdge = edge;
		}
		pathCount ++;
	}
	for(loop = pathCount -1 ;loop >= 0;loop--)
	{
		if(loop > 0)
		{
			if(loop<pathCount-1)
			{
				diffTime(path[loop] -> parentEdge -> flights -> arrive,path[loop] -> nextEdge -> flights -> departure);
			}
			diffTime(path[loop] -> nextEdge -> flights -> departure,path[loop] -> nextEdge -> flights -> arrive);
				
		}	
	}
	free(path);
	return pathCount;
}
/** Finds the lowest weight path from one vertex to 
 * another through the network using Dijkstra's
 * algorithm. 
 * 	Arguments -  startKey - Key of start vertex
 * 	          -  endKey - Key of ending vertex
 * Returns total counts of the vertex along the path.
 * Returns -1 if either key is invalid.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c] and [linkedListGraph.c].
 */
int findItineraries(char* startKey, char* endKey,int vertexCount,int sort)
{
	VERTEX_T * pVer1 = NULL;
	VERTEX_T * pVer2 = NULL;
	VERTEX_T * pDummy = NULL;
	VERTEX_T * pCurrent = NULL;
	VERTEX_T * adjacent = NULL;
	int pathCount = 0;
    	
    	EDGE_T * previous = NULL;
    	
	int weight = 0;
	
	pVer1 = (VERTEX_T *)findVertexByKey(startKey,&pDummy);
	pVer2 = (VERTEX_T *)findVertexByKey(endKey,&pDummy);
	
	if(pVer1 == NULL || pVer2 == NULL)
	{
		printf("The location does not exist\n");
		return -1;
	}
	setZero();
	colorAll(WHITE);
	queueMinInit(&compareVertices);
	initAll();
	pVer1 -> dValue[sort] = 0;
	while(queueMinSize() > 0)
	{
		pCurrent = dequeueMin(sort);
		if(pCurrent -> color == WHITE)
		{
			pCurrent -> color = BLACK;
			EDGE_T * currentEdge = pCurrent -> edgeHead;	
			while(currentEdge != NULL)
			{
				
				adjacent = currentEdge -> pVertex;
				if(adjacent -> color == WHITE)
				{
					if(pCurrent != pVer1)
					{
						previous = pCurrent -> parentEdge;
						if(previous == NULL)
						{
							break;
						}
						if(!flightTimeCompare(previous,currentEdge))
						{
							currentEdge = currentEdge -> next;
							continue;
						}
					}
					
					weight = currentEdge -> weight[sort];
					if(((pCurrent -> dValue[sort]) + weight) < adjacent -> dValue[sort])
					{
						adjacent -> dValue[sort] = pCurrent -> dValue[sort] + weight;
						adjacent -> parent = pCurrent;
						adjacent -> parentEdge = currentEdge;
					}	
				}
			currentEdge = currentEdge -> next;
			}
		}
	}
	if(pVer2 -> parent != NULL)
	{
		printf("Found\n");
		pathCount = setPath(startKey,endKey,vertexCount);
	}
	else
	{
		printf("Can not reach to\n");
	}
	return pathCount;
}
/*	This function prints the flight data
 *		Arguments - pFlight - pointers to flight.
 *		          - count - orders of flight.
 */
void printFlightData(FLIGHT_T * pFlight,int count)
{
	FLIGHT_T * fData = pFlight;
	printf("Flight %d\n",count);
	printf("|\tAirline : %s\n",fData -> airline);
	printf("|\tFlight Code : %s\n",fData -> flightNumber);
	printf("|\tFrom %s (%s) ",fData -> origin -> city,fData -> origin -> country);
	printf("------------> to %s (%s)\n",fData -> destination -> city,fData -> destination -> country);
	printf("|\t%.2d:%-40.2d",fData -> departure -> hour,fData -> departure -> min);
	printf("%.2d:%.2d\n",fData -> arrive -> hour,fData -> arrive -> min);
	printf("|\tTime travelled : %d minutes (%d hours %d minutes)\n",fData -> duration,(fData -> duration)/60,(fData -> duration)%60);
	printf("|\t%d Baht\n",fData -> price);
	printf("--------------------------------------------------------------------------\n");
}
/*	This function prints the best itinerary from the Dijkstra's algorithm.
 *		Arguments - originVertex - the origin location
 *		          - desVertex - the destination location
 *	Returns 1 for printing successfully.
 *	Returns 0 for the location does not exist.
 */
int printPath(char * originVertex,char * desVertex)
{
	VERTEX_T * pTest = NULL;
	VERTEX_T * startVertex = findVertexByKey(originVertex,&pTest);
	VERTEX_T * endVertex = findVertexByKey(desVertex,&pTest);
	VERTEX_T * pCurrent = startVertex;
	EDGE_T * currentFlight = NULL;
	FLIGHT_T * fData = NULL;
	int totalprice = 0;
	int totalTime = 0;
	int count = 1;
	int success = 0;
	if(startVertex == NULL || endVertex == NULL)
	{
		printf("The location does not exist\n");
		return success;
	}
	while(pCurrent != NULL)
	{
		currentFlight = pCurrent -> nextEdge;
		
		if(currentFlight != NULL)
		{
			fData = currentFlight -> flights;
			printFlightData(fData,count);
			totalprice += fData -> price;
			totalTime += fData -> duration;
			pCurrent = currentFlight -> pVertex;
			count++;
		}
		else
		{
			break;
		}
	}
	printf("If you book this itinerary, you will pay : %d baht\n",totalprice);
	printf("If you book this itinerary, you will travel : %d minutes (%d hours %d minutes)\n",totalTime,totalTime/60,totalTime%60);
	success = 1;
	return success;
}
