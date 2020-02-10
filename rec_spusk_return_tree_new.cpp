#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "D:\Code\Binary_tree\binary_tree.h"
#include "D:\Code\Computation_binary_tree\DSL.h"


const char* s = nil;


Node* GetG (const char* str);
Node* GetE ();
Node* GetT ();
Node* GetD ();
Node* GetP ();
Node* GetF ();
Node* GetN ();

char* Read_buff ();

void Add_Node (Node* node, FILE* f)
{

    if (node->num == NaN)

        fprintf (f, "node%p [label=\"%s\", shape=box];\n", node, node->data);

    else

        fprintf (f, "node%p [label=\"%d\", shape=box];\n", node, node->num);
}

void Print_Nodes (Node* node, FILE* f)
{
    if (node->left != nil)
    {
        Add_Node (node->left, f);

    }

    if (node->right != nil)
        Add_Node (node->right, f);

    if (node->left != nil)
        fprintf (f, "node%p->node%p\n", node, node->left);

    if (node->right != nil)
        fprintf (f, "node%p->node%p\n", node, node->right);

    if (node->left != nil)
        Print_Nodes (node->left,  f);

    if (node->right != nil)
        Print_Nodes (node->right, f);
}

void TreePrint (Node* root, FILE* f)
{
    fprintf (f, "digraph {\n");

    Add_Node (root, f_out);

    PrintNods (root, f_out);

    fprintf(f_out, "}\n");

    fclose(f_out);

}

//-------------------------------------------------
void TreeToMathView (FILE* f, Node* node, int prev_node_type)
{
    if (node != nil)
    {
        if (((node->node_type == SUM || node->node_type == SUB) && (prev_node_type == MUL || prev_node_type == DIV)) || (prev_node_type >= SIN) || (prev_node_type == DEG) || (node->node_type == TYPE_NUM && node->num < 0))
        {
            fprintf (f, "(");
        }

        if (node->node_type == DIV)
        {
            fprintf (f, "\\frac {");
        }

        TreeToMathView (f, node->left, node->node_type);//left tree printed!

        if (node->node_type == DIV)
        {
            fprintf (f, "}");
        }

        else
        {
            switch (node->node_type)
            {
                case TYPE_NUM:
                        fprintf (f, "%d", node->num);
                        break;

                case MUL:
                        fprintf (f, " \\cdot ");
                        break;

                default:
                        fprintf (f, "%s", node->data);
            }
        }

        if (node->node_type == DIV || node->node_type == DEG)
        {
            fprintf (f, "{");
        }

        TreeToMathView (f, node->right, node->node_type);//right tree printed!

        if (node->node_type == DIV || node->node_type == DEG)
        {
            fprintf (f, "}");
        }

        if (((node->node_type == SUM || node->node_type == SUB) && (prev_node_type == MUL || prev_node_type == DIV)) || (prev_node_type >= SIN) || (prev_node_type == DEG) || (node->node_type == TYPE_NUM && node->num < 0))
        {
            fprintf (f, ")");
        }
    }
}

void TreeToLaTex (FILE* f, Node* root, Node* diff_root)
{
    fprintf (f, "\\documentclass[a4paper,12pt]{article}\n"
                "\\usepackage[T2A]{fontenc}\n"
                "\\usepackage[utf8]{inputenc}\n"
                "\\usepackage[english,russian]{babel}\n"
                "\n"
                "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools} \n"
                "\n"
                "\\title{Небольшой пример взятия производной}\n"
                "\\date{\\today}\n"
                "\n"
                "\\author{E.E.}\n"
                "\\begin{document}\n"
                "\n"
                "\\maketitle\n"
                "\\subsection{Решим простой пример}\n"
                "\n"
                "{\\Large Найти производную функции \\\\ $f(x)=");

    TreeToMathView (f, root, 0);

    fprintf (f, "$:\n"
                "\\begin{center}\n"
                "\\begin{math}\n"
                "f'(x)=");

    TreeToMathView (f, diff_root, 0);

    fprintf (f, "\n"
                "\\end{math}\n"
                "\\end{center}\n"
                "}\n"
                "\\end{document}");

   fclose (f);
}
//-------------------------------------------------
Node* CopyNode (Node* node);
Node* DiffTree (Node* node);

void DeleteNode (Node* node)
{
    free (node);

    return;
}

