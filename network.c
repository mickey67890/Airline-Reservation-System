/************************************************************/
/* Network program									*/
/* This program create network of locations and flight,					*/
/* using locations as vertex and flights as edges						*/
/* Apiravit Intharakanchit (Cheetah) 63070503457						*/
/* Modified to use with itinerary.c by Chayut Surathachaipong (Mickey) ID 63070503406	*/
/* PrincessConnectSummerKyaru								*/
/************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "network.h"
#include "itineraries.h"
#include "minPriorityQueueMod.h"

#define HUGEVALUE 99999

char* colorName[] = {"WHITE", "GRAY", "BLACK"};

VERTEX_T* vListHead = NULL;			/* Head of the vertices list */
VERTEX_T* vListTail = NULL;			/* Tail of the vertices list */

FLIGHT_T* fListHead = NULL;			/* Head of the flights list */
FLIGHT_T* fListTail = NULL;			/* Tail of the flights list */

int vertexCount = 0;
int flightCount = 0;


/* Adapted with permission from function by S. Goldin in file [linkedListNetwork.c]. */
/* Get information of the node and add it to the list as a vertex */
/* 'pNode' is the current node */
void addVertex(NODE_T* pNode)
	{
	NODE_T* newNode = NULL;			/* New node for the vertex */
	VERTEX_T* newVertex = NULL;		/* New node to be added */
	
	/* Create a new node to take informations of the current node */
	newNode = (NODE_T*)calloc(1,sizeof(NODE_T));
	if(newNode == NULL)
		{
		printf("Fail to allocate new node - exiting");
		exit(1);
		}
	strcpy(newNode->city,pNode->city);
	strcpy(newNode->country,pNode->country);
	
	/* Create a new vertex and copies the information from newNode */
	newVertex = (VERTEX_T*)calloc(1,sizeof(VERTEX_T));
	if(newVertex == NULL)
		{
		printf("Fail to allocate new vertex - exiting");
		exit(1);
		}
	newVertex->location = newNode;
	
	/* Put the vertices in a list */ 
	if (vListHead == NULL)
		vListHead = newVertex;
	else
		vListTail->next = newVertex; 
	vListTail = newVertex;
	vertexCount++;
	}

/* Adapted with permission from function by S. Goldin in file [simpleBinaryTree.c]. */
void traverseInOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode))
	{
    if (pCurrent->left != NULL)
       {
       traverseInOrder(pCurrent->left,nodeFunction); 
       }
    (*nodeFunction)(pCurrent);
    if (pCurrent->right != NULL)
       {
       traverseInOrder(pCurrent->right,nodeFunction); 
       }
	}

/* Find matching node */
/* 'pCurrent' is the current node */
/* 'city' is the city to be matched */
/* 'country' is the country to be matched */	
NODE_T* findNode(NODE_T* pCurrent,char city[],char country[])
{
	NODE_T * pFound = NULL;
	if(pCurrent == NULL)
		return NULL;
	if(((strcmp(pCurrent->city,city)) == 0) && ((strcmp(pCurrent->country,country)) == 0))
		return pCurrent;
	NODE_T* found = findNode(pCurrent->left,city,country);
	if(found != NULL)
		return found;
	return findNode(pCurrent->right,city,country);
}	

