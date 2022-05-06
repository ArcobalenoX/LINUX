SRC= a.c b.c main.c
OBJ =$(SRC:%.c=%.o)
VPATH = ./:./source
vpath %.c ./source
vpath %.h ./include
#include ./source/src.mk
IMAGE= main
CFLAG= -I ./include

$(IMAGE):$(OBJ)
	# gcc -o main $(OBJ)
	gcc $^ -o $@

%.o:%.c
	gcc -c $^ $(CFLAG)
	
# main.o:head.h
	# gcc -MM main.c	
	# gcc -c $@
	# @ls
	# ls -l
	
# a.o:head.h a.c
	# @gcc -c a.c 
# b.o:head.h b.c
	# @gcc b.c -c -o b.o
	
	



.PHONY:clean all 
all:
	@#echo $(MAKEFLAGS)
	@echo make  pass
clean:
	-rm main $(OBJ)
	
	
	
	