void EasyTree (Node** root_ptr)
{
    if ((*root_ptr) != nil)
    {
        //if left and right are numbers
        if ((*root_ptr)->left != nil && ((*root_ptr)->right != nil))
            if ((*root_ptr)->left->node_type == TYPE_NUM && (*root_ptr)->right->node_type == TYPE_NUM)
            {
                switch ((*root_ptr)->node_type)
                {
                    case SUM:
                            (*root_ptr)->num = (*root_ptr)->left->num + (*root_ptr)->right->num;
                            break;

                    case SUB:
                            (*root_ptr)->num = (*root_ptr)->left->num - (*root_ptr)->right->num;
                            break;

                    case MUL:
                            (*root_ptr)->num = (*root_ptr)->left->num * (*root_ptr)->right->num;
                            break;

                    case DIV:
                            assert ((*root_ptr)->right->num != 0);
                            (*root_ptr)->num = (*root_ptr)->left->num / (*root_ptr)->right->num;
                            break;

                    case DEG:
                            (*root_ptr)->num = (int) pow ((*root_ptr)->left->num, (*root_ptr)->right->num);
                            break;
                }

                (*root_ptr)->node_type = TYPE_NUM;
                (*root_ptr)->data = "";

                DeleteNode ((*root_ptr)->left);
                DeleteNode ((*root_ptr)->right);

                (*root_ptr)->right = nil;
                (*root_ptr)->left = nil;
            }

        switch ((*root_ptr)->node_type)
        {
            case SUM:
                    if ((*root_ptr)->left->node_type == TYPE_NUM && (*root_ptr)->left->num == 0)
                    {
                        Node* root_to_del = (*root_ptr);

                        (*root_ptr) = (*root_ptr)->right;

                        DeleteNode (root_to_del->left);
                        DeleteNode (root_to_del);
                    }

                    else if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 0)
                    {
                        printf ("yes");
                        Node* root_to_del = (*root_ptr);

                        (*root_ptr) = (*root_ptr)->left;

                        printf ("\nnow root_type is %d\n", (*root_ptr)->node_type);

                        DeleteNode (root_to_del->right);
                        DeleteNode (root_to_del);
                    }

                    break;

            case SUB:
                    if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 0)
                    {
                        Node* root_to_del = *root_ptr;

                        *root_ptr = (*root_ptr)->left;

                        DeleteNode (root_to_del->right);
                        DeleteNode (root_to_del);
                    }

                    break;

            case MUL:
                    if (((*root_ptr)->left->node_type == TYPE_NUM && (*root_ptr)->left->num == 0) || ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 0))
                    {
                        (*root_ptr)->num= 0;
                        (*root_ptr)->node_type = TYPE_NUM;
                        (*root_ptr)->data = "";
                        (*root_ptr)->right = nil;
                        (*root_ptr)->left = nil;

                        DeleteTree ((*root_ptr)->left);
                        DeleteTree ((*root_ptr)->right);
                    }

                    else if ((*root_ptr)->left->node_type == TYPE_NUM && (*root_ptr)->left->num == 1)
                    {
                        Node* root_to_del = *root_ptr;

                        *root_ptr = (*root_ptr)->right;

                        DeleteNode (root_to_del->left);
                        DeleteNode (root_to_del);
                    }

                    else if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 1)
                    {
                        Node* root_to_del = *root_ptr;

                        *root_ptr = (*root_ptr)->left;

                        DeleteNode (root_to_del->right);
                        DeleteNode (root_to_del);
                    }

                    break;

            case DIV:
                    if ((*root_ptr)->left->node_type == TYPE_NUM && (*root_ptr)->left->num == 0)
                    {
                        (*root_ptr)->num= 0;
                        (*root_ptr)->node_type = TYPE_NUM;
                        (*root_ptr)->data = "";
                        (*root_ptr)->right = nil;
                        (*root_ptr)->left = nil;

                        DeleteTree ((*root_ptr)->left);
                        DeleteTree ((*root_ptr)->right);
                    }

                    else if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 1)
                    {
                        Node* root_to_del = *root_ptr;

                        *root_ptr = (*root_ptr)->left;

                        DeleteNode (root_to_del->right);
                        DeleteNode (root_to_del);
                    }

                    break;

            case DEG:
                    if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 0)//zero degree
                    {
                        (*root_ptr)->num= 1;
                        (*root_ptr)->node_type = TYPE_NUM;
                        (*root_ptr)->data = "";
                        (*root_ptr)->right = nil;
                        (*root_ptr)->left = nil;

                        DeleteTree ((*root_ptr)->left);
                        DeleteTree ((*root_ptr)->right);
                    }

                    else if ((*root_ptr)->left->node_type == TYPE_NUM && ((*root_ptr)->left->num == 1 || (*root_ptr)->left->num == 0))
                    {
                        switch ((*root_ptr)->left->num)
                        {
                            case 0: (*root_ptr)->num = 0;
                                    break;

                            case 1: (*root_ptr)->num = 1;
                                    break;
                        }

                        (*root_ptr)->node_type = TYPE_NUM;
                        (*root_ptr)->data = "";
                        (*root_ptr)->right = nil;
                        (*root_ptr)->left = nil;

                        DeleteTree ((*root_ptr)->left);
                        DeleteTree ((*root_ptr)->right);
                    }

                    else if ((*root_ptr)->right->node_type == TYPE_NUM && (*root_ptr)->right->num == 1)
                    {
                        Node* root_to_del = *root_ptr;

                        *root_ptr = (*root_ptr)->left;

                        DeleteNode (root_to_del->right);
                        DeleteNode (root_to_del);
                    }

                    break;
        }

        if ((*root_ptr)->left != nil)
            EasyTree (&(*root_ptr)->left);

        if ((*root_ptr)->right != nil)
            EasyTree (&(*root_ptr)->right);
    }

    return;
}


