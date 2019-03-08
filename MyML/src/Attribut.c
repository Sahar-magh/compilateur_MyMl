
#include "Attribut.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


void new_rg(sid i, symb_value_type e) {
  char *id = sid_to_string(i);
  if (sid_valid(i)) {
    switch(e.type) {
    case Int:
      fprintf(test_h, "%s", "int ");
      fprintf(test_h, "%si;\n", id);
      fprintf(test_c, "%si = ", id);
      fprintf(test_c, "%d;\n", e.value.vali);
      fprintf(test_c, "printf(\"%s de type <int> vaut %d\\n\");\n",id,e.value.vali);
      fprintf(test_c, "ri%d = ", e.reg);
      fprintf(test_c, "%si;", id);
      fprintf(test_h, "%s", "int ");
      fprintf(test_h, "ri%d;\n", e.reg);
      fprintf(test_c, "\n\n");
      break;
    case Float:
      fprintf(test_h, "%s", "float ");
      fprintf(test_h, "%sf;\n", id);
      fprintf(test_c, "%sf = ", id);
      fprintf(test_c, "%f;\n", e.value.valf);
      fprintf(test_c, "printf(\"%s de type <float> vaut %f\\n\");\n",id,e.value.valf);
      fprintf(test_c, "rf%d = ", e.reg);
      fprintf(test_c, "%sf;", id);
      fprintf(test_h, "%s", "float ");
      fprintf(test_h, "rf%d;\n", e.reg);
      fprintf(test_c, "\n\n");
      break;
    case String:
      fprintf(test_h, "%s", "char*");
      fprintf(test_h, "%sc;\n", id);
      fprintf(test_c, "%sc = ", id);
      fprintf(test_c, "%s;\n", e.value.vals);
      fprintf(test_c, "printf(\"%s de type <int> vaut %s\\n\");\n",id,e.value.vals);
      fprintf(test_c, "rc%d = ", e.reg);
      fprintf(test_c, "%sc;", id);
      fprintf(test_h, "%s", "char* ");
      fprintf(test_h, "rc%d;\n", e.reg);
      fprintf(test_c, "\n\n");
      break;
    case Bool:
      fprintf(test_h, "%s", "bool");
      fprintf(test_h, "%sb;\n", id);
      fprintf(test_c, "%sb = ", id);
      fprintf(test_c, "%s;\n", e.value.valb);
      fprintf(test_c, "printf(\"%s de type <Bool> vaut %s\\n\");\n",id,e.value.valb);
      fprintf(test_c, "rb%d = ", e.reg);
      fprintf(test_c, "%sb;", id);
      fprintf(test_h, "%s", "char* ");
      fprintf(test_h, "rb%d;\n", e.reg);
      fprintf(test_c, "\n\n");
      break;
    }
  }
}

void print_aff(aff_value affect){
  switch(affect.new_let_e.type) {
  case Int:
    fprintf(test_c, "printf(\"%s de type <int> vaut %d\\n\");\n", affect.id, affect.new_let_e.value.vali);
    break;
  case Float:
    fprintf(test_c, "printf(\"%s de type <float> vaut %f\\n\");\n", affect.id, affect.new_let_e.value.valf);
    break;
  case String:
    fprintf(test_c, "printf(\"%s de type <string> vaut %s\\n\");\n", affect.id, affect.new_let_e.value.vals);
    break;
  case Bool:
    fprintf(test_c, "printf(\"%s de type <bool> vaut %s\\n\");\n", affect.id, affect.new_let_e.value.valb);
    break;
  }
}

void print_exp(symb_value_type x) {
  switch(x.type) {
  case Int:
    fprintf(test_c, "printf(\"<exp> de type <int> vaut %d\\n\");\n",x.value.vali);
    break;
  case Float:
    fprintf(test_c, "printf(\"<exp> de type <float> vaut %f\\n\");\n",x.value.valf);
    break;
  case String:
    fprintf(test_c, "printf(\"<exp> de type <string> vaut %s\\n\");\n",x.value.vals);
    break;
  case Bool:
    fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",x.value.valb);
    break;
  }
}

