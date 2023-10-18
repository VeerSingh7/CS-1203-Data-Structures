#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int key;
  struct Node *left;
  struct Node *right;
  int height;
};

int
getHeight (struct Node *n)
{
  if (n == NULL)
    return 0;
  return n->height;
}

struct Node *
createNode (int key)
{
  struct Node *node = (struct Node *) malloc (sizeof (struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

void
displayTree (struct Node *root, int space)
{
  int i;

  if (root == NULL)
    return;

  space += 10;

  // Process right child first
  displayTree (root->right, space);

  // Print current node after space count
  printf ("\n");
  for (i = 10; i < space; i++)
    printf (" ");
  printf ("%d\n", root->key);

  // Process left child
  displayTree (root->left, space);
}

int
max (int a, int b)
{
  return (a > b) ? a : b;
}

int
getBalanceFactor (struct Node *n)
{
  if (n == NULL)
    {
      return 0;
    }
  return getHeight (n->left) - getHeight (n->right);
}

struct Node *
rightRotate (struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  x->height = max (getHeight (x->right), getHeight (x->left)) + 1;
  y->height = max (getHeight (y->right), getHeight (y->left)) + 1;

  return x;
}

struct Node *
leftRotate (struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max (getHeight (x->right), getHeight (x->left)) + 1;
  y->height = max (getHeight (y->right), getHeight (y->left)) + 1;

  return y;
}

struct Node *
insert (struct Node *node, int key)
{
  if (node == NULL)
    return createNode (key);

  if (key < node->key)
    node->left = insert (node->left, key);
  else if (key > node->key)
    node->right = insert (node->right, key);

  node->height = 1 + max (getHeight (node->left), getHeight (node->right));
  int bf = getBalanceFactor (node);

  // Left Left Case  
  if (bf > 1 && key < node->left->key)
    {
      return rightRotate (node);
    }
  // Right Right Case  
  if (bf < -1 && key > node->right->key)
    {
      return leftRotate (node);
    }
  // Left Right Case  
  if (bf > 1 && key > node->left->key)
    {
      node->left = leftRotate (node->left);
      return rightRotate (node);
    }
  // Right Left Case  
  if (bf < -1 && key < node->right->key)
    {
      node->right = rightRotate (node->right);
      return leftRotate (node);
    }
  return node;
}

void
preOrder (struct Node *root)
{
  if (root != NULL)
    {
      printf ("%d ", root->key);
      preOrder (root->left);
      preOrder (root->right);
    }
}

void
inOrder (struct Node *root)
{
  if (root != NULL)
    {
      preOrder (root->left);
      printf ("%d ", root->key);
      preOrder (root->right);
    }
}

struct Node *
minValueNode (struct Node *node)
{
  struct Node *current = node;
  while (current->left != NULL)
    current = current->left;

  return current;
}

struct Node *
deleteNode (struct Node *root, int key)
{
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode (root->left, key);

  else if (key > root->key)
    root->right = deleteNode (root->right, key);

  else
    {
      if ((root->left == NULL) || (root->right == NULL))
	{
	  struct Node *temp = root->left ? root->left : root->right;

	  if (temp == NULL)
	    {
	      temp = root;
	      root = NULL;
	    }
	  else
	    *root = *temp;

	  free (temp);
	}
      else
	{
	  struct Node *temp = minValueNode (root->right);
	  root->key = temp->key;
	  root->right = deleteNode (root->right, temp->key);
	}
    }

  if (root == NULL)
    return root;

  root->height = 1 + max (getHeight (root->left), getHeight (root->right));
  int balance = getBalanceFactor (root);

  if (balance > 1 && getBalanceFactor (root->left) >= 0)
    return rightRotate (root);

  if (balance > 1 && getBalanceFactor (root->left) < 0)
    {
      root->left = leftRotate (root->left);
      return rightRotate (root);
    }

  if (balance < -1 && getBalanceFactor (root->right) <= 0)
    return leftRotate (root);

  if (balance < -1 && getBalanceFactor (root->right) > 0)
    {
      root->right = rightRotate (root->right);
      return leftRotate (root);
    }

  return root;
}

int
main ()
{
  struct Node *root = NULL;
  int choice, key;

  while (1)
    {
      printf ("\nAVL Tree Menu:\n");
      printf ("1. Insert a node\n");
      printf ("2. Delete a node\n");
      printf ("3. Display the AVL tree\n");
      printf ("4. Exit\n");
      printf ("Enter your choice: ");
      scanf ("%d", &choice);

      switch (choice)
	{
	case 1:
	  printf ("Enter the key to insert: ");
	  scanf ("%d", &key);
	  root = insert (root, key);
	  break;
	case 2:
	  printf ("Enter the key to delete: ");
	  scanf ("%d", &key);
	  root = deleteNode (root, key);
	  break;
	case 3:
	  printf ("AVL Tree:\n");
	  displayTree (root, 0);
	  break;
	case 4:
	  // Cleanup and exit
	  // Release memory for the AVL tree nodes if necessary
	  exit (0);
	default:
	  printf ("Invalid choice. Please try again.\n");
	}
    }

  return 0;
}
