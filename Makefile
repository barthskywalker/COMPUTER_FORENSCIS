
################################################
# Makefile for Computer Forensics Project      #
# StudentName&ID: Barth O'Keeffe    14180847   #
#                 Mark O’Neill      14117711   #
#                 Lina Albay        14118432   #
# Lecturer:       Dr. Jacqueline Walker        #
# Date  16/02/2018                             #
################################################

HEADER  = Scanner.h

#command to link objects and create excutable
Scanner: ScannerMain.o functions.o Scanner_part1b.o Scanner_part1c.o
	gcc -o Scanner ScannerMain.o functions.o Scanner_part1b.o Scanner_part1c.o
	make clean

#compile additional source files into object file
##### Add Here !!!!
#compile functions.c files
functions.o: functions.c
	gcc -Wall -ggdb -c functions.c

#compile Scanner_part1b.c file
Scanner_part1b.o: Scanner_part1b.c
	gcc -Wall -ggdb -c Scanner_part1b.c

#compile Scanner_part1c.c file
Scanner_part1c.o: Scanner_part1c.c
	gcc -Wall -ggdb -c Scanner_part1c.c

# compile main application file
ScannerMain.o: ScannerMain.c
	gcc -Wall -ggdb -c ScannerMain.c

# clean up - handy to enforce recompilationls
clean:
	rm -f *.o #
