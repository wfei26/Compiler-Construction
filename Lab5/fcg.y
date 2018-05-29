%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
int yydebug = 1;
char* lastFunction = "";
extern void yyerror( char* );
extern int yylex();
%}

/*********************************************************
 ********************************************************/
%union {
    char* id;
}

%token <id> ID
%token INTVAL
%token DBLVAL
%token FLTVAL 		
%token STRVAL 	
%token CHARVAL 
%token VOID 	
%token SHORT	
%token CHAR
%token INT		
%token LONG	
%token FLOAT	
%token DOUBLE
%token RETURN 	
%token DO		
%token WHILE	
%token FOR		
%token SWITCH	
%token CASE		
%token DEFAULT		
%token IF		
%token ELSE 	
%token CONTINUE	
%token BREAK	
%token GOTO	 
%token UNSIGNED	
%token STRUCT	
%token CONST
%token EXTERN		
%token REGISTER	
%token TYPEDEF
%token UNION	
%token STATIC		
%token AUTO
%token SIZEOF
%token EQ
%token LE
%token ADD
%token DIV
%token AND 
%token BITXOR	
%token LSH
%token SETADD
%token SETDIV
%token SETAND
%token SETRSH
%token NE
%token GT
%token SUB
%token MOD
%token BITOR 
%token NOT 
%token RSH
%token BITAND
%token COM
%token SET
%token SETMUL
%token SETOR
%token SETLSH	
%token SETSUB			
%token SETMOD
%token SETXOR
%token GE			
%token LT				
%token MUL				
%token OR
%token PREPROC	 	
%start top

%%

/*********************************************************
 * The top level parsing rule, as set using the %start
 * directive above.
 ********************************************************/
top : 
|function top


/*This rule matches a  function in C Program*/
function : func_signature '{' func_body '}'

/*This rule matches a function signature such as int main( int argc, char *argv[] )*/
func_signature : type ID '(' args ')' { printf("%s", $2); printf(";\n"); lastFunction = $2;}

/*********************************************************
 * An example rule used to parse arguments to a
 * function call. The arguments to a function call
 * can either be nothing, one parameter, or multiple
 * parameters separated by commas.
 ********************************************************/
args : /* empty rule */
     | expr
     | expr ',' args

/*********************************************************
 * An example rule used to parse a single expression.
 * Currently this rule parses only an integer value
 * but you should modify the rule to parse the required
 * expressions.
 ********************************************************/
expr : INTVAL | type ID | CONST type ID | type ID '[' ']'
func_body : declaration func_body | declaration | statement func_body | statement 
declaration : type ID ';'

primaryExpression : INTVAL | DBLVAL | FLTVAL | STRVAL | CHARVAL | ID | func_call 
	          | type ID | CONST type ID | type ID '[' ']'
 





statement : openStatement | closeStatement

openStatement : IF '(' expression ')' statement
	      | IF '(' expression ')' closeStatement ELSE openStatement
	      | WHILE '(' expression ')' openStatement

closeStatement : simpleStatement
	      | IF '(' expression ')' closeStatement ELSE closeStatement
	      | WHILE  '(' expression ')' closeStatement

simpleStatement : assignment | returnStatement | blockStatement | func_call | func_call ';'

assignment : ID SET expression ';' | ID SET expression 
      | type ID SET expression ';' | type ID SET expression 

blockStatement : '{' blockExpression '}'  
blockExpression : statement | statement blockExpression

returnStatement : RETURN expression | RETURN expression ';' 





expression : addOperation | addOperation equalOperation

precedenceLevel1 :  MUL | DIV | MOD | LSH | RSH
precedenceLevel2 :  BITOR | BITAND | BITXOR | ADD | SUB | AND | OR
precedenceLevel3 :  GT | LT | EQ | NE | GE | LE

equalOperation : precedenceLevel3 addOperation | precedenceLevel3 addOperation equalOperation

addOperation :  multiOperation | multiOperation tempOperation
tempOperation : precedenceLevel2 multiOperation | precedenceLevel2 multiOperation tempOperation

multiOperation : primaryExpression | primaryExpression tempExpression
tempExpression : precedenceLevel1 primaryExpression | precedenceLevel1 primaryExpression tempExpression





func_call : ID '(' functionCallExpression')'  {printf ("%s -> %s;\n", lastFunction, $1);}
	  | ID '(' ')' {printf ("%s -> %s;\n", lastFunction, $1);}

functionCallExpression : expression | expression ',' functionCallExpression

type : VOID | SHORT | CHAR | INT | LONG | FLOAT | DOUBLE | VOID MUL | CHAR MUL
	    | SHORT MUL | INT MUL | LONG MUL | FLOAT MUL | DOUBLE MUL
%%



/*********************************************************
 * This method is invoked by the parser whenever an
 * error is encountered during parsing; just print
 * the error to stderr.
 ********************************************************/
void yyerror( char *err ) {
    fprintf( stderr, "at line %d: %s\n", yylineno, err );
}

/*********************************************************
 * This is the main function for the function call
 * graph program. We invoke the parser and return the
 * error/success code generated by it.
 ********************************************************/
int main( int argc, const char *argv[] ) {
    printf( "digraph funcgraph {\n" );
    int res = yyparse();
    printf( "}\n" );

    return res;
}
