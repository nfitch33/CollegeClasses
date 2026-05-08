all: cmos scanner

scanner: lex.yy.c
	gcc lex.yy.c -lfl -o scanner

cmos: cmos.cpp
	g++ cmos.cpp -o cmos

lex.yy.c: cmos.l
	flex cmos.l

clean:
	rm -f lex.yy.c cmos scanner scanner_out.txt tokens.txt PlagarismReport.txt