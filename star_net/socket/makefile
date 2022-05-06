
.PHONY:clean server client

SRC= server.c client.c
OBJ =$(SRC:%.c=%.o)

CFLAG= -I ./ -pthread

%.o:%.c
	gcc -c $^ $(CFLAG)
server:
	gcc  server.c -o server $(CFLAG)
	
client:
	gcc  client.c -o client $(CFLAG)

	

	

clean:
	-rm  $(OBJ)
	
	
	
	