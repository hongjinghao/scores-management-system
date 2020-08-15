CC=gcc
STD=-std=gnu99
BIN=go
FLAG=-Wall -Werror #-DDEBUG
OBJ=main.o adim.o teacher.o student.o tools.o 

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)
	
main.o:main.c gradef.h
	$(CC) $(STD) $(FLAG) -c main.c
adim.o:adim.h adim.c tools.h list.h
	$(CC) $(STD) $(FLAG) -c adim.c 
student.o:student.h student.c tools.h 
	$(CC) $(STD) $(FLAG) -c student.c
teacher.o:teacher.c teacher.h tools.h 
	$(CC) $(STD) $(FLAG) -c teacher.c
tools.o:tools.c tools.h dingyi.h 
	$(CC) $(STD) $(FLAG) -c tools.c


clean:
	rm -rf $(BIN) $(OBJ)
