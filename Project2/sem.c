/*
Name: Wei Fei
KUID: 2538810
Date: 12/01/15
Project: EECS665 Project2
File: sem.c
*/

# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

extern int formalnum;
extern char formaltypes[];
extern int localnum;
extern char localtypes[];
extern int localwidths[];

int numlabels = 0;                      /* total labels in file */
int numblabels = 0; 			/* toal backpatch labels in file */

int sizeOfBreak, sizeOfContinue, sizeOfGoto;
int arrOfBreak[], arrOfGoto[], arrOfContinue[];
struct labelSeries {
    	struct labelSeries* nextLabel;
	int labelNumber;
    	char* labelName;   
};
struct labelSeries* curLabel;
struct labelSeries* topLabel;
                   


/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
   	if (p == NULL)
	{
		fprintf(stderr, "error, NULL pointer!");
	}
	else
	{	
		printf("B%i=L%i\n", p->s_place, k);
	}
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{
  extern int lineno;
  printf("bgnstmt %d\n", lineno);
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
  	int countArgs = 0;
	struct id_entry* tempID = lookup(f, 0);
	
	if(tempID == NULL)
	{
		tempID = install(f, 0);
		tempID->i_scope = GLOBAL;
		tempID->i_type = T_PROC;
	}
	
	while(args) 
	{
		gen("arg", NULL, args, args->s_mode);
		countArgs++;
		args = args->back.s_link;
	}

	return gen("f", id(f), node(countArgs, 0, NULL, NULL), tempID->i_type);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	backpatch(e1->back.s_true, m);
	struct sem_rec *result = node(0, 0, e2->back.s_true, merge(e1->s_false,e2->s_false));
	return result;
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
   struct sem_rec *t1;

   if(e){

     t1 = gen("!=", e, cast(con("0"), e->s_mode), e->s_mode);

     printf("bt t%d B%d\n", t1->s_place, ++numblabels);
     printf("br B%d\n", ++numblabels);
     return (node(0, 0,
		  node(numblabels-1, 0, (struct sem_rec *) NULL,
		       (struct sem_rec *) NULL),
		  node(numblabels, 0, (struct sem_rec *) NULL,
		       (struct sem_rec *) NULL)));
   }
   else
     fprintf(stderr, "Argument sem_rec is NULL\n");
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
    	struct sem_rec *result = node(0, 0, e->s_false, e->back.s_true);
   	return result;
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
	backpatch(e1->s_false, m);
	struct sem_rec* result = node(0, 0, merge(e1->back.s_true, e2->back.s_true), e2->s_false);
	return result;
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
  struct id_entry *p;

  if((p = lookup(x, 0)) == NULL) {
    p = install(x, 0);
    p->i_type = T_INT;
    p->i_scope = GLOBAL;
    p->i_defined = 1;
  }

  /* print the quad t%d = const */
  printf("t%d := %s\n", nexttemp(), x);

  /* construct a new node corresponding to this constant generation
     into a temporary. This will allow this temporary to be referenced
     in an expression later*/
  return(node(currtemp(), p->i_type, (struct sem_rec *) NULL,
	      (struct sem_rec *) NULL));
}

/*
 * dobreak - break statement
 */
