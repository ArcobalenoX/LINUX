IMAGE = jpeg_show.out
SRC = jpeg_show.c
OBJ = $(SRC:%.c=%.o)
VPATH = ./
CFLAG = -I /home/rokudou/jpeglib/include -L /home/rokudou/jpeglib/lib -ljpeg

CC = arm-linux-gcc
	
IAMGE:$(OBJ)
	$(CC) $^ -o $@  $(CFLAG)


%.o : %.c
	$(CC) $^ -c  $(CFLAG)

.PHONY:clean
clean:
	rm $(OBJ) $(IMAGE)