symb_value_type neg_svt(symb_value_type x){
  symb_value_type result = x;
  switch(x.type){
  case Int:
    result.value.vali = result.value.vali * -1;
    fprintf(test_c,"r%d = ", result.reg);
    fprintf(test_c,"-r%d ", x.reg);
    break;
  case Float:
    result.value.vali = result.value.valf * -1;
    fprintf(test_c,"r%d = ", result.reg);
    fprintf(test_c,"-r%d ", x.reg);
    break;
  }
  print_exp(result);
}

symb_value_type plus_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.reg = new_reg();
  switch (x.type)
    {
    case Int:
      switch (y.type)
	{
	case Int:
	  // Int + Int
	  result.value.vali = x.value.vali + y.value.vali;
	  result.type = Int;
	  fprintf(test_h,"int r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d + ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	case Float:
	  // Int + Float
	  result.value.valf = x.value.vali + y.value.valf;
	  result.type = Float;
	  fprintf(test_h,"float r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d + ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	}
      break;
    case Float:
      switch (y.type) {
      case Int:
	// Float + Int
	result.value.valf = x.value.valf + y.value.vali;
	result.type = Float;
	fprintf(test_h,"int r%d;\n", result.reg);
	fprintf(test_h,"int r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d + ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      case Float:
	// Float + Float
	result.value.valf = x.value.valf + y.value.valf;
	result.type = Float;
	fprintf(test_h,"int r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d + ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      }
      break;
    }
  return result;
}

symb_value_type mult_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.reg = new_reg();
  switch (x.type)
    {
    case Int:
      switch (y.type)
	{
	case Int:
	  // Int * Int
	  result.value.vali = x.value.vali * y.value.vali;
	  result.type = Int;
	  fprintf(test_h,"int r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d * ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	case Float:
	  // Int * Float
	  result.value.valf = x.value.vali * y.value.valf;
	  result.type = Float;
	  fprintf(test_h,"float r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d * ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	}
    case Float:
      switch (y.type) {
      case Int:
	// Float * Int
	result.value.valf = x.value.valf * y.value.vali;
	result.type = Float;
	fprintf(test_h,"float r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d * ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      case Float:
	// Float * Float
	result.value.valf = x.value.valf * y.value.valf;
	result.type = Float;
	fprintf(test_h,"float r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d * ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      }
    }
  return result;
}

symb_value_type minus_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.reg = new_reg();
  switch (x.type)
    {
    case Int:
      switch (y.type)
	{
	case Int:
	  // Int - Int
	  result.value.vali = x.value.vali - y.value.vali;
	  result.type = Int;
	  fprintf(test_h,"int r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d - ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	case Float:
	  // Int - Float
	  result.value.valf = x.value.vali - y.value.valf;
	  result.type = Float;
	  fprintf(test_h,"float r%d;\n", result.reg);
	  fprintf(test_c,"r%d = ", result.reg);
	  fprintf(test_c,"r%d - ", x.reg);
	  fprintf(test_c,"r%d;\n", y.reg);
	  print_exp(result);
	  break;
	}

    case Float:
      switch (y.type) {
      case Int:
	// Float - Int
	result.value.valf = x.value.valf - y.value.vali;
	result.type = Float;
	fprintf(test_h,"float r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d - ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      case Float:
	// Float - Float
	result.value.valf = x.value.valf - y.value.valf;
	result.type = Float;
	fprintf(test_h,"float r%d;\n", result.reg);
	fprintf(test_c,"r%d = ", result.reg);
	fprintf(test_c,"r%d - ", x.reg);
	fprintf(test_c,"r%d;\n", y.reg);
	print_exp(result);
	break;
      }
    }
  return result;
}

symb_value_type div_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.reg = new_reg();
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      // int / int
      if ( y.value.vali == 0 ) {
	perror("Attention!! Division par zero!!");
	exit(-1);
      }
      result.type = Int;
      result.value.vali = x.value.vali / y.value.vali;
      fprintf(test_h,"int r%d;\n", result.reg);
      fprintf(test_c,"r%d = ", result.reg);
      fprintf(test_c,"r%d / ", x.reg);
      fprintf(test_c,"r%d;\n", y.reg);
      print_exp(result);
      break;
    case Float:
      // int / float
      if ( y.value.valf < pow(10, -10)) {
	perror("Attention!! Division par zero!!");
	exit(-1);
      }
      result.type = Float;
      result.value.valf = (float)x.value.vali / y.value.valf;
      fprintf(test_h,"float r%d;\n", result.reg);
      fprintf(test_c,"r%d = ", result.reg);
      fprintf(test_c,"r%d - ", x.reg);
      fprintf(test_c,"r%d;\n", y.reg);
      print_exp(result);
      break;
    }
  case Float:
    switch(y.type) {
    case Int:
      // float / int
      if ( y.value.vali == 0 ) {
	perror("Attention!! Division par zero!!");
	exit(-1);
      }
      result.type = Float;
      result.value.valf = x.value.valf / (float)y.value.vali;
      fprintf(test_c,"r%d = ", result.reg);
      fprintf(test_c,"r%d - ", x.reg);
      fprintf(test_c,"r%d;\n", y.reg);
      print_exp(result);
      break;
    case Float:
      // float / float
      if ( y.value.valf < pow(10, -10)) {
	perror("Attention!! Division par zero!!");
	exit(-1);
      }
      result.type = Float;
      result.value.valf = x.value.valf / y.value.valf;
      fprintf(test_h,"float r%d;\n", result.reg);
      fprintf(test_c,"r%d = ", result.reg);
      fprintf(test_c,"r%d - ", x.reg);
      fprintf(test_c,"r%d;\n", y.reg);
      print_exp(result);
      break;
    }
  }
  return result;
}

char *str_sub (const char *s, unsigned int start, unsigned int end){
  char *new_s = NULL;
  if (s != NULL && start < end)  {
    new_s = malloc (sizeof (*new_s) * (end - start + 2));
    if (new_s != NULL){
      int i;
      for (i = start; i <= end; i++) {
	new_s[i-start] = s[i];
      }
      new_s[i-start] = '\0';
    }
    else{
      fprintf (stderr, "Memoire insuffisante\n");
      exit (EXIT_FAILURE);
    }
  }
  return new_s;
}

symb_value_type concat_svt(symb_value_type x, symb_value_type y){
  symb_value_type result;
  result.reg = new_reg();
  result.type = String;
  strcpy(result.value.vals, str_sub(x.value.vals, 0, strlen(x.value.vals)-2));
  strcat(result.value.vals, str_sub(y.value.vals, 1, strlen(y.value.vals)-1));
  print_exp(result);
  return result;
}

symb_value_type or_svt(symb_value_type x, symb_value_type y){
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = r%d || r%d);\n", result.reg, x.reg, y.reg);
  if (x.value.valb == "true" || y.value.valb == "true" )
    result.value.valb = "true";
  else
    result.value.valb = "false";
  printf("<exp> de type <Bool> vaut %s\n",result.value.valb);
  return result;
}

symb_value_type and_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = r%d && r%d);\n", result.reg, x.reg, y.reg);
  if ( x.value.valb == "true" && y.value.valb == "true") {
    result.value.valb = "true";
    return result;
  }
  result.value.valb = "false";
  printf("<exp> de type <Bool> vaut %s\n",result.value.valb);
  return result;
}

symb_value_type not_svt(symb_value_type x) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (!r%d);\n", result.reg, x.reg);
  if (x.value.valb == "true"){
    result.value.valb = "false";
    return result;
  }
  result.value.valb = "false";
  fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}

symb_value_type is_lt_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (r%d < r%d);\n", result.reg, x.reg, y.reg);
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.vali < y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.vali < y.value.valf)? "true" : "false";
      break;
    }
    break;
  case Float:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.valf < y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.valf < y.value.valf)? "true" : "false";
      break;
    }
    break;
  }
  fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}

