typedef enum exprType {
  NONE = 0,
  NUMBER,
  ADD,
  SUB,
  MUL,
  DIV,
  END,
} ExprType;

typedef struct expr {
  ExprType type;
  union {
    int val;
    struct {
      struct expr* left;
      struct expr* right;
    } binop;
  } u;
} Expr;

typedef struct stack {
  Expr* expr;
  struct stack* below;
} Stack;

typedef struct list {
  Expr* expr;
  struct list* next;
} List;

extern Expr* get_next_expr_node();
extern List* get_all_expr_nodes();
extern void print_expr_node(Expr* expr);

extern Stack* add_node_to_expr_stack(Stack* stack, Expr* expr);
extern void print_fully_parenthesized_expr(Expr* expr);

extern void print_minimally_parenthesized_expr(Expr* expr);