int main ()
{
    char* str = Read_buff ();

    //printf ("%s", str);

    Node* root = GetG (str);

    FILE* f_out = fopen ("ou.txt", "w");

    //TreePrint (root, f_out);

    Node* diff_root = DiffTree (root);

    EasyTree (&diff_root);

    printf ("type of root: %d", diff_root->node_type);

    FILE* f_tex = fopen ("tex.txt", "w");

    TreeToLaTex (f_tex, root, diff_root);

    TreePrint (diff_root, f_out);

}


//--------------------------------------------------
Node* CopyNode (Node* node)
{
    if (node != nil)
    {
        switch (node->node_type)
        {
            case TYPE_NUM:
                return  NUM_NODE(node->num);

            case TYPE_VAR:
                return  VAR_NODE;

            case MUL:
                return MUL_NODE(CopyNode (node->left), CopyNode (node->right));

            case DIV:
                return DIV_NODE (CopyNode (node->left), CopyNode (node->right));

            case SUM:
                return SUM_NODE (CopyNode (node->left), CopyNode (node->right));

            case SUB:
                return SUB_NODE (CopyNode (node->left), CopyNode (node->right));

            case SIN:
                return SIN_NODE (CopyNode (node->right));

            case COS:
                return COS_NODE (CopyNode (node->right));

            case TG:
                return TG_NODE (CopyNode (node->right));

            case CTG:
                return CTG_NODE (CopyNode (node->right));

            case LN:
                return LN_NODE (CopyNode (node->right));

            case ARCTG:
                return ARCTG_NODE (CopyNode (node->right));

            case DEG:
                return DEG_NODE (CopyNode (node->left), CopyNode (node->right));

            case SH:
                return SH_NODE (CopyNode (node->right));

            case CH:
                return CH_NODE (CopyNode (node->right));

            case TH:
                return TH_NODE (CopyNode (node->right));

            case CTH:
                return CTH_NODE (CopyNode (node->right));
        }
    }

    return nil;
}

Node* DiffTree (Node* node)
{
    switch (node->node_type)
    {
        case TYPE_NUM:
                return NUM_NODE(0);

        case TYPE_VAR:
                return NUM_NODE(1);

        case SUM:
                return SUM_NODE(dL, dR);

        case SUB:
                return SUB_NODE(dL, dR);

        case MUL:
                return SUM_NODE(MUL_NODE(dL, cR), MUL_NODE(cL, dR));

        case DIV:
                return DIV_NODE(SUB_NODE(MUL_NODE(dL, cR), MUL_NODE(cL, dR)), DEG_NODE(cR, NUM_NODE(2)));

        case SIN:
                return MUL_NODE(COS_NODE(cR), dR);

        case COS:
                return MUL_NODE(NUM_NODE(-1), MUL_NODE(SIN_NODE(cR), dR));

        case TG:
                return DIV_NODE(dR, DEG_NODE(COS_NODE(cR), NUM_NODE(2)));

        case CTG:
                return DIV_NODE (MUL_NODE(dR, NUM_NODE(-1)), DEG_NODE(SIN_NODE(cR), NUM_NODE(2)));

        case LN:
                return DIV_NODE(dR, cR);

        case ARCTG:
                return DIV_NODE(dR, SUM_NODE(NUM_NODE(1), DEG_NODE(cR, NUM_NODE(2))));

        case DEG:
                return MUL_NODE(MUL_NODE(cR, DEG_NODE(cL, SUB_NODE(cR, NUM_NODE(1)))), dL);

        case SH:
                return MUL_NODE(CH_NODE(cR), dR);

        case CH:
                return MUL_NODE(SH_NODE(cR), dR);

        case TH:
                return DIV_NODE(dR, DEG_NODE(CH_NODE(cR), NUM_NODE(2)));

        case CTH:
                return DIV_NODE(MUL_NODE(dR, NUM_NODE(-1)), DEG_NODE(SH_NODE(cR), NUM_NODE(2)));
    }

    return nil;
}
//--------------------------------------------------

