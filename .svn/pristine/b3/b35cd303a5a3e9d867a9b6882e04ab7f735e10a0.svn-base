all		:	myml
y.tab.h y.tab.c :	src/myml.y
			bison -y  -d -v  src/myml.y
lex.yy.c	:	src/myml.l y.tab.h
			flex src/myml.l
myml		:	lex.yy.c y.tab.c src/Table_des_symboles.c src/Table_des_chaines.c src/Attribut.c
			gcc -o myml lex.yy.c y.tab.c src/Table_des_symboles.c src/Table_des_chaines.c src/Attribut.c
clean		:
			rm -f 	lex.yy.c *.o y.tab.h y.tab.c myml *~ y.output executable a.out test.c test.h
