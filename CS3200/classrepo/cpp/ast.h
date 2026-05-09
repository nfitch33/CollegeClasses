#ifndef AST_H
#define AST_H

typedef struct ASTNode {
    enum { NODE_INT, NODE_BOOL, NODE_ID, NODE_BINOP, NODE_IF, NODE_LET } nodetype;
    union {
        int ival;
        int bval;
        char *sval;
        struct {
            struct ASTNode *left;
            int op; // e.g., PLUS, TIMES, LE
            struct ASTNode *right;
        } binop;
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } ifnode;
        struct {
            char *id;
            struct ASTNode *expr1;
            struct ASTNode *expr2;
        } letnode;
    } data;
} ASTNode;

/* Function prototypes */
ASTNode* make_int_node(int value);
ASTNode* make_bool_node(int value);
ASTNode* make_id_node(char* id);
ASTNode* make_binop_node(int op, ASTNode* left, ASTNode* right);
ASTNode* make_if_node(ASTNode* cond, ASTNode* then_branch, ASTNode* else_branch);
ASTNode* make_let_node(char* id, ASTNode* expr1, ASTNode* expr2);
void free_ast(ASTNode* node);
void print_ast(ASTNode* node);

#endif /* AST_H */