symb_value_type is_gt_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (r%d > r%d);\n", result.reg, x.reg, y.reg);
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.vali > y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.vali > y.value.valf)? "true" : "false";
      break;
    }
    break;
  case Float:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.valf >y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.valf > y.value.valf)? "true" : "false";
      break;
    }
    break;
  }
 fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}

symb_value_type is_leq_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (r%d =< r%d);\n", result.reg, x.reg, y.reg);
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.vali <= y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.vali <= y.value.valf)? "true" : "false";
      break;
    }
    break;
  case Float:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.valf <= y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.valf <= y.value.valf)? "true" : "false";
      break;
    }
    break;
  }
  fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}


symb_value_type is_geq_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (r%d >= r%d);\n", result.reg, x.reg, y.reg);
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.vali >= y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.vali >= y.value.valf)? "true" : "false";
      break;
    }
    break;
  case Float:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.valf >= y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.valf >= y.value.valf)? "true" : "false";
      break;
    }
    break;
  }
  fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}

symb_value_type is_eq_svt(symb_value_type x, symb_value_type y) {
  symb_value_type result;
  result.type = Bool;
  result.reg = new_reg();
  fprintf(test_h, "bool r%d;", result.reg);
  fprintf(test_c ,"r%d = (r%d == r%d);\n", result.reg, x.reg, y.reg);
  switch(x.type) {
  case Int:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.vali == y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.vali == y.value.valf)? "true" : "false";
      break;
    }
    break;
  case Float:
    switch(y.type) {
    case Int:
      result.value.valb = (x.value.valf == y.value.vali)? "true" : "false";
      break;
    case Float:
      result.value.valb = (x.value.valf == y.value.valf)? "true" : "false";
      break;
    }
    break;
  }
  fprintf(test_c, "printf(\"<exp> de type <bool> vaut %s\\n\");\n",result.value.valb);
  return result;
}

