/*
 *  Attribut.h
 *
 *  Module for handling attributes
 *
 */

#ifndef ATTRIBUT_H
#define ATTRIBUT_H
#include "Table_des_chaines.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE* test_c;
extern FILE* test_h;

enum {true, false} bool;

typedef union {int vali; float valf;char* valb; char* vals;} symb_value;

typedef enum {Int,Float,Bool,String} symb_type;

typedef struct{
  symb_value value;
  symb_type type;
  symb_type type_let;
  char* id;
  int reg;
}symb_value_type;

typedef struct{
  symb_value_type new_let_e;
  char* id;
} aff_value;


void print_aff(aff_value affect);
symb_value_type plus_svt(symb_value_type x, symb_value_type y);
symb_value_type mult_svt(symb_value_type x, symb_value_type y);
symb_value_type minus_svt(symb_value_type x, symb_value_type y);
symb_value_type div_svt(symb_value_type x, symb_value_type y);
symb_value_type concat_svt(symb_value_type x, symb_value_type y);
symb_value_type neg_svt(symb_value_type x);
symb_value_type or_svt(symb_value_type x, symb_value_type y);
symb_value_type and_svt(symb_value_type x, symb_value_type y);
symb_value_type not_svt(symb_value_type x);
symb_value_type is_lt_svt(symb_value_type x, symb_value_type y);
symb_value_type is_gt_svt(symb_value_type x, symb_value_type y);
symb_value_type is_leq_svt(symb_value_type x, symb_value_type y);
symb_value_type is_geq_svt(symb_value_type x, symb_value_type y);
symb_value_type is_eq_svt(symb_value_type x, symb_value_type y);
void new_rg(sid i, symb_value_type e);
symb_value_type convert_val(symb_value_type bool, symb_value_type y, symb_value_type x);
#endif
