#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Helper functions to create AST nodes */
ASTNode* make_int_node(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_INT;
    node->data.ival = value;
    return node;
}

ASTNode* make_bool_node(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_BOOL;
    node->data.bval = value;
    return node;
}

ASTNode* make_id_node(char* id) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_ID;
    node->data.sval = strdup(id);
    return node;
}

ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

ASTNode* make_if_node(ASTNode* cond, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_IF;
    node->data.ifnode.cond = cond;
    node->data.ifnode.then_branch = then_branch;
    node->data.ifnode.else_branch = else_branch;
    return node;
}

ASTNode* make_let_node(char* id, ASTNode* expr1, ASTNode* expr2) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodetype = NODE_LET;
    node->data.letnode.id = strdup(id);
    node->data.letnode.expr1 = expr1;
    node->data.letnode.expr2 = expr2;
    return node;
}

/* Function to free the AST */
void free_ast(ASTNode* node) {
    if (!node) return;
    switch (node->nodetype) {
        case NODE_INT:
        case NODE_BOOL:
            break;
        case NODE_ID:
            free(node->data.sval);
            break;
        case NODE_BINOP:
            free_ast(node->data.binop.left);
            free_ast(node->data.binop.right);
            break;
        case NODE_IF:
            free_ast(node->data.ifnode.cond);
            free_ast(node->data.ifnode.then_branch);
            free_ast(node->data.ifnode.else_branch);
            break;
        case NODE_LET:
            free(node->data.letnode.id);
            free_ast(node->data.letnode.expr1);
            free_ast(node->data.letnode.expr2);
            break;
    }
    free(node);
}

/* Function to print the AST (optional) */
void print_ast(ASTNode* node) {
    // if (!node) return;
    // switch (node->nodetype) {
    //     case NODE_INT:
    //         printf("%d", node->data.ival);
    //         break;
    //     case NODE_BOOL:
    //         printf("%s", node->data.bval ? "true" : "false");
    //         break;
    //     case NODE_ID:
    //         printf("%s", node->data.sval);
    //         break;
    //     case NODE_BINOP:
    //         printf("(");
    //         print_ast(node->data.binop.left);
    //         printf(" %s ", node->data.binop.op == PLUS ? "+" :
    //                        node->data.binop.op == TIMES ? "*" : "<=");
    //         print_ast(node->data.binop.right);
    //         printf(")");
    //         break;
    //     case NODE_IF:
    //         printf("if ");
    //         print_ast(node->data.ifnode.cond);
    //         printf(" then ");
    //         print_ast(node->data.ifnode.then_branch);
    //         printf(" else ");
    //         print_ast(node->data.ifnode.else_branch);
    //         break;
    //     case NODE_LET:
    //         printf("let %s = ", node->data.letnode.id);
    //         print_ast(node->data.letnode.expr1);
    //         printf(" in ");
    //         print_ast(node->data.letnode.expr2);
    //         break;
    // }
}
