#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heap_t
{
	int* data;
	int data_cap;
	int data_use;
}heap_t;

heap_t* heap_create()
{
	heap_t* heap = malloc(sizeof(heap_t));
	heap->data_cap = 16;//容量
	heap->data_use = 0;//使用量
	heap->data = malloc(sizeof(int)* heap->data_cap);
	return heap;
}

int heap_cmp(heap_t* heap, int index1, int index2)
{
	return 0;
}

void heap_swap(heap_t* heap, int index1, int index2)
{
	int tmp = heap->data[index1];
	heap->data[index1] = heap->data[index2];
	heap->data[index2] = tmp;
}

void heap_add(heap_t* heap, int value)
{
	if (heap->data_use == heap->data_cap)
	{
		heap->data_cap += 16;//如果空间不够了，就增加一个步长
		heap->data = realloc(heap->data, sizeof(int)*heap->data_cap);
	}
	int index = heap->data_use++;//增加一个子节点就让index=use++,这里use是个数，index是下标
	int parent_index;//用来存储父节点的下标
	heap->data[index] = value;//将新加的节点velue赋值给data数组。

	while (1)//通过循环，来比较新加节点与它的父节点的大小
	{
		if (index == 0)//第一个节点的情况
			break;

		parent_index = (index - 1) / 2;//根据我们使用的数据结构，分析出每个节点之间下标的关系，然后得出，子节点的下标-1  除以2之后，得到父节点的下标
		if (heap->data[index] < heap->data[parent_index])//如果子节点的值小于父节点的，那么换个位置（这里我们创建的堆是最小堆）
		{
			heap_swap(heap, index, parent_index);//节点值交换。
			index = parent_index;
		}
		else
		{
			break;
		}
	}
}

void heap_del(heap_t* heap, int index)//删除某个节点
{
	if (index >= heap->data_use)
	{
		return;
	}

	//先与最后一个节点交换
	int last_index = heap->data_use - 1;//找到最后一个节点的下标
	heap_swap(heap, index, last_index);
	heap->data_use--;//这里就是删除最后一个点

	//针对index做两个方向的比较（与父节点，子节点比较）
	//首先与子节点比较
	int parent = index;
	while (1)
	{
		//两个儿子的坐标
		int ChildLeft = parent * 2 + 1;
		int ChildRight = parent * 2 + 2;

		int d = heap->data[parent];//取到之前的最后一个位置的数据
		if (ChildRight > heap->data_use)//右子节点的index大于使用的节点数，说明并没有这个子节点的存在
		{
			if (ChildLeft < heap->data_use)//左边有儿子
			{
				int l = heap->data[ChildLeft];
				if (l < d)//子节点比父节点小，交换
				{
					heap_swap(heap, parent, ChildLeft);
				}
			}
			break;//左右都没有儿子，或者上面语句走完之后，break循环
		}
		else //右边有儿子，那左边必有儿子
		{
			int r = heap->data[ChildRight];
			int l = heap->data[ChildLeft];
			if (l < r)//右儿子比左儿子大
			{
				if (l < d)//新元素也比左儿子大 
				{
					heap_swap(heap, parent, ChildLeft);
					parent = ChildLeft;
				}
				else
				{
					break;
				}
			}
			else//左儿子比右儿子大或相等
			{
				if (r < d)
				{
					heap_swap(heap, parent, ChildRight);
					parent = ChildRight;
				}
				else
				{
					break;
				}
			}
		}
	}

	//与父节点比较
	int child = index;
	while (1)
	{
		if (child == 0)//只剩一个节点的情况
		{
			break;
		}

		int parent = (child - 1) / 2;
		if (heap->data[parent] > heap->data[child])
		{
			heap_swap(heap, parent, child);
			child = parent;
		}
		else
		{
			break;
		}
	}
}

void heap_dump(heap_t* heap, int count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		printf("[%d]%d ", i, heap->data[i]);
	}
	printf("\n");
}

int main()
{
	heap_t* heap = heap_create();//创建一个空堆
	heap_add(heap, 100);
	heap_add(heap, 8);
	heap_add(heap, 5);
	heap_add(heap, 10099);
	heap_add(heap, 99);
	heap_add(heap, 80);
	heap_add(heap, 65);
	heap_add(heap, 1034);
	heap_add(heap, 433);
	heap_add(heap, 233);

	int i;
	for (i = 0; i < 10; ++i)
	{
		heap_del(heap, 0);
	}

	heap_dump(heap, 10);


	system("pause");
	return 0;
}