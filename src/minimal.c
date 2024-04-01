#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

int main() {
  List* exprs = get_all_expr_nodes();
  assert(exprs != NULL);
  Stack* stack = NULL;
  for (List* p = exprs; p != NULL; p = p->next) {
    stack = add_node_to_expr_stack(stack, p->expr);
    assert(stack != NULL);
  }
  print_fully_parenthesized_expr(stack->expr);
  printf("\n");
  print_minimally_parenthesized_expr(stack->expr);
  printf("\n");
  return 0;
}