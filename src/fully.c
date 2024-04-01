#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

void print_list(List* exprs) {
  for (List* p = exprs; p != NULL; p = p->next) {
    if (p != exprs) {
      printf(" ");
    }
    assert(p->expr != NULL);
    print_expr_node(p->expr);
  }
}

int main() {
  List* exprs = get_all_expr_nodes();
  assert(exprs != NULL);

  print_list(exprs);
  printf("\n");

  Stack* stack = NULL;
  for (List* p = exprs; p != NULL; p = p->next) {
    stack = add_node_to_expr_stack(stack, p->expr);
    assert(stack != NULL);
  }

  print_fully_parenthesized_expr(stack->expr);
  printf("\n");
  return 0;
}