/* Get information of the fl ightsand add it to the list */
/* 'root' is the root node */	
void createFlights(NODE_T* root)
	{
	FILE * pIn = NULL;				/* Input file */
	FLIGHT_T* newFlight = NULL;		/* New flight to be added */
	char input[256];				/* The input from file */
	char cityDepart[32];			/* The city name of the departure location */
    char countryDepart[32];			/* The country of the departure location */
	char cityArrive[32];			/* The city name of the arrival location */
    char countryArrive[32];			/* The country of the arrival location */
	int check = 0;					/* Check which line to read */
	int round = 0;					/* Check amount to loop */
	TIME_T * departure = NULL;
	TIME_T * arrive = NULL;
	
	pIn = fopen("flights.txt","r");
    if (pIn == NULL)
		{
    	fprintf(stderr,"Error opening flights file - exiting\n");
		exit(1);
		}
	
    while(fgets(input,sizeof(input),pIn) != NULL)
    	{
    	check++;
		if(check == 1)
			{
			newFlight = (FLIGHT_T*)calloc(1,sizeof(FLIGHT_T));
			departure = calloc(1,sizeof(TIME_T));
			arrive = calloc(1,sizeof(TIME_T));
			
			
			sscanf(input,"%[^,],%[^\n]",newFlight->flightNumber,newFlight->airline);
			}
		else if(check == 2)
			sscanf(input,"%[^,],%[^,],%d:%d",cityDepart,countryDepart,&departure -> hour,&departure -> min);
		else if(check == 3)
			sscanf(input,"%[^,],%[^,],%d:%d",cityArrive,countryArrive,&arrive -> hour,&arrive -> min);
		else if(check == 4)
			{
			sscanf(input,"%d",&newFlight->price);
			for(round = 0; round < 31; round++)
				fscanf(pIn,"%d,",&newFlight->seat[round]);
			}
		else if(check == 5)
			{
			newFlight->origin = findNode(root,cityDepart,countryDepart);	
			newFlight->destination = findNode(root,cityArrive,countryArrive);
			newFlight -> departure = departure;
			newFlight -> arrive = arrive;
			newFlight -> duration = diffTime(departure,arrive);
			
			if (fListHead == NULL)
				fListHead = newFlight;
			else
				fListTail->next = newFlight;
			fListTail = newFlight; 	
			flightCount++;		
			check = 0;
			}
		}
	}

/* Find the matching vertices by comparing their city and country 
   Used in adding edge*/
/* 'pFlight' is the flight node */
/* 'check' check whether to match origin (if 1) or destiantion (if 2) */	
VERTEX_T * findVertex(FLIGHT_T* pFlight,int check)
	{
	VERTEX_T* pVertex = NULL;		/* The vertex found */
	VERTEX_T* currentVertex = NULL;	/* The current vertex */
	int round = 0;					/* Check amount to loop */
	/* Find origin vertex */	
	if(check == 1)
		{
		currentVertex = vListHead;
		for(round = 0;round < vertexCount;round++)
			{
			if((strcmp(currentVertex->location->city,pFlight->origin->city) == 0) && (strcmp(currentVertex->location->country,pFlight->origin->country) == 0))
				{
				pVertex = currentVertex;
				break;
				}
			else
				currentVertex = currentVertex->next;
			}
		}
		
	/* Find destination vertex */
	else if(check == 2)
		{
		
		currentVertex = vListHead;
		
		for(round = 0;round < vertexCount;round++)
			{
			
			if((strcmp(currentVertex->location->city,pFlight->destination->city) == 0) && (strcmp(currentVertex->location->country,pFlight->destination->country) == 0))
				{
				pVertex = currentVertex;	
				break;
				}
			else
				currentVertex = currentVertex->next;
			}
		}
		
	
	return pVertex;
	}

/* Adapted with permission from function by S. Goldin in file [linkedListNetwork.c]. */	
void addEdge(FLIGHT_T* pFlight)
	{
    VERTEX_T* pFromVtx = NULL;		/* The origin vertex */
    VERTEX_T* pToVtx = NULL;		/* The destination vertex */
    EDGE_T* newEdge = NULL;			/* The new edge to be created */
    
    pFromVtx = findVertex(pFlight,1);
    pToVtx = findVertex(pFlight,2);
    printf("%s -> %s\n",pFromVtx -> location -> city,pToVtx -> location -> city);
	if ((pFromVtx == NULL) || (pToVtx == NULL))
		{
		printf("Fail to find vertex - exiting");
		exit(1);
		}
    	else
	{
		newEdge = (EDGE_T*) calloc(1,sizeof(EDGE_T));
		if (newEdge == NULL)
		{
			printf("Fail to allocate new edge - exiting");
			exit(1);
		}
    		else
			{
			newEdge->pVertex = pToVtx;
			newEdge->flights = pFlight; 
			if (pFromVtx->edgeTail != NULL)
				pFromVtx->edgeTail->next = newEdge;
			else
				pFromVtx->edgeHead = newEdge;
			newEdge -> weight[0] = newEdge -> flights -> duration;
			newEdge -> weight[1] = newEdge -> flights -> price;
			newEdge -> weight[2] = 1;
			pFromVtx->edgeTail = newEdge;
			}
    	}
}

