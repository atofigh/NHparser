OBJFILES = NHparser.o NHgrammar.y.o NH.lex.o NHerror.o
COMPFLAGS = -g -pedantic -std=c99


NHtester: $(OBJFILES) NHtester.c
	gcc $(COMPFLAGS) -o NHtester $^

lib: $(OBJFILES)
	ar rcs libNHparser.a $(OBJFILES)

NHparser.o: NHparser.c NHparser.h
	gcc $(COMPFLAGS) -c $<

NHgrammar.y.o: NHgrammar.y.c NHgrammar.y.h
	gcc $(COMPFLAGS) -DYYDEBUG -c $<

NHerror.o: NHerror.c NHerror.h
	gcc $(COMPFLAGS) -c $<

NHgrammar.y.c: NHgrammar.y
	bison -d -o $@ $<

NHgrammar.y.h: NHgrammar.y
	bison -d -o NHgrammar.y.c $<

NH.lex.c: NH.lex
	flex -o$@ $<

NH.lex.o: NH.lex.c
	gcc $(COMPFLAGS) -c $<

clean:
	@rm -f *~ NHgrammar.y.c NHgrammar.y.h NHgrammar.y.output NH.lex.c $(OBJFILES) libNHparser.a NHtester
