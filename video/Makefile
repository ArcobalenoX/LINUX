CAMERA = camera.out 
RECV = recv.out
MAIN = main.out
SRC = lcd.c yuyv.c touch.c main.c recv.c
OBJ = $(SRC:%.c=%.o)

VPATH = ./
CFLAGS += -I /home/rokudou/jpeglib/include  -L/home/rokudou/jpeglib/lib -ljpeg -pthread

CC = arm-linux-gcc

$(CAMERA) : lcd.o yuyv.o touch.o
	$(CC) -o $@ $^ $(CFLAGS)


RECV : recv.o yuyv.o lcd.o
	$(CC) -o $@ $^ $(CFLAGS)
	
MAIN : main.o 
	$(CC) -o $@ $^ $(CFLAGS)
	
%.o : %.c
	$(CC) -c $^ $(CFLAGS)


.PHONY:clean

clean:
	-rm $(OBJ) $(IMAGE)



