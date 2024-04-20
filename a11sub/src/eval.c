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
  BCD* bcd = eval_expr(stack->expr);
  print("%F == %M == %B", stack->expr, stack->expr, bcd);
  printf("\n");
  return 0;
}