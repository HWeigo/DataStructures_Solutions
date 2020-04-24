#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

static void PrintGraph(LinkList **graph, int totalNodes);
static LinkList *AddAdjacentyNode(short index);

LinkList **GraphConstruct(char *filename)
{
	FILE *fptr = NULL;
	fptr = fopen(filename, "r");
	if(fptr == NULL)
	{
		fprintf(stderr, "fopen failed.");
		return NULL;
	}

	size_t numGet = 0;
    short m;
    numGet = fread(&m, sizeof(short), 1, fptr);
    if((numGet != 1) || (m <= 0) || (m>SHRT_MAX))
    {
        fprintf(stderr, "wrong format");
        fclose(fptr);
        return NULL;
    }
    short n;
    numGet = fread(&n, sizeof(short), 1, fptr);
    if((numGet != 1) || (n <= 0) || (n>SHRT_MAX))
    {
        fprintf(stderr, "wrong format");
        fclose(fptr);
        return NULL;
    }
	
	// Store values into nodes 
	int totalNodes = (int) m*n;
	short *nodes = NULL;
	nodes = malloc(sizeof(short) * totalNodes);
	if(nodes == NULL)
	{
		fprintf(stderr, "malloc failed.");
		fclose(fptr);
		return NULL;
	}
	short value;
	for(int i=0;i<totalNodes;++i)
	{
		numGet = fread(&value, sizeof(short), 1 , fptr);
	    if((numGet != 1) || (value<SHRT_MIN) || (value>SHRT_MAX))
        {
            fprintf(stderr, "wrong format");
			free(nodes);
            fclose(fptr);
            return NULL;
        }
		nodes[i] = value;
		printf("%d:%hd ",i, value);
	}

	// Initial Graph 
	LinkList **graph = NULL;
	graph = malloc(sizeof(LinkList*) * totalNodes);
	for(int i=0;i<totalNodes;++i)
	{
		graph[i] = NULL;
	}
	
	//graph[2] = AddAdjacentyNode(1);
	
	// find edges's adjacency
	short index = 0; 
	LinkList **head = NULL;
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;++j)
		{
			*head = graph[index];
			// check if this node have left adjacent node 
			if((index%n != 0) && (nodes[index] < nodes[index-1]))
			{
				head = &(AddAdjacentyNode(index-1));
				if(head == NULL)
				{
					fprintf(stderr, "fail to add node.");
					free(nodes);
				    fclose(fptr);
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				*head = (*head)->next;
			}
			// check if this node have upper adjacent node 
			if((index >= n) && (nodes[index] < nodes[index-n]))
			{
				head = &(AddAdjacentyNode(index-n));
				if(head == NULL)
				{
					fprintf(stderr, "fail to add node.");
					free(nodes);
				    fclose(fptr);
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				*head = (*head)->next;
			}		
			// check if this node have right adjacent node 
			if(((index+1)%n != 0) && (nodes[index] < nodes[index+1]))
			{
				head = &(AddAdjacentyNode(index+1));
				if(head == NULL)
				{
					fprintf(stderr, "fail to add node.");
					free(nodes);
				    fclose(fptr);
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				*head = (*head)->next;
			}
			// check if this node have lower adjacent node 
			if((index < (totalNodes-n)) && (nodes[index] < nodes[index+n]))
			{
				head = &(AddAdjacentyNode(index+n));
				if(head == NULL)
				{
					fprintf(stderr, "fail to add node.");
					free(nodes);
				    fclose(fptr);
					DestroyGraph(graph, totalNodes);
					return NULL;
				}
				*head = (*head)->next;
			}
			index++;
		}
	}
	
	PrintGraph(graph, totalNodes);
	DestroyGraph(graph, totalNodes);


	free(nodes);
	fclose(fptr);
	return graph;

}

static LinkList *AddAdjacentyNode(short index)
{
	LinkList *node = NULL;
	node = malloc(sizeof(LinkList));
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	node->dest = index;
	node->next = NULL;
	return node;
}

void DestroyGraph(LinkList **graph, int totalNodes)
{
	LinkList *head = NULL;
	LinkList *p = NULL;
	for(int i=0;i<totalNodes;++i)
	{
		head = graph[i];
		while(head != NULL)
		{
			p = head->next;
			free(head);
			head = p;
		}
	}
	free(graph);
}

static void PrintGraph(LinkList **graph, int totalNodes)
{
	LinkList *head = NULL;
	for(int i=0;i<totalNodes;++i)
	{
		printf("%d: ", i);
		head = graph[i];
		while(head != NULL)
		{
			printf("%hd ", head->dest);
			head = head->next;
		}
		printf("\n");
	}
}
