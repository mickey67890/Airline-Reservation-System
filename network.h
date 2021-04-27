/********************************************************/
/* Network header					*/
/* Define the function to create and traverse a network	*/
/* Apiravit Intharakanchit (Cheetah) 63070503457	*/
/* PrincessConnectSummerKyaru				*/
/********************************************************/
#ifndef NETWORK_H
#define NETWORK_H

/* Tree Struct */
/***************/
typedef struct _node
	{
	struct _node* left;				/* Left child of the node */
	struct _node* right;				/* right child of thee node */
	char city[32];					/* The city of the location, used as key */
	char country[32];				/* The country of the location, used as secondary key */
	} NODE_T;
	
typedef struct _tree
	{
	NODE_T* root;					/* Root of the tree */
	int nodeCount;					/* Number of nodes in the tree */
	} TREE_T;
/***************/

/* Network Struct */
/******************/
typedef struct _flight
	{
	char flightNumber[6];				/* Flight code */
	char airline[32];				/* Name of airline */
	int hourArrive;					/* The hour */
	int minuteArrive;				/* The minute of the hour */
	int hourDepart;					/* The hour */
	int minuteDepart;				/* The minute of the hour */
	NODE_T* origin;					/* The origin of the flight */
	NODE_T* destination;				/* The destination of the flight */
	int seat[31];					/* Number of seat left */
	int duration;					/* Duration of the flight in minutes */
	int price;					/* Price of the flight in baht */
	int nextDay;					/* Check if the flight ends on the next day*/
	struct _flight* next;				/* Next flight in the list */
	} FLIGHT_T;

/* For the weight of this edge, use either duration or price variable of flights */
typedef struct _edge
	{
	void* pVertex;  				/* Pointer to the VERTEX_T this item refers to */
	FLIGHT_T* flights;				/* The data of the flight this edge represent */
	struct _edge* next;				/* Next item in the edge list */
	} EDGE_T;

/* For the key of this vertex, use both city and country variable of locations */
typedef struct _vertex
	{
	NODE_T* location;				/* The location of this vertex */
	char* key;					/* Key of the vertex */
	int dValue;					/* Total weight so far, for Dijkstra's algo */ 
	int color;					/* Used for coloring the vertices during traversal */
	struct _vertex* parent;				/* Pointer to parent vertex */  
	struct _vertex* next;				/* Next vertex in the list */
	EDGE_T* edgeHead;				/* Pointer to the head of the edges list */
	EDGE_T* edgeTail;				/* pointer to the tail of the edges list */
	} VERTEX_T;
/******************/

/* Location Tree */
/*****************/
/* Create the location tree */
/* Return the pointer to the tree */
TREE_T* createTree();

/* Free the tree */
/* 'pTree' is the tree */
void freeTree(TREE_T * pTree);
/*****************/

/* Location Network */
/********************/
/* Adapted with permission from function by S. Goldin in file [simpleBinaryTree.c]. */
void traverseInOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode));

/* Find matching node */
/* 'pCurrent' is the current node */
/* 'city' is the city to be matched */
/* 'country' is the country to be matched */	
NODE_T* findNode(NODE_T* pCurrent,char city[32],char country[32]);

/* Find the matching vertices by comparing their city and country */
/* 'pFlight' is the flight node */
/* 'check' check whether to match origin (if 1) or destiantion (if 2) */	
VERTEX_T* findVertex(FLIGHT_T* pFlight,int check);

/* Adapted with permission from clearGraph function by S. Goldin in file [linkedListNetwork.c]. */	
void freeGraph();

/* Create the location network */
int network();
/********************/

/* Debug Functions */
/*******************/
/* Print out the name and gender of the node, used for debug */
/* 'person' is the current node */
void printNodeDataDebug(NODE_T* node);
	
/* In order traverse the tree and print each node , used for debug */
/* 'person' is the current node */
/* 'function' is the the function to be executed */
void printAllDebug(NODE_T* node,void (*function)(NODE_T* node));
/*******************/
#endif
