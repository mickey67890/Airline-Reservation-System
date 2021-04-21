/********************************************************/
/* Network header							  		*/
/* Define the function to create and traverse a network					*/
/* Apiravit Intharakanchit (Cheetah) 63070503457						*/
/* Modified to use with itinerary.c by Chayut Surathachaipong (Mickey) ID 63070503406	*/
/* PrincessConnectSummerKyaru								*/
/********************************************************/
#ifndef NETWORK_H
#define NETWORK_H

/* Tree Struct */
/***************/
typedef struct _node
	{
	struct _node* left;			/* Left child of the node */
	struct _node* right;		/* right child of thee node */
	char city[32];				/* The city of the location, used as key */
	char country[32];			/* The country of the location, used as secondary key */
	} NODE_T;
	
typedef struct _tree
	{
	NODE_T* root;				/* Root of the tree */
	int nodeCount;				/* Number of nodes in the tree */
	} TREE_T;
/***************/

/* Network Struct */
/******************/
typedef struct
{
	int addDay;					/* Number of days after the booking day */
	int hour;					/* store the hours of arrive or depart time */
	int min;					/* store the minutes of arrive or depart time */
	
}TIME_T;
typedef struct _flight
	{
	char flightNumber[6];				/* Flight code */
	char airline[32];				/* Name of airline */
	TIME_T * departure;				/* Depart time */
	TIME_T * arrive;				/* Arrive time */
	NODE_T* origin;					/* The origin of the flight */
	NODE_T* destination;				/* The destination of the flight */
	int seat[31];					/* Number of seat left */
	int duration;					/* Duration of the flight in minutes */
	int price;					/* Price of the flight in baht */
	struct _flight* next;				/* Next flight in the list */
	} FLIGHT_T;
/* For the weight of this edge, use either duration or price variable of flights */
typedef struct _edge
	{
	void* pVertex;  				/* Pointer to the VERTEX_T this item refers to */
	FLIGHT_T* flights;				/* The data of the flight this edge represent */
	struct _edge* next;				/* Next item in the edge list */
	int weight[3];					/* The array size of 3 that stores the flight's data
							 * that use in find the best itinerary from the criteria. 
							 * Index 0 holds the duration , index 1 holds the price
							 * and index 2 holds the segment value (1) */
	} EDGE_T;

/* For the key of this vertex, use both city and country variable of locations */
typedef struct _vertex
	{
	NODE_T* location;				/* The location of this vertex */
	int dValue[3];					/* Total weight so far, for Dijkstra's algorithm
							 * Index 0 holds the duration , index 1 holds the price
							 * and index 2 holds the segment value (1) */
							 
	int color;					/* Used for coloring the vertices during traversal */
	struct _vertex* parent;				/* Pointer to parent vertex */  
	struct _vertex* next;				/* Next vertex in the list */
	EDGE_T* edgeHead;				/* Pointer to the head of the edges list */
	EDGE_T* edgeTail;				/* pointer to the tail of the edges list */
	EDGE_T * parentEdge;				/* Pointer to the previous flight for finding the itinerary */
    	EDGE_T * nextEdge;				/* Pointer to the next flight for booking */
	} VERTEX_T;
/******************/

/* Location Tree */
/*****************/
/* Create the location tree */
/* Return the pointer to the tree */
TREE_T * createTree();

/* Free the node */
/* 'person' is the node */
void freeNode(NODE_T* node);

/* Post order traverse the tree and free each node */
/* 'person' is the current node */
/* 'function' is the the function to be executed */
void freeAll(NODE_T* node,void (*function)(NODE_T* node));

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

/* Create the location network */
TREE_T * network();

/* Adapted with permission from clearGraph function by S. Goldin in file [linkedListNetwork.c]. */	
void freeGraph();
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

/* Dijkstra's initialize functions */
/*******************/
/*	
 *	This function resets the addDay time indicator to zero
 *	in starting new requesting itinerary.
 */
void setZero();
/** Color all vertices to the passed color.
 *  @param  A color constant
 *  Adapted with permission from function by S. Goldin in file [linkedListNeetwork.c].
 */
void colorAll(int color);
/** Initialize the dValue and parent for all
 * vertices. dValue should be very big, parent
 * will be set to NULL. Also add to the minPriority queue.
 * Adapted with permission from function by S. Goldin in file [linkedListNetwork.c].
 */
void initAll();
/** Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 *
 *@param key    -  Key we are looking for
 *@param pPred  -  used to return the predecessor if any
 *@return pointer to the vertex structure if one is found
 *
 *Adapted with permission from function by S. Goldin in file [linkedListNetwork.c]. 
 */
VERTEX_T * findVertexByKey(char* key, VERTEX_T** pPred) ;





#endif
