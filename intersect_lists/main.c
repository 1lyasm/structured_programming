#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int v1;
  int v2;
  struct Node *next;
} Node;

void printList(Node *n) {
  Node *cur = n;
  printf("\nList: ");
  while (cur != NULL) {
    printf("(%d, %d) ", cur->v1, cur->v2);
    cur = cur->next;
  }
  printf("\n");
}
// Verilen Linkli listeyi yazdırır. 10p

static void insert(struct Node **head_ref, int v1, int v2) {
  Node *cur;
  if (*head_ref == NULL) {
    *head_ref = malloc(sizeof(Node));
    (*head_ref)->v1 = v1;
    (*head_ref)->v2 = v2;
    (*head_ref)->next = NULL;
  } else {
    cur = (*head_ref);
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = malloc(sizeof(Node));
    cur->next->v1 = v1;
    cur->next->v2 = v2;
    cur->next->next = NULL;
  }
}
// Verilen degerlere sahip Node'u linkli listenin sonuna ekler. 10p
//
//

int compare_by_v1(Node *Node1, Node *Node2) {
  if (Node1->v1 == Node2->v1) {
    return 1;
  } else {
    return 0;
  }
}
// iki düğümün v1 değerleri aynı ise 1 değilse 0 döndürür. 10p

int compare_by_v2(Node *Node1, Node *Node2) {
  if (Node1->v2 == Node2->v2) {
    return 1;
  } else {
    return 0;
  }
}
// iki düğümün v2 değerleri aynı ise 1 değilse 0 döndürür. 10p
//

Node *intersection(Node *start1, Node *start2,
                   int (*reduce_f)(Node *, Node *)) {
  Node *result = NULL;
  Node *current1 = start1;
  Node *current2 = start2;

  /* while (current1 != NULL && current2 != NULL) { */
  /*   if (reduce_f(current1, current2)) { */
  /*     insert(&result, current1->v1, current1->v2); */
  /*   } else if (reduce_f(current1, current2)) { */
  /*     insert(&result, current2->v1, current2->v2); */
  /*     current1 = current1->next; */
  /*     current2 = current2->next; */
  /*   } */
  /* } */


  while (current1 != NULL) {
      current2 = start2;
      while (current2 != NULL) {
          if (reduce_f(current1, current2)) {
              insert(&result, current1->v1, current1->v2);
          }
          current2 = current2->next;
      }
      current1 = current1->next;
  }

  return result;
}

static void freeList(Node *head) {
  Node *cur = head, *next;
  while (cur != NULL) {
    next = cur->next;
    /* printf("\ncur: %d\n", cur->v1); */
    free(cur);
    cur = next;
  }
}

int main() {
  int i, j, k = 0, ends = 0;
  int v1, v2;
  char input;
  Node *head1 = NULL, *head2 = NULL, *byv1, *byv2;
  Node **curHead = &head1;
  while (!ends) {
    printf("\n'q': quit, 's': skip to list 2, anything else to continue: ");
    scanf(" %c", &input);
    if (input == 'q') {
      ends = 1;
    } else if (input == 's') {
      curHead = &head2;
      k = 0;
    }
    if (!ends) {
      printf("\nEnter node %d of list 1 (v1, v2): ", k);
      scanf(" %d %d", &v1, &v2);
      insert(curHead, v1, v2);
      printList(*curHead);
      k++;
    }
  }
  int (*reduce_f_1)(Node *, Node *) = compare_by_v1;
  int (*reduce_f_2)(Node *, Node *) = compare_by_v2;
  byv1 = intersection(head1, head2, reduce_f_1);
  byv2 = intersection(head1, head2, reduce_f_2);
  printf("\nComparison by v1 result: ");
  printList(byv1);
  printf("\nComparison by v2 result: ");
  printList(byv2);
  freeList(head1);
  freeList(head2);
  freeList(byv1);
  freeList(byv2);
  return 0;
}
