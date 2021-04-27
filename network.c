/****************************************************************/
/* Network program					  	*/
/* This program create network of locations and flight,		*/
/* using locations as vertex and flights as edges		*/
/* Apiravit Intharakanchit (Cheetah) 63070503457		*/
/* PrincessConnectSummerKyaru					*/
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "network.h"

#define HUGEVALUE 99999
#define WHITE 0
#define GRAY  1
#define BLACK 2

/* Adapted with permission from S. Goldin in file [linkedListNetwork.c]. */
VERTEX_T* vListHead = NULL;			/* Head of the vertices list */
VERTEX_T* vListTail = NULL;			/* Tail of the vertices list */

FLIGHT_T* fListHead = NULL;			/* Head of the flights list */
FLIGHT_T* fListTail = NULL;			/* Tail of the flights list */

int vertexCount = 0;
int flightCount = 0;

/* Adapted with permission from freeAdjacencyList function by S. Goldin in file [linkedListNetwork.c]. */	
void freeEdgeList(VERTEX_T *pVertex)
	{
	EDGE_T* pCurRef = pVertex->edgeHead;
	while (pCurRef != NULL)
		{
		EDGE_T* pDelRef = pCurRef;
		pCurRef = pCurRef->next;
		free(pDelRef->flights);
		free(pDelRef);
		}
	pVertex->edgeHead = NULL;
	pVertex->edgeTail = NULL;
	}
	
/* Adapted with permission from  clearGraph function by S. Goldin in file [linkedListNetwork.c]. */	
void freeGraph()
	{
	VERTEX_T * pCurVertex = vListHead;
	while (pCurVertex != NULL)
		{
    		freeEdgeList(pCurVertex);
    		VERTEX_T* pDelVtx = pCurVertex;
    		pCurVertex = pCurVertex->next;
    		free(pDelVtx);
		}
	vListHead = NULL;  
	vListTail = NULL; 
	}	

/* Get information of the node and add it to the list as a vertex */
/* 'pNode' is the current node */
void addVertex(NODE_T* pNode)
	{
	NODE_T* newNode = NULL;			/* New node for the vertex */
	VERTEX_T* newVertex = NULL;		/* New node to be added */
	char* key = pNode->city;		/* The city and country combine into one string as key */ 
	
	/* Create a new vertex and copies the information from pNode */
	newVertex = (VERTEX_T*)calloc(1,sizeof(VERTEX_T));
	if(newVertex == NULL)
		{
		printf("Fail to allocate new vertex - exiting");
		exit(1);
		}
	newVertex->location = pNode;
	strcat(key,".");
	strcat(key,pNode->country);
	newVertex->key = key;	
	
	/* Put the vertices in a list */ 
	if (vListHead == NULL)
		vListHead = newVertex;
	else
		vListTail->next = newVertex; 
	vListTail = newVertex;
	vertexCount++;
	}

/* Adapted with permission from function traverseInOrder by S. Goldin in file [simpleBinaryTree.c]. */
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
	if(pCurrent != NULL)
		{ 
		if(((strcasecmp(pCurrent->city,city)) == 0) && ((strcasecmp(pCurrent->country,country)) == 0))
			pFound = pCurrent;
		else 
			{ 
			pFound = findNode(pCurrent->left,city,country);
			if(pFound == NULL)
				pFound = findNode(pCurrent->right,city,country);
			}
		}
	return pFound;
	}

/* Get information of the flights and add it to the list */
/* 'root' is the root node */	
void createFlights(NODE_T* root)
	{
	FILE * pIn = NULL;			/* Input file */
	FLIGHT_T* newFlight = NULL;		/* New flight to be added */
	char input[256];			/* The input from file */
	char cityDepart[32];			/* The city name of the departure location */
	char countryDepart[32];			/* The country of the departure location */
	char cityArrive[32];			/* The city name of the arrival location */
	char countryArrive[32];			/* The country of the arrival location */
	int check = 0;				/* Check which line to read */
	int round = 0;				/* Check amount to loop */
	
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
			sscanf(input,"%[^,],%[^\n]",newFlight->flightNumber,newFlight->airline);
			}
		else if(check == 2)
			sscanf(input,"%[^,],%[^,],%d:%d",cityDepart,countryDepart,&newFlight->hourDepart,&newFlight->minuteDepart);
		else if(check == 3)
			sscanf(input,"%[^,],%[^,],%d:%d",cityArrive,countryArrive,&newFlight->hourArrive,&newFlight->minuteArrive);
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

/* Find the matching vertices by comparing their city and country */
/* 'pFlight' is the flight node */
/* 'check' check whether to match origin (if 1) or destiantion (if 2) */	
VERTEX_T* findVertex(FLIGHT_T* pFlight,int check)
	{
	VERTEX_T* pVertex = NULL;		/* The vertex found */
	VERTEX_T* currentVertex = NULL;		/* The current vertex */
	int round = 0;				/* Check amount to loop */
		
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
	else
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

/* Adapted with permission from function addEdge by S. Goldin in file [linkedListNetwork.c]. */	
void addEdge(FLIGHT_T* pFlight)
	{
	VERTEX_T* pFromVtx = NULL;		/* The origin vertex */
	VERTEX_T* pToVtx = NULL;		/* The destination vertex */
	EDGE_T* newEdge = NULL;			/* The new edge to be created */
    
	pFromVtx = findVertex(pFlight,1);
	pToVtx = findVertex(pFlight,2);
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
			pFromVtx->edgeTail = newEdge;
			}
    		}
	}

/* Create the location network */
int network()
	{
	TREE_T* pTree;				/* The tree created by tree.c */
	FLIGHT_T* currentFlight;		/* The current flight */
	int round = 0;
	
	/* Create location tree */
	pTree = createTree();
	
	/* Create vertices of location list */
	traverseInOrder(pTree->root,&addVertex);
	
	/* Create flight list */
	createFlights(pTree->root);
	
	/* Connect locations (vertex) using flights (edges) */
	currentFlight = fListHead;
	for(round = 0;round < flightCount;round++)
		{
		addEdge(currentFlight);
		currentFlight = currentFlight->next;
		}	
	}
