all:
	bison -d -v tree_builder.y
	flex tree_builder.l
	g++ tree_builder.tab.c lex.yy.c -o treebuilder -std=c++17 -lfl

clean:
	rm -f treebuilder lex.yy.c tree_builder.tab.c tree_builder.tab.h tree_builder.output