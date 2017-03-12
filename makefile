$(shell mkdir -p bin)


FINAL_PROJECT: bin/assembler.o bin/converter.o bin/errorHandler.o bin/secondRun.o bin/cmdTable.o bin/dataTable.o bin/firstRun.o bin/saveFiles.o bin/symbolTable.o bin/main.o
	gcc  -o "FINAL_PROJECT"  ./bin/assembler.o ./bin/cmdTable.o ./bin/converter.o ./bin/dataTable.o ./bin/errorHandler.o ./bin/firstRun.o ./bin/main.o ./bin/saveFiles.o ./bin/secondRun.o ./bin/symbolTable.o  -lm

bin/assembler.o: src/assembler.c src/errorHandler.h src/assembler.h
	gcc -ansi -pedantic -Wall -c src/assembler.c -o bin/assembler.o
	
bin/converter.o: src/converter.c src/converter.h
	gcc -ansi -pedantic -Wall -c src/converter.c -o bin/converter.o -lm

bin/errorHandler.o: src/errorHandler.c src/errorHandler.h src/constants.h
	gcc -ansi -pedantic -Wall -c src/errorHandler.c -o bin/errorHandler.o

bin/secondRun.o: src/secondRun.c src/assembler.h src/dataTable.h src/cmdTable.h src/symbolTable.h src/errorHandler.h
	gcc -ansi -pedantic -Wall -c src/secondRun.c -lm -o bin/secondRun.o

bin/cmdTable.o: src/cmdTable.c src/converter.h src/cmdTable.h
	gcc -ansi -pedantic -Wall -c src/cmdTable.c -o bin/cmdTable.o

bin/dataTable.o: src/dataTable.c src/dataTable.h src/constants.h src/converter.h
	gcc -ansi -pedantic -Wall -c src/dataTable.c -lm -o bin/dataTable.o

bin/firstRun.o: src/firstRun.c src/assembler.h src/dataTable.h src/cmdTable.h src/symbolTable.h
	gcc -ansi -pedantic -Wall -c src/firstRun.c -o bin/firstRun.o

bin/saveFiles.o: src/saveFiles.c src/cmdTable.h src/dataTable.h src/assembler.h src/converter.h src/symbolStructs.h
	gcc -ansi -pedantic -Wall -c src/saveFiles.c -o bin/saveFiles.o

bin/symbolTable.o: src/symbolTable.c src/assembler.h src/symbolTable.h src/symbolStructs.h
	gcc -ansi -pedantic -Wall -c src/symbolTable.c -o bin/symbolTable.o

	

bin/main.o: src/main.c src/assembler.h src/symbolTable.h src/cmdTable.h src/dataTable.h src/saveFiles.h
	gcc -ansi -pedantic -Wall -c src/main.c -o bin/main.o

clean:
	rm -r bin
	rm FINAL_PROJECT
