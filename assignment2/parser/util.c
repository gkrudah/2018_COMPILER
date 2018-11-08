/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case INT:
    case VOID:
    case THEN:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(listing,"=\n"); break;
    case EQ: fprintf(listing,"==\n"); break;
    case NE: fprintf(listing,"!=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case LE: fprintf(listing,"<=\n"); break;
    case GT: fprintf(listing,">\n"); break;
    case GE: fprintf(listing,">=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case LBRACE: fprintf(listing,"[\n"); break;
    case RBRACE: fprintf(listing,"]\n"); break;
    case LCURLY: fprintf(listing,"{\n"); break;
    case RCURLY: fprintf(listing,"}\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case COMMA: fprintf(listing,",\n"); break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function newDclNode creates a new declaration 
 * node for syntax tree construction
 */
TreeNode * newDclNode(DclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DclK;
    t->kind.dcl = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newParamNode creates a new declaration 
 * node for syntax tree construction
 */
TreeNode * newParamNode(ParamKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ParamK;
    t->kind.param = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newTypeNode creates a new declaration 
 * node for syntax tree construction
 */

TreeNode * newTypeNode(TypeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = TypeK;
    t->kind.type = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

void printType(TreeNode * tree)
{ fprintf(listing,"type : ");
  if(tree->type == Void)
    fprintf(listing,"void\n");
  else if(tree->type == Integer)
    fprintf(listing,"int\n");
  else
    fprintf(listing,"Unknwon type\n");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i, j;
  INDENT;
  while (tree != NULL) {
    if(tree->nodekind != TypeK)
      printSpaces();

    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case CompK:
          fprintf(listing,"Compound Statement\n");
          break;
        case IterK:
          fprintf(listing,"Iteration\n");
          break;
        case RetK:
          fprintf(listing,"Return\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case AssignK:
          fprintf(listing,"Assign :  (destination) (soure)\n");
          break;
        case OpK:
          fprintf(listing,"Op : ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const : %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id : %s\n",tree->attr.name);
          break;
        case ArrIdK:
          fprintf(listing,"ArrId : %s\n",tree->attr.arr.name);
          break;
        case CallK:
          fprintf(listing,"Call, name : %s, with argumetns below\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==DclK)
    { switch (tree->kind.dcl)
      { case VarK:
          fprintf(listing,"Var declaration, name : %s, ",tree->attr.name);
          printType(tree);
          break;
        case FuncK:
          fprintf(listing,"Function declaration, name : %s, return ",tree->attr.name);
          printType(tree);
          break;
        case ArrVarK:
          fprintf(listing,"ArrVar declaration, name : %s, size : %d",tree->attr.arr.name,tree->attr.arr.size);
          printType(tree);
          break;
        default:
          fprintf(listing,"Unknown DclNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ParamK)
    { switch (tree->kind.param)
      { case ParK:
          fprintf(listing,"Single parameter, name : %s, ",tree->attr.name);
          printType(tree);
          break;
        case ArrParK:
          fprintf(listing,"Array parameter, name : %s, ",tree->attr.arr.name);
          printType(tree);
          break;
        default:
          fprintf(listing,"Unknown ParamNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==TypeK)
    { break;
      /*switch (tree->kind.type)
      { case TypenameK:
          if (tree->type==Integer)
          { for(j=0;j<indentno;j++)
              fprintf(listing,"\b");
            fprintf(listing,"type : int\n");
          }
          else if (tree->type==Void)
          {
            if(!tree->attr.name)
              fprintf(listing,"Single parameter, name : %s, ", tree->attr.name);
            else
            { for(j=0;j<indentno;j++)
                fprintf(listing,"\b");
            }
            fprintf(listing,"type : void\n");
          }
          else
            fprintf(listing,"Unknown TypeNode kind\n");
          break;
        default:
          fprintf(listing,"Unknown TypeNode kind\n");
          break;
      }*/
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
      printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}