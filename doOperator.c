#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_diff(struct tokenStack *stack);
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_if(struct tokenStack *stack);
static int op_modquot(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);
static int op_rot(struct tokenStack *stack);
static int op_rotminus(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);
static int op_s(struct tokenStack *stack);
  
static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"MOD", op_mod},
  {"IF", op_if},
  {"MODQUOT", op_modquot},
  {"SWAP", op_swap},
  {"HELP", op_help},
  {"ROT", op_rot},
  {"ROTMINUS", op_rotminus},
  {"DROP", op_drop},
  {"S", op_s},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  int i = 0;
  struct lexToken *t = popTokenStack(s);
  
  /* converts a character array into a integer i*/
  sscanf(t->symbol, "%d", &i);
  freeToken(t);
  printf("popping Integer: %d\n", i);
  return i;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
    struct lexToken *t;
    t = allocToken();
    t->kind = LEX_TOKEN_NUMBER;
  
    /* sprintf adds a integer to a char array */
    sprintf(t->symbol,"%d", v);  
    printf("pushing Integer: %d\n", v);
    pushTokenStack(s, t);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1-v2);
  
  return(0);
}

static int op_product(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1*v2);
  
  return(0);
}

static int op_quotient(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1/v2);
  return(0);
}

static int op_gt(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1>v2);
  return(0);
}

static int op_lt(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1<v2);
  return(0);
}

static int op_ge(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1>=v2);
  return(0);
}

static int op_le(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1<=v2);
  return(0);
}

static int op_eq(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1==v2);
  return(0);
}

static int op_mod(struct tokenStack *stack)
{
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);
  return(0);
}

static int op_if(struct tokenStack *stack)
{
  int v1, v2, v;

  v2 = popInt(stack);
  v1 = popInt(stack);
  v = popInt(stack);
  
  if(v != 0){
    pushInt(stack, v1);
  }else
    pushInt(stack, v2);
    
  return(0); 
}

static int op_modquot(struct tokenStack *stack)
{
  int v1, v2;
  v2 = popInt(stack);
  v1 = popInt(stack);
  pushInt(stack, v1%v2);
  pushInt(stack, v1/v2);
  
  return(0);
}

static int op_swap(struct tokenStack *stack){
  int v1, v2;
  
  v2 = popInt(stack);
  v1 = popInt(stack);
  
  pushInt(stack, v2);
  pushInt(stack, v1);
  
  return(0);
}

static int op_help(struct tokenStack *stack)
{
  int i = 0;
  
  printf("List of Commands:\n");
  
  while(ops[i].name != NULL){
     printf("%s\n",ops[i].name);
     i++;
  }
  
  return(0);
}

static int op_rot(struct tokenStack *stack)
{
  int v1, v2, v3;
  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  
  pushInt(stack, v2);
  pushInt(stack, v3);
  pushInt(stack, v1);
  return(0);
}

static int op_rotminus(struct tokenStack *stack)
{
  int v1, v2, v3;
  v3 = popInt(stack);
  v2 = popInt(stack);
  v1 = popInt(stack);
  
  pushInt(stack, v3);
  pushInt(stack, v1);
  pushInt(stack, v2);
  return(0);
}

static int op_drop(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  freeToken(t);
  return(0);
}

static int op_s(struct tokenStack *stack)
{
  char *ptr;
  int i, top;
  
  top = stack->top;
  
  for(i = 0; i < top; ++i){
    ptr = stack->e[i]->symbol;
    printf("%s\n", ptr);
  }
  
  return(0);
}
