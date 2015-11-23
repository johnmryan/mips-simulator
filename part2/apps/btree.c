/*
 * btree.c
 *
 *  Created on: Oct 20, 2015
 *      Author: jbb
 */

#include "mipslib.h"
#define NULL 0

struct treeNode {
  char data;
  struct treeNode *left, *right;
};

struct treeNode *root = NULL;
char keyboard[] = "qwertyuiopasdfghjklzxcvbnm";

struct treeNode* createNode(char data) {
  struct treeNode *newNode;
  newNode = (struct treeNode *) malloc(sizeof (struct treeNode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return(newNode);
}

void insert(struct treeNode **node, char data) {
  if (*node == NULL) {
    *node = createNode(data);
  }
  else if (data < (*node)->data) {
    insert(&(*node)->left, data);
  }
  else if (data > (*node)->data) {
    insert(&(*node)->right, data);
  }
}

void traverse(struct treeNode *node) {
  if (node != NULL) {
    traverse(node->left);
    printf("%c", node->data);
    traverse(node->right);
  }
  return;
}

int main()
{
  int i;
  for (i = 0;  i < 26;  i++)
    insert(&root, keyboard[i]);
  traverse(root);
  printf("\n");
  return 0;
}
