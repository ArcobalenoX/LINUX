IMAGE = yingyin.out 
SRC = jpeg_show.c touch.c yingyin.c
OBJ = $(SRC:%.c=%.o)

VPATH = .
CFLAGS += -I /home/rokudou/jpeglib/include -L /home/rokudou/jpeglib/lib -ljpeg

CC = arm-linux-gcc

$(IMAGE):$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)


.PHONY:clean

clean:
	rm $(OBJ) $(IMAGE)



