# include <stdio.h>
# include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
# include "bcd.h"
# include "expr.h"

Expr* get_next_expr_node() {
	//read next int or op from stdin return pointer to a new expr node
	//ints get NUMBER in type field of expr
	// op get ether ADD SUB or MUL
	//not fill left or right of the u union
	char input[10];
	int intenter = 0;
	Expr *nextexp = malloc(sizeof(Expr));
	if (scanf("%s", input) == 1) {
		if (strcmp(input, "+") == 0) {
			nextexp->type = ADD;
		} else if (strcmp(input, "-") == 0) {
			nextexp->type = SUB;
		} else if (strcmp(input, "*") == 0) {
			nextexp->type = MUL;
		} else {
			nextexp->type = NUMBER;
			nextexp->u.val = string_to_bcd(input);
		}
	} else {
		return NULL;
	}
	return nextexp;
}
BCD* eval_expr(Expr* expr){
	//This function will take a pointer to an Expr node 
	//and return a pointer to a BCD node that represents 
	//the value of the expression. The Expr node will not be modified. 
	//The BCD node will be dynamically allocated.
	BCD *retval = malloc(sizeof(BCD));
	if(expr ==NULL){
		return NULL;
	}
	switch(expr->type){
	case NUMBER:
	retval = expr->u.val;
	break;
	case ADD:
		retval = add_bcd(eval_expr(expr->u.binop.left), 
				eval_expr(expr->u.binop.right));
		break;
	case MUL:
		retval = multiply_bcd(eval_expr(expr->u.binop.left), eval_expr(expr->u.binop.right));
		break;
	default:
		break;
	}
	return retval;
}

void print (char* format, ...){
	//This function will take a format string 
	//and a variable number of arguments. 
	//The format string will look like a printf format string, 
	//but will allow only these format specifiers:
	//%F fully paren, %M min paren %B BCD number
	va_list args;
	va_start(args, format);
	while(*format){
		if(*format =='%'){
			switch(*(++format)){
			case 'F':
				print_fully_parenthesized_expr(va_arg(args, Expr*));
				break;
			case 'M':
				print_minimally_parenthesized_expr(va_arg(args, Expr*));
				break;
			case 'B':
				printf("%s", bcd_to_string(va_arg(args, BCD*)));
				break;
			default:
				break;
			}
		}else{
			printf("%d",*format);
		}
		++format;
	}
	va_end(args);
}
List* get_all_expr_nodes() {
	// read expression from stdin return linked list of expr nodes
	// should call get next expr node until type end is found
	List *head = NULL;
	List **last = &head;
	Expr *enode;

	while ((enode = get_next_expr_node()) != NULL && enode->type != END) {
		*last = malloc(sizeof(List));
		(*last)->expr = enode;
		(*last)->next = NULL;
		last = &((*last)->next);
	}
	return head;
}
void print_expr_node(Expr *expr) {
	if (expr == NULL) {
		return;
	} else if (expr->type == NUMBER) {
		char *printstr=bcd_to_string(expr->u.val);
		printf("%s", printstr);
	} else if (expr->type == ADD) {
		printf("+");
	} else if (expr->type == SUB) {
		printf("-");
	} else if (expr->type == MUL) {
		printf("*");
	}
}
Stack* add_node_to_expr_stack(Stack *stack, Expr *expr) {
	Stack *newstack = malloc(sizeof(Stack));
	if (expr->type == NUMBER) {
		newstack->expr = expr;
		newstack->below = stack;
		stack = newstack;
		return stack;
	} else {
		expr->u.binop.right = stack->expr;
		stack = stack->below;
		expr->u.binop.left = stack->expr;
		stack = stack->below;
		newstack->expr = expr;
		newstack->below = stack;
		return newstack;
	}
}
void print_fully_parenthesized_expr(Expr *expr) {
	if (expr == NULL) {
		return;
	} else if (expr->type == NUMBER) {
		print_expr_node(expr);
	} else {
		printf("(");
		print_fully_parenthesized_expr(expr->u.binop.left);
		print_expr_node(expr);
		print_fully_parenthesized_expr(expr->u.binop.right);
		printf(")");
	}
}
int left_prio(Expr *expr) {
	if (expr->type == MUL
			&& (expr->u.binop.left->type == ADD
					|| expr->u.binop.left->type == SUB)) {
		return 1;
	} else {
		return 0;
	}
}
int right_prio(Expr *expr) {
	if ((expr->type == ADD || expr->type == SUB)
			&&(expr->u.binop.right->type == SUB||expr->u.binop.right->type==ADD))
		return 1;
	else if (expr->type == MUL&&expr->u.binop.right->type!=NUMBER) {
		return 1;
	} else {
		return 0;
	}
}
void print_minimally_parenthesized_expr(Expr *expr) {
	if (expr->type == NUMBER) {
		print_expr_node(expr);
		return;
	} else if (left_prio(expr) && expr->type != NUMBER) {
		printf("(");
		print_minimally_parenthesized_expr(expr->u.binop.left);
		printf(")");
	} else {
		print_minimally_parenthesized_expr(expr->u.binop.left);
	}
	print_expr_node(expr);
	if (right_prio(expr)) {
		printf("(");
		print_minimally_parenthesized_expr(expr->u.binop.right);
		printf(")");
	} else {
		print_minimally_parenthesized_expr(expr->u.binop.right);
	}
}