Node* GetG (const char* str)
{
    s = str;

    Node* val = GetE ();

    assert (*s == '\0');

    return val;
}

Node* GetE ()
{
    Node* val = GetT ();

    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;

        Node* val2 = GetT ();

        if (op == '+')
            val = SUM_NODE(val, val2);

        else
            val = SUB_NODE(val, val2);
    }

    return val;
}

Node* GetT ()
{
    Node* val = GetD ();

    while (*s == '*' || *s == '/')
    {
        char op = * s;
        s++;

        Node* val2 = GetD ();

        if (op == '*')
            val = MUL_NODE(val, val2);

        else
        {
            assert (val2->num != 0);
            val = DIV_NODE(val, val2);
        }
    }

    return val;
}

Node* GetD ()
{
    Node* val = GetP ();

    while (*s == '^')
    {
        s++;

        Node* val2 = GetP ();

        val = DEG_NODE(val, val2);
    }

    return val;
}

Node* GetP ()
{
    Node* val = nil;

    if (*s == '(')
    {
        s++;

        val = GetE ();

        assert (*s == ')');
        s++;

        return val;
    }

    if (*s == 'x')
    {
        s++;

        return VAR_NODE;
    }

    if ('0' <= *s && *s <= '9')
        return GetN ();

    return GetF ();
}

Node* GetF ()
{
    Node* val = nil;

    if (strncmp (s, "sin", 3) == 0)
    {
        s += 3;

        val = GetP ();

        return SIN_NODE(val);
    }

    if (strncmp (s, "cos", 3) == 0)
    {
        s += 3;

        val = GetP ();

        return COS_NODE(val);
    }

    if (strncmp (s, "tg", 2) == 0)
    {
        s += 2;

        val = GetP ();

        return TG_NODE(val);
    }

    if (strncmp (s, "ctg", 3) == 0)
    {
        s += 3;

        val = GetP ();

        return CTG_NODE(val);
    }

    if (strncmp (s, "ln", 2) == 0)
    {
        s += 2;

        val = GetP ();

        return LN_NODE(val);
    }

    if (strncmp (s, "arctg", 5) == 0)
    {
        s += 5;

        val = GetP ();

        return ARCTG_NODE(val);
    }

    if (strncmp (s, "sh", 2) == 0)
    {
        s += 2;

        val = GetP ();

        return SH_NODE(val);
    }

    if (strncmp (s, "ch", 2) == 0)
    {
        s += 2;

        val = GetP ();

        return CH_NODE(val);
    }

    if (strncmp (s, "th", 2) == 0)
    {
        s += 2;

        val = GetP ();

        return TH_NODE(val);
    }

    if (strncmp (s, "cth", 3) == 0)
    {
        s += 3;

        val = GetP ();

        return CTH_NODE(val);
    }

    return val;
}

Node* GetN ()
{
    int val = 0;

    do
    {
        val = val * 10 + (*s - '0');
        s++;
    }
    while ('0' <= *s && *s <= '9');

    return NUM_NODE(val);
}

char* Read_buff ()
{
    char file_name[100] = "";
    int size_of_file = 0;

   /*
    #ifndef DEBUG
        scanf ("%s", file_name);
    #endif

    ON_DEBUG(strcpy (file_name, "input.txt"));
    */

    FILE* fin = fopen ("input.txt", "r");

    fseek (fin, 0, SEEK_END) == 0;
    size_of_file = ftell (fin);
    rewind (fin);

    char* buff = (char*) calloc (size_of_file, sizeof (char));

    fread (buff, sizeof (char), size_of_file, fin);

    fclose (fin);

    return buff;
}
