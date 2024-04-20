#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bcd.h"
#include "expr.h"

int main() {
  List* exprs = get_all_expr_nodes();
  assert(exprs != NULL);
  Stack* stack = NULL;
  for (List* p = exprs; p != NULL; p = p->next) {
    stack = add_node_to_expr_stack(stack, p->expr);
    assert(stack != NULL);
  }
  print("Fully: %F", stack->expr);
  printf("\n");
  print("Minimal: %M", stack->expr);
  printf("\n");
  return 0;
}