symb_value_type convert_val(symb_value_type b, symb_value_type y, symb_value_type x){
  symb_value_type res;
  int l = new_line();
  fprintf(test_c, "if ( r%d ) ", b.reg );
  fprintf(test_c, "goto l%d;\n",l);
  int l2 = new_line();
  fprintf(test_c, "goto l%d;\n", l2);
  switch(y.type){
  case Int:
    switch(x.type){
    case Int:
      res.reg = new_reg();
      res.type = Int;
      res.value.vali = y.value.vali;
      fprintf(test_h, "int r%d;\n", res.reg);
      fprintf(test_c, "l%d : r%d = %d;\n", l, res.reg, res.value.vali);
      fprintf(test_c, "l%d : r%d = %d;\n", l2, res.reg,x.value.vali);
      break;
    case Float:
      res.reg = new_reg();
      res.type = Float;
      res.value.valf = (float) y.value.vali;
      fprintf(test_h, "float r%d;\n", res.reg);
      fprintf(test_c, "l%d : r%d = %f;\n", l, res.reg, res.value.valf);
      fprintf(test_c, "l%d : r%d = %f;\n", l2, res.reg, x.value.valf);
      break;
    }
    break;
  case Float:
    switch(x.type){
    case Int:
      res.reg = new_reg();
      res.type = Float;
      res.value.valf = (float) y.value.vali;
      fprintf(test_h, "float r%d;\n", res.reg);
      fprintf(test_c, "l%d : r%d = %f;\n", l, res.reg, res.value.valf);
      fprintf(test_c, "l%d : r%d = %d;\n", l2, res.reg, x.value.vali);
      break;
    case Float:
      res.reg = new_reg();
      res.type = Float;
      res.value.valf = (float) y.value.vali;
      fprintf(test_h, "float r%d;\n", res.reg);
      fprintf(test_c, "l%d : r%d = %f;\n", l, res.reg, res.value.valf);
      fprintf(test_c, "l%d : r%d = %f;\n", l2, res.reg, x.value.valf);
      break;
    }
    break;
  }
  return res;
}