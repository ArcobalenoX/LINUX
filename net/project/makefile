ALL=server client
SRC= server.c client.c 
OBJ =$(SRC:%.c=%.o)

CFLAG= -pthread

.PHONY:clean server client
server:
	gcc server.c -o server $(CFLAG)
client:
	gcc client.c -o client $(CFLAG)
clean:
	-rm $(ALL) $(OBJ)