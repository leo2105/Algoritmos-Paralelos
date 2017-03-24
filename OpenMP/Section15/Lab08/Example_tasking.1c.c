#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* A binary tree node has data, pointer to left child
 * and a pointer to right child */
struct node
{
	int data;
	struct node* left;
	struct node* right;
};

/* Helper function that allocates a new node with the
 * given data and NULL left and right pointers. */
struct node* newNode(int data)
{
	struct node* node = (struct node*)
	malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

/* Given a binary tree, print its nodes according to the
 * "bottom-up" postorder traversal. */
void printPostorder(struct node *p)
{
	//if (p == NULL)
	//return;
// first recur on left subtree
#pragma omp task 
if(p->left)
	printPostorder(p->left);

// then recur on right subtree
#pragma omp task  
if(p->right)	
	printPostorder(p->right);

// now deal with the node p
#pragma omp taskwait
	printf("%d \n",p->data);
}

/* Driver program to test above functions*/
int main()
{
#ifdef _OPENMP
	omp_set_num_threads(4);
#endif
	struct node *root = newNode(1);
	root->left		 = newNode(2);
	root->right		 = newNode(3);
	root->left->left	 = newNode(4);
	root->left->right 	 = newNode(5); 

#pragma omp parallel 
#pragma omp single
	{	
	printf("\n Postorder traversal of binary tree is \n");
	printPostorder(root);
	}

	return 0;
}

