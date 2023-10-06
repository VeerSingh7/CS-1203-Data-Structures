#include <stdio.h>
#include <stdlib.h>

// Node structure for Binary Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Node structure for Stack
struct StackNode {
    struct Node* treeNode;
    struct StackNode* next;
};

// Function to create a new Stack Node
struct StackNode* createStackNode(struct Node* treeNode) {
    struct StackNode* newStackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newStackNode->treeNode = treeNode;
    newStackNode->next = NULL;
    return newStackNode;
}

// Push function to add an element to the top of the stack
void push(struct StackNode** top_ref, struct Node* treeNode) {
    struct StackNode* newStackNode = createStackNode(treeNode);
    if (!newStackNode) {
        printf("Stack overflow!\n");
        exit(1);
    }
    newStackNode->next = *top_ref;
    *top_ref = newStackNode;
}

// Pop function to remove the top element from the stack
struct Node* pop(struct StackNode** top_ref) {
    if (*top_ref == NULL) {
        printf("Stack underflow!\n");
        exit(1);
    }
    struct StackNode* temp = *top_ref;
    *top_ref = temp->next;
    struct Node* poppedNode = temp->treeNode;
    free(temp);
    return poppedNode;
}

// Check if the stack is empty
int isEmpty(struct StackNode* top) {
    return (top == NULL);
}

// Function to create a new Binary Tree node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// In-order traversal of Binary Tree without recursion
void inorderTraversalWithoutRecursion(struct Node* root) {
    struct StackNode* stack = NULL;
    struct Node* current = root;

    // Continue until stack is empty or current node is NULL
    while (current != NULL || !isEmpty(stack)) {
        // Traverse the left subtree
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        // Process the current node
        current = pop(&stack);
        printf("%d ", current->data);

        // Traverse the right subtree
        current = current->right;
    }
    printf("\n");
}

int main() {
    // Create a sample binary tree for demonstration
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("In-order Traversal without Recursion:\n");
    inorderTraversalWithoutRecursion(root);

    return 0;
}