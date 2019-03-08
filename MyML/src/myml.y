
%code requires {
#include "src/Attribut.h"
  #include "src/Table_des_symboles.h"
  #include "src/Attribut.h"
}

%{
#include <stdio.h>
#include <string.h>

FILE * test_c = NULL;
FILE * test_h = NULL;
FILE * t_main = NULL;

int i =1;

int new_reg(){
  return i++;
}

int new_line(){
   static int l = 1;
   return l++;
 }

extern int yylex();
extern int yyparse();

void yyerror (char* s) {
   printf("\n%s!\n",s);
 }

%}

%union {
  symb_value_type val;
  char * sid;
  aff_value aff;
}



%token <val> NUM
%token <val> FLOAT

%token  <sid> ID
%token  <val> STRING

%token PV LPAR RPAR LBR RBR LET IN VIR

%token IF THEN ELSE

%token <val> ISLT ISGT ISLEQ ISGEQ ISEQ
%left ISEQ
%left ISLT ISGT ISLEQ ISGEQ


%token AND OR NOT
%token <val> BOOL
%left OR
%left AND



%token PLUS MOINS MULT DIV EQ
%left PLUS
%left MULT
%left CONCAT
%nonassoc UNA    /* pseudo token pour assurer une priorite locale */

 //%type <val> inst
%type <aff> aff
%type <val> exp
%type <aff> aff_id
 //%type <val> aff_fun
 //%type <val> fun_head
%type <val> arith_exp
%type <sid> id_list
%type <val> atom_exp
%type <val> control_exp
%type <val> let_exp
%type <sid>  funcall_exp

%type <val> list_exp
%type <val> exp_list
%type <val> bool

%type <val> atom_list
%start prog



%%

prog : inst PV
| prog inst PV
;


inst : aff
| exp
;

aff : aff_id {$$ = $1;}
| aff_fun
;

aff_id : ID EQ exp
{  set_symbol_value2(sid_to_string($1), $3);  new_rg($1, $3);}
;

aff_fun : fun_head EQ exp
;

fun_head : ID id_list
;

id_list : ID
| id_list ID
;


exp : arith_exp {$$=$1;}
| atom_exp {$$=$1;}
| control_exp {$$=$1;}
| bool { $$ = $1;}
| let_exp  {$$=$1;}
| LPAR funcall_exp RPAR
;

 arith_exp : MOINS exp %prec UNA {$$=neg_svt($2);}
| exp PLUS exp {$$=plus_svt($1,$3);}
| exp MULT exp  {$$=mult_svt($1,$3);}
| exp MOINS exp  {$$=minus_svt($1,$3);}
| exp DIV exp  {$$=div_svt($1,$3);}
| exp CONCAT exp {$$=concat_svt($1, $3);}
;

atom_exp : NUM {$$=$1; $$.reg= new_reg(); fprintf(test_h, " int r%d;\n", $$.reg); fprintf(test_c, "r%d = %d;\n", $$.reg, $$.value.vali);}
| FLOAT {$$=$1; $$.reg= new_reg(); fprintf(test_h, " float r%d;\n", $$.reg); fprintf(test_c, "r%d = %f;\n", $$.reg, $$.value.valf);}
|STRING { $$=$1;$$.reg= new_reg(); fprintf(test_h, " char* r%d;\n", $$.reg); fprintf(test_c, "r%d = %s;\n", $$.reg, $$.value.vals);}
   //| BOOL { $$=$1;$$.reg= new_reg();}
| ID { $$= get_symbol_value($1);}
//| list_exp
| LPAR exp RPAR {$$=$2;}
;

 control_exp : IF bool THEN atom_exp ELSE atom_exp {
  if (!strcmp($2.value.valb,"true")) {
    $$ = convert_val($2,$4, $6);
      }
  else {
    $$ = convert_val($2,$6, $4);
  };
 }
;

let_exp : LET aff IN atom_exp {del_symbol_value(string_to_sid($2.id));$$=$4;}

;
funcall_exp : ID atom_list
;

atom_list : atom_exp {$$=$1;}
| atom_list atom_exp
;

list_exp : LBR exp_list RBR {$$=$2;}
;

exp_list : exp {$$=$1;}
| exp_list VIR exp
;


bool : BOOL {$$=$1; }
| bool OR bool {$$ = or_svt($1, $3);}
| bool AND bool {$$ = and_svt($1, $3);}
| NOT bool %prec UNA{$$ = not_svt($2);}
|exp ISLT exp {$$ = is_lt_svt($1, $3);}
|exp ISGT exp {$$ = is_gt_svt($1, $3);}
|exp ISLEQ exp {$$ = is_leq_svt($1, $3);}
|exp ISGEQ exp {$$ = is_geq_svt($1, $3);}
|exp ISEQ exp {$$ = is_eq_svt($1,$3);}
| LPAR bool RPAR {$$=$2;}
;



comp :  ISLT | ISGT | ISLEQ | ISGEQ | ISEQ
;

%%
int main () {
  printf ("? ");
  test_c = fopen("test.c", "a");
  test_h = fopen("test.h", "a");
  fprintf(test_h, "%s\n", "#include <stdio.h>");
  fprintf(test_h, "%s\n", "#include <stdlib.h>");
  fprintf(test_h, "%s\n", "#include <stdbool.h>");
  fprintf(test_c, "%s\n", "#include \"test.h\"");
  fprintf(test_c, "\n", "");
  fprintf(test_c, "%s\n","int main(int argc,char*argv[]){");
  fprintf(test_c, "\n", "");

  yyparse ();
  fprintf(test_c, "%s\n","return 0;");
  fprintf(test_c, "%s\n","}");
  fclose(test_c);

  fclose(test_h);

  return 1;
}
