#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_converter.h"
#include "evaluation.h"
#include "tree.h"
#include "hbt.h"

#define DEBUG_TREE

Tnode *TreeReconstruct(int *arr, char *branch, int *idx, int size)
{
	if((*idx) == size)
	{
		return NULL;
	}
	Tnode *node = CreateTreeNode(arr[*idx]);
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	int currIdx = *idx;
	(*idx)++;
	
	node->left = NULL;
	node->right = NULL;
	if((branch[currIdx] == 2) || (branch[currIdx] == 3))
	{
		node->left = TreeReconstruct(arr, branch, idx, size);
	}
	if((branch[currIdx] == 1) || (branch[currIdx] == 3))
	{
		node->right = TreeReconstruct(arr, branch, idx, size);
	}
	
	return node;
}

Tnode *PreorderBSTConstruct(int *arr, int *idx, int size, int ub)
{
	if((*idx) == size)
	{
		return NULL;
	}
	if(arr[*idx] > ub)
	{
		return NULL;
	}
	Tnode *node = CreateTreeNode(arr[*idx]);
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	(*idx)++;
	node->left = PreorderBSTConstruct(arr, idx, size, node->key);
	node->right = PreorderBSTConstruct(arr, idx, size, ub);

	return node;
}

Tnode *CreateTreeNode(int key)
{
	Tnode *node = malloc(sizeof(*node));
	if(node == NULL)
	{
		fprintf(stderr, "malloc failed.");
		return NULL;
	}
	node->key = key;
	node->balance = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void PrintTreePreorder(Tnode *root)
{
	if(root == NULL)
	{
		return;
	}
	fprintf(stdout, "%d ", root->key);
	PrintTreePreorder(root->left);
	PrintTreePreorder(root->right);
}
