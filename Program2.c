#include <stdio.h>
#include <stdlib.h>

struct RB_tree{
  int key;
  struct RB_tree *left;
  struct RB_tree *right;
  struct RB_tree *parent;
  char color;
};
typedef struct RB_tree node;

void RB_Insert(node** root, int val);
void RB_Fixup(node** root, node* z);
void Left_Rotate(node** root, node* x);
void Right_Rotate(node** root, node* x);
int height(node* Node);
void printGivenLevel(node* root, int level);
void print_tree(node* tree);

void Left_Rotate(node** root, node* x){
  //printf("\n----- Left Rotate -----\n");
  node* y;
  y = x->right;
  x->right = y->left;
  if(y->left != NULL){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == NULL){
    *root = y;
  }
  else if(x == x->parent->left){
    x->parent->left = y;
  }
  else{
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void Right_Rotate(node** root, node* x){
  //printf("\n----- Right Rotate -----\n");
  node* y;
  y = x->left;
  x->left = y->right;
  if(y->right != NULL){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == NULL){
    *root = y;
  }
  else if(x->key == x->parent->right->key){
    x->parent->right = y;
  }
  else{
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;

}

void RB_Fixup(node** root, node* pt){
  node *parent_pt = NULL;
  node *grand_parent_pt = NULL;

  while ((pt != (*root)) && (pt->color != 'b') && (pt->parent->color == 'r')){
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;
    if(parent_pt == grand_parent_pt->left){
      node *uncle_pt = grand_parent_pt->right;
      if(uncle_pt != NULL && uncle_pt->color == 'r'){
        grand_parent_pt->color = 'r';
        parent_pt->color = 'b';
        uncle_pt->color = 'b';
        pt = grand_parent_pt;
      }
      else{
        if(pt == parent_pt->right){
          pt = parent_pt;
          Left_Rotate(root, pt);
        }
        pt->parent->color = 'b';
        pt->parent->parent->color = 'r';
        Right_Rotate(root, pt->parent->parent);
      }
    }
    else{
      node *uncle_pt = grand_parent_pt->left;
      if(uncle_pt != NULL && uncle_pt->color == 'r'){
        grand_parent_pt->color = 'r';
        parent_pt->color = 'b';
        uncle_pt->color = 'b';
        pt = grand_parent_pt;
      }
      else{
        if(pt == parent_pt->left){
          pt = parent_pt;
          Right_Rotate(root, pt);
        }
        pt->parent->color = 'b';
        pt->parent->parent->color = 'r';
        Left_Rotate(root, pt->parent->parent);
      }
    }
  }
  (*root)->color = 'b';
}

void RB_Insert(node** root, int val){
  if((*root) == NULL){
    printf("First insert...\n");
  }
  node* z = (node*)malloc(sizeof(node));
  z->key = val;
  z->left = NULL;
  z->right = NULL;
  z->parent = NULL;
  z->color = 'r';
  node* y = NULL;
  node* x = *root;
  while(x != NULL){
    y = x;
    if(z->key < y->key){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  z->parent = y;
  if(y == NULL){
    *root = z;
  }
  else if(z->key < y->key){
    y->left = z;
  }
  else{
    y->right = z;
  }
  RB_Fixup(root, z);
}

int height(node* Node){
  if(Node == NULL){
    return 0;
  }
  else{
    int lheight = height(Node->left);
    int rheight = height(Node->right);

    if(lheight > rheight){
      return (lheight+1);
    }
    else{
      return (rheight+1);
    }
  }
}

void printGivenLevel(node* root, int level){
  if(root == NULL){
    return;
  }
  if(level == 1){
    printf("(key: %d color: %c) -> \n",root->key, root->color);
  }
  else if(level > 1){
    printGivenLevel(root->left, level-1);
    printGivenLevel(root->right, level-1);
  }
}

void print_tree(node* root){
  int h = height(root);
  int i = 1;
  for(i=1;i<=h;i++){
    printGivenLevel(root, i);
  }
}

int main(void){
  node* root;
  root = NULL;
  int val = 1;
  while(val>0){
    printf("\nPlease enter a value greater than 0 to be inserted into the tree\n");
    printf("Enter '-1' to exit\n");
    scanf("%d",&val);
    if(val>0){
      printf("value to be inserted: %d\n",val);
      RB_Insert(&root,val);
      //print_tree(root);
    }
  }
  print_tree(root);
  return 0;
}
