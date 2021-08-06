/**内核链表由小结构体查找大结构体**/


/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <errno.h>
#include <stdarg.h>

struct _Head{

	struct _Head *prev;
	struct _Head *next;
};

typedef struct _node{

	int data;
	struct _Head K;

}Node , *PNode;


#define  GetBig(SmallAddr, BigName, SmallName) \
	(BigName)( (void*)SmallAddr - (void*)&((BigName)0)->SmallName )

int main(int argc,char **argv)
{

	Node nd1,nd2;

	nd1.data = 22;
	nd2.data = 33;

	nd1.K.next = &(nd2.K);//结构体运算符优先于位与运算符
	nd2.K.prev = &(nd1.K);


	//nd2.K.prev <--> &nd1.k --->?? get nd1
#ifdef _F1

	void * tmp1 = (void*)nd2.K.prev;
	void * tmp2 = (void*)&((PNode)0)->K;

	PNode Big = (PNode)(tmp1 - tmp2);

	printf(" %d \n",Big->data);

#elif defined(_F2)

	PNode Big = (PNode)(  (void*)nd2.K.prev -   (void*)&( ((PNode)0)->K) );

	printf(" %d \n",Big->data);

#elif defined(_F3)

	PNode Big = GetBig(nd2.K.prev, PNode, K);
	printf(" %d \n",Big->data);

#endif

//(void *)  &(PNode)12->K  -  (void*)12  12为任意数，取零方便
//大结构体12的小结构K的地址  减去12的首地址  为大小结构体偏移量

	return 0;
}//end of te main