void dobreak()
{
	numblabels++;
	arrOfBreak[sizeOfBreak] = numblabels;
    	sizeOfBreak++;
    	printf("br B%d\n", numblabels);
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
	numblabels++;
	arrOfContinue[sizeOfContinue] = numblabels;
	sizeOfContinue++;
	printf("br B%d\n", numblabels);
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
	backpatch(e->back.s_true, m1);
   	backpatch(e->s_false, m3);
   	endloopscope(m3);
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
           int m3, struct sem_rec *n2, int m4)
{
	backpatch(e2->back.s_true, m3);
	backpatch(e2->s_false, m4);
	backpatch(n1, m1);
	backpatch(n2, m2);
	endloopscope(m4);
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{
    	printf("br L%d\n", arrOfGoto[sizeOfGoto]);
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
    	struct sem_rec * nextPtr = e->back.s_true;
	
	for(; nextPtr; nextPtr = nextPtr->back.s_link)    	
	{
      		backpatch(nextPtr, m1);	
    	}
    	
	nextPtr =e->s_false;

    	for(; nextPtr; nextPtr = nextPtr->back.s_link)
	{
      		backpatch(nextPtr, m2);
    	}
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
                         int m2, int m3)
{
    	struct sem_rec * nextPtr = e->back.s_true;

    	for(; nextPtr; nextPtr = nextPtr->back.s_link)
	{
      		backpatch(nextPtr, m1);
      	}

    	nextPtr = e->s_false;
    
	for(; nextPtr; nextPtr = nextPtr->back.s_link)
	{
      		backpatch(nextPtr, m2);
    	}

   	backpatch(n,m3);
}

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{
	if(T_INT == e->s_mode)
	{
		printf("reti t%i\n", currtemp());
   	}
	else if(T_DOUBLE == e->s_mode)
	{
		printf("retf t%i\n", currtemp());
	}
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
             int m3)
{
	struct sem_rec* nextPtr = e->back.s_true;

	for(; nextPtr; nextPtr = nextPtr->back.s_link)
	{
		backpatch(nextPtr,m2);	
  	}

  	nextPtr = e->s_false;

  	for(; nextPtr; nextPtr = nextPtr->back.s_link)
	{
    		backpatch(nextPtr, m3);
  	}

    	backpatch(n, m1);
    	endloopscope(m3);
 
    	if(sizeOfContinue > 0)
	{
        	struct sem_rec* tempPtr_Continue = node(arrOfContinue[--sizeOfContinue], 0,  NULL, NULL);
        	backpatch(tempPtr_Continue, m1);
    	}

	if(sizeOfBreak > 0)
	{
        	struct sem_rec* tempPtr_Break = node(arrOfBreak[--sizeOfBreak], 0, NULL, NULL);
        	backpatch(tempPtr_Break, m3);
    	}
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
	leaveblock();
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
   	struct sem_rec *tempL = l;

	while(tempL->back.s_link)
	{
		tempL = tempL->back.s_link;
   	}

   	tempL->back.s_link = e;

   	return l;
}

/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
	int i;
	for(i = 0; i < formalnum; i++)
	{
		if(formaltypes[i] == 'i')
		{
			printf("formal %d\n", 4);
		}
		else if(formaltypes[i] == 'f')
		{
			printf("formal %d\n", 8);
		}
	}

	for(i = 0; i < localnum; i++)
	{
		if(localtypes[i] == 'i')
		{
			printf("localloc %d\n", 4);
		}
		else if(localtypes[i] == 'f')
		{
			printf("localloc %d\n", 8);
		}
	}
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
	printf("func %s\n", id);
	enterblock();
	return NULL;
}

/*
 * ftail - end of function body
 */
void ftail()
{
	printf("fend\n");
    	leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
   struct id_entry *p;

   if ((p = lookup(x, 0)) == NULL) {
      yyerror("undeclared identifier");
      p = install(x, -1);
      p->i_type = T_INT;
      p->i_scope = LOCAL;
      p->i_defined = 1;
   }
   if (p->i_scope == GLOBAL)
      printf("t%d := global %s\n", nexttemp(), x);
   else if (p->i_scope == LOCAL)
      printf("t%d := local %d\n", nexttemp(), p->i_offset);
   else if (p->i_scope == PARAM) {
      printf("t%d := param %d\n", nexttemp(), p->i_offset);
      if (p->i_type & T_ARRAY) {
         (void) nexttemp();
         printf("t%d := @i t%d\n", currtemp(), currtemp()-1);
      }
   }

   /* add the T_ADDR to know that it is still an address */
   return (node(currtemp(), p->i_type|T_ADDR, (struct sem_rec *) NULL,
                (struct sem_rec *) NULL));
}

/*
 * index - subscript
 */
