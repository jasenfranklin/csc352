# include <stdio.h>
# include <string.h>
#include <malloc.h>
# include "expr.h"
Expr* get_next_expr_node(){
    //read next int or op from stdin return pointer to a new expr node
    //ints get NUMBER in type field of expr
    // op get ether ADD SUB or MUL
    //not fill left or right of the u union
    Expr *nextexp=malloc(sizeof(expr));
    char input;
    int intenter=0;
    for(;scanf("/c",&input); input!=NULL ){
        if(input>='0'&&input<='9'){
         intenter=atoi(&input);
         nextexp->type=NUMBER;
         nextexp->u.val = intenter;
        }
        else if(input=='+'){
            nextexp->type = ADD;
        }else if(input=='-'){
            nextexp->type = SUB;
        }else if(input == '*'){
            nextexp ->type = MUL;
        }
    }
    return nextexp;
}

List* get_all_expr_nodes(){
    // read expression from stdin return linked list of expr nodes
    // should call get next expr node until type end is found
    List *head = malloc(sizeof(List));
    Expr *ind;
    List *phony=  NULL;
    phony->next = head;
    for(;scanf("/c", ind=get_next_expr_node());head->next!=NULL){
        phony->next=ind;
        head = head->next;
    }
}
void print_expr_node(Expr* expr){

}
Stack * add_node_to_expr_stack(Stack* stack, Expr* expr){

}
void print_fully_parenthesized_expr(Expr* expr){

}
void print_minimally_parenthesized_expr(Expr* expr){

}