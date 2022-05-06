SRC += main.c slist.c http.c
OBJ = $(SRC:%.c=%.o)
IMAGE = main
CFLAG =  -pthread
VPATH += :./ 

$(IMAGE): $(OBJ)
	gcc $^ -o $@  $(CFLAG)	
%.o:%.c
	gcc -c $^ $(CFLAG)	

clean:
	rm *.o $(IMAGE) 

.PHONY:clean
