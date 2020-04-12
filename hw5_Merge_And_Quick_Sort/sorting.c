#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sorting.h"

//#define DEBUG_HW
static long MedianOfThree(long *array, int lb, int mid, int ub);
static void Swap(long *array, int idx1, int idx2);
static void QuickSortHelper(long *array, int lb, int ub);

void Quick_Sort(long *Array, int Size)
{
	QuickSortHelper(Array, 0, Size-1);
}

static void printArray(long *array, int size)
{
    for(int i=0; i<size;++i)
    {   
        printf("%ld ", array[i]);
    }   
    printf("\n");
}

static void QuickSortHelper(long *array, int lb, int ub)
{
	if(lb >= ub)
	{
		return;
	}
	
	int mid = (lb + ub)/2;
	long pivot = MedianOfThree(array, lb, mid, ub);
	int down = lb;
	int up = ub;
	int left = lb;
	int right = ub;
	int leftLength = 0, rightLength = 0;

	while(down < up)
	{
		while((array[down] <= pivot) && (down <= up))
		{
			if(array[down] == pivot)
			{
				Swap(array, down, left);
				left++;
				leftLength++;
			}
			down++;
		}
		while((array[up] >= pivot) && (down <= up))
		{
			if(array[up] == pivot)
			{
				Swap(array, up, right);
				right--;
				rightLength++;
			}
			up--;
		}

		if(down < up)
		{
			Swap(array, down, up);
		}
	}
	
	int i = up;
	int j = lb;
	while(j < left)
	{
		Swap(array, i, j);
		i--;
		j++;
	}

	i = down;
	j = ub;
	while(j > right)
	{
		Swap(array, i, j);
		i++;
		j--;
	}
#ifdef DEBUG_HW
	printf("pivot: %ld\n down: %d, up: %d\n", pivot, down, up);	
	printArray(array, 25);
#endif
	QuickSortHelper(array, lb, up-leftLength);
	QuickSortHelper(array, down+rightLength, ub);
}

static long MedianOfThree(long *array, int lb, int mid, int ub)
{
	if(array[mid] > array[ub])
	{
		Swap(array, mid, ub);
	}
	if(array[lb] > array[ub])
	{
		Swap(array, lb, ub);
	}
	if(array[lb] > array[mid])
	{
		Swap(array, lb, mid);
	}
	// Now array[lb]<=array[mid]<=array[ub]
	return array[mid];
}

static void Swap(long *array, int idx1, int idx2)
{
	if(array == NULL)
	{
		fprintf(stderr, "empty array");
		return;
	}
	long tmp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = tmp;
}

//static int Patition(long *array, int lb, int ub)
//{
//	int mid = (lb + ub)/2;
//	int pivotIdx = 0;
//	if(array[lb] < array[mid])
//	{
//		if(array[mid] < array[ub])
//		{
//			pivotIdx = mid;
//		}
//		else if(array[lb] < array[ub])
//		{
//			pivotIdx = ub;
//		}
//		else
//		{
//			pivotIdx = lb;
//		}
//	}
//	else if(array[ub] < array[mid])
//	{
//		pivotIdx = mid;
//	}
//	else if(array[ub] < array[lb])
//	{
//		pivotIdx = ub;
//	}
//	else
//	{
//		pivotIdx = lb;
//	}
//	
//	int pivot = array[pivotIdx];
//	int down = lb;
//	int up = ub;
//	while(down < up)
//	{
//		while((array[down] <= pivot) && (down < up))
//		{
//			down++;
//		}
//		while((array[up] >= pivot) && (up > down))
//		{
//			up--;
//		}
//		if(down < up)
//		{
//			long tmp = array[down];
//			array[down] = array[up];
//			array[up] = tmp;
//		}
//	}
//	return up;
//}

void Merge_Sort(long *Array, int Size)
{

}
