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
	heap->data_cap = 16;//����
	heap->data_use = 0;//ʹ����
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
		heap->data_cap += 16;//����ռ䲻���ˣ�������һ������
		heap->data = realloc(heap->data, sizeof(int)*heap->data_cap);
	}
	int index = heap->data_use++;//����һ���ӽڵ����index=use++,����use�Ǹ�����index���±�
	int parent_index;//�����洢���ڵ���±�
	heap->data[index] = value;//���¼ӵĽڵ�velue��ֵ��data���顣

	while (1)//ͨ��ѭ�������Ƚ��¼ӽڵ������ĸ��ڵ�Ĵ�С
	{
		if (index == 0)//��һ���ڵ�����
			break;

		parent_index = (index - 1) / 2;//��������ʹ�õ����ݽṹ��������ÿ���ڵ�֮���±�Ĺ�ϵ��Ȼ��ó����ӽڵ���±�-1  ����2֮�󣬵õ����ڵ���±�
		if (heap->data[index] < heap->data[parent_index])//����ӽڵ��ֵС�ڸ��ڵ�ģ���ô����λ�ã��������Ǵ����Ķ�����С�ѣ�
		{
			heap_swap(heap, index, parent_index);//�ڵ�ֵ������
			index = parent_index;
		}
		else
		{
			break;
		}
	}
}

void heap_del(heap_t* heap, int index)//ɾ��ĳ���ڵ�
{
	if (index >= heap->data_use)
	{
		return;
	}

	//�������һ���ڵ㽻��
	int last_index = heap->data_use - 1;//�ҵ����һ���ڵ���±�
	heap_swap(heap, index, last_index);
	heap->data_use--;//�������ɾ�����һ����

	//���index����������ıȽϣ��븸�ڵ㣬�ӽڵ�Ƚϣ�
	//�������ӽڵ�Ƚ�
	int parent = index;
	while (1)
	{
		//�������ӵ�����
		int ChildLeft = parent * 2 + 1;
		int ChildRight = parent * 2 + 2;

		int d = heap->data[parent];//ȡ��֮ǰ�����һ��λ�õ�����
		if (ChildRight > heap->data_use)//���ӽڵ��index����ʹ�õĽڵ�����˵����û������ӽڵ�Ĵ���
		{
			if (ChildLeft < heap->data_use)//����ж���
			{
				int l = heap->data[ChildLeft];
				if (l < d)//�ӽڵ�ȸ��ڵ�С������
				{
					heap_swap(heap, parent, ChildLeft);
				}
			}
			break;//���Ҷ�û�ж��ӣ����������������֮��breakѭ��
		}
		else //�ұ��ж��ӣ�����߱��ж���
		{
			int r = heap->data[ChildRight];
			int l = heap->data[ChildLeft];
			if (l < r)//�Ҷ��ӱ�����Ӵ�
			{
				if (l < d)//��Ԫ��Ҳ������Ӵ� 
				{
					heap_swap(heap, parent, ChildLeft);
					parent = ChildLeft;
				}
				else
				{
					break;
				}
			}
			else//����ӱ��Ҷ��Ӵ�����
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

	//�븸�ڵ�Ƚ�
	int child = index;
	while (1)
	{
		if (child == 0)//ֻʣһ���ڵ�����
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
	heap_t* heap = heap_create();//����һ���ն�
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