/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

typedef struct _node
{
    struct _node *left;
    struct _node *right;
    int data;
} Node,*PNode;

PNode root_init(int data)
{
    PNode root =calloc(1,sizeof(Node));
    root->left=root->right=NULL;
    root->data=data;
    return root;
}



PNode tree_add(PNode root,PNode new)
{
    if(root == NULL)
    {
        root = new;
    }

    else if(new->data < root->data)
    {
        printf("%d insert %d's left\n",new->data,root->data);
        root->left=tree_add(root->left,new);
    }
    else //(new->data >= root->data)
    {
        printf("%d insert %d's right\n",new->data,root->data);
        root->right=tree_add(root->right,new);
    }


    return root;
}


void tree_show_m(PNode root)
{
    if(root==NULL)return;

    if(root->left!=NULL)
    {
        tree_show_m(root->left);
    }
    printf("%d\n",root->data);
    if(root->right!=NULL)
    {
        tree_show_m(root->right);
    }

}


void tree_show_l(PNode root)
{
    if(root==NULL)return;

    printf("%d\n",root->data);
    if(root->left!=NULL)
    {

        tree_show_l(root->left);
    }

    if(root->right!=NULL)
    {
        tree_show_l(root->right);
    }

}
void tree_show_r(PNode root)
{
    if(root==NULL)return;

    if(root->right!=NULL)
    {
        tree_show_r(root->right);
    }

    printf("%d\n",root->data);
    if(root->left!=NULL)
    {

        tree_show_r(root->left);
    }


}
void tree_free(PNode root)
{

    if(root!=NULL)
    {
        tree_free(root->left);
        tree_free(root->right);
        printf("free->%d\n",root->data);

        free(root);

    }

}

void tree_seek(PNode root,int data)
{
    if(root == NULL)
        return;
    else if(data < root->data)
    {
        printf("%d's left\n",root->data);
        tree_seek(root->left,data);
    }
    else if(data > root->data)
    {
        printf("%d's right\n",root->data);
        tree_seek(root->right,data);
    }
    else
    {
        printf("find--%d\n",root->data);
    }

}



int main(int argc,char **argv)
{

    PNode root=NULL;
    int i,data;
    for(i=0; i<7; i++)
    {
        scanf("%d",&data);
        PNode new =root_init(data);
        root=tree_add(root,new);
    }

    puts("先序");
    tree_show_m(root);
    puts("中序");
    tree_show_l(root);
    puts("后序");
    tree_show_r(root);
	tree_seek(root,-1);
    tree_free(root);
    root=NULL;
    tree_show_r(root);

    return 0;
}

