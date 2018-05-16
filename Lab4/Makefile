lexer: lex.yy.c
	gcc lex.yy.c -g -o lexer

lex.yy.c: lexer.l
	lex lexer.l

clean:
	$(RM) *.o
	$(RM) *.yy.c *.l~
	$(RM) *.tex *.log *.aux *.out
	$(RM) lexer

