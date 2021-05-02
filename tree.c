/****************************************************************/
/* Tree program							*/
/* This program create tree of locations,		  	*/
/* each node contains the name of the city and its country	*/
/* Apiravit Intharakanchit (Cheetah) 63070503457		*/
/* PrincessConnectSummerKyaru					*/
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "network.h"

/* Debug Functions */
/*******************/
void printNodeDataDebug(NODE_T* node);						/* Print out the name and gender of the node */
void printAllDebug(NODE_T* node,void (*function)(NODE_T* node));		/* In order traverse the tree and print each node */
/*******************/

/* Free the node */
/* 'person' is the node */
void freeNode(NODE_T* node)
	{
	free(node);
	}
	
/* Post order traverse the tree and free each node */
/* 'person' is the current node */
/* 'function' is the the function to be executed */
void freeAll(NODE_T* node,void (*function)(NODE_T* node))
	{
	if (node->left != NULL)
		freeAll(node->left,function); 
	if (node->right != NULL)
		freeAll(node->right,function); 
	(*function)(node);
	} 

/* Free the tree */
/* 'pTree' is the tree */
void freeTree(TREE_T * pTree)
	{
	if (pTree != NULL)
		{
		if (pTree->root != NULL)	
			freeAll(pTree->root,&freeNode);
		free(pTree);
		}
	}

/* Traverse the tree and insert node */
/* 'currentNode' is the current node */
/* 'newNode' is the node to be inserted into the tree */
void insertNode(NODE_T* currentNode,NODE_T * newNode)
	{
	/* If the cities name aren't identical */
	if(strcmp(newNode->city,currentNode->city) != 0)
		{
		if (strcmp(newNode->city,currentNode->city) < 0)
			{
			if (currentNode->left == NULL)
        			currentNode->left = newNode;
    			else
        			insertNode(currentNode->left,newNode); 
			}	
		else
    			{
    			if (currentNode->right == NULL)
        			currentNode->right = newNode;
    			else
        			insertNode(currentNode->right,newNode); 
    			}
    		}
	/* If the cities name are identical */
	/* Use country instead */
	else
    		{
		if (strcmp(newNode->country,currentNode->country) < 0)
			{
			if (currentNode->left == NULL)
        			currentNode->left = newNode;
    			else
        			insertNode(currentNode->left,newNode); 
			}	
		else
    			{
    			if (currentNode->right == NULL)
        			currentNode->right = newNode;
    			else
        			insertNode(currentNode->right,newNode); 
    			}
    		}
	}  

/* Create the location tree */
/* Return the pointer to the tree */
TREE_T* createTree()
	{
	FILE * pIn = NULL;			/* Input file */
	TREE_T* pTree = NULL;			/* The tree */
	NODE_T* location = NULL;		/* The location node */
	char input[256];			/* The input from file */
	char city[32];				/* The city name of the location */
	char country[32];			/* The country of the location */
    
	pIn = fopen("location.txt","r");
	if (pIn == NULL)
		{
    		fprintf(stderr,"Error opening location file - exiting\n");
		exit(1);
		}
    
	pTree = calloc(1,sizeof(TREE_T));
	while(fgets(input,sizeof(input),pIn) != NULL)
    		{
		sscanf(input,"%s %s",city,country);
		location = (NODE_T*) calloc(1,sizeof(NODE_T));
		if (location == NULL)
			{
    			printf("Error allocating location array - exiting\n");
        		exit(1);
        		}
        	else
        		{
        		strcpy(location->city,city);
			strcpy(location->country,country);
        		if(pTree->root == NULL)
        			{
        			pTree->root = location;
        			pTree->nodeCount++;
        			}
        		else
        			{
				insertNode(pTree->root,location);
				pTree->nodeCount++;
				}
			}
		}
	fclose(pIn);
    
	/* Debug */
	/*********
	printAllDebug(pTree->root,&printNodeDataDebug);
	freeTree(pTree);
	/*********/
    
	return pTree;
	}

/* Debug Functions */
/*******************/
/* Print out the name and gender of the node, used for debug */
/* 'person' is the current node */
void printNodeDataDebug(NODE_T* node)
	{
	printf("%s %s\n", node->city, node->country);
	}
	
/* In order traverse the tree and print each node , used for debug */
/* 'person' is the current node */
/* 'function' is the the function to be executed */
void printAllDebug(NODE_T* node,void (*function)(NODE_T* node))
	{
	if (node->left != NULL)
		printAllDebug(node->left,function); 
	(*function)(node);
	if (node->right != NULL)
		printAllDebug(node->right,function); 
	}
/*******************/
