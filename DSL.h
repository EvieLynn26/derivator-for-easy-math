#ifndef DSL_H_INCLUDED
#define DSL_H_INCLUDED

#define SUM_NODE(left, right) CreateNode (NaN, SUM, "+", left, right)
#define SUB_NODE(left, right) CreateNode (NaN, SUB, "-", left, right)
#define MUL_NODE(left, right) CreateNode (NaN, MUL, "*", left, right)
#define DIV_NODE(left, right) CreateNode (NaN, DIV, "/", left, right)
#define DEG_NODE(left, right) CreateNode (NaN, DEG, "^", left, right)
#define VAR_NODE CreateNode ((int) 'x', TYPE_VAR, "x")
#define MORE_VAR_NODE(var) CreateNode (var, TYPE_VAR, "var");
#define NUM_NODE(num) CreateNode (num)
#define ASSIGN_NODE(left, right) CreateNode (NaN, TYPE_ASSIGN, "=", left, right)
#define IF_NODE(left, right) nil//CreateNode (NaN, TYPE_IF, "if", left, right)
#define COMPARE_NODE(compare, left, right) CreateNode (NaN, compare, "comp", left, right);
#define OP_NODE(left, next_left) CreateNode(NaN, NaN, "op", left, CreateNode (NaN, NaN, "op", next_left, nil));
#define SQRT_NODE(right) CreateNode (NaN, SQRT, "sqrt", nil, right)
#define SIN_NODE(right) CreateNode (NaN, SIN, "sin", nil, right)
#define COS_NODE(right) CreateNode (NaN, COS, "cos", nil, right)
#define TG_NODE(right) CreateNode (NaN, TG, "tg", nil, right)
#define CTG_NODE(right) CreateNode (NaN, CTG, "ctg", nil, right)
#define ARCTG_NODE(right) CreateNode (NaN, ARCTG, "arctg", nil, right)
#define LN_NODE(right) CreateNode (NaN, LN, "ln", nil, right)
#define SH_NODE(right) CreateNode (NaN, SH, "sh", nil, right)
#define CH_NODE(right) CreateNode (NaN, CH, "ch", nil, right)
#define TH_NODE(right) CreateNode (NaN, TH, "th", nil, right)
#define CTH_NODE(right) CreateNode (NaN, CTH, "cth", nil, right)

#define cL CopyNode (node->left)
#define cR CopyNode (node->right)
#define dL DiffTree (node->left)
#define dR DiffTree (node->right)


#endif // DSL_H_INCLUDED