/* Create the location network */
int network()
	{
	TREE_T* pTree;					/* The tree created by tree.c */
	FLIGHT_T* currentFlight = NULL;		/* The current flight */
	int round = 0;
	
	/* Create location tree */
	pTree = createTree();
	/* Create vertices of location list */
	traverseInOrder(pTree->root,&addVertex);
	
	/* Create flight list */
	printf("tree\n");
	createFlights(pTree->root);
	
	/* Connect locations (vertex) using flights (edges) */
	
	currentFlight = fListHead;
	for(round = 0;round < flightCount;round++)
		{
		addEdge(currentFlight);
		currentFlight = currentFlight->next;
		}
	}

/*	
 *	This function resets the addDay time indicator to zero
 *	to start new requesting  and booing itinerary.
 */
void setZero()
{
	VERTEX_T * current = vListHead;
	VERTEX_T * pAdjacent = NULL;
	EDGE_T * currentEdge = NULL;
	while(current != NULL)
	{
		current -> parent = NULL;
		current -> parentEdge = NULL;
		current -> nextEdge = NULL;
		currentEdge = current -> edgeHead;
		
		while(currentEdge != NULL)
		{
			currentEdge -> flights -> departure -> addDay = 0;
			currentEdge -> flights -> arrive -> addDay  = 0;
			currentEdge = currentEdge -> next;
		}
		current = current -> next;
	}
}
/** Color all vertices to the passed color.
 *  @param  A color constant
 *  Adapted with permission from function by S. Goldin in file [linkedListNeetwork.c].
 */
void colorAll(int color)
{
    VERTEX_T* pVertex = vListHead;
    while (pVertex != NULL)
       {
       pVertex->color = color;
       pVertex = pVertex->next;
       }
}

/** Initialize the dValue and parent for all
 * vertices. dValue should be very big, parent
 * will be set to NULL. Also add to the minPriority queue.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c].
 */
void initAll()
{
    VERTEX_T* pVertex = vListHead;
    while (pVertex != NULL)
       {
       pVertex->dValue[0] = HUGEVALUE;
       pVertex -> dValue[1] = HUGEVALUE;
       pVertex -> dValue[2] = HUGEVALUE;
       pVertex->parent = NULL;
       enqueueMin(pVertex);
       pVertex = pVertex->next;
       }
}

/** Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 *
 *@param key    -  Key we are looking for
 *@param pPred  -  used to return the predecessor if any
 *@return pointer to the vertex structure if one is found
 *
 *Adapted with permission from function by S. Goldin in file [linkedListNetwork.c]. 
 */
VERTEX_T * findVertexByKey(char* key, VERTEX_T** pPred) 
{
    VERTEX_T * pFoundVtx = NULL;
    VERTEX_T * pCurVertex = vListHead;
    *pPred = NULL;
    /* while there are vertices left and we haven't found
     * the one we want.
     */
    while ((pCurVertex != NULL) && (pFoundVtx == NULL))
       {
       if (strcasecmp(pCurVertex-> location -> city,key) == 0)
          {
	  pFoundVtx = pCurVertex;
	  }
       else
          {
	  *pPred = pCurVertex;
          pCurVertex = pCurVertex->next;
          }
       }
    return pFoundVtx;
}