struct sem_rec *tom_index(struct sem_rec *x, struct sem_rec *i)
{
  return (gen("[]", x, cast(i, T_INT), x->s_mode&~(T_ARRAY)));
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{
	install(id, 0);
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
	numlabels++;
	printf("label L%i\n", numlabels);
   	return numlabels;
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
   	numblabels++;
  	printf("br B%i\n", numblabels);
  	return node(numblabels, 0, NULL, NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
  	if (*op == '@' && !(y->s_mode&T_ARRAY))
	{
    		/* get rid of T_ADDR if it is being dereferenced so can handle
       		T_DOUBLE types correctly */
    		y->s_mode &= ~T_ADDR;
    		return (gen(op, (struct sem_rec *) NULL, y, y->s_mode));
  	}
  	else if ((*op == '~') && (y->s_mode == T_DOUBLE))
	{
    		return NULL;
  	}
  	else 
  	{
    		return (gen(op, NULL, y, y->s_mode));
  	}
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
	int type = T_INT;
   	if((T_DOUBLE == x->s_mode) || (T_DOUBLE == y->s_mode))
	{
		type = T_DOUBLE;
   	}
   	return gen(op, cast(x, type), cast(y, type), type);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
	return gen(op, cast(x, T_INT), cast(y, T_INT), T_INT);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
   	int type = T_INT;

   	if((x->s_mode == T_DOUBLE) || (y->s_mode == T_DOUBLE))
	{
		type = T_DOUBLE;
   	}
	struct sem_rec *result = gen(op, cast(x, type), cast(y, type), type);
  	printf("bt t%d B%d\n", result->s_place, ++numblabels);

	result->back.s_true = (struct sem_rec*)malloc(sizeof(struct sem_rec));
  	result->back.s_true->s_place = numblabels;
   	printf("br B%d\n", ++numblabels);

   	result->s_false = (struct sem_rec*)malloc(sizeof(struct sem_rec));
   	result->s_false->s_place = numblabels;

  	return result;
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
  /* assign the value of expression y to the lval x */
  struct sem_rec *p, *cast_y;

	if(*op!='\0' || x==NULL || y==NULL)
	{
		struct sem_rec *tempResult;
    		int type1, type2;
		type1 = x->s_mode;
   	 	type2 = y->s_mode;

    		if ((type1 & T_INT) && (!(type2 & T_INT))) 
		{
     			type1 = T_INT;
      			type2 = T_DOUBLE;
    		}
		else if ((!(type1 & T_INT)) && (!(type2 & T_INT))) 
		{
			type1 = T_DOUBLE;
      			type2 = type1;
    		}
    		else if ((!(type1 & T_INT)) && (type2 & T_INT)) 
		{
			type1 = T_DOUBLE;
      			type2 = T_INT;	
    		}
		else
		{
			type1 = x->s_mode;
   	 		type2 = y->s_mode;
		}

    		if(y->s_mode != T_ARRAY) 
		{
			return gen("=", x, gen(op, gen("@", NULL, x, type1), cast(y, type1), type1), type1);	
    		}
    		else 
		{
			return gen("=", x, gen(op, gen("@", NULL, x, type1), gen("@", NULL, cast(y, type1), type2), type1), type1);
    		}
  	}

  /* if for type consistency of x and y */
  cast_y = y;
  if((x->s_mode & T_DOUBLE) && !(y->s_mode & T_DOUBLE)){
    
    /*cast y to a double*/
    printf("t%d := cvf t%d\n", nexttemp(), y->s_place);
    cast_y = node(currtemp(), T_DOUBLE, (struct sem_rec *) NULL,
		  (struct sem_rec *) NULL);
  }
  else if((x->s_mode & T_INT) && !(y->s_mode & T_INT)){

    /*convert y to integer*/
    printf("t%d := cvi t%d\n", nexttemp(), y->s_place);
    cast_y = node(currtemp(), T_INT, (struct sem_rec *) NULL,
		  (struct sem_rec *) NULL);
  }

  /*output quad for assignment*/
  if(x->s_mode & T_DOUBLE)
    printf("t%d := t%d =f t%d\n", nexttemp(), 
	   x->s_place, cast_y->s_place);
  else
    printf("t%d := t%d =i t%d\n", nexttemp(), 
	   x->s_place, cast_y->s_place);

  /*create a new node to allow just created temporary to be referenced later */
  return(node(currtemp(), (x->s_mode&~(T_ARRAY)),
	      (struct sem_rec *)NULL, (struct sem_rec *)NULL));
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
	enterblock();
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
	printf("t%i := %s\n", nexttemp(), s);
	struct sem_rec* tempNpde = node(currtemp(), T_STR, NULL, NULL);
	tempNpde->s_mode = T_STR;
	return tempNpde;
}



/************* Helper Functions **************/

/*
 * cast - force conversion of datum y to type t
 */
struct sem_rec *cast(struct sem_rec *y, int t)
{
   if (t == T_DOUBLE && y->s_mode != T_DOUBLE)
      return (gen("cv", (struct sem_rec *) NULL, y, t));
   else if (t != T_DOUBLE && y->s_mode == T_DOUBLE)
      return (gen("cv", (struct sem_rec *) NULL, y, t));
   else
      return (y);
}

/*
 * gen - generate and return quadruple "z := x op y"
 */
struct sem_rec *gen(char *op, struct sem_rec *x, struct sem_rec *y, int t)
{
   if (strncmp(op, "arg", 3) != 0 && strncmp(op, "ret", 3) != 0)
      printf("t%d := ", nexttemp());
   if (x != NULL && *op != 'f')
      printf("t%d ", x->s_place);
   printf("%s", op);
   if (t & T_DOUBLE && (!(t & T_ADDR) || (*op == '[' && *(op+1) == ']'))) {
      printf("f");
      if (*op == '%')
         yyerror("cannot %% floating-point values");
   }
   else
      printf("i");
   if (x != NULL && *op == 'f')
      printf(" t%d %d", x->s_place, y->s_place);
   else if (y != NULL)
      printf(" t%d", y->s_place);
   printf("\n");
   return (node(currtemp(), t, (struct sem_rec *) NULL,
           (struct sem_rec *) NULL));
}





