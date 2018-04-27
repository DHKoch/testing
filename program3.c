#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
}Node;

Node* BFS_Queue_Head = NULL;
Node* BFS_Queue_Tail = NULL;
Node* List_Queue_Head = NULL;
Node* List_Queue_Tail = NULL;

void BFS(int Floors, int start, int end, int up, int down);
void EnQueue(int num, Node** Head, Node** Tail);
Node* DeQueue(Node** Head);
int search(int end, Node* Head);
void printResult(Node* Head);
void deleteQueue(Node** Head);

void BFS(int Floors, int start, int end, int up, int down){
  Node* ptr = NULL;
  EnQueue(start, &BFS_Queue_Head, &BFS_Queue_Tail);
  while(BFS_Queue_Head){
    ptr = DeQueue(&BFS_Queue_Head);
    EnQueue(ptr->num, &List_Queue_Head, &List_Queue_Tail);
    if(ptr->num == end){
      deleteQueue(&BFS_Queue_Head);
      free(ptr);
      printResult(List_Queue_Head);
      return;
    }
    if(ptr->num < end && (ptr->num + up) <= end){
      if(search(ptr->num + up, List_Queue_Head) == 0){
        EnQueue(ptr->num + up, &BFS_Queue_Head, &BFS_Queue_Tail);
      }
    }
    else if((ptr->num - down) > 0){
      if(search(ptr->num - down, List_Queue_Head) == 0){
        EnQueue(ptr->num - down, &BFS_Queue_Head, &BFS_Queue_Tail);
      }
    }
    free(ptr);
  }
  printf("Take the stairs\n");
  return;
}

void EnQueue(int num, Node** Head, Node** Tail){
  Node* new;
  new = malloc(sizeof(Node));
  new->num = num;
  new->next = NULL;
  if(*Head == NULL){
    *Head = new;
    *Tail = new;
  }
  else{
    (*Tail)->next = new;
    *Tail = new;
  }
}

Node* DeQueue(Node** Head){
  if(*Head == NULL){
    return NULL;
  }
  Node* temp;
  temp = *Head;
  *Head = (*Head)->next;
  return temp;
}

int search(int end, Node* Head){
  if(Head == NULL){
    return 0;
  }
  Node* temp = Head;
  while(temp){
    if(temp->num == end){
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void printResult(Node* Head){
  Node* temp = Head;
  while(temp->next){
    printf("%d -> ",temp->num);
    temp = temp->next;
  }
  printf("%d \n",temp->num);
}

void deleteQueue(Node** Head){
  if(*Head == NULL){
    return;
  }
  Node* ptr = *Head;
  Node* next;
  while(ptr){
    next = ptr->next;
    free(ptr);
    ptr = next;
  }
}

int main(void){
  int start = 0;
  int Floors = 0;
  int end = 0;
  int up = 0;
  int down = 0;
  
  Node* ptr = malloc(sizeof(Node));
  printf("Please enter the # of floors, start, finish, up #, down #:\n");
  scanf("%d %d %d %d %d",&Floors, &start, &end, &up, &down);

  BFS(Floors,start,end,up,down);
  deleteQueue(&BFS_Queue_Head);
  deleteQueue(&List_Queue_Head);

  return 0;

}
