#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

typedef struct node* type_node;

type_node newNode(int data)
{
	type_node new_node = malloc(sizeof(struct node));
	
	new_node->data = data;
	
	new_node->left = NULL;
	new_node->right= NULL;
	
	return new_node;
}

void insert(type_node tree , int data)
{
	if(tree == NULL)
		tree = newNode(data);		
	else
	{
		if(data <= tree->data)
		{
			if(tree->left != NULL)
				insert(tree->left,data);
			else
				tree->left = newNode(data);
		}	
		else
		{
			if(tree->right != NULL)
				insert(tree->right,data);
			else
				tree->right = newNode(data);
		}			
	}
}

void init(type_node tree,int num_nodes)
{
	srand(time(NULL));
	int i;
	for(i=0;i<num_nodes;i++)
		insert(tree,rand()%50+1);
}


void inOrder(type_node tree)
{
	if(tree!=NULL)
	{
		#pragma omp task
		inOrder(tree->left);
		
		#pragma omp taskwait
		printf("%d ",tree->data);
		
		#pragma omp task
		inOrder(tree->right);		
	}
	
}

void postOrder(type_node tree)
{
	if(tree!=NULL)
	{
		#pragma omp task
		postOrder(tree->left);
		
		#pragma omp task	
		postOrder(tree->right);
		
		#pragma omp taskwait
		printf("%d ",tree->data);
	}
}

void start_background_work(type_node tree,int* sum)
{
	if(tree != NULL){
		
		#pragma omp task
		start_background_work(tree->left,sum);
		
		#pragma omp taskwait
		*sum += tree->data;
		
		#pragma omp task
		start_background_work(tree->right,sum);
	}

}

void compute_tree(type_node tree)
{
	if(tree != NULL){
		#pragma omp task
		compute_tree(tree->left);
		
		#pragma omp task
		compute_tree(tree->right);
		
		#pragma omp taskwait
		tree->data = tree->data*tree->data;
	}
}


int main()
{
	int suma=0;
	type_node tree = newNode(rand()%50+1);
	init(tree,9);
	
	#pragma omp parallel shared(suma)
		#pragma omp single
		{	
			#pragma omp taskgroup
			{
				#pragma omp task
				{
					printf("Inorder walk : ");
					inOrder(tree);
				}
			
				#pragma omp taskwait
				{
					start_background_work(tree,&suma);
					printf("\nSuma: %d \n",suma);
				}
			
				#pragma omp task
					compute_tree(tree);
								
				#pragma omp taskwait
				{
					printf("Valores elevados al cuadrado: ");
					postOrder(tree);
					printf("\n");
				}
			}
		}

	return 0;	
}
